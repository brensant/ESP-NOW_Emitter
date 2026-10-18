#ifndef CONTROLLER_HPP
# define CONTROLLER_HPP

# include <cstdint>

# define CONTROLLER_VRX_PIN 0 // Pino eixo X (analógico)
# define CONTROLLER_VRY_PIN 1 // Pino eixo Y (analógico)
# define CONTROLLER_SW_PIN  2 // Pino botão  (digital)

class Controller {
  public:
	static constexpr uint16_t ADC_MAX  = 4095; // ADC de 12 bits
	static constexpr uint16_t DEADZONE = 150;  // zona morta ao redor do centro (em contagens do ADC)

	Controller(int xPin = CONTROLLER_VRX_PIN, int yPin = CONTROLLER_VRY_PIN, int buttonPin = CONTROLLER_SW_PIN);

	void init();
	void calibrate();

	uint16_t getX() const;
	uint16_t getY() const;
	bool     isButtonPressed() const;

  private:
	uint16_t readAverage(int pin, int samples = 16) const;
	uint8_t  normalize(uint16_t raw, uint16_t center) const;

	const int m_xPin;
	const int m_yPin;
	const int m_buttonPin;

	uint16_t m_centerX;
	uint16_t m_centerY;
};

#endif // CONTROLLER_HPP
