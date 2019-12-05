int buttonpin = 2;
int valor;
void setup ()
{
  Serial.begin(9600);
  pinMode (buttonpin, INPUT);
}
void loop ()
{
  valor = digitalRead (buttonpin);
  if (valor == HIGH)
  {
    Serial.println("EMA ME ESTÁ TOCANDO");
  }
  else
  {
    Serial.println("nada");
  }
  delay(3000);
}
