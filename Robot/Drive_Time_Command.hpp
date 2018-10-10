// Drive_Time_Command
/*
 * Allows the robot to drive in the specified direction for the specified amount of time.
 * 
 * Input:
 *  - Drive Subsystem
 *  - Direction
 *  - Time in milliseconds
 *  - Servo Speed
 * Output:
 *  - Visible driving.
 * Notes:
 *  - Time input should be more than 3 milliseconds due to capabilities of the current arduinos.
 * 
 */

#include "RobotCmd.hpp"
#include "RobotRunner.hpp"
#include "Drive_Subsystem.hpp"

class Drive_Time_Command: public RobotCmd {
private:
  Drive_Subsystem *_drive;
  Direction _dir;
  unsigned long _time;
  int _speed;

public:
  Drive_Time_Command(Drive_Subsystem *drive, Direction dir, unsigned long time, int speed) {
    _drive = drive;
    _dir = dir;
    _time = time;
    _speed = speed;
  }
  
  void initialise() {
    Serial.println("Initialising Drive_Time_Command\n");
    _time = millis() + _time;	// _time is now the end time.
  }

  bool execute() {
    unsigned long curTime = millis();

    if (curTime > _time) {
      return true;
    }

    _drive->drive(_dir, _speed);
    return false;
  }

  void end() {
    _drive->drive(drive_stop, 0);
  }
};
