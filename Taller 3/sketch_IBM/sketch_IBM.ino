/* GRUPO : SEELE
 * INTEGRANTES: Aguirre Federico, Costilla Patricio, Huerga Emanuel, Lima Paula, Pollero Emiliano 
 * MATERIA: Teoría de Control
 * AÑO: 2019
 * Correcciones al modelo de la fuente 
 * Fuente: https://www.hackster.io/Altaga/the-ultimate-ibm-watson-iot-platform-guide-eb6bfc
*/

int tactil_pin = 4;
int tactil_read;

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Adaptar estos valores

const char* ssid = "********";      // Nombre de la red WiFi
const char* password = "***********";  // Contraseña de la red WiFi

#define ORG "rq9lax" // Nombre de la organización
#define DEVICE_ID "1"        // ID del dispositivo 
#define DEVICE_TYPE "NodeMCU"      // Tipo del dispositivo
#define TOKEN "********"         // Token del dispositivo

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char TopicSub[] = "iot-2/cmd/status/fmt/json"; // No modificar
char TopicPub[] = "iot-2/evt/status/fmt/json"; // No modificar

char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;
unsigned int Delay = 10;    // Tiempo que el dispositivo va a tomar para envar los datos
unsigned int i=(Delay*100);

WiFiClient wifiClient;
PubSubClient client(server, 1883,NULL, wifiClient);


void callback(char* topic, byte* payload, unsigned int length) 
{
  String data="";
  for (int i = 0; i < length; i++) 
  {
    data+=char(payload[i]);
  }
  Serial.println("Received Data:" + data); // Se imprime la información recibida desde el sitio web.
}

void setup() {
  Serial.begin(115200); 
  Serial.println();
  // Configuración para sensor táctil
  pinMode(tactil_pin,INPUT);
  
  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }  
  Serial.println("");
  
  Serial.print("WiFi connected, IP address: "); Serial.println(WiFi.localIP());
  client.setCallback(callback); // Conectamos la función callback para recibir datos.
}

void loop() {
  client.loop();

   if (!!!client.connected()) 
   {
     Serial.print("Reconnecting client to "); 
     Serial.println(server);
     while ( !!!client.connect(clientId, authMethod, token)) 
     {
        Serial.print(".");
        delay(500); // No modificar
     }
     Serial.println();
     client.subscribe(TopicSub);  // Esto es para el callback
   }

  if(i>=(Delay*100)) 
  {
    String payload = get_tactil();
    Serial.print("Sending payload: "); Serial.println(payload);
      
    if (client.publish(TopicPub, (char*) payload.c_str())) 
    {
      Serial.println("Publish ok"); // Envio correcto
    } 
    else 
    {
      Serial.println("Publish failed"); // Fallo en el envio
    }
    i=0;
  }
  else
  {
    i++;
    delay(10);
  }
}

String get_tactil() 
{
  tactil_read = digitalRead(tactil_pin);
  if (tactil_read == HIGH){
    return "1";
  }
  return "0";
}
