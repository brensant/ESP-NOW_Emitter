#include "Controller.h"

#include <Arduino.h>

/********************************* LIFECYCLE **********************************/

Controller::Controller(int xPin, int yPin, int buttonPin)
  : m_xPin(xPin)
  , m_yPin(yPin)
  , m_buttonPin(buttonPin)
  , m_centerX(ADC_MAX / 2)
  , m_centerY(ADC_MAX / 2)
{
}

Controller::~Controller()
{
}

/************************ NON-STATIC MEMBER FUNCTIONS *************************/

/*
 * Rotina para ser chamada no `setup()`.
 */
void Controller::init()
{
	pinMode(m_xPin, INPUT),
	pinMode(m_yPin, INPUT),
	pinMode(m_buttonPin, INPUT_PULLUP);
	calibrate();
}

void Controller::calibrate()
{
	m_centerX = readAverage(m_xPin, 64);
	m_centerY = readAverage(m_yPin, 64);
}

uint16_t Controller::getX() const
{
	return (normalize(readAverage(m_xPin), m_centerX));
}

uint16_t Controller::getY() const
{
	return (normalize(readAverage(m_yPin), m_centerY));
}

bool Controller::isButtonPressed() const
{
	return (digitalRead(m_buttonPin) == LOW); // INPUT_PULLUP: pressionado = LOW
}

/****************************** HELPER FUNCTIONS ******************************/

/*
 * Calcula uma média das leituras para diminuir o ruído do ESP32.
 */
uint16_t Controller::readAverage(int pin, int samples) const
{
	uint32_t sum = 0;

	for (int i = 0; i < samples; i++)
		sum += analogRead(pin);

	return (sum / samples);
}

/**
 * Converte a leitura crua (0..4095) em 0..255, com o centro calibrado em 128 e
 * uma zona morta em volta dele.
 */
uint8_t Controller::normalize(uint16_t raw, uint16_t center) const
{
	if (abs((int)raw - (int)center) < DEADZONE)
		return (128);

	if (raw < center)
		return (map(raw, 0, center - DEADZONE, 0, 127));
	return (map(raw, center + DEADZONE, ADC_MAX, 129, 255));
}
