#include <ESP8266WiFi.h>
#include <Arduino_JSON.h>
#include <ESP8266HTTPClient.h>

const char* ssid="mywifi";
const char* password="12345678";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid,password);

  while(WiFi.status()!=WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting");
  }

  Serial.println("");
  Serial.println("Connected");
  Serial.println("Ip Address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  if(WiFi.status()==WL_CONNECTED){
    HTTPClient http;
    http.begin("http://jsonplaceholder.typicode.com/users/1");
    int code=http.GET();

    if(code>0){
      JSONVar obj = JSON.parse(http.getString());
      if(JSON.typeof(obj)== "undefined"){
        Serial.println("Error Json Obj");
        return;
      }
      JSONVar address=obj["address"];
      Serial.println( (const char*) address["street"]);
    }
  }

  delay(6000);

}
