// Drive_Sensor_Command
/*
 * Allows the robot to drive in the specified direction until a specified sensor is pressed.
 * 
 * Input:
 *  - Drive Subsystem
 *  - Direction
 *  - Sensor pin
 *  - Sensor state
 *  - Servo Speed
 * Output:
 *  - Visible driving.
 * Notes:
 * 
 */

#include "RobotCmd.hpp"
#include "RobotRunner.hpp"
#include "Drive_Subsystem.hpp"

// #define SENSOR_PRESSED 0

class Drive_Sensor_Command: public RobotCmd {
private:
  Drive_Subsystem *_drive;
  Direction _dir;
  int _sensor_pin;
  bool _sensor_state;
  int _speed;

public:
  Drive_Sensor_Command(Drive_Subsystem *drive, Direction dir, int sensor_pin, bool sensor_state, int speed) {
    _drive = drive;
    _dir = dir;
    _sensor_pin = sensor_pin;
    _sensor_state = sensor_state;
    _speed = speed;
  }
  
  void initialise() {
    Serial.println("Initialising Drive_Sensor_Command\n");
    pinMode(_sensor_pin, INPUT_PULLUP);	// Use the pin's internal pull up resistor.
  }

  bool execute() {
  	bool sensed = digitalRead(_sensor_pin);

    if (sensed == _sensor_state) {
      return true; // End the Command
    }

    _drive->drive(_dir, _speed);
    return false;
  }

  void end() {
    _drive->drive(drive_stop, 0);
  }
};
