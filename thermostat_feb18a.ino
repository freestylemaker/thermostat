#include <uTimerLib.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <WiFi.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>


WiFiClient wiFiClient;
Adafruit_MQTT_Client mqttClient(&wiFiClient, "192.168.0.104", 1883);

Adafruit_MQTT_Publish temperaturePublisher(&mqttClient, "/temperature");
Adafruit_MQTT_Publish humidityPublisher(&mqttClient, "/humidity");

DHT dht(19, DHT11);

void sendData(){
 int temperature = dht.readTemperature();
 temperaturePublisher.publish(temperature); 

 int humidity = dht.readHumidity();
 humidityPublisher.publish(humidity);  
 
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin("createch2019", "createch2019");
  delay(5000);
  TimerLib.setInterval_s(sendData, 2);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
 
}

void loop() {

 if (mqttClient.connected()) {
    mqttClient.processPackets(10000);
    mqttClient.ping();
  } else {
    mqttClient.disconnect();
    mqttClient.connect();
  } 
  
 

}
