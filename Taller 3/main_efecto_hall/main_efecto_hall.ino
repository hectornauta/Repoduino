int hallSensorPin = 22;     
int ledPin =  13;    
int lectura = 0;          
void setup() {
  pinMode(ledPin, OUTPUT);      
  pinMode(hallSensorPin, INPUT); 
  Serial.begin(9600);    
}
void loop()
{  
  lectura = digitalRead(hallSensorPin);
  if (lectura == HIGH)
  {        
    digitalWrite(ledPin, HIGH);  
    Serial.println("APA");
  } 
  else
  {
    digitalWrite(ledPin, LOW); 
    Serial.println("NADAP");
  }
  delay(1000);
}
