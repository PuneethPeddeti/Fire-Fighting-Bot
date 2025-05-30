#  Fire Fighting Bot
> An autonomous robot designed to detect and extinguish fires in hazardous environments.

---

##  Table of Contents
- [Overview](#overview)
- [Key Features](#key-features)
- [Hardware Components](#hardware-components)
- [Setup Instructions](#setup-instructions)
- [Operation Modes](#operation-modes)
- [Advantages](#advantages)
- [Future Enhancements](#future-enhancements)
- [Contributors](#contributors)

---

##  Overview

The **Fire Fighting Bot** is an autonomous robot built to detect and extinguish fire sources using onboard flame detection sensors and a water pump. It is capable of navigating complex environments using ultrasonic sensors to avoid obstacles and operates in either autonomous or manual mode via Bluetooth control. The goal is to minimize human exposure to dangerous fire situations while providing a low-cost and scalable firefighting solution.

---

##  Key Features

-  **Autonomous Fire Detection**  
  Detects flames using infrared flame sensors.

-  **Obstacle Avoidance**  
  Ultrasonic sensors allow the bot to navigate safely through cluttered areas.

-  **Real-Time Control**  
  Bluetooth module (HC-05) enables manual control via smartphone.

-  **Efficient Fire Suppression**  
  DC water pump activates automatically upon detecting flames.

-  **Dual Operation Modes**  
  - **Auto Mode:** Fully autonomous fire detection and extinguishing  
  - **Manual Mode:** Controlled manually via Bluetooth app

-  **Low-Cost Design**  
  Built using affordable and widely available components.

---

##  Hardware Components

| Component             | Description                                                                 |
|-------------------    |-----------------------------------------------------------------------------|
| **Arduino Nano**      | Microcontroller for processing sensor data and controlling actuators.       |
| **L293D IC**          | Motor driver for controlling DC motors.                                     |
| **Li-ion Battery**    | 3.7V, 3000mAh rechargeable power source.                                    |
| **DC Water Pump**     | For extinguishing flames.                                                   |
| **HC-05 Bluetooth**   | Enables wireless communication with smartphones.                            |
| **Servo Motor**       | Rotates sensors for optimal flame detection.                                |
| **Ultrasonic Sensor** | Detects obstacles to avoid collisions.                                      |
| **Flame Sensor**      | Identifies fire using infrared radiation.                                   |

---

##  Setup Instructions

###  1. Hardware Assembly
- Mount all components securely on the robot chassis.
- Connect sensors, motors, and the water pump according to the ['circuit diagram'](https://github.com/PuneethPeddeti/Fire-Fighting-Bot/blob/main/Circuit_Diagram.png).


---

###  2. Software Setup

#### Upload the Code
- Use the Arduino IDE to flash the following sketch to the **Arduino Nano**:  
  [`Fire_Fighting_Bot.ino`](https://github.com/PuneethPeddeti/Fire-Fighting-Bot/blob/main/Fire_Fighting_Bot/Fire_Fighting_Bot.ino)
- Make sure to:
  - Select the correct board (`Arduino Nano`)
  - Choose the appropriate port

---

###  3. Bluetooth App Setup
- Install the **Arduino Bluetooth Controller** app (or similar) from the Play Store or App Store.
- Pair your phone with the HC-05 module (Default PIN: `1234` or `0000`)
- Configure the app buttons to send the following commands:

| Command | Action           |
|---------|------------------|
| `F`     | Move Forward     |
| `B`     | Move Backward    |
| `L`     | Turn Left        |
| `R`     | Turn Right       |
| `P`     | Pump ON          |
| `O`     | Pump OFF         |
| `A`     | Toggle Auto Mode |

---

##  Operation Modes

###  Auto Mode
- No commands received within 2 minutes after startup.
- Robot automatically scans, detects fire, navigates, and extinguishes it.

###  Manual Mode
- Send any command from the Bluetooth app.
- Use real-time control for movement and pump activation.


---

##  Advantages

-  **Enhanced Safety**: Operates in dangerous environments without risking human lives.  
-  **Modular Design**: Easily upgradeable with additional sensors or controls.  
-  **Scalable**: Can be modified for residential, industrial, or educational use.

---

##  Future Enhancements

-  **AI Integration**: Improve fire detection and decision-making using machine learning models.
-  **Solar Power**: Add solar panels for sustainable energy and longer operation.
-  **GPS Navigation**: Enable mapping and tracking of fire-affected areas for efficient response.

---

##  Contributors

- [Puneeth](https://github.com/PuneethPeddeti)  
- [Pasunath](https://github.com/pasunath)

---




