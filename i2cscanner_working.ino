// wire-kirjaston dokumentointi, jonka pohjalta tämä koodi on kirjoitettu: https://docs.arduino.cc/language-reference/en/functions/communication/wire/

#include <Wire.h>

#define SDA_PIN 9   // nämä pinnit pitäisi olla jo entuudestaan SCL ja SDA linjoja meidän moduulilla
#define SCL_PIN 8

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("I2C scanner start.");

  Wire.begin(SDA_PIN, SCL_PIN);   // wire-kirjaston initialisointi. Ottaa muuttujana 7-bitin osoitteen.

  Wire.setClock(100000);    // 100kHz. Asetetaan taajuus, jolla i2c laitteet kommunikoivat. 
}

void loop() {
  int address = 0;
  int count = 0;
  byte error; // virhekoodi -muuttuja

  Serial.println("Scanning...");

  for (address = 1; address < 127; address++) {   // käydään kaikki 1-126 osoitteet läpi, 0 ja 127 ei pitäisi olla valideja osotteita i2c:ta käyttäville sensoreille
    Wire.beginTransmission(address);              // koitetaan ottaa yhteys jokaiseen i2c osoitteeseen
    error = Wire.endTransmission();               // error muuttujaan talletetaan vastaus, mikä i2c linjalta tulee

    if (error == 0) {
      Serial.print("Found device at 0x");         // tarkistetaan mikä error koodi tuli
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println();
      count++;
    } else if (error == 4) {
      Serial.print("Unknown error at 0x");
      Serial.println(address, HEX);
    }
  }

  if (count == 0) {                               // jos ei erroreita, eikä vastauksia, niin laitteita ei löydy ollenkaan
    Serial.println("No I2C devices found");
  } else {
    Serial.println("Done");
  }

  delay(3000);
}