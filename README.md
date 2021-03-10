# RobotController
This is an Arduino sketch that was written to be used with a Bluetooth enabled React Native phone app:
https://github.com/stephenkridel/RobotAppBLE

This code was written to be used with a PCA9685 servo motor driver that you can find here: 
https://www.adafruit.com/product/815

The other needed factor for this code is some type of serial data source (i.e. something to send serial data to the arduino like a handheld controller, phone app, etc).
You can also just type in the data through the Serial Monitor in the Arduino IDE.

As of writing this (3/9/21), the bulk of the code is one class called Motor. The class is instantiated with 5 inputs:
1) The pin number on the PCA9685 motor driver the motor object is connected to.
2) The delay between incrementing the motor object's position when moving the motor (i.e. how much you want to slow the motor movement).
3) The serial data character that runs the motor forward.
4) The serial data character that runs the motor backward.
5) The serial data character that stops the motor.

*If you have questions, open an issue and I'll get back to you*
