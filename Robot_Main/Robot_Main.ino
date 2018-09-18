#include "DEFINE"

#define SERIAL_SPEED 9600

void setup() {
  // Setup communications back to computer for testing.
  Serial.begin(SERIAL_SPEED);
  
  // Initialise the servos and the other ports as input or output
  pinMode(LED, 13); // Inbuilt led onto the arduino board (from memory)
  pinMode(WHEEL_L_T, OUTPUT);
  pinMode(WHEEL_L_B, OUTPUT);
  pinMode(WHEEL_R_T, OUTPUT);
  pinMode(WHEEL_R_B, OUTPUT);
}

void loop() {
  // Initialise variables
  int wheelSpeed = 10;
  
  
  while (TRUE) {
    drive(wheelSpeed); // Initially just try to get the robot driving in a straight line.
  }
}
