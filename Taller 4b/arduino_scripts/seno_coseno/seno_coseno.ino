int t;
float sine;
float cosine;
Stringz json;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  t = 0;

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  sine = sin(t);
  cosine = cos(t);
  json = "\'sine\':" + (String) sine + "," + "\'cosine\':" + (String) cosine;
  json = "{" + json + "}";
  //  Serial.println("{\'sine\':" + (String) sin(t) + "," + "\'cosine\':" + (String) cos(t) + "}");
  Serial.println(json);
  t = t + 1;  

}
