/*
 ***********************************************************************
 *              LIBRERIAS y CONSTANTES
 ***********************************************************************
 */
// Docs: http://www.pjrc.com/teensy/td_libs_TimerOne.html
#include <TimerOne.h>

const byte pinOutSenalDigital = 13; // Pin de Salida de Senal
const byte pinOutClk1 = 12;         // pin clock triada
const int ts = 15;                  // tiempo en millis
const long deltaT = 12500;          // microsegundos 180000us 180ms
// Constantes tipo byte va de 0 a 255, es suficiente para representar los pines

const byte ledPin = 53;           // Indicador de interrupcion, led de salida
const byte pinInClk1 = 2;         // Pin de entrada de la interrupcion
const byte pinInSenalDigital = 3; // Pin de entrada de la senal digital

const byte pinOutClk2 = 46;         // Pin de salida del CLK2
const byte pinInClk2 = 18;          // Pin de entrada de la interrupcion auxiliar para decodificar
const byte pinInSenalAnalogaX = A8; // Pin de entrada de la senal analoga decodificada
const byte pinInSenalAnalogaY = A9; // Pin de entrada de la senal analoga decodificada

bool estadoClk1 = LOW; // Estado inicial de clk1
bool estadoClk2 = LOW; // Estado inicial de clk2

const byte pinX = 11;
const byte pinY = 10;
const byte pinMenosX = 9;
const byte pinMenosY = 8;

const byte pinXmedios = 7;
const byte pinYmedios = 6;
const byte pinMenosXmedios = 5;
const byte pinMenosYmedios = 4;

volatile bool buffer[] = {LOW, LOW, LOW};

/*
 ***********************************************************************
 *              SETUP CONFIGURACIÓN INICIAL
 ***********************************************************************
 */
void setup() {
  Serial.begin(9600);                       // Tasa de baudios del puerto serial
  pinMode(pinInSenalDigital, INPUT_PULLUP); // Entra senal de pulsos
  pinMode(pinOutSenalDigital, OUTPUT);      // Señal de pulsos aleatorios
  pinMode(pinInClk1, INPUT_PULLUP); // Pin como entrada de la interrupcion
  pinMode(pinOutClk1, OUTPUT);      // Señal clk1
  pinMode(pinInClk2, INPUT_PULLUP); // Pin como entrada de la interrupcion
  pinMode(pinOutClk2, OUTPUT);      // Señal clk1
  pinMode(pinX, OUTPUT);            // Salida de tension sobre el eje X
  pinMode(pinY, OUTPUT);            // "               " sobre el eje Y
  pinMode(pinMenosX, OUTPUT);       // Salida de tension sobre el eje menosX
  pinMode(pinMenosY, OUTPUT);       // "               " sobre el eje menosY
  pinMode(pinXmedios, OUTPUT);      // Salida de tension sobre el eje X medios
  pinMode(pinYmedios, OUTPUT);      // "               " sobre el eje Y medios
  pinMode(pinMenosXmedios,
          OUTPUT); // Salida de tension sobre el eje menosXmedios
  pinMode(pinMenosYmedios,
          OUTPUT); // "               " sobre el eje menosYmedios
  pinMode(ledPin, OUTPUT);
  Timer1.initialize(deltaT); // 180 ms
  Timer1.attachInterrupt(ISR_Callback);
  Timer1.stop();
  attachInterrupt(digitalPinToInterrupt(pinInClk1), clk1Detection, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinInClk2), clk2Detection, CHANGE);
}

/*
 ***********************************************************************
 *              LOOP BUCLE PRINCIPAL
 ***********************************************************************
 */
void loop() {
  int numeroAleatorio = generadorNumeroAletorio();
  generaSenalAleatoria(numeroAleatorio);
  codificar();
}

int generadorNumeroAletorio() {
  /*Si cargamos un #constante como semilla generamos
     numeros seudo-aeatorios, cargando una semilla cambiante
     generamos numeros aleatorios*/
  randomSeed(analogRead(0));
  int azar = random(0, 8); // genera numero aleatorio desde random(n,(m-1))
  // azar = 0;
  Serial.println("Azar:" + String(azar));
  return azar;
}

