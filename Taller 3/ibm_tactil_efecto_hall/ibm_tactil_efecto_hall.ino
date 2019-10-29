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

const char* ssid = "Redmi4X";      // ssid
const char* password = "12345678";  // password

#define ORG "wv2p89" // ORG IBM IoT
#define DEVICE_ID "sensores"        //  id dispositivo 
#define DEVICE_TYPE "ESP8266"      // tipo de dispositivo
#define TOKEN "rj4ofarJZuHqJR(E6G"         // Token dispositivo autognerado

//----------------- Sensores ---------------------------
int  PIN_HALL = 10 ; // define  pin para sensor de efecto Hall magnético
int  PIN_TACT = 11 ; // define  pin para sensor de efecto Hall magnético
int lecturaHall ; // variable para captura del valor de sensor de efecto hall
int lecturaTacto; // variable para captura del valor de sensor de tacto
String payload;
String payload1;

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char TopicSub[] = "iot-2/cmd/status/fmt/json";
char TopicPubHall[] = "iot-2/evt/status1/fmt/json";
char TopicPubTact[] = "iot-2/evt/status2/fmt/json";
const char responseTopic[] = "iotdm-1/response";
const char manageTopic[] = "iotdevice-1/mgmt/manage";
//const char updateTopic[] = "iotdm-1/device/update";
const char rebootTopic[] = "iotdm-1/mgmt/initiate/device/reboot"; 

char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;
unsigned int Delay = 30;    // Esta vez es lo que tomará el dispositivo para enviar datos.
unsigned int i=(Delay*100);

void callback(char* topic, byte* payload, unsigned int payloadLength);

WiFiClient wifiClient;
PubSubClient client(server, 1883,callback, wifiClient);

int publishInterval = 30000; // 30 segundos
long lastPublishMillis;

//void callback(char* topic, byte* payload, unsigned int length) 
//{
//  String data="";
//  for (int i = 0; i < length; i++) 
//  {
//    data+=char(payload[i]);
//  }
//  Serial.println("Recibiendo Datos:" + data); // En este caso imprimimos los datos recibidos del sitio web.
//}

void callback(char* topic, byte* payload, unsigned int payloadLength) {
 Serial.print("Devolución de llamada invocada para el tópico:"); Serial.println(topic);

 if (strcmp (responseTopic, topic) == 0) {
   return; // solo imprime la respuesta
 }

 if (strcmp (rebootTopic, topic) == 0) {
   Serial.println("Reiniciando...");
   ESP.restart();
 }

// if (strcmp (updateTopic, topic) == 0) {
//   handleUpdate(payload);
// }
}

void setup() {
  Serial.begin(115200); 
  Serial.println();
  
  pinMode (PIN_HALL, INPUT) ;  // define el  sensor magnetico hall como entrada
  pinMode (PIN_TACT, INPUT) ;  // define el  sensor de tacto como entrada
  
  wifiConnect();
  initManagedDevice();
  client.setCallback(callback); // Aquí "conectamos" la función de devolución de llamada para suscribir la recepción de datos
}

void loop() {
 if (millis() - lastPublishMillis > publishInterval) {
   publishDataSensorHall();
   publishDataSensorTact();
   lastPublishMillis = millis();
 }

 if (!client.loop()) {
   mqttConnect();
   initManagedDevice();
 }
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

void initManagedDevice() { //maneja inicializacion de dispositivos
 if (client.subscribe("iotdm-1/response")) {
   Serial.println("Suscripto para Respuestas");
 } else {
   Serial.println("No se pudo suscribir para Respuestas");
 }

 if (client.subscribe(rebootTopic)) {
   Serial.println("Suscripto para Reiniciar");
 } else {
   Serial.println("No se pudo suscribir para Reiniciar");
 }

// if (client.subscribe("iotdm-1/device/update")) {
//   Serial.println("subscribe to update OK");
// } else {
//   Serial.println("subscribe to update FAILED");
// }

}

void publishDataSensorHall(){ //manejo de captura y envio de datos para sensor efecto hall
  lecturaHall = digitalRead(PIN_HALL);// lectura sensor hall mag.
    if (lecturaHall == HIGH)
    {       
      Serial.println("Con CAMPO");
      payload = "{\"d\":{\"Nombre\":\"" DEVICE_ID "\"";
      payload += ",\"efecto_hall\":";
      payload += lecturaHall;
      payload += "}}";      
    }else
    {
      Serial.println("Sin CAMPO");
    }
    Serial.print("Enviando datos sensor Efecto Hall: "); Serial.println(payload);      
    if (client.publish(TopicPubHall, (char*) payload.c_str())) 
    {
      Serial.println("Publicado correctamente");
    } 
    else 
    {
      Serial.println("Falla al Publicar");
    }

  }

void publishDataSensorTact(){  //manejo de captura y envio de datos para sensor de tacto
    lecturaTacto = digitalRead(PIN_TACT);// lectura sensor de tacto
    if (lecturaTacto == HIGH)
    {       
      Serial.println("Tocado");
      payload1 = "{\"d\":{\"Nombre\":\"" DEVICE_ID "\"";
      payload1 += ",\"tacto\":";
      payload1 += lecturaTacto;
      payload1 += "}}";   
    }else
    {
      Serial.println("No Tocado");
    }

    if (client.publish(TopicPubTact, (char*) payload1.c_str())) 
    {
      Serial.println("Publicado correctamente");
    } 
    else 
    {
      Serial.println("Falla al Publicar");
    }
}
