# ESP32-S3-WROOM-1-Weather-station

## Overview
A simple weather station built around the ESP32 S3 WROOM1 SoC, BME680 4-in-1 sensor and OPT3001 ambient light sensor. The device measures ambient light, temperature, humidity and air pressure, before storing the readings in a remote MySQL database through a Wi-Fi connection.

## PCB design
A custom PCB was designed and built for the device. Powered from USB-C with voltage regulation, headers for an I2C display, ESD protection and programming via usb, which the ESP32 supports natively. This is an early design and there are many possible improvements for a future update.

### Things to update/add for an upgraded version
- Battery powered. (Had to be scrapped due to time constraints)
- Add test points and diagnostics LEDs (Would have been useful when troubleshooting)
- More compact layout (Overestimated the space needed to do soldering work)
- Connect unused GPIOs to headers for future expansions
- Better isolation for sensors


Kicad render:

![Pic missing](documents/render.png?raw=true "render")


## Software
Software was developed using Arduino IDE. Communication with the sensors was implemented using I2C and libraries by Adafruit and Sitronlabs for the BME680 and OPT3001 respectively. 

Sensors are polled for measurements a set number of times and an average of the values is taken to account for incorrect readings. A Wi-Fi connection to a known hotspot is then established, and the values are sent as a JSON payload using a HTTP POST request. A node.js API stores the received values in a MySQL database.