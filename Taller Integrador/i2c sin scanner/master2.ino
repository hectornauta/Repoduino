#include <Wire.h>
void setup()
{
	Wire.begin(2);
}
int y = 0;

void loop()
{
  delay(3);
  Wire.beginTransmission(4);
  Wire.write("2Y");
  //Wire.write(y);
  Wire.endTransmission();
  y++;
  delay(3);
}