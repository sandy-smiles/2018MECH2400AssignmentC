// Lift_Time_Sensor_Command
/*
 * Allows the robot to move the lift in the specified direction funtil a specified sensor is pressed.
 * 
 * Input:
 *  - Lift Subsystem
 *  - Direction
 *  - Time in milliseconds
 *  - Servo Speed
 * Output:
 *  - Visible movement of the cascade lift.
 * Notes:
 *  - Time input should be more than 3 milliseconds due to capabilities of the current arduinos.
 * 
 */

#include "RobotCmd.hpp"
#include "RobotRunner.hpp"
#include "Drive_Subsystem.hpp"

// #define SENSOR_PRESSED 0

class Lift_Time_Sensor_Command: public RobotCmd {
private:
  Lift_Subsystem *_lift;
  Lift_Direction _dir;
  unsigned long _time;
  int _sensor_pin;
  bool _sensor_state;
  int _speed;

public:
  Lift_Time_Sensor_Command(Lift_Subsystem *lift, Lift_Direction dir, unsigned long time, int sensor_pin, bool sensor_state, int speed) {
    _lift = lift;
    _dir = dir;
    _time = time;
    _sensor_pin = sensor_pin;
    _sensor_state = sensor_state;
    _speed = speed;
  }
  
  void initialise() {
    Serial.println("Initialising Lift_Time_Sensor_Command\n");
    _time = millis() + _time;	// _time is now the end time.
    pinMode(_sensor_pin, INPUT_PULLUP);	// Use the pin's internal pull up resistor.
  }

  bool execute() {
    unsigned long curTime = millis();
  	bool sensed = digitalRead(_sensor_pin);

    if (curTime > _time && sensed == _sensor_state) {
      return true; // End the Command
    }

    _lift->move(_dir, _speed);
    return false;
  }

  void end() {
    _lift->move(lift_stop, 0);
  }
};
