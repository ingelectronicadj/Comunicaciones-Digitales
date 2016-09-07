/*
 ***********************************************************************
 *              LIBRERIAS y CONSTANTES
 ***********************************************************************
 */
 
int azar;

/*
 ***********************************************************************
 *              SETUP CONFIGURACIÓN INICIAL
 ***********************************************************************
 */
void setup(){
  Serial.begin(9600);
}

 /*
 ***********************************************************************
 *              LOOP BUCLE PRINCIPAL
 ***********************************************************************
 */
void loop(){
  numeroAletorio();
  delay(300);
  }
   
  
void numeroAletorio(){
    /*Si cargamos un #constante como semilla generamos 
    numeros seudo-aeatorios, cargando una semilla cambiante
    generamos numeros aleatorios*/
    randomSeed(millis());  
    azar = random(1,9); // genera numero aleatorio desde random(n,(m-1))
    Serial.println(azar);
  }


