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
  
   //Robot main Program
  Sensor_Command *startCommand = new Sensor_Command(start_pin, SENSOR_PRESSED); // Press Start
  Drive_Time_Command *drive_cmd01 = new Drive_Time_Command(driveSubsystem, forwards, 4100, 15); // Move forward 250mm
  Lift_Time_Command *lift_cmd01 = new Lift_Time_Command(liftSubsystem, up, 2000, 90); // Lift up (min 100mm)
  Lift_Time_Command *lift_cmd02 = new Lift_Time_Command(liftSubsystem, lift_stop, 10000, 0); // Stop the lift
  Drive_Time_Sensor_Command *drive_cmd02 = new Drive_Time_Sensor_Command(driveSubsystem, forwards, 200, right_pin, SENSOR_PRESSED, 15); // Move forwards until front sensor hits
  Drive_Time_Command *drive_cmd03 = new Drive_Time_Command(driveSubsystem, drive_stop, 10000, 0);
  Lift_Time_Command *lift_cmd03 = new Lift_Time_Command(liftSubsystem, up, 10000, 90); // Lift up until max - changed = 1000
  Lift_Time_Command *lift_cmd04 = new Lift_Time_Command(liftSubsystem, lift_stop, 10000, 0); // Stop the lift
  Drive_Time_Command *drive_cmd04 = new Drive_Time_Command(driveSubsystem, backwards, 1000, 15); // Move backwards 200mm
  Drive_Time_Command *drive_cmd05 = new Drive_Time_Command(driveSubsystem, turn_right, 2350, 15); // Rotate 90 anti-clockwise
  Drive_Time_Command *drive_cmd06 = new Drive_Time_Command(driveSubsystem, forwards, 15000, 15); // Move forward 250mm
  Drive_Time_Command *drive_cmd10 = new Drive_Time_Command(driveSubsystem, turn_right, 2350 , 15); // Rotate 180 clockwise
  Drive_Time_Sensor_Command *drive_cmd11 = new Drive_Time_Sensor_Command(driveSubsystem, forwards, 2000, front1_pin, SENSOR_PRESSED, 15); // Move forwards until front sensor hits
  Drive_Time_Sensor_Command *drive_cmd12 = new Drive_Time_Sensor_Command(driveSubsystem, forwards, 2000, front2_pin, SENSOR_PRESSED, 15); //Move forwards until other front sensor hits
  Drive_Time_Sensor_Command *drive_cmd13 = new Drive_Time_Sensor_Command(driveSubsystem, right, 2000, front2_pin, !SENSOR_PRESSED, 15); // Move right until right sensor de-activates
  Drive_Time_Command *drive_cmd14 = new Drive_Time_Command(driveSubsystem, left, 3468, 15); // Move left 196mm
  Lift_Time_Command *lift_cmd07 = new Lift_Time_Command(liftSubsystem, down, 8000, 90); // Lift down (all the way)
  Drive_Time_Command *driveStopCommand = new Drive_Time_Command(driveSubsystem, drive_stop, 10000, 0);
  Lift_Time_Command *liftStopCommand = new Lift_Time_Command(liftSubsystem, lift_stop, 10000, 0);
  
  startCommand->addSequential(drive_cmd01);
  drive_cmd01->addSequential(lift_cmd01);
  lift_cmd01->addSequential(lift_cmd02);
  lift_cmd02->addSequential(drive_cmd02);
  drive_cmd02->addSequential(drive_cmd03);
  drive_cmd03->addSequential(lift_cmd03);
  lift_cmd03->addSequential(lift_cmd04);
  lift_cmd04->addSequential(drive_cmd04);
  drive_cmd04->addSequential(drive_cmd05);
  drive_cmd05->addSequential(drive_cmd06);
  drive_cmd06->addSequential(drive_cmd10);
  drive_cmd10->addSequential(drive_cmd11);
  drive_cmd11->addSequential(drive_cmd12);
  drive_cmd12->addSequential(drive_cmd13);
  drive_cmd13->addSequential(drive_cmd14);
  drive_cmd14->addSequential(driveStopCommand);
  
  drive_cmd14->addParallel(lift_cmd07);
  lift_cmd07->addSequential(liftStopCommand);
  
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
