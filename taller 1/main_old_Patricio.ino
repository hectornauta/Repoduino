int valor;
int t;
float salida;
String cadena;

void setup()
{
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  t = 0;
}

float sine(int valor, int t) 
{
	float omega = 2 * PI / valor;
  	float salida = 2.5 + 2.5 * sin(omega * t);
  	return salida;
}

float square(int valor, int t)
{
  	float periodo = (float) valor;
  	float medio_periodo = periodo / 2.0;
  	int modulo = t % valor;
  	float modulo_float = (float) modulo;
  	if (modulo_float <= medio_periodo)
    {
    	return 5;
    }
  	else
  	{
    	return 0;
    }
}

float triangle(int valor, int t)
{
	float periodo = (float) valor;
  	float medio_periodo = periodo / 2.0;
  	int modulo = t % valor;
  	float modulo_float = (float) modulo;
  	if (modulo_float <= medio_periodo)
    {
      	float m = 5.0 / medio_periodo;
      	int t1 = t % valor;
      	float salida = m * t1;
      	return salida;
    }
  	else
  	{
    	float m = 5.0 / medio_periodo;
      	int t1 = t % valor;
      	float salida = 10.0 - m * t1;
      	return salida;
    }
}

void loop()
{
  	valor = analogRead(A0);
  	valor = map(valor, 0, 1023, 1, 1024);
  	while (Serial.available() > 0)
  	{
  		cadena = Serial.readStringUntil(' ');
  	}
  	if (cadena == "SQUARE")
    {
    	salida = square(valor, t);
    }
  	else if (cadena == "TRIANGLE")
  	{
    	salida = triangle(valor, t);
    }
  	else if (cadena == "SINE")
    {
    	salida = sine(valor, t);
    }
  	else
  	{
    	salida = 0.0;
      	Serial.println("Sin funcion de entrada");
    }
  	Serial.println(salida);
  	t = t + 1;
}