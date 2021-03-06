#include <ESP8266WiFi.h>

const char* ssid="mywifi";
const char* password="12345678";
WiFiServer server(80);
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
  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client =server.available();
  if(client){
    client.println("<!DOCTYPE html>");
    client.println("Hi from <b>NodeMcu</b>");
    client.println("</html>");
  }

}
