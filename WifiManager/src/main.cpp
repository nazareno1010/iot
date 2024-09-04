#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

// WiFi Manager example, a code to connect your microcontroller
// to WiFi without hardcode credentials

// Get MAC address without colons
String getMAC() {
    String mac = WiFi.macAddress();
    mac.replace(":", "");
    return mac;
}

void setup() {
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

}

void loop() {
    // put your main code here, to run repeatedly:   
}