#include <Servo.h>

#include "RobotCmd.hpp"
#include "RobotRunner.hpp"
#include "Motor.hpp"
#include "Wheel.hpp"
#include "Drive_Subsystem.hpp"
#include "Lift_Subsystem.hpp"
//#include "Drive_Distance_Command.hpp"
#include "Drive_Sensor_Command.hpp"
#include "Drive_Time_Command.hpp"
#include "Drive_Time_Sensor_Command.hpp"
#include "Lift_Sensor_Command.hpp"
#include "Lift_Time_Command.hpp"
#include "Lift_Time_Sensor_Command.hpp"
#include "Sensor_Command.hpp"

#define SERIAL_SPEED 9600
#define SENSOR_PRESSED 0

RobotRunner *cmds;
// Define Drive Subsystem
Drive_Subsystem *driveSubsystem;
// Define Wheel Motors (Servos)
Wheel *dlt; //drive_left_top;
Wheel *dlb; //drive_left_bottom;
Wheel *drt; //drive_right_top;
Wheel *drb; //drive_right_bottom;
// Define wheel control pins
int dlt_control = 9;
int dlb_control = 10;
int drt_control = 11;
int drb_control = 12;
/*// Define wheel feedback pins 
// NOTE: Sre not using these due to type of servos.
int dlt_feedback = 3;
int dlb_feedback = 2;
int drt_feedback = 5;
int drb_feedback = 6;
*/

// Define Lift Subsystem
Lift_Subsystem *liftSubsystem;
// Define Lift Motors (Servos)
Motor *l1; //lift_servo_1;
Motor *l2;
// Define lift control pins
int l1_control = 3; // Left Lift Servo
int l2_control = 4; // Right Lift Servo

// Define Sensor pins
int start_pin = 13;
int left_pin = 26;
int right_pin = 27;
int front1_pin = 22;
int front2_pin = 23;


