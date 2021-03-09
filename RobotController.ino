#include <Servo.h>
// #include <Base64.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define FREQUENCY   50

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

class Motor {
  int motorNum;
  bool shouldMoveForward = false;
  bool shouldMoveBackward = false;
  int pos = 300;
  int maxPos = 500;
  int minPos = 100;
  int motorDelay;
  
  public:
    Motor(int a, int b)
    {
      motorNum = a;
      motorDelay = b;
    }

    void moveForward() {
      shouldMoveForward = true;
    }

    void moveBackward() {
      shouldMoveBackward = true;
    }

    void stopMotor() {
      shouldMoveBackward = false;
      shouldMoveForward = false;
    }

    void loop() {
      if (shouldMoveForward && pos < maxPos) {
          pos++;
          pwm.setPWM(motorNum, 0, pos);
          delay(motorDelay);
      } else if (shouldMoveBackward && pos > minPos) {
          pos--;
          pwm.setPWM(motorNum, 0, pos);
          delay(motorDelay);
      }
    }
};

Motor elbow(15, 15);
Motor wrist(11, 15);
Motor gripper(7, 15);
Motor forearm(3, 15);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Monitor Connected");

  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
}

void loop() {
  // put your main code here, to run repeatedly:
    if (Serial.available() > 0) {
    char data = Serial.read();
    Serial.println(data);
    switch (data) {
      case 'S':
        elbow.stopMotor();
        wrist.stopMotor();
        gripper.stopMotor();
        forearm.stopMotor();
        break;
      case 'C':
        elbow.moveForward();
        break;
      case 'B':
        elbow.moveBackward();
        break;
      case 'Y':
        wrist.moveForward();
        break;
      case 'X':
        wrist.moveBackward();
        break;
      case 'G':
        gripper.moveForward();
        break;
      case 'R':
        gripper.moveBackward();
        break;
      case 'F':
        forearm.moveForward();
        break;
      case 'A':
        forearm.moveBackward();
        break;
      default:
        break;
    }
  }
  elbow.loop();
  wrist.loop();
  forearm.loop();
  gripper.loop();
}
