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
  unsigned long _dist;
  int _speed;

public:
  Drive_Distance_Command::Drive_Distance_Command(Drive_Subsystem *drive, Direction dir, unsigned long dist, int speed) {
    _drive = drive;
    _dir = dir;
    _dist = dist;
    _speed = speed;
  }
  
  void initialise() {
  }

  bool execute() {
    unsigned long curDist = _drive->; // TODO Think about how to include a function in the subsystem that calculates the distance that we have travelled.

    if (curDist > _dist) {
      return true;
    }

    _drive->drive(_dir, _speed);
    return false;
  }

  void end() {
    _drive->drive(stop, 0);
  }
};
