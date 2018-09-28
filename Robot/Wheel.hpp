// Wheel
/*
 * Is used for driving the cascade lift
 * 
 * Defines:
 *  - private int mapSpeed
 *  - public Wheel
 *    - public Wheel *setSpeed
 *    - public Wheel *reset
 *    - public int getCurrentPos // Stub
 *    - public int getCurrentRev // Stub
 */

#ifndef _WHEEL_HPP
#define _WHEEL_HPP

#include <Servo.h>

#define SPEED_MAX 90
#define SPEED_MIN -90

class Wheel {
private:
	Servo _wheel;
	int _speed;
	int _control_pin;
	int _feedback_pin;
	int _current_pos;
	int _current_rev;

  // mapSpeed
  /*
   * Input:
   *  - Integer speed between -90 and 90
   * Output:
   *  - Mapped integer speed between 0 to 180
   */
	int
	mapSpeed(int speed) {
		if (speed > SPEED_MAX) {
			speed = SPEED_MAX;
		} else if (speed < SPEED_MIN) {
			speed = SPEED_MIN;
		}
		return (int)map(speed, SPEED_MIN, SPEED_MAX, 0, 180);
	}

public:
	Wheel(int control_pin, int feedback_pin) {
		_control_pin = control_pin;
		_feedback_pin = feedback_pin;
		pinMode(_control_pin, OUTPUT);
		pinMode(_feedback_pin, INPUT);
		_wheel.attach(_control_pin);
		_wheel.write(mapSpeed(0));
	}

  // setSpeed
  /*
   * Input:
   *  - Integer speed between -90 and 90
   * Output:
   *  - Servo moves at the specified speed
   */
	Wheel *
	setSpeed(int speed) {
		_speed = mapSpeed(speed);
		_wheel.write(_speed);
		return this;
	}

  // reset
  /*
   * Input:
   *  - None
   * Output:
   *  - Servo becomes stationary
   */
	Wheel *
	reset() {
		_speed = 0;
		_current_pos = 0;
		_current_rev = 0;
		_wheel.write(mapSpeed(0));
		return this;
	}

  // getCurrentPos (STUB)
  /*
   * Input:
   *  - None
   * Output:
   *  - Current position within the revolution (angle)
   */
	int
	getCurrentPos() {
		return _current_pos;
	}

  // getCurrentRev (STUB)
  /*
   * Input:
   *  - None
   * Output:
   *  - Current revolution
   */
	int
	getCurrentRev() {
		return _current_rev;
	}
};

#endif // Wheel.hpp
