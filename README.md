# <p align="center"><i>Automated Smart Home<br><sub style="font-size: 8px;">CSE-316 Microprocessors, Microcontrollers, and Embedded Systems Sessional Project</sub></i></p>



## Introduction

<b>Automated Smart Home</b>, a part of our CSE-316 sessional, is built to provide an easy solution to automate the appliances of a home. It has `Arduino Uno` as its micro-controller and consists of several modules and sensors. [Here](https://youtu.be/9xGL9s6JJDY) is a detailed demo video describing all the features.

---

## Built With

### Software
- Arduino IDE
- Microchip Studio

### Hardware
- Arduino Uno
- GSM Module
- Bluetooth Module
- Servo Motor
- Relay Module
- 16x2 LCD Display
- LDR
- DHT11 Temperature & Humidity Sensor
- Flame Sensor
- Gas Sensor
- IR Sensor
- Rain Sensor
- Motor
- LED

---

## 🌟 Features

### Automation
**1. Keep Tracking Person Count**: We've kept track how many persons are in the home right now with 2 `IR Sensors`. One IR sensor is placed at outside the door and another one at inside the door. IF anyone enters or exits, person count is automatically updated.

**2. Automated Light & Fan**: `LDR` has been used to automate the lights and `DHT11` has been used to automate the fan. When there is enough light in the house, the light is turned off automatically, and turned on otherwise. Measuring the temperature with DHT11, if the temperature is more than 28 degree celcius, the fan is turned on automatically, otherwise, it is turned off. <i>If there is nobody at home(person count=0), lights and fan are turned off.</i>

**3. Automated Window:** The Window has been made automated using `servo motor` and a `rain sensor`.

**4. Bluetooth Control:** All the appliances can be controlled with smartphone via Bluetooth. Lights, fan and window can be turned on or off using smartphone too, along with automation.

### Secuirity
**1. Fire & Gas Leakage Alert:** If there is an occurance of fire or gas leakage at home, there will be an automatic call at the owner's phone. `GSM 900A` has been used to implement this. `Flame Sensor` and `Gas Sensor` have been used to detect fire and gas leakage, respectively. <i>If there is a gas leakage, the window will get opened atomatically.</i>

**2 Rain Alert:** If it is rainning outside, a message will be sent to the owner's phone via GSM.

---

## 🚀 Getting Started

### Prerequisites

- Node.js - [Installation Guide](https://nodejs.org/en)
- MongoDB - [Installation Guide](https://www.youtube.com/watch?v=PHXhuc8MwRw)


### Installation Steps

1. Clone the repository
    ```bash
    git clone https://github.com/Mamun097/FoodFly
    ```
2. Open 2 seperate terminals to run backend and frotend

3. Run backend server
    ```bash
    cd backend
    npm install
    npm start
    ```
4. Run frontend server
    ```bash
    cd frontend
    npm install
    npm start
    ```

---

## Supervisor
- <b>Professor Dr. Mahmuda Naznin</b><br>
  - Head of the department, CSE, BUET
  - [Profile](https://cse.buet.ac.bd/faculty_list/detail/mahmudanaznin)

---
