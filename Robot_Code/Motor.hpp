class Motor {
private:
	int _speed;
	int _control_pin;

public:
	Motor::Motor(int control_pin) {
		_control_pin = control_pin;
		pinMode(_control_pin, OUTPUT);
	}

	Motor *
	setSpeed(int speed) {
		_speed = speed;
		return this;
	}

	Motor *
	reset() {
		_speed = 0;
		return this;
	}
};