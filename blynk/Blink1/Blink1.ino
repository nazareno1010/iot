#define LED_PIN 2
#define BLINK_INTERVAL 1000  // Time in milliseconds

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("LED Blink program started");
}

void loop() {
  static unsigned long previousMillis = 0;
  static bool ledState = false;
  
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= BLINK_INTERVAL) {
    previousMillis = currentMillis;
    ledState = !ledState;
    
    digitalWrite(LED_PIN, ledState);
    Serial.println(ledState ? "LED ON" : "LED OFF");
  }
}