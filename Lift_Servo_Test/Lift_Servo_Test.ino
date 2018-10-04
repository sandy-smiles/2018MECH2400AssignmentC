#include <Servo.h>

#define SERIAL_SPEED 9600

// Define the Servos
Servo servoA;
Servo servoB;

// Define servo control pins as variables so that they can be changed.
int servoA_control = 7;
int servoB_control = 8;

// Different servo speeds where 0 is full speed up, 90 is stopped, and 180 is full speed down
int servo_full_speed = 0;
int servo_looks_like_full_speed = 70;
int servo_slow_speed = 85;
int servo_stop_speed = 90;

void setup() {
  // Setup communications back to computer for testing.
  Serial.begin(SERIAL_SPEED);
  Serial.println("Setting the Servo control pins to be output.");
  pinMode(servoA_control, OUTPUT);
  pinMode(servoB_control, OUTPUT);
  servoA.attach(servoA_control);
  servoB.attach(servoB_control);
  
  // Driving lift downwards currently.
  int speed = 90;
  Serial.print("Writing to the servos speed");
  Serial.println(speed);
  servoA.write(speed);
  servoB.write(180-speed); // Negative as for the lift we want one to turn the opposite way.
}

void loop() {
  // Initialise variables
  delay(1500);
}
