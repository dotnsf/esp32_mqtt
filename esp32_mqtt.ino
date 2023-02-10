#include <WiFi.h>
#include <PubSubClient.h>

//. WiFi.
const char* ssid = "ssid";
const char* pass = "pass";

//. MQTT
const char *mqttHost = "mqtt_host";
const int mqttPort = 1883;
const char *mqttUser = "mqtt_user";
const char *mqttPass = "mqtt_pass";
WiFiClient wifiClient;
PubSubClient mqttClient( wifiClient );
const char *topic = "topic";
char *payload;


void setup() {
  // put your setup code here, to run once:

  Serial.begin( 115200 );

  //. connect WiFi
  connectWiFi();

  //. connect MQTT
  connectMQTT();
}

void loop() {
  // put your main code here, to run repeatedly:

  //. 送信処理
  payload = "Hello, World.";
  mqttClient.publish( topic, payload );
  delay( 1000 );

  //. WiFi
  if( WiFi.status() == WL_DISCONNECTED ){
    connectWiFi();
  }

  //. MQTT
  if( !mqttClient.connected() ){
    connectMQTT();
  }
  mqttClient.loop();
}


//. Connect WiFi
void connectWiFi(){
  WiFi.begin( ssid, pass );
  Serial.print( "WiFi connecting..." );
  while( WiFi.status() != WL_CONNECTED ){
    Serial.print( "." );
    delay( 100 );
  }
  Serial.print( " connected." );
  Serial.println( WiFi.localIP() );
}

//. Connect MQTT
void connectMQTT(){
  mqttClient.setServer( mqttHost, mqttPort );
  while( !mqttClient.connected() ){
    Serial.println( "Connecting to MQTT..." );
    String clientId = "ESP32-" + String( random( 0xffff ), HEX );
    if( mqttClient.connect( clientId.c_str(), mqttUser, mqttPass ) ){
      Serial.println( "connected" );
    }
    delay( 1000 );
    randomSeed( micros() );
  }
}
