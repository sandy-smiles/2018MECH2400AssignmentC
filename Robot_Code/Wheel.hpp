#include <Servo.h>

#define SPEED_MAX 90
#define SPEED_MIN -90

class Wheel {
private:
	Servo wheel
	int _speed;
	int _control_pin;
	int _feedback_pin;
	int _current_pos;
	int _current_rev;

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
	Wheel::Wheel(int control_pin, int feedback_pin) {
		_control_pin = control_pin;
		_feedback_pin = feedback_pin;
		pinMode(_control_pin, OUTPUT);
		pinMode(_feedback_pin, INPUT);
		wheel.attach(_control_pin);
		wheel.write(mapSpeed(0));
	}

	Wheel *
	setSpeed(int speed) {
		_speed = mapSpeed(speed);
		wheel.write(_speed);
		return this;
	}

	Wheel *
	reset() {
		_speed = 0;
		_current_pos = 0;
		_current_rev = 0;
		wheel.write(mapSpeed(0));
		return this;
	}

	int
	getCurrentPos() {
		return _current_pos;
	}

	int
	getCurrentRev() {
		return _current_rev;
	}
};