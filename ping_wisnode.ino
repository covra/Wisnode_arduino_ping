/**
*
*  Ping a Wisnode-Lora desde Arduino Nano clon
*  Compilar con "Nano, ATMega328 (old Bootloader)"
*
*/

#include "Arduino.h"
#include "string.h"
#include "stdlib.h"

#define COMANDO "at+version"  //comando a mandar repetidamente
#define tiempoBucle 2000   // tiempo entre comandos en milisegundos

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {   //Envia repetidamente un comando para conseguir el OK

  String respuesta = comandoSerial(COMANDO);
    if (respuesta.startsWith("OK"))  {
        blinkLed(20,10);  //Si responde correctamente, parpadea rapidamente
    }else{
      blinkLed(3,1);   //Si no responde, parpadea 3 veces lento
    }
    delay(tiempoBucle);
    
}

/**
*   Funciones del skecth
*
*/

void blinkLed (int veces, int velocidad) {  //Parpadea el led de la placa (veces, velocidad[1=1sec, 10=1/10sec])
    for(int i=0; i < veces; i++){
    digitalWrite(LED_BUILTIN, HIGH);
     for (int n=11; n > velocidad; n--){
      delay(50);
     }
     digitalWrite(LED_BUILTIN, LOW);
     for (int n=11; n > velocidad; n--){
      delay(50);
     }

  }
}

String comandoSerial(String commando) //Envia un comando [comando] y devuelve la respuesta del modulo [respuesta]
{
  delay(100);
  while(Serial.available())
  Serial.read();
  Serial.println(commando);
  String respuesta = Serial.readStringUntil('\n');
  respuesta.trim();
  return respuesta;
}
