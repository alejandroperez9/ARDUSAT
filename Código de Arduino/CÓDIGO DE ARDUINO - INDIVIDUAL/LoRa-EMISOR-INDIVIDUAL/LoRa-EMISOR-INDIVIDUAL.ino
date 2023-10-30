/*

GNU GENERAL PUBLIC LICENSE v3.0
REALIZACIÓN DE UN SATÉLITE METEOROLÓGICO BASADO EN ARDUINO
PROYECTO REALIZADO POR ALEJANDRO PÉREZ ARANDA.
https://github.com/alejandroperez9/ARDUSAT                  // PERFIL DE GITHUB.
https://linkedin.com/in/alejandro-p￩rez-aranda-a91012278    // PERFIL DE LINKEDIN.

---------- EMISOR LoRa ----------

*/

#include <LoRa.h>                                           // LIBRERÍA LoRa.

void setup(){

  Serial.begin(9600);                                       // VELOCIDAD PUERTO DE COMUNICACIÓN - 9600.
  if (!LoRa.begin(433E6)){                                  // EN CASO DE QUE EL MÓDULO LORA NO FUNCIONES, BUCLE INFINITO.
    Serial.println("Error al iniciar el módulo LoRa.");
    while (1);
  }

}

void loop(){

  int PAQUETE = "VALORES A ENVIAR";                          // PAQUETE A ENVIAR.

  LoRa.beginPacket();                                        // INICIO DEL ENVIO DE PAQUETES.
  LoRa.print(PAQUETE);                                       // PAQUETE A ENVIAR.
  LoRa.endPacket();                                          // FINALIZA EL ENVIO.
  
  delay(5000);                                               // TIEMPO DE ESPERA.
}
