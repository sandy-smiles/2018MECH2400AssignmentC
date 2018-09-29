#include <Servo.h>

#define SERIAL_SPEED 9600

// Define the Servos
Servo servoA;
Servo servoB;

// Define servo control pins as variables so that they can be changed.
int servoA_control = 9;
int servo_control = 10;

// Different servo speeds where 0 is full speed ____-clockwise, 90 is stopped, and 180 is full speed ____-clockwise
int servo_full_speed = 0;
int servo_looks_like_full_speed = 70;
int servo_slow_speed = 85;
int servo_stop_speed = 90;

void setup() {
  // Setup communications back to computer for testing.
  Serial.begin(SERIAL_SPEED);
  Serial.println("Setting the Servo control pins to be output.");
  pinMode(servoA, OUTPUT);
  pinMode(servoB, OUTPUT);
  servoA.attach(servoA_control);
  servoB.attach(servoB_control);
  
  
  int speed = servo_looks_like_full_speed;
  Serial.print("Writing to the servos speed");
  Serial.println(speed);
  servoA.write(speed);
  servoB.write(180-speed); // Negative as for the lift we want one to turn the opposite way.
}

void loop() {
  // Initialise variables
  delay(1500);
}
