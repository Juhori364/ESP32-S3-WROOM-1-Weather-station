#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64


#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define SDA_PIN 9
#define SCL_PIN 8
Adafruit_BME680 bme;

const char* ssid = "Juho's Galaxy A54 5G";
const char* password = "hökäle04";


const char* serverName = "http://192.168.36.77:3000/upload";


unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
 

  if (!bme.begin(0x76)) {
    Serial.println("Sensoria ei löytynyt.");
    while (1);
  }

  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // lämpötila, ms

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  float temp = bme.readTemperature();
 
  Serial.print("Lämpötila: ");
  Serial.print(temp);
  Serial.println(" °C");

  char buf[16];
  dtostrf(temp, 6, 2, buf);

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(buf);

  display.display(); // Always call this to push the buffer to the screen

  delay(1000);








  if ((millis() - lastTime) > timerDelay) {

    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
    
      http.begin(client, serverName);
      
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
      
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"temperature\":24.25,\"humidity\":49.54}");
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}