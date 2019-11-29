
#include <Wire.h>
void setup()
{
	Wire.begin(1);
}
int x = 0;
void loop()
{
  Wire.beginTransmission(4);
  Wire.write("1X");
  //Wire.write(x);
  Wire.endTransmission();
  x++;
  delay(6);
}