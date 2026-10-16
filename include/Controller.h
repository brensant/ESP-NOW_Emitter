#ifndef CONTROLLER_HPP
# define CONTROLLER_HPP

# include <cstdint>

# define CONTROLLER_VRX_PIN 0 // Pino eixo X (analógico)
# define CONTROLLER_VRY_PIN 1 // Pino eixo Y (analógico)
# define CONTROLLER_SW_PIN  2 // Pino botão  (digital)

class Controller {
  public:
	Controller(int xPin = CONTROLLER_VRX_PIN, int yPin = CONTROLLER_VRY_PIN, int buttonPin = CONTROLLER_SW_PIN);
	~Controller();

	void init(void (*onPressedRoutine)() = nullptr);

	uint16_t getX() const;
	uint16_t getY() const;
	int      getJoystickButton() const;

  private:
	const int m_xPin;
	const int m_yPin;
	const int m_buttonPin;
};


#endif // CONTROLLER_HPP
