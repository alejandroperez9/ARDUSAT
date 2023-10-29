/*

GNU GENERAL PUBLIC LICENSE v3.0
REALIZACIÓN DE UN SATÉLITE METEOROLÓGICO BASADO EN ARDUINO
PROYECTO REALIZADO POR ALEJANDRO PÉREZ ARANDA.
https://github.com/alejandroperez9/ARDUSAT                  // PERFIL DE GITHUB.
https://linkedin.com/in/alejandro-p￩rez-aranda-a91012278    // PERFIL DE LINKEDIN.

---------- LECTURA LDR ----------

*/

void setup(){
                        
  Serial.begin(9600);                                       // VELOCIDAD PUERTO DE COMUNICACIÓN - 9600.
  pinMode(A0,INPUT);                                        // PINMODE = PIN DE LECTURA, VALOR DE ENTRADA. 

} 
 
void loop(){

  int valorLDR = analogRead(A0);                            // VALORLDR = LECTURA ANALÓGICA DE A0.          
  Serial.println(valorLDR);                                 // SE MUESTRA EL VALOR EN EL PUERTO SERIE.

  } 