/*
 * A subsystem is a wrapper class around a piece of hardware functionality.
 * It generally holds the state about a piece of hardware, and is used to manipulate the state of the hardware.
 *
 * Each piece of hardware should have its own subsystem class.
 */

#ifndef _DRIVE_SUBSYSTEM_HPP
#define _DRIVE_SUBSYSTEM_HPP

enum Direction { left, right, forwards, backwards, stop };

class Drive_Subsystem {
private:
	Wheel *_dlt; //drive_left_top;
	Wheel *_dlb; //drive_left_bottom;
	Wheel *_drt; //drive_right_top;
	Wheel *_drb; //drive_right_bottom;

public:
	Drive_Subsystem::Drive_Subsystem(Wheel *dlt, Wheel *dlb, Wheel *drt, Wheel *drb) {
		_dlt = dlt;
		_dlb = dlb;
		_drt = drt;
		_drb = drb;

		reset();
	}

	void
	reset() {
		// Make robot stationary
		dlt->reset();
		dlb->reset();
		drt->reset();
		drb->reset();
	}

	bool
	drive(Direction dir, int speed) {
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
		case stop:
			_dlt->setSpeed(0);
			_dlb->setSpeed(0);
			_drt->setSpeed(0);
			_drb->setSpeed(0);
			break;			
	}




	setSpeed() {
	}
};

#endif // Drive_Subsystem.hpp