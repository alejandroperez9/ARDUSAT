/*

GNU GENERAL PUBLIC LICENSE v3.0
REALIZACIÓN DE UN SATÉLITE METEOROLÓGICO BASADO EN ARDUINO
PROYECTO REALIZADO POR ALEJANDRO PÉREZ ARANDA.
https://github.com/alejandroperez9/ARDUSAT                  // PERFIL DE GITHUB.
https://linkedin.com/in/alejandro-p￩rez-aranda-a91012278    // PERFIL DE LINKEDIN.

---------- LECTURA DHT ----------

*/

#include <DHT.h>                                            // LIBRERÍA DHT.

#define DHTPIN 2                                            // DEFINIMOS EL PIN DE CONEXIONADO.
#define DHTTYPE DHT11                                       // DEFINIMOS EL TIPO DE DHT; DHT11 - DHT22.

DHT dht(DHTPIN, DHTTYPE);                                   // DEFINIMOS EL OBJETO DHT.

void setup(){

  Serial.begin(9600);                                       // VELOCIDAD DEL PUERTO DE COMUNICACIÓN - 9600.
  dht.begin();                                              // COMIENZO DE LA FUNCIÓN DHT.

}

void loop() {

  float h = dht.readHumidity();                             // OBTENEMOS EL VALOR DE HUMEDAD.
  float t = dht.readTemperature();                          // OBTENEMOS EL VALOR DE TEMPERATURA.

  Serial.print(Temp: );                                     // IMPRIMIMOS VALORES Y TXT EN PUERTO SERIE.
  Serial.print(t);
  Serial.print(" Hum: ");
  Serial.println(h);

}
