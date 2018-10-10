#include <Servo.h>
Servo dlt;
Servo drt;
Servo dlb;
Servo drb;

// Define wheel control pins
int dlt_control = 9;
int dlb_control = 10;
int drt_control = 11;
int drb_control = 12;  
int finalAngle = 32000;
int baseAngle = -200;
int angleIncrement = 47;
int Turns[4] = {0, 0, 0, 0};     //The number of rotations
int i = 0;
float incrementSpeed = 15;
float speed[4]= {1000, 1000, 1000, 1000};  // Set speed
float theta[4] = {0, 0, 0, 0};             // The theta[i] of this measurement
float init_angle[4] = {0, 0, 0, 0};        // Offset angle
float thetaP[4] = {0, 0, 0, 0};            //The previous theta[i]
int count = 0;     // Count for the number of measurements; the number of times Angle is called
int kp = 1;
int angle_current[4] = {0, 0, 0, 0};  
int angle_previous[4] = {0, 0, 0, 0};  


int min_speed = 1270;     // Slowest
int max_speed = 900;      // Fastest
int min_speed_cc = 1700;  // Slowest
int max_speed_cc = 1600;  // Fastest

int readPos(int pwmPin){
i = pwmPin - 3;
int tHigh;           // time "on"
int tLow;            // time "off"
int tCycle;          // length of duty cycle
int q2min = 90;      // lower limit of q2
int q3max = 270;     // Upper limit of q3
float dc = 0;        // duty cycle
int unitsFC = 360;   // 360 degrees in a circle
float dcMin = 0.029; // Minimum dc (data sheet)
float dcMax = 0.971; // maximum dc (data sheet)
float dutyScale = 1;
float angle[4]={0, 0, 0, 0};     // the angle of rotation (infinite)

// While loop calculates the time "on" and time "off" until tCycle is between 1050 and 1150 (average is 1100)
while(1) {
  tHigh = pulseIn(pwmPin, HIGH); // receive signal on
  tLow =  pulseIn(pwmPin, LOW);  // receive signal off
  tCycle = tHigh + tLow;
  
  if ((tCycle > 1050) && ( tCycle < 1150)) break; // Stop the loop
}

  // Equation used to calculate duty cycle and theta[i] (where theta[i] is between 0 and 360)
  dc = (dutyScale * tHigh) / tCycle;
  theta[i] = ((dc - dcMin) * unitsFC) / (dcMax - dcMin);

   // Print theta

  
  // Set boundaries so theta[i] is in the range of 0 and 360  
  if(theta[i] < 0) theta[i] = 0;
  else if(theta[i] > (unitsFC - 1)) theta[i] = unitsFC - 1;

  // Incrementing or decrementing number of Turns[i]
  if((theta[i] < q2min) && (thetaP[i] > q3max)){ // If 4th to 1st quadrant
    Turns[i]++; 
  } // Increment Turns[i] count
  else if((thetaP[i] < q2min) && (theta[i] > q3max)) // If in 1st to 4th quadrant
    Turns[i]--; // Decrement Turns[i] count

  // Change the angle by theta[i] based on Turns[i] (add if positive Turns[i], subtract if negative Turns[i])
  if(Turns[i] >= 0)
    angle[i] = (Turns[i] * unitsFC) + theta[i];
  else if(Turns[i] < 0)
    angle[i] = ((Turns[i] + 1) * unitsFC) - (unitsFC - theta[i]);

  // Print turns
  Serial.print(Turns[i]);
  Serial.print("\t");


  // Set the current theta[i], as thetaP[i] of the next round
  thetaP[i] = theta[i];
  return angle[i];

}


void setup() {
  Serial.begin(9600);   
  dlt.attach(dlt_control);
  dlb.attach(dlb_control);
  drb.attach(drb_control);
  drt.attach(drt_control);
    
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  
  for (i = 0; i < 1; i++){
    init_angle[i] = readPos(i+3); // Find value of initial angle
    Serial.print(init_angle[i]);  // Print the value of initial angle
    Serial.print("\t");
  }
  
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
}

 //int count = 0;
