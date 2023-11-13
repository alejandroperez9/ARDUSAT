/*

GNU GENERAL PUBLIC LICENSE v3.0
REALIZACIÓN DE UN SATÉLITE METEOROLÓGICO BASADO EN ARDUINO
PROYECTO REALIZADO POR ALEJANDRO PÉREZ ARANDA.
https://github.com/alejandroperez9/ARDUSAT                  // PERFIL DE GITHUB.
https://linkedin.com/in/alejandro-p￩rez-aranda-a91012278    // PERFIL DE LINKEDIN.

---------- EMISOR ----------

*/

#include <DHT.h>                                            // LIBRERÍA PARA LOS SENSORES DHT, TEMPERATURA Y HUMEDAD.
#include <LoRa.h>                                           // LIBRERÍA PARA EL MÓDULO DE TRANSMISIÓN E32-900T30D.
#include <I2Cdev.h>                                         // LIBRERÍA DE COMUNICACIÓN I2C.
#include <MPU6050.h>                                        // LIBRERÍA MÓDULO MPU6050 - ACELERÓMETRO Y GIROSCOPIO.
#include <Wire.h>                                           // LIBRERÍA DE COMUNICACIÓN WIRE.

#define DHTPIN 11                                           // ESTABLECEMOS EL PIN DE CONEXIÓN PARA LA TRANSMISIÓN DE DATOS.
#define DHTTYPE DHT11                                       // DEFINIMOS EL TIPO DE SENSOR DHT - DHT11 O DHT22.

#define DHTPINA 10                                          // ESTABLECEMOS EL PIN DE CONEXIÓN PARA LA TRANSMISIÓN DE DATOS.
#define DHTTYPEA DHT11                                      // DEFINIMOS EL TIPO DE SENSOR DHT - DHT11 O DHT22.

#define DHTPINB 9                                           // ESTABLECEMOS EL PIN DE CONEXIÓN PARA LA TRANSMISIÓN DE DATOS.
#define DHTTYPEB DHT11                                      // DEFINIMOS EL TIPO DE SENSOR DHT - DHT11 O DHT22.

DHT dht(DHTPIN, DHTTYPE);                                   // SE CREA EL OBJETO DHT, DEFINIENDO EL PIN CONECTADO Y EL TIPO DE SENSOR.
DHT dhtA(DHTPINA, DHTTYPEA);                                // SE CREA EL OBJETO DHTA, DEFINIENDO EL PIN CONECTADO Y EL TIPO DE SENSOR.
DHT dhtB(DHTPINB, DHTTYPEB);                                // SE CREA EL OBJETO DHTB, DEFINIENDO EL PIN CONECTADO Y EL TIPO DE SENSOR.

const int ledPIN1 = 6;                                      // UBICACIÓN DEL PIN DIGITAL, DESTINADO AL LED Nº1.
const int ledPIN2 = 5;                                      // UBICACIÓN DEL PIN DIGITAL, DESTINADO AL LED Nº2.
const int ledPIN3 = 4;                                      // UBICACIÓN DEL PIN DIGITAL, DESTINADO AL LED Nº3.
const int ledPIN4 = 3;                                      // UBICACIÓN DEL PIN DIGITAL, DESTINADO AL LED Nº4.
const int ledPIN5 = 2;                                      // UBICACIÓN DEL PIN DIGITAL, DESTINADO AL LED Nº5.

const int LDR_A = A0;                                       // UBICACIÓN DEL PIN ANALÓGICO, DESTINADO AL LDR_A.
const int LDR_B = A1;                                       // UBICACIÓN DEL PIN ANALÓGICO, DESTINADO AL LDR_B.
const int FUEGO = A2;                                       // UBICACIÓN DEL PIN ANALÓGICO, DESTINADO AL FIRE.

const int mpuAddress = 0x68;                                // DIRECCIÓN DEL MPU, PUDIENDO SER 0X68 O 0X69.
MPU6050 mpu(mpuAddress);                                    // SE CREA EL OBJETO MPU, DANDOLE LA DIRECCIÓN NECESARIA.

