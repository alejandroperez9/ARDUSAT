/*

GNU GENERAL PUBLIC LICENSE v3.0
REALIZACIÓN DE UN SATÉLITE METEOROLÓGICO BASADO EN ARDUINO
PROYECTO REALIZADO POR ALEJANDRO PÉREZ ARANDA.
https://github.com/alejandroperez9/ARDUSAT                  // PERFIL DE GITHUB.
https://linkedin.com/in/alejandro-p￩rez-aranda-a91012278    // PERFIL DE LINKEDIN.

---------- LECTURA MPU6050 ----------

*/

#include <Wire.h>                                           // LIBRERÍA COMUNICACIÓN WIRE.
#include <MPU6050.h>                                        // LIBRERÍA MPU6050.

const int mpuAddress = 0x68;                                // DIRECCIÓN DEL MPU, PUDIENDO SER 0X68 O 0X69.
MPU6050 mpu(mpuAddress);                                    // SE CREA EL OBJETO MPU, DANDOLE LA DIRECCIÓN NECESARIA.

void setup() {

  Serial.begin(9600);                                       // VELOCIDAD DEL PUERTO DE COMUNICACIÓN, ESTABLECIDA EN 9600.  
  Wire.begin();                                             // COMIENZO DE LA FUNCIÓN DE COMUNICACIÓN WIRE.
  mpu.initialize();                                         // COMIENZO DE LA FUNCIÓN DEL MPU6050.

}

void loop() {

  int16_t ax, ay, az;                                       // VARIABLES ACELERÓMETRO EN EL EJE X - EJE Y - EJE Z.
  int16_t gx, gy, gz;                                       // VARIABLES GIROSCOPIO EN EL EJE X - EJE Y - EJE Z.

  mpu.getRotation(&gx, &gy, &gz);                           // FUNCIÓN PARA LA OBTENCIÓN DE VALORES DE LAS VARIABLES DEL GIROSCOPIO.
  mpu.getAcceleration(&ax, &ay, &az);                       // FUNCIÓN PARA LA OBTENCIÓN DE VALORES DE LAS VARIABLES DEL ACELERÓMETRO.

  // AQUÍ PUEDE AÑADIRSE LA IMPRESIÓN EN EL PUERTO SERIE DE CADA VALOR.

}
