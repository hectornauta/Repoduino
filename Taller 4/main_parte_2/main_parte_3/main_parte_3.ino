/*
* GRUPO : SEELE
* INTEGRANTES: Aguirre Federico, Costilla Patricio, Huerga Emanuel, Lima Paula, Pollero Emiliano 
* MATERIA: Teoría de Control
* AÑO: 2019
*/
int lectura; // espacio reservado para resguardar el valor leido de la entrada analógica
int periodo; // mapeo del valor de la entrada analógica con la escala a manejar (1024 ms)
const int entrada = A0; // define la entrada analógica A0
int t = 0; //para manejo en el tiempo
float salida = 0.0; //variable que guardará la salida en cada ciclo
float voltaje; //Variable para guardar el voltaje del potenciómetro leído

String cadena; // resguarda el string de entrada por el serial (tipo de función)
String nombre = "";
String seno = "";
String cuadrada = "";
String jason ="";

int salida1;
int salida2;

void setup()
{
  Serial.begin(9600); // Iniciar comunicación serial
  pinMode(entrada, INPUT); // A0 como un pin de entrada
  pinMode(10, OUTPUT); // 13 como pin de salida
  pinMode(11, OUTPUT); // 13 como pin de salida
  t = 0; // variable de tiempo
}

float sine(int valor, int t) //función sinusoidal
{
	float omega = (2 * PI) / valor; //Determinar valor Omega de la función seno
  	float salida = 2.5 + 2.5 * sin(omega * t); //Aplicar fórmula de seno
  	return salida;
}

float square(int valor, int t) //función cuadrada
{
  	float medio_periodo = (float) valor;
  	medio_periodo = medio_periodo / 2.0; //Establecer período medio para variar la función
  	int modulo = t % valor; //Asignar correctamente el tiempo en función del período
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

float triangle(int valor, int t) //función triangular
{
    float salida;
	float medio_periodo = ((float) valor) / 2.0; //Establecer período medio para variar la función
  	float modulo = (float) (t % valor); //Asignar correctamente el tiempo en función del período
  	if (modulo <= medio_periodo)
    {
        salida = (modulo) * (5.0) / (periodo);
        salida = 2.5 + salida; //2.5 por el ajuste a cero ficticio
        return salida;
    }
    else
    {
        salida = (modulo) * (5.0) / (periodo);
        salida = 5.0 + 2.5 - salida; // 5 por empezar en 5V y 2.5 por el ajuste a cero ficticio
        return salida;  
    }
}


void loop()
{
  	lectura = analogRead(A0); //lectura del valor de la entrada (potenciómetro)  
  	periodo = 1023;//periodo = map(lectura, 0, 1023, 1, 1024); // mapeo del valor de la entrada
    float voltaje = lectura * (5.0 / 1023.0); // Conversión a voltaje recibido
  	while (Serial.available() > 0) // lectura de la entrada para determinar la función a usar
  	{
  		cadena = Serial.readStringUntil(' ');
  	}
    if (periodo == 1)
    {
        salida = 2.5;
    }
    else
    {
        if (cadena == "SQUARE")
        {
            salida = square(periodo, t);
        }
        else if (cadena == "TRIANGLE")
        {
            salida = triangle(periodo, t);
        }
        else if (cadena == "SINE")
        {
            salida = sine(periodo, t);
        }
        else
        {
            salida = voltaje;
            //Serial.println("Sin funcion de entrada");
        }
    }  
  nombre = "\"Nombre\":";
  seno = "\"sine\":";
  cuadrada = "\"square\":";
  jason = "";
  nombre+="\"Dispositivo\"";
  seno+=(String)sine(periodo, t);
  cuadrada+=(String)square(periodo, t);
  jason = "{" + nombre + "," + seno + "," + cuadrada + "},";
  //salida1 = map(sine(periodo,t),0,5,0,255);
  //salida2 = map(square(periodo,t),0,5,0,255);
  
  analogWrite(10,salida1);
  analogWrite(11,salida2);
  //Serial.println(jason);
  //Serial.println((String)sine(periodo, t));
  Serial.println((String)sine(periodo, t));
  	t = t + 1;
    //delayMicroseconds(1000); //retardo de 1 microsegundos
    //delay(1); //retardo de 1 ms
}
