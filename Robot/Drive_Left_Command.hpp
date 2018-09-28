// Drive_Left_Command
/*
 * Allows the robot to drive left for a certain amount of time.
 * 
 * Input:
 *  - Time in milliseconds
 * Output:
 *  - Visible driving to the left.
 * Notes:
 *  - Time input should be more than 3 milliseconds due to capabilities of the current arduinos.
 * 
 */

#include "RobotCmd.hpp"
#include "RobotRunner.hpp"
#include "Drive_Subsystem.hpp"

class Drive_Left_Command: public RobotCmd {
private:
  Drive_Subsystem *_drive;
  unsigned long _time;
  int _speed;

public:
  Drive_Left_Command::Drive_Left_Command(Drive_Subsystem *drive, unsigned long time, int speed) {
    _drive = drive;
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

    _drive->drive(left, _speed);
    return false;
  }

  void end() {
    _drive->drive(stop, 0);
  }
};
