#include <Wire.h>
#define kouhai 3
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  Wire.begin(kouhai);
  Wire.onReceive(receiveEvent);
  delay(250);
}
void receiveEvent(int howMany)
{
  String z;
  z = "";
  for (int i = 0; i < howMany; i++)
  {
    z += Wire.read();
  }
  char zz[40];
  z.toCharArray(zz,40);
  Serial.println(zz);
}
