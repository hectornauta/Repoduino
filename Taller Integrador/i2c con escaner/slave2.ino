#include <Wire.h>

#define direccion 2
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
  paquete[0] = 50; 
  paquete[1] = 89;
}

void requestEvent()
{
  Wire.write(paquete,numerodebytes);  
}