/*

GNU GENERAL PUBLIC LICENSE v3.0
REALIZACIÓN DE UN SATÉLITE METEOROLÓGICO BASADO EN ARDUINO
PROYECTO REALIZADO POR ALEJANDRO PÉREZ ARANDA.
https://github.com/alejandroperez9/ARDUSAT                  // PERFIL DE GITHUB.
https://linkedin.com/in/alejandro-p￩rez-aranda-a91012278    // PERFIL DE LINKEDIN.

---------- LECTURA LLAMA DE FUEGO (FIRE) ----------

*/

const int sensorPin = A0;

void setup() {

  Serial.begin(9600);  // VELOCIDAD PUERTO DE COMUNICACIÓN - 9600.
}

void loop() {

  int llama = analogRead(sensorPin);  // VARIABLE "llama" DANDOLE EL VALOR ANALÓGICO DE "sensorPin".
  Serial.println(llama);              // IMPRIME EL VALOR DE "LLAMA" EN EL PUERTO SERIE.

  if (llama < 500) {              // CONDICIONAL EN CASO DE DETECTAR UN VALOR MENOR DE 500.
    Serial.println("Detección");  // SE IMPRIME "DETECCIÓN" EN EL PUERTO SERIE.
                                  // SE AÑADEN LAS MEDIDAS QUE QUIERAN REALIZARSE, DE MANERA OPORTUNA.
  }

  delay(1000);  // TIEMPO DE ESPERA DE 1 SEGUNDO.
}
