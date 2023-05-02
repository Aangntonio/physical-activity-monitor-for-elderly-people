#include <MAX30100.h>

#include <Wire.h>
#include <MPU6050.h>


MPU6050 mpu;
// aceleracion
float accelX = 0;
float accelY = 0;
float accelZ = 0;

//Pines para la detección
 bool pulsorelajado = false ;
 int ledrelajado = 9;
 int ledcaminata = 10;
 int ledactividad = 11;
 int alertabuzz = 12;
//Promedio de la señal
const int BUFFER_SIZE = 50; // Definimos el tamaño del búfer y el índice del búfer
float bufferX[BUFFER_SIZE];
float bufferY[BUFFER_SIZE];
float bufferZ[BUFFER_SIZE];
int bufferIndex = 0;



void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  Serial.println("Inicializando MPU6050...");
  delay(3000);
  pinMode(ledrelajado,OUTPUT);
  pinMode(pulsorelajado,OUTPUT);
}

void Ledmuestra(int pin, int duration) {
  digitalWrite(pin, HIGH);
  delay(duration);
  digitalWrite(pin, LOW);
  delay(duration);
}

void loop() {
 int16_t ax = mpu.getAccelerationX();
  int16_t ay = mpu.getAccelerationY();
  int16_t az = mpu.getAccelerationZ();

  float accelX = ax / 16384.0;
  float accelY = ay / 16384.0;
  float accelZ = az / 16384.0;

  Serial.print("Aceleración X: ");
  Serial.print(accelX);
  Serial.print("  Aceleración Y: ");
  Serial.print(accelY);
  Serial.print("  Aceleración Z: ");
  Serial.println(accelZ);
  
  delay(250);

//Detección del pulso 



// MOnitor ejercicio

if  (-1.2 < accelZ < -0.8  ||  0.0 < accelY < 0.16 || -0.05 < accelX < 0.12) {
    Serial.println("Tu estas en reposo");
    digitalWrite(ledrelajado,HIGH);
  }
//caminata
else if(0.16 < accelY < 0.6 & -0.6 < accelZ < 1.2){
  //caminata
  Serial.println("estas caminando");
  digitalWrite(ledrelajado,LOW);
  Ledmuestra(ledcaminata,500);
  //eJercicio
}
 else if(-0.2 < accelX < 0.3 ){
   Serial.print("estas haciendo jumpingjacks ");


 }   
  //}
  //CAMINATA

} 



