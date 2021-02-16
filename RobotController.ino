/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
// #include <Base64.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define FREQUENCY           50

//Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

boolean shouldMoveForward = false;
boolean shouldMoveBackward = false;
int pos = 300;    // variable to store the servo position
int motorA = 15;
int motorB = 11;
int motorC = 7;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  //myservo.attach(8);  // attaches the servo on pin 8 to the servo object
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
        // pwm.setPWM(motorC, 0, pos);
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

// int inputStringLength = strlen(data);

// int decodedLength = Base64.decodedLength(data, inputStringLength);

// char decodedString[decodedLength];
// Base64.decode(decodedString, data, inputStringLength);
// Serial.println(decodedString);
