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
#define SPEED_TOLERANCE_CHANGE 0

enum Direction { left, right, forwards, backwards, turn_left, turn_right, drive_stop };

class Drive_Subsystem {
private:
	Wheel *_dlt; //drive_left_top;
	Wheel *_dlb; //drive_left_bottom;
	Wheel *_drt; //drive_right_top;
	Wheel *_drb; //drive_right_bottom;  

  int ghost_angle;
  int dlt_angle;
  int dlb_angle;
  int drt_angle;
  int drb_angle;
  
  int dlt_speed;
  int dlb_speed;
  int drt_speed;
  int drb_speed;

  int angleIncrement = 47;
  int start_ghost_angle = -200;
  int incrementSpeed = 15;

public:
	Drive_Subsystem(Wheel *dlt, Wheel *dlb, Wheel *drt, Wheel *drb) {
		_dlt = dlt;
		_dlb = dlb;
		_drt = drt;
		_drb = drb;

    ghost_angle = start_ghost_angle; // Give real-time wheels a head start to speed up.

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
    Serial.print("Drive_Subsystem - Reseting the wheels\n");
    Serial.print("Drive_Subsystem - Attempting dlt\n");
		_dlt->reset();
    Serial.print("Drive_Subsystem - Finished dlt\n");
    Serial.print("Drive_Subsystem - Attempting dlb\n");
		_dlb->reset();
    Serial.print("Drive_Subsystem - Finished dlb\n");
    Serial.print("Drive_Subsystem - Attempting drt\n");
		_drt->reset();
    Serial.print("Drive_Subsystem - Finished drt\n");
    Serial.print("Drive_Subsystem - Attempting drb\n");
		_drb->reset();
    Serial.print("Drive_Subsystem - Finished drb\n");
    Serial.print("Drive_Subsystem - Reset all wheels\n");
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
    bool debug = true;
    speed = abs(speed); // If everything is around the wrong way, please uncomment this line.

    /*
    ghost_angle += angleIncrement;
    dlt_angle = _dlt->getCurrentPos();
    dlb_angle = _dlb->getCurrentPos();
    drt_angle = _drt->getCurrentPos();
    drb_angle = _drb->getCurrentPos();

    dlt_speed = speedControl(ghost_angle, dlt_angle, abs(dlt_speed));
    dlb_speed = speedControl(ghost_angle, dlb_angle, abs(dlb_speed));
    drt_speed = speedControl(ghost_angle, drt_angle, abs(drt_speed));
    drb_speed = speedControl(ghost_angle, drb_angle, abs(drb_speed));
    */
    
		switch(dir) {
		case left:
      if (debug) Serial.println("Going left.");
      speed = -speed;
		case right:
      if (debug) Serial.println("Going right.");
			_dlt->setSpeed(speed);
			_dlb->setSpeed(-speed);
			_drt->setSpeed(speed);
			_drb->setSpeed(-speed);
			break;
		case backwards:
      speed = -speed;
      if (debug) Serial.println("Going backwards.");
		case forwards:
      if (debug) Serial.println("Going forwards.");
			_dlt->setSpeed(speed);
			_dlb->setSpeed(speed);
			_drt->setSpeed(-speed);
			_drb->setSpeed(-speed);
			break;
    case turn_left:
      speed = -speed;
      if (debug) Serial.println("Going turn_left.");
    case turn_right:
      if (debug) Serial.println("Going turn_right.");
      _dlt->setSpeed(speed);
      _dlb->setSpeed(speed);
      _drt->setSpeed(speed);
      _drb->setSpeed(speed);
      break;
		case drive_stop:
      if (debug) Serial.println("Set drive_stop.");
			_dlt->setSpeed(0);
			_dlb->setSpeed(0);
			_drt->setSpeed(0);
			_drb->setSpeed(0);
			break;	
    Serial.print("\n");
		return; // distance done.	
		}
	}

  // speedControl
  /*
   * Input:
   *  - None
   * Output:
   *  - None
   * Side Effects:
   *  - Changes 
   * Note:
   *  - THIS IS A STUB. DO NOT USE THIS FUNCTION OR IF IT IS USED. DO NOT USE THAT COMMAND.
   */
  int
  speedControl(int ghost_angle, int angle, int speed) {
    int max_speed = 1000;
    int min_speed = 700;
    if (ghost_angle - angle > 10){ // The wheel is too fast
      speed = speed + incrementSpeed;
      
      if (speed > max_speed) // Lower limit = slow
        speed = max_speed;  
      
      Serial.print(" fast ");
      Serial.print("\t");        
    }
    else if (ghost_angle - angle < -10){ // The wheel is too slow
      speed = speed - incrementSpeed;
   
      if (speed > min_speed) // Upper limit = slow
        speed = min_speed;  
    
      Serial.print(" slow ");
      Serial.print("\t");
    }
    else { // Speed is equal
      Serial.print(" == ");
      Serial.print("\t");
    }
    return speed;
  }

};

#endif // Drive_Subsystem.hpp
