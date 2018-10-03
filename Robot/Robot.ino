#include <Servo.h>

#include "RobotCmd.hpp"
#include "RobotRunner.hpp"
#include "Motor.hpp"
#include "Wheel.hpp"
#include "Drive_Subsystem.hpp"
#include "Lift_Subsystem.hpp"
#include "Drive_Distance_Command.hpp"
#include "Drive_Sensor_Command.hpp"
#include "Drive_Time_Command.hpp"
#include "Lift_Sensor_Command.hpp"
#include "Lift_Time_Command.hpp"
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
// Define wheel feedback pins
// NOTE: Can't understand feedback so we are not using it.
int dlt_feedback = 3;
int dlb_feedback = 4;
int drt_feedback = 5;
int drb_feedback = 6;

// Define Lift Subsystem
Lift_Subsystem *liftSubsystem;
// Define Lift Motors (Servos)
Motor *l1; //lift_servo_1;
Motor *l2;
// Define lift control pins
int l1_control = 7;
int l2_control = 8;

// Define Sensor pins
int start_pin = 13;

void setup() {
  Serial.begin(SERIAL_SPEED);
  
  l1 = new Motor(l1_control);
  l2 = new Motor(l2_control);
  liftSubsystem = new Lift_Subsystem(l1, l2);

  dlt = new Wheel(dlt_control, dlt_feedback);
  dlb = new Wheel(dlb_control, dlb_feedback);
  drt = new Wheel(drt_control, drt_feedback);
  drb = new Wheel(drb_control, drb_feedback);
  driveSubsystem = new Drive_Subsystem(dlt, dlb, drt, drb);
  
  cmds = new RobotRunner();     // create an execution environment

  // Define all of the commands before structuring it into a command tree.
  Sensor_Command *startCommand = new Sensor_Command(start_pin, SENSOR_PRESSED);
  Drive_Time_Command *cmd01 = new Drive_Time_Command(driveSubsystem, forwards, 2000, 90);
  Lift_Time_Command *cmd03 = new Lift_Time_Command(liftSubsystem, up, 2000, 90);
  Lift_Sensor_Command *cmd04 = new Lift_Sensor_Command(liftSubsystem, up, start_pin, SENSOR_PRESSED, 90);
  Drive_Time_Command *driveStopCommand = new Drive_Time_Command(driveSubsystem, drive_stop, 10000, 0);
  Lift_Time_Command *liftStopCommand = new Lift_Time_Command(liftSubsystem, lift_stop, 10000, 0);
  
  
//RobotFlashLed *rfl = new RobotFlashLed(new SubsystemLED(led1), 500);
//rfl->addParallel(new RobotFlashLed(new SubsystemLED(led2), 300));

  
  // When creating commands, you want to create the structure of a massive tree that can branch into two.
  // Build up command tree from the first command.
 
  startCommand->addSequential(cmd01);
  cmd01->addParallel(cmd03);
  cmd03->addSequential(cmd04);
  cmd01->addSequential(driveStopCommand);
  cmd04->addSequential(liftStopCommand);
  

// Start on limit switch press/trigger
// Drive forwards for a little bit
// Start lifting the lift at the same as driving forwards more.
// Turn left on the spot
// 

  
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
