#include <WiFiS3.h>
#include <MQTTClient.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"

Adafruit_SHT31 sht31 = Adafruit_SHT31();

const char* WIFI_SSID     = "Guied";
const char* WIFI_PASSWORD = "guiedeiei";
IPAddress staticIP(172,20,10,10);       // IP ที่กำหนดเอง
IPAddress gateway(172,20,10,1);         // IP ของ iPhone (ดูจาก Pi)
IPAddress subnet(255,255,255,240);

const char* MQTT_BROKER   = "172.20.10.2"; // IP ของ Raspberry Pi
const int   MQTT_PORT     = 1883;
const char* MQTT_CLIENTID = "uno-r4-sht31";
const char* MQTT_TOPIC    = "kmitl/iot/66070273/sensor";

WiFiClient net;
MQTTClient client(256);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  if (!sht31.begin(0x44)) {
    Serial.println("Couldn't find SHT31 sensor!");
    while (1);
  }

  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ WiFi connected!");
  Serial.print("IP address: "); Serial.println(WiFi.localIP());

  client.begin(MQTT_BROKER, MQTT_PORT, net);
  while (!client.connect(MQTT_CLIENTID)) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ MQTT connected!");
}

void loop() {
  client.loop();
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();
  if (!isnan(t) && !isnan(h)) {
    char payload[128];
    snprintf(payload, sizeof(payload), "{\"temp\":%.2f,\"humidity\":%.2f}", t, h);
    client.publish(MQTT_TOPIC, payload);
    Serial.println(payload);
  }
  delay(2000);
}
