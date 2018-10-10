// Lift_Time_Command
/*
 * Allows the robot to move the lift in the specified direction for the specified amount of time.
 * 
 * Input:
 *  - Lift Subsystem
 *  - Direction
 *  - Time in milliseconds
 *  - Servo Speed
 * Output:
 *  - Visible movement of the cascade lift.
 * Notes:
 *  - Time input should be more than 3 milliseconds due to capabilities of the current arduinos.
 * 
 */

#include "RobotCmd.hpp"
#include "RobotRunner.hpp"
#include "Drive_Subsystem.hpp"

class Lift_Time_Command: public RobotCmd {
private:
  Lift_Subsystem *_lift;
  Lift_Direction _dir;
  unsigned long _time;
  int _speed;

public:
  Lift_Time_Command(Lift_Subsystem *lift, Lift_Direction dir, unsigned long time, int speed) {
    _lift = lift;
    _dir = dir;
    _time = time;
    _speed = speed;
  }
  
  void initialise() {
    Serial.println("Initialising Lift_Time_Command\n");
    _time = millis() + _time;	// _time is now the end time.
    
    Serial.print("Lift_Time_Command with ");
    Serial.print(_dir);
    Serial.print("  ");
    Serial.print(_speed);
    Serial.println("");
  }

  bool execute() {
    unsigned long curTime = millis();

    if (curTime > _time) {
      return true;
    }

    _lift->move(_dir, _speed);
    return false;
  }

  void end() {
    _lift->move(lift_stop, 0);
  }
};