void setup() {
  Serial.begin(SERIAL_SPEED);
  
  Serial.println("Initialising Robot Code.");
  
  Serial.println("Initialising Lift Motors");
  l1 = new Motor(l1_control);
  l2 = new Motor(l2_control);
  Serial.println("Initialising Lift_Subsystem");
  liftSubsystem = new Lift_Subsystem(l1, l2);
  Serial.println("Lift System Initialised");
  
  Serial.println("Initialising Drive Wheels");
  dlt = new Wheel(dlt_control); //, dlt_feedback);
  dlb = new Wheel(dlb_control); //, dlb_feedback);
  drt = new Wheel(drt_control); //, drt_feedback);
  drb = new Wheel(drb_control); //, drb_feedback);
  Serial.println("Initialising Drive_Subsystem");
  driveSubsystem = new Drive_Subsystem(dlt, dlb, drt, drb);
  Serial.println("Drive System Initialised");
  
  cmds = new RobotRunner();     // create an execution environment

  // Define all of the commands before structuring it into a command tree.
  
  // When creating commands, you want to create the structure of a massive tree that can branch into two.
  // Build up command tree from the first command.
  
   //Lift Program
  Lift_Direction _dir = up;
  int _s = 75;
  Sensor_Command *startCommand = new Sensor_Command(start_pin, SENSOR_PRESSED);
  Lift_Time_Command *cmd01 = new Lift_Time_Command(liftSubsystem, _dir, 500, _s);
  Lift_Sensor_Command *cmd02 = new Lift_Sensor_Command(liftSubsystem, _dir, start_pin, SENSOR_PRESSED, _s); // Make lift travel up
  Lift_Time_Command *cmd03 = new Lift_Time_Command(liftSubsystem, lift_stop, 500, 0);
  Lift_Sensor_Command *cmd04 = new Lift_Sensor_Command(liftSubsystem, lift_stop, start_pin, SENSOR_PRESSED, 0); // Stop lifts
  Lift_Time_Command *cmd05 = new Lift_Time_Command(liftSubsystem, _dir, 500, _s);
  Lift_Sensor_Command *cmd06 = new Lift_Sensor_Command(liftSubsystem, _dir, start_pin, SENSOR_PRESSED, _s); // Make lift travel down
  Lift_Time_Command *cmd07 = new Lift_Time_Command(liftSubsystem, lift_stop, 500, 0);
  Lift_Sensor_Command *cmd08 = new Lift_Sensor_Command(liftSubsystem, lift_stop, start_pin, SENSOR_PRESSED, 0); // Stop lifts
  Lift_Time_Command *cmd09 = new Lift_Time_Command(liftSubsystem, _dir, 500, _s);
  Lift_Sensor_Command *cmd10 = new Lift_Sensor_Command(liftSubsystem, _dir, start_pin, SENSOR_PRESSED, _s); // Make lift travel down
  Lift_Time_Command *cmd11 = new Lift_Time_Command(liftSubsystem, lift_stop, 500, 0);
  Lift_Sensor_Command *cmd12 = new Lift_Sensor_Command(liftSubsystem, lift_stop, start_pin, SENSOR_PRESSED, 0); // Stop lifts
  Lift_Time_Command *cmd13 = new Lift_Time_Command(liftSubsystem, _dir, 500, _s );
  Lift_Sensor_Command *cmd14 = new Lift_Sensor_Command(liftSubsystem, _dir, start_pin, SENSOR_PRESSED, _s); // Make lift travel down
  Lift_Time_Command *liftStopCommand = new Lift_Time_Command(liftSubsystem, lift_stop, 10000, 0);
  
  startCommand->addSequential(cmd01);
  cmd01->addSequential(cmd02);
  cmd02->addSequential(cmd03);
  cmd03->addSequential(cmd04);
  cmd04->addSequential(cmd05);
  cmd05->addSequential(cmd06);
  cmd06->addSequential(cmd07);
  cmd07->addSequential(cmd08);
  cmd08->addSequential(cmd09);
  cmd09->addSequential(cmd10);
  cmd10->addSequential(cmd11);
  cmd11->addSequential(cmd12);
  cmd12->addSequential(cmd13);
  cmd13->addSequential(cmd14);
  cmd14->addSequential(liftStopCommand);
   
  
  /* //Parallel Program
  int _s = 1000;
  Sensor_Command *startCommand = new Sensor_Command(start_pin, SENSOR_PRESSED);
  Drive_Time_Command *cmd01 = new Drive_Time_Command(driveSubsystem, forwards, 5000, _s);
  Lift_Time_Command *cmd03 = new Lift_Time_Command(liftSubsystem, up, 2000, _s);
  Lift_Sensor_Command *cmd04 = new Lift_Sensor_Command(liftSubsystem, up, start_pin, SENSOR_PRESSED, _s);
  Drive_Time_Command *driveStopCommand = new Drive_Time_Command(driveSubsystem, drive_stop, 10000, 0);
  Lift_Time_Command *liftStopCommand = new Lift_Time_Command(liftSubsystem, lift_stop, 10000, 0);
  
  startCommand->addSequential(cmd01);
  cmd01->addParallel(cmd03);
  cmd03->addSequential(cmd04);
  cmd01->addSequential(driveStopCommand);
  cmd04->addSequential(liftStopCommand);
  */
  
  /*  //Parallel Drive Program
  Sensor_Command *startCommand = new Sensor_Command(start_pin, SENSOR_PRESSED); // Press Start
  Drive_Time_Command *drive_cmd01 = new Drive_Time_Command(driveSubsystem, forwards, 20000, 90); // Move forwards 650mm
  Drive_Time_Command *drive_cmd02 = new Drive_Time_Command(driveSubsystem, turn_left, 1500, 90); // Rotate 90 anti-clockwise
  Lift_Time_Command *lift_cmd01 = new Lift_Time_Command(liftSubsystem, up, 10000, 90); // Lift up (min 100mm)
  Lift_Time_Command *lift_cmd02 = new Lift_Time_Command(liftSubsystem, lift_stop, 10000, 0); // Stop the lift
  Drive_Time_Command *drive_cmd03 = new Drive_Time_Command(driveSubsystem, fowards, 8000, 90); // Move forward 250mm
  Drive_Time_Sensor_Command *drive_cmd04 = new Drive_Time_Sensor_Command(driveSubsystem, left, 8000, start_pin, SENSOR_PRESSED, 90); // Move left until left sensor hits
  Drive_Time_Command *drive_cmd05 = new Drive_Time_Command(driveSubsystem, right, 8000, 90);// Move right 69.5mm
  Drive_Time_Sensor_Command *drive_cmd06 = new Drive_Time_Sensor_Command(driveSubsystem, forwards, 8000, front1_pin, SENSOR_PRESSED, 90); // Move forwards until front sensor hits
  Lift_Time_Command *lift_cmd03 = new Lift_Time_Command(liftSubsystem, up, 5000, 90); // Lift up until max
  Lift_Time_Command *lift_cmd04 = new Lift_Time_Command(liftSubsystem, lift_stop, 10000, 0); // Stop the lift
  Drive_Time_Command *drive_cmd07 = new Drive_Time_Command(driveSubsystem, backwards, 15000, 90); // Move backwards 200mm
  Drive_Time_Command *drive_cmd08 = new Drive_Time_Command(driveSubsystem, forwards, 20000, 90); // Move right 1231.78mm
  Lift_Time_Command *lift_cmd05 = new Lift_Time_Command(liftSubsystem, down, 10000, 90); // Lift up (min 100mm)
  Lift_Time_Command *lift_cmd06 = new Lift_Time_Command(liftSubsystem, lift_stop, 10000, 0); // Stop the lift
  Drive_Time_Command *drive_cmd09 = new Drive_Time_Command(driveSubsystem, turn_right, 3000, 90); // Rotate 90 clockwise
  
  Drive_Time_Command *driveStopCommand = new Drive_Time_Command(driveSubsystem, drive_stop, 10000, 0);
  Lift_Time_Command *liftStopCommand = new Lift_Time_Command(liftSubsystem, lift_stop, 10000, 0);
  
  startCommand->addSequential(drive_cmd01);
  drive_cmd01->addSequential(drive_cmd02);
  drive_cmd02->addSequential(drive_cmd03);
  
  drive_cmd02->addParallel(lift_cmd01);
  lift_cmd01->addSequential(lift_cmd02);
  
  drive_cmd03->addSequential(drive_cmd04);
  drive_cmd04->addSequential(drive_cmd05);
  drive_cmd05->addSequential(drive_cmd06);

  drive_cmd06->addParallel(lift_cmd03);
  lift_cmd03->addSequential(lift_cmd04);
  
  drive_cmd06->addSequential(drive_cmd07);
  drive_cmd07->addSequential(drive_cmd08);
  
  drive_cmd08->addParallel(lift_cmd05);
  lift_cmd05->addSequential(lift_cmd06);
  
  
  
  cmd03->addSequential(liftStopCommand);
  cmd010->addSequential(driveStopCommand);
  */
  

  
  // After commands, then add all of the command tree to register to run.
  Serial.println("Starting Robot Code now!");
  cmds->add(startCommand);
  Serial.println("Activating Commands!");
  cmds->setParallelActive(startCommand); // Sets top commands active and then flows through the tree
}

void loop() {
  // put your main code here, to run repeatedly:
  cmds->update();   // run robot commands
}
