#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"
#include <iostream>
#include <WiFiManager.h>

WiFiClient espClient;
PubSubClient mqtt_client(espClient);

int main() {

    // MQTT Broker Settings
    std::cout << "password: " << mqtt_broker << std::endl;
    std::cout << "password: " << mqtt_topic << std::endl;
    std::cout << "password: " << mqtt_username << std::endl;
    std::cout << "password: " << mqtt_password << std::endl;
    std::cout << "password: " << mqtt_port << std::endl;
    
    return 0;
}

// Get MAC address without colons
String getMAC() {
    String mac = WiFi.macAddress();
    mac.replace(":", "");
    return mac;
}

// Function Declarations
void connectToWiFi();

void connectToMQTT();

void mqttCallback(char *mqtt_topic, byte *payload, unsigned int length);

void setup() {
    Serial.begin(115200);
    connectToWiFi();
    mqtt_client.setServer(mqtt_broker, mqtt_port);
    mqtt_client.setKeepAlive(60);
    mqtt_client.setCallback(mqttCallback); // Corrected callback function name
    connectToMQTT();
}

void connectToMQTT() {
    while (!mqtt_client.connected()) {
        String client_id = "esp32-client-" + String(WiFi.macAddress());
        Serial.printf("Connecting to MQTT Broker as %s.....\n", client_id.c_str());
        if (mqtt_client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Connected to MQTT broker");
            mqtt_client.subscribe(mqtt_topic);
            mqtt_client.publish(mqtt_topic, "Hi EMQX I'm ESP32 ^^"); // Publish message upon successful connection
        } else {
            Serial.print("Failed, rc=");
            Serial.print(mqtt_client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void mqttCallback(char *mqtt_topic, byte *payload, unsigned int length) {
    Serial.print("Message received on mqtt_topic: ");
    Serial.println(mqtt_topic);
    Serial.print("Message: ");
    for (unsigned int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println("\n-----------------------");
}

void loop() {

    Serial.begin(115200);
    while (!Serial);  // Wait for serial port to connect

    // Setup WiFi using WiFiManager
    WiFiManager wm;
    String SSID = "ESP32-" + getMAC();
    bool connected = wm.autoConnect(SSID.c_str(), "password");

    if (!connected) {
        Serial.println("Failed to connect to WiFi");
        delay(100);
        ESP.restart(); // Restart ESP32 to begin again
    } else {
        Serial.println("Connected to WiFi");
    }

    // Connecting to MQTT Broker

    if (!mqtt_client.connected()) {
        connectToMQTT();
    }
    mqtt_client.loop();
}