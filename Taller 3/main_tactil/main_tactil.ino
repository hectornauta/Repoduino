int buttonpin = 22;
int valor;
void setup ()
{
  Serial.begin(115200);
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
    //digitalWrite (Led, LOW);
  }
  delay(3000);
}