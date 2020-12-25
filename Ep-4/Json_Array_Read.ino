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
    http.begin("http://jsonplaceholder.typicode.com/users/");
    int code=http.GET();

    if(code>0){
      JSONVar Arr = JSON.parse(http.getString());
      if(JSON.typeof(Arr)== "undefined"){
        Serial.println("Error Json Obj");
        return;
      }

      for(int i=0; i<Arr.length(); i++){
        JSONVar obj=Arr[i];
        Serial.println( (const char*) obj["name"]);
      }
    }
  }

  delay(60000);

}
