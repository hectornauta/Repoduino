#include <Wire.h>

void setup()
{
  Wire.begin(0); //PONER EL Nº DE GRUPO - 1 => PARA EL GRUPO 1 VA 0
  Wire.onRequest(sendData);
  Serial.begin(9600);
}

void loop()
{
  delay(10);
}

void sendData(int howMany)
{
  int value1 = tactil();
  char data[4];
  sprintf(data, "%0.4d", value1);
  for (int i = 0; i<4; i++) {
    Wire.write(data[i]);
  }

  int value2 = efecto_hall();
  sprintf(data, "%0.4d", value2);
  for (int i = 0; i<4; i++) {
    Wire.write(data[i]);
  }
}

int tactil()
{
  int buttonpin = 2;
  int informacion;
  
  informacion = digitalRead(buttonpin);
  return informacion;
}

int efecto_hall()
{
  int hallSensorPin = 12;
  int informacion;
  
  informacion = digitalRead(hallSensorPin);
  return informacion;
}
