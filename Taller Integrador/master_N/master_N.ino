#include <Wire.h>
#define senpai 1 //número de este master (1 y en este ejemplo)
#define kouhai 3 //número de este slave (sólo 3 en este caso)
void setup()
{
  Wire.begin(senpai);
}
int x = 0;

void loop()
{
  Wire.beginTransmission(kouhai);
  Wire.write("1X");
  Wire.write(x);
  Wire.endTransmission();
  x++;
  delay(100);//este tiempo no debe coincidir con los otros maestros!!!
}
