// Lift Subsystem
/*
 * Is used for driving the cascade lift that uses 2 servos running together.
 * 
 * Defines:
 *  - enum Lift_Direction
 *  - Lift_Subsystem
 *    - void reset
 *    - void move
 * Notes:
 *  - Different servo speeds where 0 is full speed up, 90 is stopped, and 180 is full speed down
 * 
 * TODO:
 *  - Fix up within move, the function that pokes the servos to spin.
 */

#ifndef _LIFT_SUBSYSTEM_HPP
#define _LIFT_SUBSYSTEM_HPP

enum Lift_Direction { up, down, lift_stop };

class Lift_Subsystem {
private:
	Motor *_m1; // Motor 1
	Motor *_m2; // Motor 2

public:
	Lift_Subsystem(Motor *m1, Motor *m2) {
		_m1 = m1;
		_m2 = m2;
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
		// Make motors stationary
		_m1->reset();
		_m2->reset();
	}

  // move
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
	move(Lift_Direction dir, int speed) {
		switch(dir) {
		case up:
			speed = -speed;
		case down:
			_m1->setSpeed(speed);
			_m2->setSpeed(-speed); // Depend on wiring as to whether this is -speed or +speed
			break;
		case lift_stop:
			_m1->setSpeed(0);
			_m2->setSpeed(0);
			break;	
		return; // distance done.	
		}
	}

};

#endif // Lift_Subsystem.hpp
