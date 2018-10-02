// Drive Subsystem
/*
 * Is used for driving the chassis
 * 
 * Defines:
 *  - enum Direction
 *  - Drive_Subsystem
 *    - void reset
 *    - void drive
 */

#ifndef _DRIVE_SUBSYSTEM_HPP
#define _DRIVE_SUBSYSTEM_HPP

enum Direction { left, right, forwards, backwards, turn_left, turn_right, drive_stop };

class Drive_Subsystem {
private:
	Wheel *_dlt; //drive_left_top;
	Wheel *_dlb; //drive_left_bottom;
	Wheel *_drt; //drive_right_top;
	Wheel *_drb; //drive_right_bottom;

public:
	Drive_Subsystem(Wheel *dlt, Wheel *dlb, Wheel *drt, Wheel *drb) {
		_dlt = dlt;
		_dlb = dlb;
		_drt = drt;
		_drb = drb;

		reset();
	}

  // reset
  /*
   * Input:
   *  - None
   * Output:
   *  - Robot becomes stationary
   */
	void
	reset() {
		// Make robot stationary
		_dlt->reset();
		_dlb->reset();
		_drt->reset();
		_drb->reset();
	}

  // drive
  /*
   * Input:
   *  - Direction you wish the robot to move in
   *  - Speed of the servos.
   * Output:
   *  - Visible movement of robot
   * Note:
   *  - Cascade fall on affect has been used when programming the switch case statement.
   *    Please note the breaks within the statement.
   */
	void
	drive(Direction dir, int speed) {
    // speed = -speed; // If everything is around the wrong way, please uncomment this line.
		switch(dir) {
		case left:
			speed = -speed;
		case right:
			_dlt->setSpeed(speed);
			_dlb->setSpeed(-speed);
			_drt->setSpeed(speed);
			_drb->setSpeed(-speed);
			break;
		case backwards:
			speed = -speed;
		case forwards:
			_dlt->setSpeed(speed);
			_dlb->setSpeed(speed);
			_drt->setSpeed(-speed);
			_drb->setSpeed(-speed);
			break;
    case turn_left:
      speed = -speed;
    case turn_right:
      _dlt->setSpeed(speed);
      _dlb->setSpeed(speed);
      _drt->setSpeed(speed);
      _drb->setSpeed(speed);
      break;
		case drive_stop:
			_dlt->setSpeed(0);
			_dlb->setSpeed(0);
			_drt->setSpeed(0);
			_drb->setSpeed(0);
			break;	
		return; // distance done.	
		}
	}

  // calculateDist (STUB)
  /*
   * Input:
   *  - None
   * Output:
   *  - Distance robot has travelled.
   * Note:
   *  - THIS IS A STUB. DO NOT USE THIS FUNCTION OR IF IT IS USED. DO NOT USE THAT COMMAND.
   */
  unsigned long
  calculateDist() {
    return 0;
  }

};

#endif // Drive_Subsystem.hpp
