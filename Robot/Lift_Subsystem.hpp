/*
 * A subsystem is a wrapper class around a piece of hardware functionality.
 * It generally holds the state about a piece of hardware, and is used to manipulate the state of the hardware.
 *
 * Each piece of hardware should have its own subsystem class.
 */

#ifndef _LIFT_SUBSYSTEM_HPP
#define _LIFT_SUBSYSTEM_HPP

enum Lift_Direction { up, down, LiftStop };

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

	void
	reset() {
		// Make motors stationary
		_m1->reset();
		_m2->reset();
	}

	void
	move(Lift_Direction dir, int speed) {
		switch(dir) {
		case up:
			speed = -speed;
		case down:
			_m1->setSpeed(speed);
			_m2->setSpeed(speed); // Depend on wiring as to whether this is -speed or +speed
			break;
		case LiftStop:
			_m1->setSpeed(0);
			_m2->setSpeed(0);
			break;	
		return; // distance done.	
		}
	}

};

#endif // Lift_Subsystem.hpp
