#include <ESP8266WiFi.h>

const char* ssid="aidid";
const char* password="aididalam";
WiFiServer server(80);
int led=D2;
void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
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
    String request=client.readStringUntil('\r');
    Serial.println(request +"check: "+request.indexOf("on"));

    if(request.indexOf("on")!=-1){
      digitalWrite(led,HIGH);
    }else if(request.indexOf("off")!=-1){
      digitalWrite(led,LOW);
    }


    client.println("<!DOCTYPE html>");
    client.println("<head>");
    client.println("<link rel=\"icon\" href=\"data\":;");
    client.println("</head>");
    client.println("<a href=\"/on\"><button>On</button></a>");
    client.println("<a href=\"/off\"><button>Off</button></a>");
    client.println("</html>");
  }

}
