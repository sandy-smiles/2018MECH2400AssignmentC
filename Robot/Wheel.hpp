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

#define WHEEL_SPEED_MAX 90
#define WHEEL_SPEED_MIN -90
#define REV_DEGREES 360

class Wheel {
private:
	Servo _wheel;
	int _speed;
	int _control_pin;
	//int _feedback_pin;
  //int _start_angle = 0;
	//int _current_pos;
	//int _current_rev;
  //int _current_angle;

  // mapSpeed
  /*
   * Input:
   *  - Integer speed between -90 and 90
   * Output:
   *  - Mapped integer speed between 0 to 180
   */
	int
	mapSpeed(int speed) {
		if (speed > WHEEL_SPEED_MAX) {
			speed = WHEEL_SPEED_MAX;
		} else if (speed < WHEEL_SPEED_MIN) {
			speed = WHEEL_SPEED_MIN;
		}
		return (int)map(speed, WHEEL_SPEED_MIN, WHEEL_SPEED_MAX, 0, 180); // 1500 is middle for writeMicroseconds, 90 for write
	}

  // http://forum.arduino.cc/index.php?topic=524993.5
  /*
   * Input:
   *  - Control pin for the wheel
   * Output:
   *  - The current angle where the servo is
   */
  float readPos(int pwmPin)
  {
   Serial.print("Wheel - Starting readPos()\n");
   int tHigh;
   int tLow;
   int tCycle;
  
   float theta = 0;
   float dc = 0;
   int unitsFC = 360;
   float dcMin = 0.029;
   float dcMax = 0.971;
   float dutyScale = 1;
   while(1) {
     pulseIn(pwmPin, LOW);
     tHigh = pulseIn(pwmPin, HIGH);
     tLow =  pulseIn(pwmPin, LOW);
     tCycle = tHigh + tLow;
     if ((tCycle > 1000) && ( tCycle < 1200)) break; // if ((tCycle > 1050) && ( tCycle < 1150)) break;
   }
  
   dc = (dutyScale * tHigh) / tCycle;
   theta = ((dc - dcMin) * unitsFC) / (dcMax - dcMin);
   Serial.print("Wheel - Finished readPos()\n");
   return theta;
  }

public:
	Wheel(int control_pin) {//, int feedback_pin) {
		_control_pin = control_pin;
		//_feedback_pin = feedback_pin;
		pinMode(_control_pin, OUTPUT);
		//pinMode(_feedback_pin, INPUT);
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
		_speed = speed;
		//_wheel.writeMicroseconds(mapSpeed(_speed));
    _wheel.write(mapSpeed(_speed));
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
		//_current_pos = 0;
		//_current_rev = 0;
    //_current_angle = 0;
		_wheel.write(mapSpeed(0));
    //_start_angle = readPos(_feedback_pin);
		return this;
	}

  // getCurrentPos
  /*
   * Input:
   *  - None
   * Output:
   *  - Current position within the revolution (angle)
	int
	getCurrentPos() {
    _current_pos = getCurrentRev()*REV_DEGREES+_current_angle;
		return _current_pos;
	}
   */

  // getCurrentRev
  /*
   * Input:
   *  - None
   * Output:
   *  - Current revolution
	int
	getCurrentRev() {
    int angle = _current_angle;
    int tmp = getCurrentAngle();
    // If our previous polled angle is greater than our current polled angle
    if (_current_angle-angle < 0) { 
      _current_rev++;
    }
		return _current_rev;
	}
   */

  // getCurrentAngle
  /*
   * Input:
   *  - None
   * Output:
   *  - Current Angle within revolution
  int
  getCurrentAngle() {
    int angle = readPos(_feedback_pin);
    _current_angle = (angle-_start_angle+REV_DEGREES)%REV_DEGREES;
    return _current_angle;
  }
   */
 
};

#endif // Wheel.hpp
