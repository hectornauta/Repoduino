/* GRUPO : SEELE
 * INTEGRANTES: Aguirre Federico, Costilla Patricio, Huerga Emanuel, Lima Paula, Pollero Emiliano 
 * MATERIA: Teoría de Control
 * AÑO: 2019
 * Descripción:  Envio de datos de los sensores Keyes ky-024 y ky-036 utilizando la plataforma de IBM Watson Cloud, utilizando hub de IoT. 
 * Fuente Base: https://www.hackster.io/Altaga/the-ultimate-ibm-watson-iot-platform-guide-eb6bfc
*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

int valor = 64;
int t;
//-------- credenciales WIFI y IBM Watson -----------------------

const char* ssid = "PCostilla";             // ssid
const char* password = "kikeputo";          // password

#define ORG "rq9lax"                        // ORG IBM IoT
#define DEVICE_ID "ondas"                //  id dispositivo 
#define DEVICE_TYPE "ESP8266"               // tipo de dispositivo
#define TOKEN "Vv42Dwo&HNy4g?3(jV"          // Token dispositivo autognerado

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char TopicSub[] = "iot-2/cmd/status/fmt/json"; // topico suscripto
char TopicPub[] = "iot-2/evt/status/fmt/json"; //tópico a publicar 

char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;
//unsigned int Delay = 10;    // Tiempo que el dispositivo va a tomar para envar los datos
//unsigned int i=(Delay*100);

WiFiClient wifiClient;
PubSubClient client(server, 1883,NULL, wifiClient);

//----------------- Sensores ---------------------------
int publishInterval = 1000; // intervalo de lectura: 10 segundos
long lastPublishMillis;

void callback(char* topic, byte* payload, unsigned int length) 
{
  String data="";
  for (int i = 0; i < length; i++) 
  {
    data+=char(payload[i]);
  }
  Serial.println("Recibiendo datos:" + data); // Se imprime la información recibida desde el sitio web.
}

void wifiConnect() {// maneja la conexión a la red WiFi
  Serial.print("Conectando a "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }  
  Serial.println("");  
  Serial.print("WiFi conectado, IP: "); Serial.println(WiFi.localIP());
}

void mqttConnect() {// maneja la conexion por MQTT
 if (!!!client.connected()) 
   {
     Serial.print("Reconectando cliente a "); 
     Serial.println(server);
     while ( !!!client.connect(clientId, authMethod, token)) 
     {
        Serial.print(".");
        delay(500);
     }
     Serial.println();
     client.subscribe(TopicSub); 
   }
}


void setup() {
  Serial.begin(115200); 
  Serial.println();
  t = 0;
  wifiConnect();
  
}

void loop() {
  client.loop();
  mqttConnect();
  
  if (millis() - lastPublishMillis > publishInterval) 
  {
    String valueSine = sine(valor, t);
    String valueSquare = square(valor, t);
    String payload = "{\"d\":{\"Nombre\":\"" DEVICE_ID "\"";
    payload += ",\"sine\":";
      payload += valueSine;
      payload += ",\"square\":";
      payload += valueSquare;
      payload += "}}";
    Serial.print("Sending payload: "); Serial.println(payload);
      
    if (client.publish(TopicPub, (char*) payload.c_str())) 
    {
      Serial.println("Publicado correctamente"); // Envio correcto
    } 
    else 
    {
      Serial.println("Problemas al prublicar"); // Fallo en el envio
    }
    lastPublishMillis = millis();
    t = t + 1;
  }
  
}

String sine(int valor, int t) //función sinusoidal
{
	float omega = (2 * PI) / valor; //Determinar valor Omega de la función seno
  	float salida = 2.5 + 2.5 * sin(omega * t); //Aplicar fórmula de seno
  	return (String) salida;
}

String square(int valor, int t) //función cuadrada
{
  	float medio_periodo = (float) valor;
  	medio_periodo = medio_periodo / 2.0; //Establecer período medio para variar la función
  	int modulo = t % valor; //Asignar correctamente el tiempo en función del período
  	float modulo_float = (float) modulo;
  	if (modulo_float <= medio_periodo)
    {
    	float salida = 5.0;
    	return (String) salida;
    }
  	else
  	{
      float salida = 0.0;
    	return (String) salida;
    }
}
