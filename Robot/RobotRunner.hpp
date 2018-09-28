/*
 * Robot executer
 *
 * This code will execute  all the RobotCmd structs added.
 * Initially they are added inactive, the first is made active and we start running them.
 *
 * Sadly, we run through a linked list of all RobotCmd each loop to see which are active.
 * But given we generally have only a few commands this n^2 should not become burdensome.
 * If it does a smarter algorithm is required.
 *
 * Taken from https://github.com/rexdibona/ArduinoRobotExample/blob/master/RobotRunner.hpp
 *
 */
#ifndef _ROBOTRUNNER_HPP
#define _ROBOTRUNNER_HPP
#include "RobotCmd.hpp"		// we need the RobotCmd strustures that we utilise.

class RobotRunner {
public:
	RobotCmd *_base;
	
	RobotRunner()
	{
		_base = NULL;	// initialise it!
	}

	RobotRunner *
	add(RobotCmd *newRC) {
		if (newRC == NULL) return this;	// all done
		_base = newRC->setNext(_base);
		add(newRC->_sibling);
		add(newRC->_child);
		return this;
	}

	void
	setParallelActive(RobotCmd *setRC) {
		while (setRC != NULL) {
			setRC->initialise();
			setRC->_active = true;
			setRC = setRC->_sibling;
		}
	}

	void
	update() {
		RobotCmd *ptr;

		for (ptr = _base; ptr != NULL; ptr = ptr->_next) {
			if (ptr->_active == false) {
				continue;
			}
			if (ptr->execute()) {
				ptr->_active = false;
				setParallelActive(ptr->_child);
			}
		}
	}
};

#endif /* RobotRunner.hpp */
