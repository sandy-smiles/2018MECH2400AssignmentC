#include <Servo.h>

#define SERIAL_SPEED 9600

Servo myS;

void setup() {
  // Setup communications back to computer for testing.
  Serial.begin(SERIAL_SPEED);
  myS.attach(12);
  myS.write(90); // Stop servo
  pinMode(13, INPUT_PULLUP);
}

void loop() {
  // Initialise variables
  
  Serial.print("Moving now\n\n");
  myS.write(85); // Initially just try to get the robot driving in a straight line.
  /*delay(5000);
  Serial.print("\tStopping now\n\n");
  myS.write(map(0, -1, 1, 0, 180)); // Initially just try to get the robot driving in a straight line.
  delay(2000);
  myS.write(180);
  delay(2000);
  myS.write(90); // Initially just try to get the robot driving in a straight line.
  delay(2000);
  */
  float sensed = readPos(13);
  Serial.print("Sensor is showing ");
  Serial.println(sensed);
  //delay(1500);
}


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


