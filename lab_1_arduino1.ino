/*
* GRUPO : SEELE
* INTEGRANTES: Aguirre Federico, Costilla Patricio, Huerga Emanuel, Lima Paula, Pollero Emiliano 
* MATERIA: Teoría de Control
* AÑO: 2019
*/
int valor; // espacio reservado para resguardar el valor leido de la entrada analógica
int valor_conversion; // mapeo del valor de la entrada analógica con la escala a manejar (1024 ms)
const int entrada = A0; // define la entrada analógica A0
int tiempo = 0; //para manejo en el tiempo

String cadena; // resguarda el string de entrada por el serial (tipo de función)

void setup()
{
  Serial.begin(115200); //inicializaciónd e comunicación Serial
  pinMode(entrada, INPUT); // A0 como un pin de entrada
}


float triangulo() //función triangular
{
  int periodo_temporal = tiempo % (valor_conversion);
  if (periodo_temporal>(valor_conversion/2))
    {
  		return 7.5-((periodo_temporal - 0) * (5.0 - 0.0) / (valor_conversion - 0.0) + 0.0);
    }
  else
    {
  		return 2.5+(((periodo_temporal - 0) * (5.0 - 0.0) / (valor_conversion - 0.0) + 0.0));    }
}

float seno(float numero,float periodo) //función sinusoidal
{
  return (2.5+2.5*sin(tiempo*(2* PI/(valor_conversion))));
}

int cuadrada() //función cuadrada
{
    int periodo_temporal = tiempo % (valor_conversion);
  if (periodo_temporal>(valor_conversion/2))
    {
      return(5);
    }
      else
    {
      return(0);
    }
}

void loop()
{
  valor = analogRead(entrada); //lectura del valor de la entrada (potenciómetro)  
  valor_conversion = map(valor,0,1023,0,1024); // mapero del valor de la entrada
  while(Serial.available()> 0) // lectura de la entrada para determinar la función a usar
  {
    cadena = Serial.readStringUntil(' ');
    Serial.read();
  }
  
    if (cadena == "SQUARE")
    {
      Serial.println(cuadrada());
    }
    else
    if (cadena == "TRIANGLE")
    {
      Serial.println(triangulo());
    }
    else
    if (cadena == "SINE")
    {
      Serial.println(seno(5,valor_conversion));
    }
    else
    { // si no se determina ninguna función
      Serial.println("Sin función de entrada");
    }
  
  tiempo=tiempo+1;
  delayMicroseconds(1); //retardo de 1 microsegundos
}
