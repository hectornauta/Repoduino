/* GRUPO : SEELE
 * INTEGRANTES: Aguirre Federico, Costilla Patricio, Huerga Emanuel, Lima Paula, Pollero Emiliano 
 * MATERIA: Teoría de Control
 * AÑO: 2019
 * Descripción:  Envio de datos de los sensores Keyes ky-024 y ky-036 utilizando la plataforma de IBM Watson Cloud, utilizando hub de IoT. 
 * Fuente Base: https://www.hackster.io/Altaga/the-ultimate-ibm-watson-iot-platform-guide-eb6bfc
*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//-------- credenciales WIFI y IBM Watson -----------------------

const char* ssid = "Raspberry-Pruebas";      // ssid
const char* password = "CLAVEMAESTRA";  // password

#define ORG "wv2p89" // ORG IBM IoT
#define DEVICE_ID "sensores"        //  id dispositivo 
#define DEVICE_TYPE "ESP8266"      // tipo de dispositivo
#define TOKEN "wD7g(xz5HUfeqDRPGX"         // Token dispositivo autognerado

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

int tactil_pin = 4;
int tactil_read;
int hall_pin = 5;
int hall_read;

int publishInterval = 10000; // intervalo de lectura: 10 segundos
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

  pinMode(tactil_pin,INPUT);
  pinMode(hall_pin,INPUT);  

  wifiConnect();
  
}

void loop() {
  client.loop();
  mqttConnect();
  
  if (millis() - lastPublishMillis > publishInterval) 
  {
    String valueTact = get_tactil();
    String valueHall = get_hall();
    String payload = "{\"d\":{\"Nombre\":\"" DEVICE_ID "\"";
    payload += ",\"tacto\":";
      payload += valueTact;
      payload += ",\"hall\":";
      payload += valueHall;
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
  }

}

String get_tactil()// obtención del valor leido por el sensor de tacto 
{
  tactil_read = digitalRead(tactil_pin);
  if (tactil_read == HIGH){
    Serial.println(hall_read); 
    return "1";
  }
  return "0";
}

String get_hall()// obtención del valor leido por el sensor de efecto hall magnetico 
{
  hall_read = digitalRead(hall_pin);
  if (hall_read == HIGH){
    Serial.println(hall_read);    
    return "1";
  }
  return "0";
}
