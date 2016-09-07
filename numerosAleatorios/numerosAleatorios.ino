/*
 ***********************************************************************
 *              LIBRERIAS y CONSTANTES
 ***********************************************************************
 */
int IN1 = 8; 
int IN2 = 7;
int IN3 = 6;
int tiempoDePulso = 500; // 0.5s
 
int azar;

/*
 ***********************************************************************
 *              SETUP CONFIGURACIÓN INICIAL
 ***********************************************************************
 */
void setup(){
  Serial.begin(9600);    // Tasa de baudios del puerto serial
  pinMode (IN1, OUTPUT); // Salidas de pulso
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  
}

 /*
 ***********************************************************************
 *              LOOP BUCLE PRINCIPAL
 ***********************************************************************
 */
void loop(){
  numeroAletorio();
  //delay(300);
  if(azar == 0){ // Si el numero aleatorio es 0 = 000
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      delay(tiempoDePulso);
    }
  if(azar == 1){ // Si el numero aleatorio es 1 = 001
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,HIGH);
      delay(tiempoDePulso);
    }
  if(azar == 2){ // Si el numero aleatorio es 2 = 010
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,LOW);
      delay(tiempoDePulso);
    }
  if(azar == 3){ // Si el numero aleatorio es 3 = 011
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,HIGH);
      delay(tiempoDePulso);
    }
  if(azar == 4){ // Si el numero aleatorio es 4 = 100
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      delay(tiempoDePulso);
    }
  if(azar == 5){ // Si el numero aleatorio es 6 = 101
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,HIGH);
      delay(tiempoDePulso);
    }
  if(azar == 6){ // Si el numero aleatorio es 6 = 110
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,LOW);
      delay(tiempoDePulso);
    }
  if(azar == 7){ // Si el numero aleatorio es 7 = 111
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,HIGH);
      delay(tiempoDePulso);
    }
  }
   
  
void numeroAletorio(){
    /*Si cargamos un #constante como semilla generamos 
    numeros seudo-aeatorios, cargando una semilla cambiante
    generamos numeros aleatorios*/
    randomSeed(millis());  
    azar = random(0,8); // genera numero aleatorio desde random(n,(m-1))
    Serial.println(azar);
  }


