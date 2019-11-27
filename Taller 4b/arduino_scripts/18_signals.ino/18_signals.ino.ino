double t;
int array_length = 18;
double values[18];
String json;
void setup() {
  // put your setup code here, to run once:
  t = 0.0;
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  // Cálculo de valores por iteración
  for(int i = 0; i < array_length; i++){
    values[i] = sin(t + i);  
  }
  // Formación del JSON string
  json = "{";
  for(int i = 0; i < array_length; i++){
    json = json + "\"val_" + (String) i + "\":" + (String) values[i];
    if (i < array_length - 1) {
      json = json + ",";
    }
  }
  json = json + "}";
  Serial.println(json);
  
  t = t + 0.1;
}
