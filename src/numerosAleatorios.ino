/*
 ***********************************************************************
 *              LIBRERIAS y CONSTANTES
 ***********************************************************************
 */
#include <TimerOne.h>

const byte pinOutSenalDigital = 13; // Pin de Salida de Senal
const int ts = 200;                 // tiempo en millis
const int deltaT = 180000;          // nanosegundos 180ms
// Constantes tipo byte va de 0 a 255, es suficiente para representar los pines
const byte pinOutClk1 = 12; // pin clock triada
const byte ledPin = 53;     // Indicador de interrupcion, led de salida
const byte pinInClk1 = 2;   // Pin de entrada de la interrupcion
// int tensionX, tensionY;      // valor analogico de tension
// const byte pinX = 11;
// const byte pinmenosX = 10;
// const byte pinY = 9;
// const byte pinmenosY = 8;

bool estado = HIGH; // Estado inicial de clk1

/*
 ***********************************************************************
 *              SETUP CONFIGURACIÓN INICIAL
 ***********************************************************************
 */
void setup() {
  Serial.begin(9600);                  // Tasa de baudios del puerto serial
  pinMode(pinOutSenalDigital, OUTPUT); // Señal de pulsos aleatorios
  pinMode(pinOutClk1, OUTPUT);         // Señal clk1
  // pinMode(pinX, OUTPUT);               // Salida de tension sobre el eje X
  // pinMode(pinY, OUTPUT);               // "               " sobre el eje Y
  // pinMode(pinmenosX, OUTPUT);          // Salida de tension sobre el eje -X
  // pinMode(pinmenosY, OUTPUT);          // "               " sobre el eje -Y
  pinMode(pinInClk1, INPUT_PULLUP); // Pin como entrada de la interrupcion
  pinMode(ledPin, OUTPUT);
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
  Serial.println(azar);
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
  Timer1.initialize(deltaT); // 180 ms
  Timer1.attachInterrupt(ISR_Callback);
  digitalWrite(pinOutClk1, estado);
  estado = !estado;
  digitalWrite(pinOutSenalDigital, bit1);
  delay(ts);
  digitalWrite(pinOutSenalDigital, bit2);
  delay(ts);
  digitalWrite(pinOutSenalDigital, bit3);
  delay(ts);
  Timer1.detachInterrupt();
}

void clk1Detection() {
  // Serial.println("Int");
  digitalWrite(ledPin, estado);
}

void ISR_Callback() { // Serial.println("ISR");
}
