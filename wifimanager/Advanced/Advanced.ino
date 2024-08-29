#include <WiFiManager.h>

void setup() {
    Serial.begin(115200);
    while (!Serial);  // Wait for serial port to connect

    // Setup WiFi using WiFiManager
    WiFiManager wm;
    bool connected = wm.autoConnect("nazareno", "password");

    if (!connected) {
        Serial.println("Failed to connect to WiFi");
        delay(1000);
        // ESP.restart();
    } else {
        Serial.println("Connected to WiFi");
    }

}

void loop() {
  
}