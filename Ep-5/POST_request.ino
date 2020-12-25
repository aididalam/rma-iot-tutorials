#include <ESP8266WiFi.h>
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
    http.begin("http://192.168.43.23/");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int code=http.POST("data=Hello");

    if(code>0){
      Serial.println(http.getString());
    }
  }

  delay(6000);

}
