

# Humidity Monitoring System with Arduino, LCD 16x2, and DHT11 Sensor

This project uses an **Arduino**, **DHT11 sensor**, and a **16x2 LCD** to monitor humidity levels in an environment. The system checks if the humidity is within a defined range (maximum and minimum limits) and provides an alert if it falls outside of the acceptable range. A button is used to control the system and reset settings.

## Features:
- **Real-time humidity display** on a 16x2 LCD screen.
- **Humidity range check** to ensure the humidity is within specified limits.
- **Alert system** when the humidity falls outside the defined range.
- **Button control** for adjusting settings or resetting the system.

## Libraries Used:
- **LiquidCrystal Library**: Used to control the 16x2 LCD screen.
- **DHT Sensor Library**: Used to interface with the DHT11 sensor to read humidity data.  
  [DHT Sensor Library by Adafruit](https://github.com/adafruit/DHT-sensor-library)

## Components:
- **Arduino Board** (e.g., Arduino Uno)
- **DHT11 Humidity Sensor**
- **16x2 LCD Display**
- **Button**

## Wiring Diagram:
- Connect the **DHT11 sensor** to the appropriate pins on the Arduino.
- Wire the **16x2 LCD** to the Arduino using the correct pins.
- Connect the **button** to an input pin on the Arduino.

## How it Works:
1. The **DHT11 sensor** reads the current humidity level and sends the data to the **Arduino**.
2. The **Arduino** processes the data and checks whether the humidity is within the specified limits.
3. The **LCD** displays the current humidity and system status.
4. If the humidity exceeds the maximum or minimum limits, an alert is triggered.
5. The **button** allows for system control, such as resetting or adjusting the limits.

## Installation:
1. Install the required libraries using the Arduino Library Manager:
   - **LiquidCrystal** (pre-installed with Arduino IDE)
   - **DHT Sensor Library** by Adafruit [Link](https://github.com/adafruit/DHT-sensor-library)
   
2. Upload the code to your Arduino board and connect the components as shown in the wiring diagram.

## License:
This project is open-source and available for modification and sharing. Feel free to contribute or make improvements!

