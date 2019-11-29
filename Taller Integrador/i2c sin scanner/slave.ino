#include <Wire.h>
#include <stdlib.h>

void setup()
{
  Serial.begin(9600);
}


void loop()
{
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  //delay(10);
}
void receiveEvent(int howMany)
{
  String z;
  z = "";
  for (int i = 0; i < howMany; i++)
  {
    z += (char)Wire.read();
  	//Serial.println((char)Wire.read());
  }
  char zz[40];
  z.toCharArray(zz,40);
  Serial.println(zz);
  
}