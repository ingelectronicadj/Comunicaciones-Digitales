/*
 ***********************************************************************
 *              LIBRERIAS y CONSTANTES
 ***********************************************************************
 */
int pinSenalDigital = 5;
int ts = 1000; // tiempo en millis

int tensionX, tensionY; // valor analogico de tension
int pinX = 11;
int pinmenosX = 10;
int pinY = 9;
int pinmenosY = 8;

/*
 ***********************************************************************
 *              SETUP CONFIGURACIÓN INICIAL
 ***********************************************************************
 */
void setup() {
  Serial.begin(9600);               // Tasa de baudios del puerto serial
  pinMode(pinSenalDigital, OUTPUT); // Señal de pulsos aleatorios
  pinMode(pinX, OUTPUT);            // Salida de tension sobre el eje X
  pinMode(pinY, OUTPUT);            // "               " sobre el eje Y
  pinMode(pinmenosX, OUTPUT);       // Salida de tension sobre el eje -X
  pinMode(pinmenosY, OUTPUT);       // "               " sobre el eje -Y
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
  azar = random(0, 8); // genera numero aleatorio desde random(n,(m-1))
  Serial.println(azar);
  return azar;
}

void generaSenalAleatoria(int azar) {
  switch (azar) {
  case 0: // Si el numero aleatorio es 0 = 000
    escribirSenalDigital(LOW, LOW, LOW);
    break;
  case 1: // Si el numero aleatorio es 1 = 001
    escribirSenalDigital(LOW, LOW, LOW);
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
  analogWrite(X, tensionX);
  analogWrite(Y, tensionY);
  analogWrite(menosX, 0);
  analogWrite(menosY, 0);
}

void segundoCuadrante() {
  analogWrite(menosX, tensionX);
  analogWrite(Y, tensionY);
  analogWrite(X, 0);
  analogWrite(menosY, 0);
}

void tercerCuadrante() {
  analogWrite(menosX, tensionX);
  analogWrite(menosY, tensionY);
  analogWrite(X, 0);
  analogWrite(Y, 0);
}

void cuartoCuadrante() {
  analogWrite(X, tensionX);
  analogWrite(menosY, tensionY);
  analogWrite(menosX, 0);
  analogWrite(Y, 0);
}

void escribirSenalDigital(bool bit1, bool bit2, bool bit3) {
  digitalWrite(pinSenalDigital, bit1);
  delay(ts);
  digitalWrite(pinSenalDigital, bit2);
  delay(ts);
  digitalWrite(pinSenalDigital, bit3);
  delay(ts);
}
