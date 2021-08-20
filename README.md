# weatherStation
![WeatherStation](https://imgur.com/GxdUQAs)
This is a simple Weather Station having the following sensors:

 - Temperature sensor
 - Humidity sensor
 - Wind Speed sensor

Currently the Station uses the **NodeMCU V3**, with the embedded **ESP8266** `WiFi Module.`
For this reason, the station can only have **one** `Analog Input`, and the port is wired to the `Wind Speed sensor`.

The next version will use the `ESP32`, that has **18** Analog Inputs, yes, a lot of pins!
Having such a number of `analog inputs` i'll be able to connect a lot of analog sensors, and i'm planning to add:

 - Light sensor
 - Rain sensor
 - Barometer
 - Pyranometer 
 - CO2 sensor

---
### Parts used

 - `NodeMCU V3` with `ESP8266` **WiFi Module**
 - One `10k Ohm resistor`
 - `DHT11` Temperature/Humidity sensor (I don't like this sensor, if you are planning to build something like this, use another sensor)
 - `5V DC motor` (Used for the Wind Speed Sensor, agin, do not use this method. The next version will use a `Magnetic Sensor` to compute the wind speed)
 - `A 3D Printer` (mh, that's crucial)

---
### 3D Project
The project is available on **Thingiverse**, or there is a **Folder** where all files are uploaded.
The project consists of **two main parts**:

#### Arduino case
The case only has room for the `NodeMCU` and the `DHT11 sensor`.
Moreover, the case has an hole on the left side for the external `Wind Sensor` and a vent on the right for the `DHT11 sensor`.

#### Wind Speed Support
The wind speed sensor is supported by a 3D printed part mounted on the wall.
This part should be printed in a weather resistant material, such as PETG or ABS, don't use PLA.
Moreover, the "blades" are 3D printed too.
