#include "comms.h"
#include "Controller.h"
#include "Emitter.h"

#include <Arduino.h>
#include <WiFi.h>

static constexpr uint32_t SEND_PERIOD_MS = 20; // 50 Hz
static const uint8_t      RECEIVER[] = RECEIVER_MAC;

Controller g_controller;
Emitter    g_emitter(RECEIVER);
bool       g_ready = false;
uint32_t   g_lastSend = 0;

void setup()
{
	Serial.begin(9600);
	WiFi.mode(WIFI_STA);

	g_controller.init();
	g_ready = (g_emitter.init() == ESP_OK);
}

void loop()
{
	if (!g_ready)
		return;

	uint32_t now = millis();

	if (now - g_lastSend < SEND_PERIOD_MS)
		return;

	g_lastSend = now;

	t_ctrl_pckt pckt = {};
	pckt.steering = g_controller.getX();
	pckt.throttle = g_controller.getY();
	pckt.flags.isWeaponEnabled = g_controller.isButtonPressed();

	if (g_emitter.send(pckt) != ESP_OK)
		Serial.println("Error sending the data");
}
