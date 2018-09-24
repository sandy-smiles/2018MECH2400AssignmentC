// Drive_Command
/*
 * Allows the robot to drive in the specified direction for a certain amount of time.
 * 
 * Input:
 *  - Time in milliseconds
 *  - Direction
 * Output:
 *  - Visible driving.
 * Notes:
 *  - Time input should be more than 3 milliseconds due to capabilities of the current arduinos.
 * 
 */

#include "RobotCmd.hpp"
#include "RobotRunner.hpp"
#include "Drive_Subsystem.hpp"

class Drive_Command: public RobotCmd {
private:
  Drive_Subsystem *_drive;
  Direction _dir;
  unsigned long _time;
  int _speed;

public:
  Drive_Command::Drive_Command(Drive_Subsystem *drive, Direction dir, unsigned long time, int speed) {
    _drive = drive;
    _dir = dir;
    _time = time;
    _speed = speed;
  }
  
  void initialise() {
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
    _drive->drive(stop, 0);
  }
};