void setup(){

  Serial.begin(9600);                                       // VELOCIDAD DEL PUERTO DE COMUNICACIÓN, ESTABLECIDA EN 9600.             

                                                            // --- FUNCIONES ---
  Wire.begin();                                             // COMIENZO DE LA FUNCIÓN DE COMUNICACIÓN WIRE.
  mpu.initialize();                                         // COMIENZO DE LA FUNCIÓN DEL MPU6050.

  dht.begin();                                              // COMIENZO DE LA FUNCIÓN DE DHT-INTERIOR.
  dhtA.begin();                                             // COMIENZO DE LA FUNCIÓN DE DHT-A. 
  dhtB.begin();                                             // COMIENZO DE LA FUNCIÓN DE DHT-B.

                                                            // --- PINES DIGITALES ---
  pinMode(ledPIN1, OUTPUT);                                 // PINMODE = PIN DEL LED DADO POR "ledPIN1", VALOR DE SALIDA.
  pinMode(ledPIN2, OUTPUT);                                 // PINMODE = PIN DEL LED DADO POR "ledPIN2", VALOR DE SALIDA.
  pinMode(ledPIN3, OUTPUT);                                 // PINMODE = PIN DEL LED DADO POR "ledPIN3", VALOR DE SALIDA.
  pinMode(ledPIN4, OUTPUT);                                 // PINMODE = PIN DEL LED DADO POR "ledPIN4", VALOR DE SALIDA.
  pinMode(ledPIN5, OUTPUT);                                 // PINMODE = PIN DEL LED DADO POR "ledPIN5", VALOR DE SALIDA.

                                                            // --- PINES ANALÓGICOS ---
  pinMode(LDR_A, INPUT);                                    // PINMODE = PIN DEL SENSOR DADO POR "LDR_A" , VALOR DE ENTRADA.
  pinMode(LDR_B, INPUT);                                    // PINMODE = PIN DEL SENSOR DADO POR "LDR_B" , VALOR DE ENTRADA.
  pinMode(FUEGO, INPUT);                                    // PINMODE = PIN DEL SENSOR DADO POR "FIRE" , VALOR DE ENTRADA.

}

