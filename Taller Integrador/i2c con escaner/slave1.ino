#include <Wire.h>

#define direccion 1
#define numerodebytes 2

byte paquete[numerodebytes];

void setup()
{

  Serial.begin(9600);
  Wire.begin(direccion);
  Wire.onRequest(requestEvent);
}

void loop()
{ 
  delay(100);
  paquete[0] = 49; 
  paquete[1] = 88;
}

void requestEvent()
{
  Wire.write(paquete,numerodebytes);  
}