#include "config.h"

// WiFi Credentials
const char *ssid = "WIFI_SSID";            // Replace with your WiFi name
const char *password = "WIFI_PASSWORD";  // Replace with your WiFi password

// MQTT Broker Settings
const char *mqtt_broker = "broker.emqx.io";
const char *mqtt_topic = "emqx/esp32";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;