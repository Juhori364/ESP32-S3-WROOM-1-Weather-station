#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <opt3001.h>

#define SDA_PIN 9
#define SCL_PIN 8

Adafruit_BME680 bme;
opt3001 sensor;

const uint8_t I2C_ADDRESS = 0x44;

//float delayTemp = 0.0;
//float actualTemp = 0.0;
//float maxRise = 1.0;
//float maxFall = 1.0;
float tempOffSet = 4.2;   // mitattu labrassa lämpömittarilla, sekä verrattu ulkolämpötilaan kotona olevaa digitaalista lämpömittaria vasten. Ulkona lämpötila heittää jopa kolmella asteella, eli ulkona offset voisi olla 4.2 astetta.

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("BME688 lämpötilahälytys käynnistyy...");
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!bme.begin(0x76)) {
    Serial.println("Sensoria ei löytynyt.");
    while (1);
  }

  if (sensor.setup(Wire, I2C_ADDRESS) !=0) {
    Serial.println("Sensoria ei löytynyt.");
    while (1);
  }

  sensor.config_set(OPT3001_CONVERSION_TIME_800MS);

  sensor.conversion_continuous_enable();

  Serial.println("Molemmat sensorit alustettu!");

  bme.setTemperatureOversampling(BME680_OS_4X);   // tätä vähän pienennetty 8 -> 4, saadaan vähemmän kohinaa ja käytetään vähemmän virtaa, jos tämän laitteen haluaisi toimimaan akulla
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  //bme.setGasHeater(320, 150); // lämpötila, ms

  delay(2000);

  /*Serial.print("Annetaan sensorin asettua huoneenlämpöön.");
  for (int i = 0; i < 10; i++) {                // labrassa mitattu, että sensorilla voi mennä jopa 5min ennenkuin se asettuu huoneenlämpöön, tätä funktiota voi käyttää halutessa, ennenkuin oikea loop-mittaus käynnistyy 
    delayTemp = bme.readTemperature();
    Serial.print(delayTemp);
    Serial.println(" °C");
    delay(10000);
  }
  Serial.print("Sensori asettunut lämpötilaan: ");
  Serial.println(delayTemp);
  Serial.println(" °C");
  baseSet = true;
  actualTemp = delayTemp - tempOffSet;
  Serial.print(actualTemp);*/
}

void loop() {
  float rawTemp;
  float temp;
  float tempSum = 0.0;
  float sendTemp = 0.0;
  float hum;
  float humSum = 0.0;
  float sendHum = 0.0;
  float pres;
  float presSum = 0.0;
  float sendPres = 0.0;
  float lux;
  float luxSum = 0.0;
  float sendLux = 0.0;

  for (int i = 0; i < 30; i++) {
  rawTemp = bme.readTemperature();
  temp = rawTemp - tempOffSet;
  hum = bme.readHumidity();
  pres = bme.readPressure();

  Serial.print("RawTemp: ");
  Serial.print(rawTemp);
  Serial.println("°C");

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.println(" °C");
  tempSum += temp;

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println(" %");
  humSum += hum;

  Serial.print("Pressure: ");
  Serial.print(pres);
  Serial.println(" pascal");
  presSum += pres;

  if (sensor.lux_read(&lux) == 0) {
    Serial.print("Illuminance: ");
    Serial.print(lux);
    Serial.println(" lux");
    luxSum += lux;
  }

  delay(2000);
}

Serial.println("ULOS LOOPISTA");
/*Serial.println(tempSum);
Serial.println(humSum);
Serial.println(presSum);
Serial.println(luxSum);*/

sendTemp = tempSum / 30.0;
sendHum  = humSum / 30.0;
sendPres = (presSum / 30.0) / 100.0;    // muutetaan tässä hehtopascaleiksi
sendLux  = luxSum / 30.0;

// LÄHETETTÄVÄT ARVOT
Serial.print("Temperature: ");
Serial.print(sendTemp);
Serial.println(" °C");
Serial.print("Humidity: ");
Serial.print(sendHum);
Serial.println(" %");
Serial.print("Air pressure: ");
Serial.print(sendPres);
Serial.println(" hPa");
Serial.print("Illuminance: ");
Serial.print(sendLux);
Serial.println(" lux");


  /*if (!stabilized) {
    waitForStableTemperature();
    return;
  }*/

  /*if (sensor.lux_read(&lux) == 0) {
    Serial.print("Valaistusvoimakkuus: ");
    Serial.print(lux);
    Serial.println(" lux.");
  }*/

  //Serial.print("Kaasuvastus: ");
  //Serial.print(gasRes);
  //Serial.println(" Ohm");

  /*Serial.print("Lämpötila: ");
  Serial.print(temp);
  Serial.println(" °C");

  Serial.print("Kosteus: ");
  Serial.print(hum);
  Serial.println(" %");*/

  /*Serial.print("Ilmanpaine: ");
  Serial.print(pres / 100.0);
  Serial.println(" hPa");*/


  /*if (baseSet) {
    float diffTemp = temp - actualTemp;

    if (diffTemp >= maxRise) {
      Serial.println("HUOM! Lämpötila on noussut ");
      Serial.print(maxRise);
      Serial.print(" °C verran.");
      // alkuarvon resetointi
      actualTemp = temp;
      Serial.print("Uusi delayTemp: ");
      Serial.println(actualTemp);
    }
    else if (diffTemp <= -maxFall) {
        Serial.println("HUOM! Lämpötila on laskenut: ");
        Serial.print(maxFall);
        Serial.print(" °C verran.");
        actualTemp = temp;
        Serial.print("Uusi delayTemp: ");
        Serial.println(actualTemp);
    }
  }*/
  

  //delay(2000);
}


