/*
 ***********************************************************************
 *              LIBRERIAS y CONSTANTES
 ***********************************************************************
 */
const byte pinSenalDigital = 5; // Pin de Salida de Senal
const int ts = 1000;            // tiempo en millis
// Constantes tipo byte va de 0 a 255, es suficiente para representar los pines
const byte pinclk1 = 12;     // pin clock triada
const byte ledPin = 13;      // Indicador de interrupcion, led de salida
const byte interruptPin = 2; // Pin de entrada de la interrupcion
int tensionX, tensionY;      // valor analogico de tension
const byte pinX = 11;
const byte pinmenosX = 10;
const byte pinY = 9;
const byte pinmenosY = 8;

bool estado = HIGH; // Estado inicial de clk1

/*
 ***********************************************************************
 *              SETUP CONFIGURACIÓN INICIAL
 ***********************************************************************
 */
void setup() {
  Serial.begin(9600);                  // Tasa de baudios del puerto serial
  pinMode(pinSenalDigital, OUTPUT);    // Señal de pulsos aleatorios
  pinMode(pinclk1, OUTPUT);            // Señal clk1
  pinMode(pinX, OUTPUT);               // Salida de tension sobre el eje X
  pinMode(pinY, OUTPUT);               // "               " sobre el eje Y
  pinMode(pinmenosX, OUTPUT);          // Salida de tension sobre el eje -X
  pinMode(pinmenosY, OUTPUT);          // "               " sobre el eje -Y
  pinMode(interruptPin, INPUT_PULLUP); // Pin como entrada de la interrupcion
  pinMode(ledPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), clk1detection, CHANGE);
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
  randomSeed(millis());
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

void primerCuadrante() {
  analogWrite(pinX, tensionX);
  analogWrite(pinY, tensionY);
  analogWrite(pinmenosX, 0);
  analogWrite(pinmenosY, 0);
}

void segundoCuadrante() {
  analogWrite(pinmenosX, tensionX);
  analogWrite(pinY, tensionY);
  analogWrite(pinX, 0);
  analogWrite(pinmenosY, 0);
}

void tercerCuadrante() {
  analogWrite(pinmenosX, tensionX);
  analogWrite(pinmenosY, tensionY);
  analogWrite(pinX, 0);
  analogWrite(pinY, 0);
}

void cuartoCuadrante() {
  analogWrite(pinX, tensionX);
  analogWrite(pinmenosY, tensionY);
  analogWrite(pinmenosX, 0);
  analogWrite(pinY, 0);
}

void escribirSenalDigital(bool bit1, bool bit2, bool bit3) {
  digitalWrite(pinclk1, estado);
  estado = !estado;
  digitalWrite(pinSenalDigital, bit1);
  delay(ts);
  digitalWrite(pinSenalDigital, bit2);
  delay(ts);
  digitalWrite(pinSenalDigital, bit3);
  delay(ts);
}

void clk1detection() {
  Serial.println("Sex");
  digitalWrite(ledPin, estado);
}
