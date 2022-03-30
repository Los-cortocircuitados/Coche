
// LIBRERÍAS

#include <RF24.h> // Librería Módulo-RF

// CONSTANTES RF

#define CE_PIN 7 // Constante de datos Chip Enable (CE) del módulo de RF
#define CSN_PIN 8 // Constante de datos Chip Select (CS) del módulo de RF

byte canal[6] =("00001"); // Se define un canal predeconfigurado en la librería RF24.h por donde se enviarán los datos

RF24 radio(CE_PIN, CSN_PIN); // Se define el objeto radio por los pines anteriores

// VARIABLES

int datos[2]; // Se define la matriz con un tamaño fijo de 2 bytes

void setup(){ 

  radio.begin(); // Se inicia el objeto radio
  Serial.begin(9600); // Se inicia el puerto serie a 9600 bps
  radio.openWritingPipe(canal); // Escribe los datos en el canal de transmisión

} 

void loop(){ 

datos[0] = map(analogRead(0), 0, 512, 0, 180); // Joystick_1 -- Eje X (Servo)
datos[1] = analogRead(1);  // Joystick_1 -- Eje Y (Motor)

radio.write(&datos, sizeof(datos)); // Envía la matriz datos[] por el objeto radio

// CONSOLA

if (radio.available()) { 

Serial.print("Joystick_1 -- Eje X  ");
Serial.print(datos[0]);

Serial.print("Joystick_1 -- Eje Y  ");
Serial.println(datos[1]);

Serial.print("Joystick_2 -- Eje X  ");
Serial.print(datos[2]);

Serial.print("Joystick_2 -- Eje Y  ");
Serial.println(datos[3]);
}
else
{
Serial.println("No se ha podido enviar");
  delay(5000); 

}
} 
