
#include <Servo.h>
// #include <Base64.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define FREQUENCY           50

bool shouldMoveForward = false; // variable to decide if motor should run on main loop
bool shouldMoveBackward = false; // variable to decide if motor should run on main loop
int pos = 300;    // variable to store the servo position
int motorA = 15; // denotes the pin on the PCA9685 that the motor is connected to
int motorB = 11;
int motorC = 7;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(9600);
  Serial.print("Monitor Connected");

  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
}

void loop() {
  if (Serial.available() > 0) {

    char data = Serial.read();

    Serial.println(data);
    switch (data) {
      case 'C':
        pwm.setPWM(motorA, 0, 500);
        break;
      case'B':
        pwm.setPWM(motorA, 0, 100);
        break;
      case 'X':
        pwm.setPWM(motorB, 0, 500);
        break;
      case 'Y':
        pwm.setPWM(motorB, 0, 100);
        break;
      case 'S':
        pwm.setPWM(motorA, 0, 300);
        pwm.setPWM(motorB, 0, 300);
        break;
      case 'G':
        shouldMoveBackward = true;
        break;
      case 'R':
        shouldMoveForward = true;
        break;
      case 'I':
        shouldMoveBackward = false;
        shouldMoveForward = false;
        break;
      default:
        break;
    }
  }
  if (shouldMoveForward && pos < 500) {
    pos += 1;
    pwm.setPWM(motorC, 0, pos);
    delay(5);
  }
  if (shouldMoveBackward && pos > 100) {
    pos -= 1;
    pwm.setPWM(motorC, 0, pos);
    delay(5);
  }
}

// Base64 decoding:
// int inputStringLength = strlen(data);
// int decodedLength = Base64.decodedLength(data, inputStringLength);
// char decodedString[decodedLength];
// Base64.decode(decodedString, data, inputStringLength);
// Serial.println(decodedString);
