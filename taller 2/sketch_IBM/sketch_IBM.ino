/* GRUPO : SEELE
 * INTEGRANTES: Aguirre Federico, Costilla Patricio, Huerga Emanuel, Lima Paula, Pollero Emiliano 
 * MATERIA: Teoría de Control
 * AÑO: 2019
 * Correcciones al modelo de la fuente 
 * Fuente: https://www.hackster.io/Altaga/the-ultimate-ibm-watson-iot-platform-guide-eb6bfc
*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Adaptar estos valores

const char* ssid = "Raspberry-Pruebas";      // SSID de la red
const char* password = "CLAVEMAESTRA";  // contraseña

#define ORG "wv2p89" // ORG ID
#define DEVICE_ID "sensores"        //  ID dispositivo
#define DEVICE_TYPE "ESP8266"      // Tipo Dispositivo
#define TOKEN "rj4ofarJZuHqJR(E6G"         // TOKEN agregado o autogenerado

//const char* ssid = "YOUR_SSID";      // Nombre de la red WiFi
//const char* password = "YOUR_PASS";  // Contraseña de la red WiFi
//
//#define ORG "YOUR_ORGANIZATION_ID" // Nombre de la organización
//#define DEVICE_ID "Test001"        // ID del dispositivo 
//#define DEVICE_TYPE "ESP8266"      // Tipo del dispositivo
//#define TOKEN "YOUR_TOKEN"         // Token del dispositivo


char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char TopicSub[] = "iot-2/cmd/status/fmt/json"; // No modificar
char TopicPub[] = "iot-2/evt/status/fmt/json"; // No modificar

char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;
unsigned int Delay = 30;    // Tiempo que el dispositivo va a tomar para envar los datos
unsigned int i=(Delay*100);

WiFiClientSecure wifiClient;
PubSubClient client(server, 8883, NULL, wifiClient);


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
    String payload ="Hello IBM"; // La información que se va a enviar, se puede reemplazar por un JSON
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
