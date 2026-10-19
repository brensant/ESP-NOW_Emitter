#include "comms.h"
#include "Joystick.h"
#include "Emitter.h"

#include <Arduino.h>
#include <WiFi.h>

static constexpr uint32_t SEND_PERIOD_MS = 20; // 50 Hz
static const uint8_t      RECEIVER[] = RECEIVER_MAC;

Joystick g_joystick;
Emitter  g_emitter(RECEIVER);
bool     g_ready = false;
uint32_t g_lastSend = 0;

void setup()
{
	Serial.begin(9600);
	WiFi.mode(WIFI_STA);

	g_joystick.init();
	g_ready = (g_emitter.init() == ESP_OK);
}

void loop()
{
	if (!g_ready) {
		Serial.println("Erro ao iniciar emissor");
		delay(1000);
		return;
	}

	uint32_t now = millis();

	if (now - g_lastSend < SEND_PERIOD_MS)
		return;

	g_lastSend = now;

	t_ctrl_pckt packet = {};
	packet.steering = g_joystick.getX();
	packet.throttle = g_joystick.getY();
	packet.button = g_joystick.isButtonPressed();

	if (g_emitter.send(packet) != ESP_OK)
		Serial.println("Error sending the data");
}
