#include <Wire.h>
#include <opt3001.h>

#define SDA_PIN 9
#define SCL_PIN 8

// Create sensor object
opt3001 sensor;

// I2C address (0x44, 0x45, 0x46, or 0x47)
const uint8_t I2C_ADDRESS = 0x44;

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("Käynnistyy...");
  
  // Initialize I2C
  Wire.begin(SDA_PIN, SCL_PIN);
  
  // Setup the OPT3001 (I2C library, I2C address)
  if (sensor.setup(Wire, I2C_ADDRESS) != 0) {
    Serial.println("Sensoria ei löytynyt.");
    return;
  }
  
  // Detect the sensor
  if (sensor.detect() != 0) {
    Serial.println("OPT3001 not detected");
    return;
  }
  
  // Configure conversion time (100ms or 800ms)
  sensor.config_set(OPT3001_CONVERSION_TIME_800MS);
  
  // Enable continuous conversion mode
  sensor.conversion_continuous_enable();
  
  Serial.println("OPT3001 initialized");
}

void loop() {
  delay(200);
  float lux;
  
  // Read illuminance in lux
  if (sensor.lux_read(&lux) == 0) {
    Serial.print("Illuminance: ");
    Serial.print(lux);
    Serial.println(" lux");
  } else {
    Serial.println("Failed to read illuminance");
  }
  
  delay(1000);
}