void loop() {
  count = count + 1;
  dlt.writeMicroseconds(speed[0]);
  //dlb.writeMicroseconds(speed[1]);
  //drt.writeMicroseconds(speed[2]);
  //drb.writeMicroseconds(speed[3]); 

  for (i = 0; i < 1; i++){
    angle_current[i] = readPos(i+3)-init_angle[i];  
   // Serial.print(i);
      //  Serial.print(" ");
    Serial.print("Angle = ");
    Serial.print(angle_current[i]);
    Serial.print("\t");
  }


  int j = 0;
  if(baseAngle < finalAngle){
  while(j < 1){

    // Clockwise, clockwise
   //if((angle_current[0] - angle_previous[0] >= 0)&&(angle_current[j] - angle_previous[j] >= 0)){
            baseAngle = baseAngle + angleIncrement;  

      if (baseAngle - angle_current[j] > 10){
        speed[j] = speed[j] - incrementSpeed;
        
        if (speed[j] < max_speed) // lower limit = fast
          speed[j] = max_speed;
        
        Serial.print(" fast ");
        Serial.print("\t");        
      }
      else if (baseAngle - angle_current[j] < -10){
        speed[j] = speed[j] + incrementSpeed;
     
        if (speed[j] > min_speed) // Upper limit = slow
          speed[j] = min_speed;  
      
        Serial.print(" slow ");
        Serial.print("\t");
      }
      else {
        Serial.print(" == ");
        Serial.print("\t");
      }
           // Serial.print (j);
      //Serial.print (" ");
      Serial.print("Speed = ");
      Serial.print(speed[j]);
         Serial.print("\t");
         Serial.print("Base Angle = ");
         Serial.print(baseAngle);
         Serial.print("\t");
   Serial.print(baseAngle - angle_current[j]);
      j = j + 1;
  }
}

else{
  
  //dlt.write(1500);
  //delay(10000);
  
}
Serial.println();
}
   /*
    
   
    // Clockwise, anticlockwise
    if ((angle_current[0] - angle_previous[0] >= 0)&&(angle_current[j] - angle_previous[j] < 0)){
      if (angle_current[0] + angle_current[j] > 10){
        speed[j] = speed[j] + incrementSpeed;
        
        if (speed[j] > max_speed_cc) // Upper limit = fast
          speed[j] = max_speed_cc;
        
        Serial.print(" slow ");
        Serial.print("\t");        
        }
      }
      else if (angle_current[0] + angle_current[j] < -10){
        if (speed[j] < min_speed_cc) // lower limit = slow
          speed[j] = min_speed_cc;
      
        Serial.print(" slow ");
        Serial.print("\t");
      }
      else {
        Serial.print(" == ");
        Serial.print("\t");
      }
            Serial.print (j);
      Serial.print (" ");
      Serial.print(speed[j]);
      j = j + 1;
    }
        // anticlockwise, Clockwise
    if ((angle_current[0] - angle_previous[0] < 0)&&(angle_current[j] - angle_previous[j] >= 0)){
      if (angle_current[0] + angle_current[j] > 10){
        speed[j] = speed[j] + incrementSpeed;
        
        if (speed[j] > min_speed) // lower limit = slow down
          speed[j] = min_speed;
        
        Serial.print(" slow ");
        Serial.print("\t");        
        
      }
      else if (angle_current[0] + angle_current[j] < -10){
        if (speed[j] < max_speed) // upper limit = fast
          speed[j] = max_speed;
      
        Serial.print(" fast ");
        Serial.print("\t");
      }
      else {
        Serial.print(" == ");
        Serial.print("\t");
      }
            Serial.print (j);
      Serial.print (" ");
      Serial.print(speed[j]);
      j = j + 1;
    }
        // anticlockwise, anticlockwise
    if ((angle_current[0] - angle_previous[0] < 0)&&(angle_current[j] - angle_previous[j] < 0)){
      if (angle_current[0] - angle_current[j] > 10){
        speed[j] = speed[j] - incrementSpeed;
        if (speed[j] < max_speed_cc) // Upper limit
          speed[j] = max_speed_cc;
        
          Serial.print(" fast ");
          Serial.print("\t");        
       
      }
      else if (angle_current[0] + angle_current[j] < -10){
        if (speed[j] < min_speed_cc) // lower limit
          speed[j] = min_speed_cc;
      
          Serial.print(" slow ");
          Serial.print("\t");
      }
      else {
        Serial.print(" == ");
        Serial.print("\t");
      }
            Serial.print (j);
      Serial.print (" ");
      Serial.print(speed[j]);
      j = j + 1;
      angle_previous[j] = angle_current[j];

    }
  
  Serial.println();
 // angle_previous[0] = angle_current[0];
 // angle_previous[j] = angle_current[j];
}

  */
