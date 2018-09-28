#include <Servo.h>

#define SERIAL_SPEED 9600

Servo myS;
int servo_pin = 12;
// Servo speed is where 0 is full speed ____-clockwise, 90 is stopped, and 180 is full speed ____-clockwise
int servo_full_speed = 0;
int servo_slow_speed = 85;
int servo_stop_speed = 90;

int switch_pin = 13;

void setup() {
  // Setup communications back to computer for testing.
  Serial.begin(SERIAL_SPEED);
  myS.attach(servo_pin);
  myS.write(servo_stop_speed); // Stop servo
  pinMode(switch_pin, INPUT_PULLUP);
}

void loop() {
  // Initialise variables
  
  Serial.print("Moving now\n\n");
  myS.write(servo_slow_speed); // Initially just try to get the robot driving in a straight line.
  
  float sensed = readPos(switch_pin);
  Serial.print("Sensor is showing ");
  Serial.println(sensed);
  //delay(1500); // Lets there be a waiting period between sampling.
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
