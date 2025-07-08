# SmartAIR Room Filter

A compact IoT-based system to monitor indoor air quality and control air filtration automatically or manually through a mobile app.

---

## 📝 Project Details

* **Microcontroller:** ESP32
* **Display:** 0.96-inch OLED (I2C)
* **Sensors:**

  * **MQ135 Gas Sensor** (Air Quality)
  * **DHT11 Sensor** (Temperature & Humidity)
* **Actuator:** DC Fan controlled via Relay
* **Connectivity:** Blynk IoT Mobile App (Wi-Fi)

---

## 🚀 Features

* Real-time **AQI, Temperature, Humidity** monitoring
* **OLED Display** for on-device feedback
* **Automatic Fan Control** when AQI > 150
* **Manual Fan Control** via Blynk Mobile App button (V0)
* Mobile dashboard shows:

  * AQI (V1)
  * Temperature (V2)
  * Humidity (V3)
  * AQI Category (V4)
  * Fan Status (V5)

---

## 📌 Wiring Summary

| Component      | ESP32 Pin                            |
| -------------- | ------------------------------------ |
| **OLED SDA**   | GPIO 21                              |
| **OLED SCL**   | GPIO 22                              |
| **MQ135 AOUT** | GPIO 34                              |
| **DHT11 DATA** | GPIO 25                              |
| **Relay IN1**  | GPIO 15                              |
| **Relay VCC**  | 5V                                   |
| **Relay GND**  | GND                                  |
| **Fan**        | Powered via Relay + External Battery |

---

## 🔌 Power

* ESP32, OLED, Sensors: Powered via USB or 5V
* Fan: Powered through relay by 6V-9V battery pack

---

## 🛡 Why Relay?

* The relay safely switches higher current fan using low-power ESP32 signals.
* Protects ESP32 from high current and voltage surges.

---

## 🔄 Future Upgrade: Variable Fan Speed (PWM + MOSFET)

* Planned for future versions.
* Requires N-Channel MOSFET, flyback diode, and ESP32 PWM pin.

---

## 📲 Blynk Setup

* V0: Button (Fan ON/OFF)
* V1: AQI
* V2: Temperature
* V3: Humidity
* V4: AQI Category
* V5: Fan Status

---

## 💡 Conclusion

SmartAIR Room Filter is an easy-to-build, scalable project for smart indoor air quality management, with both autonomous and remote control capabilities.