void generaSenalAleatoria(int azar) {
  switch (azar) {
  case 0: // Si el numero aleatorio es 0 = 000
    escribirSenalDigital(LOW, LOW, LOW);
    break;
  case 1: // Si el numero aleatorio es 1 = 001
    escribirSenalDigital(LOW, LOW, HIGH);
    break;
  case 2: // Si el numero aleatorio es 2 = 010
    escribirSenalDigital(LOW, HIGH, LOW);
    break;
  case 3: // Si el numero aleatorio es 3 = 011
    escribirSenalDigital(LOW, HIGH, HIGH);
    break;
  case 4: // Si el numero aleatorio es 4 = 100
    escribirSenalDigital(HIGH, LOW, LOW);
    break;
  case 5: // Si el numero aleatorio es 6 = 101
    escribirSenalDigital(HIGH, LOW, HIGH);
    break;
  case 6: // Si el numero aleatorio es 6 = 110
    escribirSenalDigital(HIGH, HIGH, LOW);
    break;
  default: // Si el numero aleatorio es 7 = 111 (azar == 7)
    escribirSenalDigital(HIGH, HIGH, HIGH);
    break;
  }
}

void escribirSenalDigital(bool bit1, bool bit2, bool bit3) {
  cambiarYEnviarClk1();
  digitalWrite(pinOutSenalDigital, bit1);
  delay(ts);
  digitalWrite(pinOutSenalDigital, bit2);
  delay(ts);
  digitalWrite(pinOutSenalDigital, bit3);
  delay(ts);
}

void cambiarYEnviarClk1() {
  digitalWrite(pinOutClk1, estadoClk1);
  estadoClk1 = !estadoClk1;
}

void clk1Detection() {
  // Serial.println("Int: ");
  digitalWrite(ledPin, estadoClk1);
  // noInterrupts();
  // interrupts();
  Timer1.start();
  // Timer1.detachInterrupt();
  // Timer1.start();
}

volatile byte cuenta = 0;
void ISR_Callback() {
  // Serial.println("Cuenta: " + String(cuenta));
  if (cuenta == 0) {
    cuenta = cuenta + 1;
    return;
  }
  // unsigned long resta = millis() - tiempo;
  // Serial.println("Tiempo: " + String(resta));
  bool senal = digitalRead(pinInSenalDigital);
  Serial.println("ISR: " + String(senal));
  buffer[cuenta - 1] = senal;

  if (cuenta == 3) {
    // Serial.println("llegue");
    // Timer1.detachInterrupt();
    cuenta = 0;
    Timer1.stop();
    Serial.println();
  } else {
    cuenta = cuenta + 1;
  }
}

void codificar() {
  byte valor;
  if (buffer[0] == LOW && buffer[1] == LOW && buffer[2] == LOW) {
    valor = 0;
    // pinX,pinY,pinMenosX,pinMenosY,pinXmedios,pinYmedios,pinMenosXmedios,pinMenosYmedios
    escribirSenalAnaloga(LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH);
  } else if (buffer[0] == LOW && buffer[1] == LOW && buffer[2] == HIGH) {
    valor = 1;
    // pinX,pinY,pinMenosX,pinMenosY,pinXmedios,pinYmedios,pinMenosXmedios,pinMenosYmedios
    escribirSenalAnaloga(LOW, LOW, LOW, LOW, HIGH, LOW, LOW, LOW);
  } else if (buffer[0] == LOW && buffer[1] == HIGH && buffer[2] == LOW) {
    valor = 2;
    // pinX,pinY,pinMenosX,pinMenosY,pinXmedios,pinYmedios,pinMenosXmedios,pinMenosYmedios
    escribirSenalAnaloga(LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW);
  } else if (buffer[0] == LOW && buffer[1] == HIGH && buffer[2] == HIGH) {
    valor = 3;
    // pinX,pinY,pinMenosX,pinMenosY,pinXmedios,pinYmedios,pinMenosXmedios,pinMenosYmedios
    escribirSenalAnaloga(LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW);
  } else if (buffer[0] == HIGH && buffer[1] == LOW && buffer[2] == LOW) {
    valor = 4;
    // pinX,pinY,pinMenosX,pinMenosY,pinXmedios,pinYmedios,pinMenosXmedios,pinMenosYmedios
    escribirSenalAnaloga(HIGH, HIGH, LOW, LOW, LOW, LOW, LOW, LOW);
  } else if (buffer[0] == HIGH && buffer[1] == LOW && buffer[2] == HIGH) {
    valor = 5;
    // pinX,pinY,pinMenosX,pinMenosY,pinXmedios,pinYmedios,pinMenosXmedios,pinMenosYmedios
    escribirSenalAnaloga(LOW, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW);
  } else if (buffer[0] == HIGH && buffer[1] == HIGH && buffer[2] == LOW) {
    valor = 6;
    // pinX,pinY,pinMenosX,pinMenosY,pinXmedios,pinYmedios,pinMenosXmedios,pinMenosYmedios
    escribirSenalAnaloga(LOW, LOW, HIGH, HIGH, LOW, LOW, LOW, LOW);
  } else { // if (buffer[0] == HIGH && buffer[1] == HIGH && buffer[2] == HIGH)
    valor = 7;
    // pinX,pinY,pinMenosX,pinMenosY,pinXmedios,pinYmedios,pinMenosXmedios,pinMenosYmedios
    escribirSenalAnaloga(HIGH, LOW, LOW, HIGH, LOW, LOW, LOW, LOW);
  }
  Serial.println("Valor: " + String(valor) + "\n\n");
}

