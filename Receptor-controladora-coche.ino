
// LIBRERÍAS

#include <Servo.h> // Librería Servo-motor
#include <RF24.h> // Librería Módulo-RF
#include <AFMotor.h> // Librería controlador del motor

// CONSTANTES RF

#define CE_PIN 32 // Constante de datos Chip Enable (CE) del módulo de RF
#define CSN_PIN 33 // Constante de datos Chip Select (CS) del módulo de RF

byte canal[6] =("00001"); // Se define un canal predeconfigurado en la librería RF24.h por donde se enviarán los datos

RF24 radio(CE_PIN, CSN_PIN); // Se define el objeto radio por los pines anteriores

// CONSTANTES MOTOR

AF_DCMotor Motor_1(1);
AF_DCMotor Motor_2(2);
AF_DCMotor Motor_3(3);
AF_DCMotor Motor_4(4);

// VARIABLES

int datos[3]; // Se define la matriz con un tamaño fijo de 2 bytes

void Imprimir(){
Serial.print("x: ");
Serial.println(datos[0]);
Serial.print("y: ");
Serial.println(datos[1]);
Serial.print("x2: ");
Serial.println(datos[2]);
}
void Velocidad(int velo) {
  Motor_1.setSpeed(velo);
  Motor_2.setSpeed(velo);
  Motor_3.setSpeed(velo);
  Motor_4.setSpeed(velo);
}

Servo direccion;

void setup()
{
  
Serial.begin(9600); // Se inicia el puerto serie a 9600 bps

radio.begin(); // Se inicia el objeto radio
radio.startListening(); // El módulo RF se pone en modo escucha
radio.openReadingPipe(1, canal); // Lee los datos del canal de transmisión

Motor_1.run(RELEASE);
Motor_2.run(RELEASE);
Motor_3.run(RELEASE);
Motor_4.run(RELEASE);


direccion.attach(21);


}
 
void loop() {

radio.read(datos,sizeof(datos)); // Lee la matriz enviada por el emisor y lo almacena el la matriz datos[].

 switch (datos[1]) {
  
  case 0 ... 10:
    Velocidad(200);
    Motor_1.run(BACKWARD);
    Motor_2.run(BACKWARD);
    Motor_3.run(BACKWARD);
    Motor_4.run(BACKWARD);
      break;
 
  case 170 ... 180:
    Velocidad(200);
    Motor_1.run(FORWARD);
    Motor_2.run(FORWARD);
    Motor_3.run(FORWARD);
    Motor_4.run(FORWARD);
      break;
          
  default:
    Velocidad(0);
      break;
 }

direccion.write(datos[0]);

Imprimir();
delay(200);

}
