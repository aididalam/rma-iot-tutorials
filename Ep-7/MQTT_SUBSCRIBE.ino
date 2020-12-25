#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define mqtt_broker "broker.hivemq.com"

WiFiClient esp;
PubSubClient client(esp);

const char* ssid="ssid";
const char* password="password";

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

  client.subscribe("rma/iotTutorial/test");
  client.setCallback(callback);

}

void loop() {
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length){
  Serial.println("Message Arrived");
  Serial.println(topic);
  Serial.print("Message: ");
  for(int i=0; i< length; i++){
    Serial.print((char) payload[i]);
  }
  Serial.println();
  Serial.println("-------------");
}
