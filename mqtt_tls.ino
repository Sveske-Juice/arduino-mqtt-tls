#include <M5StickCPlus.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

const char* SSID = "<ssid_here>";
const char* WIFI_PASS = "<pass_here>";

const char* MQTT_SERVER = "<mqtt_server_here>";
const uint16_t MQTT_PORT = 8883;
const char* MQTT_CLIENT_ID = "<unique_mqtt_id>";

WiFiClientSecure wifiClient;
PubSubClient pubSubClient(wifiClient);

void setup_wifi() {
  Serial.printf("Connecting to %s", SSID);
  WiFi.begin(SSID, WIFI_PASS);

  // Wait until WiFi is connected.
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.printf("\nSuccessfully connected to %s!\n", SSID);

  // important for connection!
  wifiClient.setInsecure();
}

void setup_mqtt() {
  pubSubClient.setServer(MQTT_SERVER, MQTT_PORT);
  pubSubClient.setCallback(mqtt_callback);
}

void reconnect_mqtt() {
  while (!pubSubClient.connected()) {
    Serial.printf("Attempting to reconnect to MQTT Broker: %s\n", MQTT_SERVER);
    if (pubSubClient.connect(MQTT_CLIENT_ID)) {
      Serial.printf("Connected!\n");
      pubSubClient.publish("testtopic", "i am connected");
    } else {
      Serial.printf("failed to connect, rc=%d\n", pubSubClient.state());
      delay(5000);
    }
  }
}

void setup() {
  setup_wifi();
  setup_mqtt();
}

void loop() {
  if (!pubSubClient.connected()) {
    Serial.println("Connection lost to MQTT Broker!");
    reconnect_mqtt();
  }
  pubSubClient.loop();
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    // handle messages here
}

