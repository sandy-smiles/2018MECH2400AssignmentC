#include <Servo.h>

#define SERIAL_SPEED 9600

Servo dlt;
Servo drt;
Servo dlb;
Servo drb;
// Define wheel control pins
int dlt_control = 9;
int dlb_control = 10;
int drt_control = 11;
int drb_control = 12;
// Define wheel feedback pins
// NOTE: Can't understand feedback so we are not using it.
int dlt_feedback = 13;
int dlb_feedback = 13;
int drt_feedback = 13;
int drb_feedback = 13;

// Servo speed is where 0 is full speed ____-clockwise, 90 is stopped, and 180 is full speed ____-clockwise
int servo_full_speed = 0;
int servo_looks_like_full_speed = 70;
int servo_slow_speed = 85;
int servo_stop_speed = 90;

void setup() {
  // Setup communications back to computer for testing.
  Serial.begin(SERIAL_SPEED);
  pinMode(dlt_control, OUTPUT);
  pinMode(dlb_control, OUTPUT);
  pinMode(drt_control, OUTPUT);
  pinMode(drb_control, OUTPUT);
  dlt.attach(dlt_control);
  dlb.attach(dlb_control);
  drt.attach(drt_control);
  drb.attach(drb_control);
  
  
  Serial.print("Moving now\n\n");
  int speed = servo_looks_like_full_speed;
  dlt.write(speed);
  dlb.write(speed);
  drt.write(speed);
  drb.write(speed);
}

void loop() {
  // Initialise variables
  /*delay(5000);
  Serial.print("\tStopping now\n\n");
  myS.write(map(0, -1, 1, 0, 180)); // Initially just try to get the robot driving in a straight line.
  delay(2000);
  myS.write(180);
  delay(2000);
  myS.write(90); // Initially just try to get the robot driving in a straight line.
  delay(2000);
  *//*
  float sensed = readPos(13);
  Serial.print("Sensor is showing ");
  Serial.println(sensed);
  */
  delay(1500);
  
 /*
  Serial.print("\tStopping now\n\n");
  speed = 0;
  dlt.write(speed);
  dlb.write(speed);
  drt.write(speed);
  drb.write(speed);
  delay(1500);
  */
}

// Function gotten off the internet to figure out where the sensor is in terms of angle through the revolution.
// Has a really slow sampling speed and thus is not of much use.
float readPos(int pwmPin)
{
 int tHigh;
 int tLow;
 int tCycle;

 float theta = 0;
 float dc = 0;
 int unitsFC = 360;
 float dcMin = 0.029;
 float dcMax = 0.971;
 float dutyScale = 1;
 while(1) {
   pulseIn(pwmPin, LOW);
   tHigh = pulseIn(pwmPin, HIGH);
   tLow =  pulseIn(pwmPin, LOW);
   tCycle = tHigh + tLow;
   if ((tCycle > 1000) && ( tCycle < 1200)) break;
 }

 dc = (dutyScale * tHigh) / tCycle;
 theta = ((dc - dcMin) * unitsFC) / (dcMax - dcMin);
 return theta;
}
