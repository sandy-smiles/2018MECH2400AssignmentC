// Motor
/*
 * Is used for driving the chassis
 * 
 * Defines:
 *  - private int mapSpeed
 *  - public Motor
 *    - public Motor *setSpeed
 *    - public Motor *reset
 */

#ifndef _MOTOR_HPP
#define _MOTOR_HPP

#include <Servo.h>

#define MOTOR_SPEED_MAX 90
#define MOTOR_SPEED_MIN -90

class Motor {
private:
	Servo _motor;
	int _speed;
	int _control_pin;

  // mapSpeed
  /*
   * Input:
   *  - Integer speed between -90 and 90
   * Output:
   *  - Mapped integer speed between 0 to 180
   */
  int
  mapSpeed(int speed) {
    if (speed > MOTOR_SPEED_MAX) {
      speed = MOTOR_SPEED_MAX;
    } else if (speed < MOTOR_SPEED_MIN) {
      speed = MOTOR_SPEED_MIN;
    }
    return (int)map(speed, MOTOR_SPEED_MIN, MOTOR_SPEED_MAX, 180, 0);
  }

public:
	Motor(int control_pin) {
		_control_pin = control_pin;
		pinMode(_control_pin, OUTPUT);
		_motor.attach(_control_pin);
		_motor.write(mapSpeed(0));
	}

  // setSpeed
  /*
   * Input:
   *  - Integer speed between -90 and 90
   * Output:
   *  - Servo moves at the specified speed
   */
	Motor *
	setSpeed(int speed) {
    _speed = mapSpeed(speed);
		_motor.write(_speed);
		return this;
	}

  // reset
  /*
   * Input:
   *  - None
   * Output:
   *  - Servo becomes stationary
   */
	Motor *
	reset() {
		_speed = 0;
		_motor.write(mapSpeed(0));
		return this;
	}
};


#endif // Motor.hpp
