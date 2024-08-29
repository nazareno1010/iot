#if CONFIG_FREERTOS_UNICORE
#error This example is designed to run on both cores of ESP32. Please enable both cores in menuconfig.
#endif

#define LED_PIN 2
#define BLINK_INTERVAL 1000 // milliseconds

TaskHandle_t Task1;
TaskHandle_t Task2;

// Task1: Blink LED
void blinkTask(void *parameter) {
  pinMode(LED_PIN, OUTPUT);
  
  while(1) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(BLINK_INTERVAL / 2 / portTICK_PERIOD_MS);
    Serial.println("LED ON from Core " + String(xPortGetCoreID()));
    digitalWrite(LED_PIN, LOW);
    vTaskDelay(BLINK_INTERVAL / 2 / portTICK_PERIOD_MS);
    Serial.println("LED OFF from Core " + String(xPortGetCoreID()));
  }
}

// Task2: Serial output
void serialTask(void *parameter) {
  while(1) {
    Serial.println("Hello from Core " + String(xPortGetCoreID()));
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000); // Give time for serial to initialize

  // Create tasks
  xTaskCreatePinnedToCore(
    blinkTask,   // Function to implement the task
    "BlinkTask", // Name of the task
    1000,        // Stack size in words
    NULL,        // Task input parameter
    1,           // Priority of the task
    &Task1,      // Task handle
    0            // Core where the task should run
  );

  xTaskCreatePinnedToCore(
    serialTask,   // Function to implement the task
    "SerialTask", // Name of the task
    1000,         // Stack size in words
    NULL,         // Task input parameter
    1,            // Priority of the task
    &Task2,       // Task handle
    1             // Core where the task should run
  );
}

void loop() {
  // Empty. Tasks are running on both cores
}