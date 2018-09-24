class Wheel {
private:
	int _speed;
	int _control_pin;
	int _feedback_pin;
	int _current_pos;
	int _current_rev;

public:
	Wheel::Wheel(int control_pin, int feedback_pin) {
		_control_pin = control_pin;
		_feedback_pin = feedback_pin;
		pinMode(_control_pin, OUTPUT);
		pinMode(_feedback_pin, INPUT);
	}

	Wheel *
	setSpeed(int speed) {
		_speed = speed;
		return this;
	}

	Wheel *
	reset() {
		_speed = 0;
		_current_pos = 0;
		_current_rev = 0;
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