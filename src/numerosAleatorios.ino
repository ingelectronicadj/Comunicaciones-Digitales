/*
 ***********************************************************************
 *              LIBRERIAS y CONSTANTES
 ***********************************************************************
 */
// Docs: http://www.pjrc.com/teensy/td_libs_TimerOne.html
#include <TimerOne.h>

const byte pinOutSenalDigital = 13; // Pin de Salida de Senal
const byte pinOutClk1 = 12;         // pin clock triada
const int ts = 200;                 // tiempo en millis
const long deltaT = 180000;         // microsegundos 180000us 180ms
// Constantes tipo byte va de 0 a 255, es suficiente para representar los pines

const byte ledPin = 53;           // Indicador de interrupcion, led de salida
const byte pinInClk1 = 2;         // Pin de entrada de la interrupcion
const byte pinInSenalDigital = 4; // Pin de entrada de la senal digital

bool estadoClk1 = LOW; // Estado inicial de clk1

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
  // pinMode(pinX, OUTPUT);               // Salida de tension sobre el eje X
  // pinMode(pinY, OUTPUT);               // "               " sobre el eje Y
  // pinMode(pinmenosX, OUTPUT);          // Salida de tension sobre el eje -X
  // pinMode(pinmenosY, OUTPUT);          // "               " sobre el eje -Y
  pinMode(ledPin, OUTPUT);
  Timer1.initialize(deltaT); // 180 ms
  Timer1.attachInterrupt(ISR_Callback);
  Timer1.stop();
  attachInterrupt(digitalPinToInterrupt(pinInClk1), clk1Detection, CHANGE);
}

/*
 ***********************************************************************
 *              LOOP BUCLE PRINCIPAL
 ***********************************************************************
 */
void loop() {
  int numeroAleatorio = generadorNumeroAletorio();
  generaSenalAleatoria(numeroAleatorio);
}

int generadorNumeroAletorio() {
  /*Si cargamos un #constante como semilla generamos
     numeros seudo-aeatorios, cargando una semilla cambiante
     generamos numeros aleatorios*/
  randomSeed(analogRead(0));
  int azar = random(0, 8); // genera numero aleatorio desde random(n,(m-1))
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

// void primerCuadrante() {
//   analogWrite(pinX, tensionX);
//   analogWrite(pinY, tensionY);
//   analogWrite(pinmenosX, 0);
//   analogWrite(pinmenosY, 0);
// }
//
// void segundoCuadrante() {
//   analogWrite(pinmenosX, tensionX);
//   analogWrite(pinY, tensionY);
//   analogWrite(pinX, 0);
//   analogWrite(pinmenosY, 0);
// }
//
// void tercerCuadrante() {
//   analogWrite(pinmenosX, tensionX);
//   analogWrite(pinmenosY, tensionY);
//   analogWrite(pinX, 0);
//   analogWrite(pinY, 0);
// }
//
// void cuartoCuadrante() {
//   analogWrite(pinX, tensionX);
//   analogWrite(pinmenosY, tensionY);
//   analogWrite(pinmenosX, 0);
//   analogWrite(pinY, 0);
// }

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

volatile unsigned long tiempo = 0;
void clk1Detection() {
  // Serial.println("Int: ");
  digitalWrite(ledPin, estadoClk1);
  noInterrupts();
  tiempo = millis();
  interrupts();
  Timer1.start();
  // Timer1.detachInterrupt();
  // Timer1.start();
}

int cuenta = 0;
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
