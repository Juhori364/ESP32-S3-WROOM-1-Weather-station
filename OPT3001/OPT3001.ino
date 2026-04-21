#include <Wire.h>
#include <opt3001.h>
#include "esp_sleep.h"

// Create sensor object
opt3001 sensor;

// I2C address
const uint8_t I2C_ADDRESS = 0x44;

// Sleep time in microseconds (5 minutes = 5 * 60 * 1,000,000)
#define SLEEP_TIME 300000000ULL  

void setup() {

  Serial.begin(115200);
  delay(100); // delay to allow Serial to initialize

  Serial.println("\nESP32 woke up");

  // Initialize I2C
  Wire.begin(9, 8); // SDA = 9, SCL = 8
  
  // Initialize the sensor
  sensor.setup(Wire, I2C_ADDRESS);

  if (sensor.detect() != 0) {
    Serial.println("OPT3001 not found!");
  } else {
    Serial.println("OPT3001 detected");
  }

  // Set conversation time (100ms)
  sensor.config_set(OPT3001_CONVERSION_TIME_100MS);

  float lux;

  // Trigger single-shot conversion
  sensor.conversion_singleshot_trigger();
  
  // Wait for conversion to completee
  delay(100); 

    // Read the result
  if (sensor.lux_read(&lux) == 0) {
    Serial.print("Illuminance: ");
    Serial.print(lux);
    Serial.println(" lux");
  } else {
    Serial.println("Luku epäonnistui");
  }

  // Configure timer wakeup
  esp_sleep_enable_timer_wakeup(SLEEP_TIME);

  // Enter deep sleep
  esp_deep_sleep_start();
}

void loop() {
  // Not used because ESP32 restarts after deep sleep
}