void escribirSenalAnaloga(bool ejeX, bool ejeY, bool ejeMenosX, bool ejeMenosY,
                          bool ejeXmedios, bool ejeYmedios,
                          bool ejeMenosXmedios, bool ejeMenosYmedios) {
  digitalWrite(pinX, ejeX);
  digitalWrite(pinY, ejeY);
  digitalWrite(pinMenosX, ejeMenosX);
  digitalWrite(pinMenosY, ejeMenosY);
  digitalWrite(pinXmedios, ejeXmedios);
  digitalWrite(pinYmedios, ejeYmedios);
  digitalWrite(pinMenosXmedios, ejeMenosXmedios);
  digitalWrite(pinMenosYmedios, ejeMenosYmedios);
  cambiarYEnviarClk2();
}

void cambiarYEnviarClk2() {
  digitalWrite(pinOutClk2, estadoClk2);
  estadoClk2 = !estadoClk2;
}

void clk2Detection() {
  int x = analogRead(pinInSenalAnalogaX);
  float voltageX = x * (5.0 / 1023.0);
  byte posX = voltajeAPosicion(voltageX);

  int y = analogRead(pinInSenalAnalogaY);
  float voltageY = y * (5.0 / 1023.0);
  byte posY = voltajeAPosicion(voltageY);
  if (posX == 2 && posY == 1) { // 000
    Serial.println("Posicion: 000");
  } else if (posX == 3 && posY == 2) { // 001
    Serial.println("Posicion: 001");
  } else if (posX == 2 && posY == 3) { // 010
    Serial.println("Posicion: 010");
  } else if (posX == 1 && posY == 2) { // 011
    Serial.println("Posicion: 011");
  } else if (posX == 4 && posY == 4) { // 100
    Serial.println("Posicion: 100");
  } else if (posX == 0 && posY == 4) { // 101
    Serial.println("Posicion: 101");
  } else if (posX == 0 && posY == 0) { // 110
    Serial.println("Posicion: 110");
  } else { // (posX == 4 && posY == 0) // 111
    Serial.println("Posicion: 111");
  }
}

byte voltajeAPosicion(float voltaje) {
  byte posicion = 0;
  if (voltaje >= 0 && voltaje < 0.625) { // rango de 0v
    posicion = 0;
  } else if (voltaje >= 0.625 && voltaje < 1.875) { // rango de 1.25v
    posicion = 1;
  } else if (voltaje >= 1.875 && voltaje < 3.125) { // rango de 2.5v
    posicion = 2;
  } else if (voltaje >= 3.125 && voltaje < 4.375) { // rango de 3.75v
    posicion = 3;
  } else { // voltaje >= 4.375 && voltaje < 5 // rango de 5v
    posicion = 4;
  }
  return posicion;
}