void loop(){

                                                            // --- OBTENCIÓN LDR - VALORES ANALÓGICOS ---
  int LDRA = analogRead(LDR_A);                             // SE APLICA LA NUEVA VARIABLE "LDRA", DANDOLE EL VALOR DE LECTURA DEL VALOR ANALÓGICO DEL LDR_A.
  int LDRB = analogRead(LDR_B);                             // SE APLICA LA NUEVA VARIABLE "LDRB", DANDOLE EL VALOR DE LECTURA DEL VALOR ANALÓGICO DEL LDR_B.

  if (isnan(LDRA) || isnan(LDRB)){                          // CONDICIONAL PARA EL VALOR DEL LDR-A Y LDR-B, SIENDO ERRÓNEO O NULO.
    digitalWrite(ledPIN3, HIGH);                            // EL LED INDICADOR DE ERROR, SE ENCIENDE.
  }else{
    digitalWrite(ledPIN3, LOW);                             // EL LED INDICADOR DE ERROR, SE APAGA.
  }

  int Lectura_Solar = (LDRA + LDRB)/2;                      // VALOR MEDIO DE LA LECTURA ANALÓGICA DEL LDR-A Y LDR-B.

  Serial.print("Luz: ");                                    // MUESTRA DE DATOS EN EL PUERTO SERIE.
  Serial.println(Lectura_Solar);                            // MUESTRA DE "LECTURA SOLAR"

                                                            // --- DETECCIÓN FUEGO - VALOR ANALÓGICO ---
  int ALERTA_FUEGO = analogRead(FUEGO);                     // SE APLICA LA NUEVA VARIABLE "ALERTA_FUEGO", DANDOLE EL VALOR DE LECTURA DEL VALOR ANALÓGICO DEL FIRE.

  Serial.print("Fuego: ");                                  // MUESTRA DE DATOS EN EL PUERTO SERIE.

  if (ALERTA_FUEGO < 500){                                  // CONDICIONAL PARA EL VALOR DEL FIRE, DANDOLE LA LECTURA DESDE "ALERTA_FUEGO".
    digitalWrite(ledPIN4, HIGH);                            // EL LED INDICADOR DE ERROR, SE ENCIENDE.
    Serial.println("ALERTA POR FUEGO EN EL MÓDULO CENTRAL");// MUESTRA DE ALERTA EN EL PUERTO SERIE.
  }else{
    digitalWrite(ledPIN4, LOW);                             // EL LED INDICADOR DE ERROR, SE APAGA.
    Serial.println("ESTADO DEL MÓDULO - CORRECTO");         // MUESTRA DE DATOS CORRECTOS EN EL PUERTO SERIE.
  }

                                                            // --- TEMPERATURA INTERIOR - VALOR DIGITAL ---
  float Temp_Int = dht.readTemperature();                   // SE APLICA LA NUEVA VARIABLE "Temp_Int", DANDOLE EL VALOR DE LECTURA DE TEMPERATURA DEL DHT11 - INTERIOR.

  Serial.print("Temp Módulo: ");                            // MUESTRA DE DATOS EN EL PUERTO SERIE.
  Serial.print(Temp_Int);                                   // MUESTRA DE "TEMPERATURA INTERIOR".
  Serial.println(" ºC");                                    // MUESTRA DE LA UNIDAD DE MEDIDA.

  if (isnan(Temp_Int)){                                     // CONDICIONAL PARA EL VALOR DE LA TEMPERATURA EN EL SENSOR INTERIOR, SIENDO ERRÓNEA O NULA. 
    digitalWrite(ledPIN1, HIGH);                            // EL LED INDICADOR DE ERROR, SE ENCIENDE.
    return;                                                 // DEVOLVEMOS LA FUNCIÓN.
  }else{
    digitalWrite(ledPIN1, LOW);                             // EL LED INDICADOR DE ERROR, SE APAGA.
  }

  if (Temp_Int >= 22){                                      // CONDICIONAL EN CASO DE QUE LA TEMPERATURA INTERIOR SEA MAYOR O IGUAL QUE 22 (REFERIDOS A GRADOS).
    digitalWrite(8, HIGH);                                  // VENTILADOR DE DISIPACIÓN ENCENDIDO.
  }else{
    digitalWrite(8, LOW);                                   // VENTILADOR DE DISIPACIÓN APAGADO.
  }

                                                            // --- TEMPERATURA EXTERIOR - VALOR DIGITAL ---
  float Temp_ExtA = dhtA.readTemperature();                 // SE APLICA LA NUEVA VARIABLE "Temp_ExtA", DANDOLE EL VALOR DE LECTURA DE TEMPERATURA DEL DHT11 - 1º SENSOR.
  float Hum_ExtA = dhtA.readHumidity();                     // SE APLICA LA NUEVA VARIABLE "Hum_ExtA", DANDOLE EL VALOR DE LECTURA DE HUMEDAD DEL DHT11 - 1º SENSOR.

  if (isnan(Temp_ExtA) || isnan(Hum_ExtA)){                 // CONDICIONAL PARA EL VALOR DE LA TEMPERATURA Y DE LA HUMEDAD EN EL SENSOR A, SIENDO ERRÓNEA O NULA.
    digitalWrite(ledPIN2, HIGH);                            // EL LED INDICADOR DE ERROR, SE ENCIENDE.
    return;
  }else{
    digitalWrite(ledPIN2, LOW);                             // EL LED INDICADOR DE ERROR, SE APAGA.
  }

  float Temp_ExtB = dhtB.readTemperature();                 // SE APLICA LA NUEVA VARIABLE "Temp_ExtB", DANDOLE EL VALOR DE LECTURA DE TEMPERATURA DEL DHT11 - 2º SENSOR.
  float Hum_ExtB = dhtB.readHumidity();                     // SE APLICA LA NUEVA VARIABLE "Hum_ExtB", DANDOLE EL VALOR DE LECTURA DE HUMEDAD DEL DHT11 - 2º SENSOR.

  if (isnan(Temp_ExtB) || isnan(Hum_ExtB)){                 // CONDICIONAL PARA EL VALOR DE LA TEMPERATURA Y DE LA HUMEDAD EN EL SENSOR B, SIENDO ERRÓNEA O NULA.
    digitalWrite(ledPIN2, HIGH);                            // EL LED INDICADOR DE ERROR, SE ENCIENDE.
    return;                                                 // DEVOLVEMOS LA FUNCIÓN.
  }else{
    digitalWrite(ledPIN2, LOW);                             // EL LED INDICADOR DE ERROR, SE APAGA.
  }

  float Temp_Ext = (Temp_ExtA + Temp_ExtB)/2;               // CÁLCULO DEL VALOR MEDIO DE TEMPERATURA, ENTRE LOS SENSORES DHT11 EXTERIORES A Y B.
  float Hum_Ext = (Hum_ExtA + Hum_ExtB)/2;                  // CÁLCULO DEL VALOR MEDIO DE HUMEDAD, ENTRE LOS SENSORES DHT11 EXTERIORES A Y B.

  Serial.print("Temp Exterior: ");                          // MUESTRA DE DATOS EN EL PUERTO SERIE.
  Serial.print(Temp_Ext);                                   // MUESTRA DE "TEMPERATURA MEDIA EXTERIOR".
  Serial.println(" ºC");                                    // MUESTRA DE LA UNIDAD DE MEDIDA.

  Serial.print("Hum Ext: ");                                // MUESTRA DE DATOS EN EL PUERTO SERIE.
  Serial.print(Hum_Ext);                                    // MUESTRA DE "HUMEDAD MEDIA EXTERIOR".
  Serial.println(" %");                                     // MUESTRA DE LA UNIDAD DE MEDIDA.

                                                            // --- VALORES MPU6050 - VALORES DIGITALES ---
  int16_t ax, ay, az;                                       // VARIABLES ACELERÓMETRO EN EL EJE X - EJE Y - EJE Z.
  int16_t gx, gy, gz;                                       // VARIABLES GIROSCOPIO EN EL EJE X - EJE Y - EJE Z.

  mpu.getRotation(&gx, &gy, &gz);                           // FUNCIÓN PARA LA OBTENCIÓN DE VALORES DE LAS VARIABLES DEL GIROSCOPIO.
  mpu.getAcceleration(&ax, &ay, &az);                       // FUNCIÓN PARA LA OBTENCIÓN DE VALORES DE LAS VARIABLES DEL ACELERÓMETRO.

  Serial.print("Aceleración X: ");                          // MUESTRA DE DATOS EN EL PUERTO SERIE.
  Serial.print(ax);                                         // MUESTRA DE "ACELERACIÓN EN X".
  Serial.println(" m/s^2");                                 // MUESTRA DE LA UNIDAD DE MEDIDA.

  Serial.print("Aceleración Y: ");                          // MUESTRA DE DATOS EN EL PUERTO SERIE.
  Serial.print(ay);                                         // MUESTRA DE "ACELERACIÓN EN Y".
  Serial.println(" m/s^2");                                 // MUESTRA DE LA UNIDAD DE MEDIDA.

  Serial.print("Aceleración Z: ");                          // MUESTRA DE DATOS EN EL PUERTO SERIE.
  Serial.print(az);                                         // MUESTRA DE "ACELERACIÓN EN Z".
  Serial.println(" m/s^2");                                 // MUESTRA DE LA UNIDAD DE MEDIDA.

  Serial.print("Giroscopio X: ");                           // MUESTRA DE DATOS EN EL PUERTO SERIE,
  Serial.print(gx);                                         // MUESTRA DE "GIROSCOPIO EN X".
  Serial.println(" rpm");                                   // MUESTRA DE LA UNIDAD DE MEDIDA.

  Serial.print("Giroscopio Y: ");                           // MUESTRA DE DATOS EN EL PUERTO SERIE.
  Serial.print(gy);                                         // MUESTRA DE "GIROSCOPIO EN Y".
  Serial.println(" rpm");                                   // MUESTRA DE LA UNIDAD DE MEDIDA.

  Serial.print("Giroscopio Z: ");                           // MUESTRA DE DATOS EN EL PUERTO SERIE.
  Serial.print(gz);                                         // MUESTRA DE "GIROSCOPIO EN Z".
  Serial.println(" rpm");                                   // MUESTRA DE LA UNIDAD DE MEDIDA.

  delay(7000);                                              // TIEMPO DE ESPERA DE 7 SEGUNDOS.

}