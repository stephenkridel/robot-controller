#include <Servo.h>
// #include <Base64.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define FREQUENCY   50

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

class Motor {
  int motorNum; // pin on the PCCA9685 the motor is connected to
  bool shouldMoveForward = false;
  bool shouldMoveBackward = false;
  const int initialPosition = 300;
  int pos = initialPosition;
  const int maxPos = 450;
  const int minPos = 100;
  int motorDelay; // speeds up and slows down movement. Recommended between 10 to 25.
  char forwardInput;
  char backwardInput;
  char stopInput;
  char prevState;
  
  public:
    Motor(int a, int b, char c, char d, char e)
    {
      motorNum = a;
      motorDelay = b;
      forwardInput = c;
      backwardInput = d;
      stopInput = e;
    }

    void moveToPosition(int positionToMoveTo) {
      if (positionToMoveTo > minPos && positionToMoveTo < maxPos) {
        pwm.setPWM(motorNum, 0, positionToMoveTo);
      }
    }

    void setInitialPosition() {
      pwm.setPWM(motorNum, 0, initialPosition);
    }

    void loop(char data) {
      if (data != prevState) {
        if (data == forwardInput){
          moveForward();
        } else if (data == backwardInput){
          moveBackward();
        } else if (data == stopInput) {
          stopMotor();
        }
      }
      runMotor();
      prevState = data;
    }

  private:
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

    void runMotor() {
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

Motor elbow(15, 15, 'C', 'B', 'S');
Motor wrist(11, 15, 'X', 'Y', 'S');
Motor gripper(7, 5, 'G', 'R', 'S');
Motor forearm(3, 5, 'F', 'A', 'S');

Motor motorArr[4] = {elbow, wrist, gripper, forearm};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Monitor Connected");

  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);

  Serial.println(sizeof(motorArr)/sizeof(motorArr[0]));

  for (int i = 0; i < sizeof(motorArr)/sizeof(motorArr[0]); i++) {
    motorArr[i].setInitialPosition();
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  char data;
  if (Serial.available() > 0) {
    data = Serial.read();
    Serial.println(data);
  }

  for (int i = 0; i < sizeof(motorArr)/sizeof(motorArr[0]); i++) {
    motorArr[i].loop(data);
  }
}
