/*
 ***********************************************************************
 *              LIBRERIAS y CONSTANTES
 ***********************************************************************
 */
int azar;
int senal = 5;
int ts = 20; // tiempo en millis

int tensionX, tensionY; // valor analogico de tension
int X = 11;
int menosX = 10;
int Y= 9;
int menosY = 8;

/*
 ***********************************************************************
 *              SETUP CONFIGURACIÓN INICIAL
 ***********************************************************************
 */
void setup(){
  Serial.begin(9600);    // Tasa de baudios del puerto serial
  pinMode (senal, OUTPUT); // Señal de pulsos aleatorios
  pinMode (X, OUTPUT); // Salida de tension sobre el eje X
  pinMode (Y, OUTPUT); // "               " sobre el eje Y
  pinMode (menosX, OUTPUT); // Salida de tension sobre el eje -X
  pinMode (menosY, OUTPUT); // "               " sobre el eje -Y
}

 /*
 ***********************************************************************
 *              LOOP BUCLE PRINCIPAL
 ***********************************************************************
 */
void loop(){
  numeroAletorio();
  generaSenal();

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
    tensionX = 100;
    tensionY = 0;
    primerCuadrante(); // x,y
      digitalWrite(senal,LOW);
      delay(ts);
      digitalWrite(senal,LOW);
      delay(ts);
      digitalWrite(senal,LOW);
      delay(ts);
    }
  if(azar == 1){ // Si el numero aleatorio es 1 = 001
    tensionX = 0;
    tensionY = 100;
    primerCuadrante();
      digitalWrite(senal,LOW);
      delay(ts);
      digitalWrite(senal,LOW);
      delay(ts);
      digitalWrite(senal,HIGH);
      delay(ts);
    }
  if(azar == 2){ // Si el numero aleatorio es 2 = 010
    tensionX = 200;
    tensionY = 200;
    primerCuadrante();
      digitalWrite(senal,LOW);
      delay(ts);
      digitalWrite(senal,HIGH);
      delay(ts);
      digitalWrite(senal,LOW);
      delay(ts);
    }
  if(azar == 3){ // Si el numero aleatorio es 3 = 011
    tensionX = 100;
    tensionY = 0;
    segundoCuadrante(); // -x,y
      digitalWrite(senal,LOW);
      delay(ts);
      digitalWrite(senal,HIGH);
      delay(ts);
      digitalWrite(senal,HIGH);
      delay(ts);
    }
  if(azar == 4){ // Si el numero aleatorio es 4 = 100
    tensionX = 200;
    tensionY = 200;
    segundoCuadrante();
      digitalWrite(senal,HIGH);
      delay(ts);
      digitalWrite(senal,LOW);
      delay(ts);
      digitalWrite(senal,LOW);
      delay(ts);
    }
  if(azar == 5){ // Si el numero aleatorio es 6 = 101
    tensionX = 0;
    tensionY = 100;
    tercerCuadrante();
      digitalWrite(senal,HIGH);
      delay(ts);
      digitalWrite(senal,LOW);
      delay(ts);
      digitalWrite(senal,HIGH);
      delay(ts);
    }
  if(azar == 6){ // Si el numero aleatorio es 6 = 110
    tensionX = 200;
    tensionY = 200;
    tercerCuadrante();
      digitalWrite(senal,HIGH);
      delay(ts);
      digitalWrite(senal,HIGH);
      delay(ts);
      digitalWrite(senal,LOW);
      delay(ts);
    }else{ // Si el numero aleatorio es 7 = 111
      //(azar == 7){
      tensionX = 200;
      tensionY = 200;
      cuartoCuadrante();
        digitalWrite(senal,HIGH);
        delay(ts);
        digitalWrite(senal,HIGH);
        delay(ts);
        digitalWrite(senal,HIGH);
        delay(ts);
    }
}

void primerCuadrante(){
    analogWrite(X,tensionX);
    analogWrite(Y,tensionY);
    analogWrite(menosX, 0);
    analogWrite(menosY, 0);

}

void segundoCuadrante(){
    analogWrite(menosX,tensionX);
    analogWrite(Y,tensionY);
    analogWrite(X, 0);
    analogWrite(menosY, 0);
}

void tercerCuadrante(){
    analogWrite(menosX,tensionX);
    analogWrite(menosY,tensionY);
    analogWrite(X, 0);
    analogWrite(Y, 0);
}

void cuartoCuadrante(){
    analogWrite(X,tensionX);
    analogWrite(menosY,tensionY);
    analogWrite(menosX, 0);
    analogWrite(Y, 0);
}
