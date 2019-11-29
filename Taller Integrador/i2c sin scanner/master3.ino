
#include <Wire.h>
void setup()
{
	Wire.begin(3);
}
int z = 0;

void loop()
{
  delay(6);
  Wire.beginTransmission(4);
  Wire.write("3Z");
  //Wire.write(z);
  Wire.endTransmission();
  z++;
}