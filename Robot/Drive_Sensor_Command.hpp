// Drive_Command
/*
 * Allows the robot to drive in the specified direction for a certain amount of time.
 * 
 * Input:
 *  - Time in milliseconds
 *  - Direction
 * Output:
 *  - Visible driving.
 * Notes:
 *  - Time input should be more than 3 milliseconds due to capabilities of the current arduinos.
 * 
 */

#include "RobotCmd.hpp"
#include "RobotRunner.hpp"
#include "Drive_Subsystem.hpp"

#define SENSOR_PRESSED 0

class Drive_Command: public RobotCmd {
private:
  Drive_Subsystem *_drive;
  Direction _dir;
  int _sensor_pin
  int _speed;

public:
  Drive_Command::Drive_Command(Drive_Subsystem *drive, Direction dir, int sensor_pin, int speed) {
    _drive = drive;
    _dir = dir;
    _sensor_pin = sensor_pin;
    _speed = speed;
  }
  
  void initialise() {
    pinMode(_sensor_pin, INPUT_PULLUP);	// Use the pin's internal pull up resistor.
  }

  bool execute() {
  	bool sensed = digitalRead(_sensor_pin);

    if (sensed == SENSOR_PRESSED) {
      return true; // End the Command
    }

    _drive->drive(_dir, _speed);
    return false;
  }

  void end() {
    _drive->drive(stop, 0);
  }
};
