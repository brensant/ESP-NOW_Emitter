#include "Controller.h"

#include <Arduino.h>

/*********************************** TYPES ************************************/

/********************************* LIFECYCLE **********************************/

Controller::Controller(int xPin, int yPin, int buttonPin)
  : m_xPin(xPin)
  , m_yPin(yPin)
  , m_buttonPin(buttonPin)
{
}

Controller::~Controller()
{
}

/************************** STATIC MEMBER FUNCTIONS ***************************/

/************************ NON-STATIC MEMBER FUNCTIONS *************************/

/*
 * Rotina para ser chamada no `setup()`.
 */
void Controller::init(void (*onPressRoutine)())
{
	pinMode(m_xPin, INPUT),
	pinMode(m_yPin, INPUT),
	pinMode(m_buttonPin, INPUT_PULLUP);

	if (onPressRoutine)
		attachInterrupt(digitalPinToInterrupt(m_buttonPin), onPressRoutine, FALLING);
}

uint16_t Controller::getX() const
{
	return (analogRead(m_xPin));
}

uint16_t Controller::getY() const
{
	return (analogRead(m_yPin));
}

int Controller::getJoystickButton() const
{
	return (digitalRead(m_buttonPin));
}

/* OPERATORS */

/****************************** HELPER FUNCTIONS ******************************/


/* OPERATORS */
