// Drive_Distance_Command (Does not work, do not use)
/*
 * Allows the robot to drive in the specified direction for a specified distance.
 * 
 * Input:
 *  - Drive Subsystem
 *  - Direction
 *  - Distance
 *  - Servo Speed
 * Output:
 *  - Visible driving.
 * Notes:
 * 
 */

#include "RobotCmd.hpp"
#include "RobotRunner.hpp"
#include "Drive_Subsystem.hpp"

class Drive_Distance_Command: public RobotCmd {
private:
  Drive_Subsystem *_drive;
  Direction _dir;
  unsigned long _dist;
  int _speed;

public:
  Drive_Distance_Command(Drive_Subsystem *drive, Direction dir, unsigned long dist, int speed) {
    _drive = drive;
    _dir = dir;
    _dist = dist;
    _speed = speed;
  }
  
  void initialise() {
    Serial.println("Initialising Drive_Distance_Command\n");
  }

  bool execute() {
    unsigned long curDist = 0;
    //_drive->speedControl(); // TODO Think about how to include a function in the subsystem that calculates the distance that we have travelled.

    if (curDist > _dist) {
      return true;
    }

    _drive->drive(_dir, _speed);
    return false;
  }

  void end() {
    _drive->drive(drive_stop, 0);
  }
};
