#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define mqtt_broker "broker.hivemq.com"

WiFiClient esp;
PubSubClient client(esp);

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

  client.setServer(mqtt_broker,1883);

  while(!client.connected()){
    if(client.connect("RMATUTORIAL")){
      Serial.print("Broker Connected");
    }else{
      Serial.println("Broker not connected");
      Serial.println("Retring in 2s");
      delay(2000);
    }
  }

}

void loop() {

    const char* cars[]={"BMW", "VOLVO", "FORD", "MAZDA"};
    for(int i=0; i<4; i++){
      client.publish("rma/iotTutorials/cars", cars[i]);
      Serial.println(cars[i]);
      Serial.println("------------");
      delay(1000);
    }
}
