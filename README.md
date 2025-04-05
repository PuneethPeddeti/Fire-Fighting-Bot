Fire Fighting Bot

Overview
The Fire Fighting Bot is an autonomous robot designed to detect and extinguish fires in hazardous environments. It integrates flame sensors, ultrasonic sensors for obstacle avoidance, and a water pump for fire suppression. The project aims to reduce human intervention in dangerous firefighting scenarios while maintaining high efficiency and reliability.

Key Features
- Autonomous Fire Detection: Uses flame sensors to detect fire sources.
- Obstacle Avoidance: Ultrasonic sensors enable safe navigation in cluttered environments.
- Real-time Control: Bluetooth module (HC-05) allows manual override via smartphone.
- Efficient Fire Suppression: DC water pump activates automatically upon flame detection.
- Dual Operation Modes: 
  - Auto Mode: Fully autonomous fire detection and extinguishing.
  - Manual Mode: Remote control via Bluetooth.
- Low-Cost Design: Built with affordable, widely available components.


Hardware Components

| Component               | Description                                                                 |
|-------------------------|-----------------------------------------------------------------------------|
| Arduino Nano            | Microcontroller for processing sensor data and controlling actuators.       |
| L293D IC                | Motor driver for precise control of DC motors.                              |
| Li-ion Battery          | 3.7V, 3000mAh rechargeable power source.                                    |
| DC Water Pump           | For extinguishing flames.                                                   |
| HC-05 Bluetooth         | Enables wireless communication with smartphones.                            |
| Servo Motor             | Adjusts sensor angles for optimal flame detection.                          |
| Ultrasonic Sensor       | Detects obstacles to avoid collisions.                                      |
| Flame Sensor            | Identifies fire using infrared radiation.                                   |


Setup Instructions
1. Hardware Assembly:
   - Mount sensors, motors, and water pump on the chassis.
   - Connect components as per the circuit diagram.
2. Software Setup:
   - Upload the Arduino code to the Nano.
   - Install the Bluetooth control app (e.g., Arduino Bluetooth Controller).
3. Power On:
   - Switch to Auto Mode for autonomous operation or Manual Mode via Bluetooth.

Advantages
Safety: Operates in hazardous environments without human risk.  
Scalability: Can be adapted for industrial or residential use.

Future Enhancements
- AI Integration: Improve flame detection accuracy using ML.
- Solar Power: Add solar panels for extended battery life.
- GPS Navigation: Enable mapping of fire-affected areas.


Contributors
- [Puneeth](https://github.com/username) 
- [Pasunath](https://github.com/username) 




