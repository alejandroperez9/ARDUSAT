/*

GNU GENERAL PUBLIC LICENSE v3.0
REALIZACIÓN DE UN SATÉLITE METEOROLÓGICO BASADO EN ARDUINO
PROYECTO REALIZADO POR ALEJANDRO PÉREZ ARANDA.
https://github.com/alejandroperez9/ARDUSAT                  // PERFIL DE GITHUB.
https://linkedin.com/in/alejandro-p￩rez-aranda-a91012278    // PERFIL DE LINKEDIN.

---------- RECEPTOR LoRa ----------

*/

#include <LoRa.h>                                           // LIBRERÍA LoRa.

void setup(){

  Serial.begin(9600);                                       // VELOCIDAD PUERTO DE COMUNICACIÓN - 9600.
  if (!LoRa.begin(433E6)){                                  // EN CASO DE ERROR POR PARTE DEL MÓDULO, BUCLE INFINITO.
    Serial.println("Error al iniciar el módulo LoRa.");
    while (1);
  }

}

void loop(){

  if (LoRa.parsePacket()){                                  // TENIENDO DATOS A RECIBIR...
    float PAQUTE = LoRa.parseFloat();                       // OBTENGO LOS DATOS Y LOS NOMBRO "PAQUETE".
    Serial.print("Recibido: ");                             // IMPRIMO: "RECIBIDO: ".
    Serial.println(PAQUETE);                                // IMPRIMO EL PAQUETE.
  }
}

