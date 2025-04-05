#include <Servo.h>

// Pin Definitions
const int motorPin1 = 8;
const int motorPin2 = 7;
const int motorPin3 = 6;
const int motorPin4 = 5;
const int enablePinA = 9;
const int enablePinB = 10;
const int trigPin = 2;
const int echoPin = 3;
const int flamePin = 4;
const int servoPin = 12;
const int pumpPin = 13;

// System State
Servo waterservo;
char command;
bool autoModeActive = false;
bool waterPumpActivated = false;

// Timing Control
unsigned long lastReceivedTime = 0;
unsigned long flameDetectedTime = 0;
unsigned long commandCheckTime = 0;
const unsigned long COMMAND_CHECK_INTERVAL = 200; 

// Servo Control
int servoAngle = 0;
unsigned long servoPreviousMillis = 0;
const int servoInterval = 15;

void setup() {
  // Initialize motor control pins
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(enablePinA, OUTPUT);
  pinMode(enablePinB, OUTPUT);

  // Initialize sensors
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(flamePin, INPUT);

  // Initialize actuators
  pinMode(pumpPin, OUTPUT);
  waterservo.attach(servoPin);

  // Start serial communication
  Serial.begin(9600);
  lastReceivedTime = millis();
}

void loop() {
  //check for new commands
  checkForCommands();

  if (autoModeActive) {
    runAutoMode();
  } else {
    runManualMode();
  }

  updateServo();
  checkFlame();
}

void checkForCommands() {
  if (Serial.available()) {
    command = Serial.read();
    lastReceivedTime = millis();
    
    switch (command) {
      case 'M': 
        autoModeActive = false;
        stopMotors();
        break;
      case 'A':
        autoModeActive = true;
        break;
    }
  }
}

void runAutoMode() {
  // Check for manual override every COMMAND_CHECK_INTERVAL
  if (millis() - commandCheckTime > COMMAND_CHECK_INTERVAL) {
    commandCheckTime = millis();
    if (checkForManualOverride()) return;
  }

  if (flameDetected()) {
    handleFire();
    if (checkForManualOverride()) return;
  } else {
    handleNavigation();
  }
}

bool checkForManualOverride() {
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == 'M') {
      autoModeActive = false;
      emergencyStop();
      return true;
    }
  }
  return false;
}

void handleFire() {
  activatePump();
  stopMotors();
  
  // Continue checking for manual override
  unsigned long fireStartTime = millis();
  while (millis() - fireStartTime < 5000) { // Fight fire for 5 seconds
    if (checkForManualOverride()) return;
    delay(100);
  }
}

void handleNavigation() {
  if (obstacleDetected()) {
    avoidObstacle();
  } else {
    moveForward();
    
    // Check for override while moving
    unsigned long moveStart = millis();
    while (millis() - moveStart < 1000) { // Move for 1 second intervals
      if (checkForManualOverride()) return;
      delay(100);
    }
  }
}

void avoidObstacle() {
  stopMotors();
  float leftDist = scanDirection(true); // Scan left
  float rightDist = scanDirection(false); // Scan right
  
  if (leftDist > rightDist) {
    turnLeft();
    delay(500);
  } else {
    turnRight();
    delay(500);
  }
}

float scanDirection(bool left) {
  if (left) turnLeft();
  else turnRight();
  
  delay(300);
  stopMotors();
  return getDistance();
}

void runManualMode() {
  if (Serial.available()) {
    command = Serial.read();
    lastReceivedTime = millis();
    
    switch (command) {
      case 'F': 
        if (!obstacleDetected()) moveForward();
        else stopMotors();
        break;
      case 'B': moveBackward(); break;
      case 'L': turnLeft(); break;
      case 'R': turnRight(); break;
      case 'S': stopMotors(); break;
      case 'P': activatePump(); break;
      case 'O': deactivatePump(); break;
    }
  }
  
  // Auto switch to auto-mode after 2 minutes of inactivity
  if (millis() - lastReceivedTime > 120000) {
    autoModeActive = true;
  }
}

// Sensor and Actuator Functions
float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  unsigned long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

bool obstacleDetected() {
  return getDistance() < 30;
}

bool flameDetected() {
  return digitalRead(flamePin) == HIGH;
}

void checkFlame() {
  if (flameDetected()) {
    if (flameDetectedTime == 0) {
      flameDetectedTime = millis();
    } else if (millis() - flameDetectedTime > 5000 && !waterPumpActivated) {
      activatePump();
    }
  } else {
    flameDetectedTime = 0;
    if (!autoModeActive) deactivatePump();
  }
}

void activatePump() {
  digitalWrite(pumpPin, HIGH);
  waterPumpActivated = true;
}

void deactivatePump() {
  digitalWrite(pumpPin, LOW);
  waterPumpActivated = false;
}

void updateServo() {
  if (waterPumpActivated && millis() - servoPreviousMillis >= servoInterval) {
    servoAngle = (servoAngle + 1) % 180;
    waterservo.write(servoAngle);
    servoPreviousMillis = millis();
  }
}

void emergencyStop() {
  stopMotors();
  deactivatePump();
}

// Motor Control Functions
void moveForward() {
  digitalWrite(enablePinA, HIGH);
  digitalWrite(enablePinB, HIGH);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}

void moveBackward() {
  digitalWrite(enablePinA, HIGH);
  digitalWrite(enablePinB, HIGH);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}

void turnLeft() {
  digitalWrite(enablePinA, HIGH);
  digitalWrite(enablePinB, HIGH);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}

void turnRight() {
  digitalWrite(enablePinA, HIGH);
  digitalWrite(enablePinB, HIGH);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}

void stopMotors() {
  digitalWrite(enablePinA, LOW);
  digitalWrite(enablePinB, LOW);
}