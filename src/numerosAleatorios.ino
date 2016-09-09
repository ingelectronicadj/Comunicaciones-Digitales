/*
 ***********************************************************************
 *              LIBRERIAS y CONSTANTES
 ***********************************************************************
 */
int azar;
int senal = 8;
int ts = 200; // millis
int ejeX = 6;
int ejeY= 7;

/*
 ***********************************************************************
 *              SETUP CONFIGURACIÓN INICIAL
 ***********************************************************************
 */
void setup(){
  Serial.begin(9600);    // Tasa de baudios del puerto serial
  pinMode (senal, OUTPUT); // Salidas de pulso
  pinMode (ejeX, OUTPUT); // Nivel de tension sobre el eje X
  pinMode (ejeY, OUTPUT); // Nivel de tension sobre el eje Y
}

 /*
 ***********************************************************************
 *              LOOP BUCLE PRINCIPAL
 ***********************************************************************
 */
void loop(){
  numeroAletorio();
  generaSenal();
  tensionCuadratura();
  delay(ts);
  }


void numeroAletorio(){
    /*Si cargamos un #constante como semilla generamos
    numeros seudo-aeatorios, cargando una semilla cambiante
    generamos numeros aleatorios*/
    randomSeed(millis());
    azar = random(0,8); // genera numero aleatorio desde random(n,(m-1))
    Serial.println(azar);
  }

void generaSenal(){
  if(azar == 0){ // Si el numero aleatorio es 0 = 000
      digitalWrite(senal,LOW);
      delay(ts);
      digitalWrite(senal,LOW);
      delay(ts);
      digitalWrite(senal,LOW);
      delay(ts);
    }
  if(azar == 1){ // Si el numero aleatorio es 1 = 001
      digitalWrite(senal,LOW);
      delay(ts);
      digitalWrite(senal,LOW);
      delay(ts);
      digitalWrite(senal,HIGH);
      delay(ts);
    }
  if(azar == 2){ // Si el numero aleatorio es 2 = 010
      digitalWrite(senal,LOW);
      delay(ts);
      digitalWrite(senal,HIGH);
      delay(ts);
      digitalWrite(senal,LOW);
      delay(ts);
    }
  if(azar == 3){ // Si el numero aleatorio es 3 = 011
      digitalWrite(senal,LOW);
      delay(ts);
      digitalWrite(senal,HIGH);
      delay(ts);
      digitalWrite(senal,HIGH);
      delay(ts);
    }
  if(azar == 4){ // Si el numero aleatorio es 4 = 100
      digitalWrite(senal,HIGH);
      delay(ts);
      digitalWrite(senal,LOW);
      delay(ts);
      digitalWrite(senal,LOW);
      delay(ts);
    }
  if(azar == 5){ // Si el numero aleatorio es 6 = 101
      digitalWrite(senal,HIGH);
      delay(ts);
      digitalWrite(senal,LOW);
      delay(ts);
      digitalWrite(senal,HIGH);
      delay(ts);
    }
  if(azar == 6){ // Si el numero aleatorio es 6 = 110
      digitalWrite(senal,HIGH);
      delay(ts);
      digitalWrite(senal,HIGH);
      delay(ts);
      digitalWrite(senal,LOW);
      delay(ts);
    }else{ // Si el numero aleatorio es 7 = 111
      //(azar == 7){
      digitalWrite(senal,HIGH);
      delay(ts);
      digitalWrite(senal,HIGH);
      delay(ts);
      digitalWrite(senal,HIGH);
      delay(ts);
    }
}

void tensionCuadratura(){
  if(azar <= 3){
    digitalWrite(ejeX,30);
    digitalWrite(ejeY,30);
  }
}
