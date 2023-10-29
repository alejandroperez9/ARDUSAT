/*

GNU GENERAL PUBLIC LICENSE v3.0
REALIZACIÓN DE UN SATÉLITE METEOROLÓGICO BASADO EN ARDUINO
PROYECTO REALIZADO POR ALEJANDRO PÉREZ ARANDA.
https://github.com/alejandroperez9/ARDUSAT                  // PERFIL DE GITHUB.
https://linkedin.com/in/alejandro-p￩rez-aranda-a91012278    // PERFIL DE LINKEDIN.

---------- RECEPTOR ----------

*/

#include <LoRa.h>                                           // LIBRERÍA LoRa.

void setup(){

  Serial.begin(9600);                                       // VELOCIDAD PUERTO DE COMUNICACIÓN - 9600;   

  if (!LoRa.begin(433E6)){                                  // EN CASO DE ERROR, COMIENZO DEL BUCLE WHILE(1).
    Serial.println("Error al iniciar el módulo LoRa.");
    while (1);
  }

}

void loop(){

  if (LoRa.parsePacket()){                                  // MIENTRAS SE RECIBAN DATOS...
    String data = LoRa.readString();                        // LECTURA DEL MÓDULO LoRa.
    Serial.print("Datos: ");                                // SE IMPRIME "DATOS: ".
    Serial.println(data);                                   // SE IMPRIME EL VALOR DEL DATO.

    float values[11];                                       // VALORES INTEGRADOS EN LA CADENA.

    char *token = strtok(data.c_str(), ",");                // SEPARACIÓN DE LOS VALORES, MEDIANTE COMAS ",".
    int i = 0;                                              // VARIABLE PARA SUMATORIA "i".

    while (token != NULL && i < 11){                        // MIENTRAS "TOKEN" NO SEA NULO E "i" INFERIOR A 11...           

      values[i] = atof(token);                              // SEPARACIÓN DE LOS VALORES.
      Serial.print("Valor: ");                              // IMPRIME "VALOR:".
      Serial.print(i);                                      // IMPRIME EL VALOR DE "i".
      Serial.print(": ");                                   // IMPRIME ":".
      Serial.println(values[i]);                            // IMPRIME CON SALTO DE LÍNEA EL VALOR DE "i".
      token = strtok(NULL, ",");                            // ACTUALIZA "strtok".
      i++;                                                  // INCREMENTO DE VARIABLE.

    }

  }

}
