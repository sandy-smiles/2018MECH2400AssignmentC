// Sensor_Command
/*
 * Waits until a specified sensor is/is not pressed.
 * 
 * Input:
 *  - Sensor pin
 *  - Sensor state
 * Output:
 *  - No visible output
 * Notes:
 * 
 */

#include "RobotCmd.hpp"
#include "RobotRunner.hpp"

// #define SENSOR_PRESSED 0

class Sensor_Command: public RobotCmd {
private:
  int _sensor_pin;
  bool _sensor_state;

public:
  Sensor_Command(int sensor_pin, bool sensor_state) {
    _sensor_pin = sensor_pin;
    _sensor_state = sensor_state;
  }
  
  void initialise() {
    Serial.println("Initialising Sensor_Command\n");
    pinMode(_sensor_pin, INPUT_PULLUP);	// Use the pin's internal pull up resistor.
  }

  bool execute() {
  	bool sensed = digitalRead(_sensor_pin);

    if (sensed == _sensor_state) {
      return true; // End the Command
    }
    return false;
  }

  void end() {
  }
};
