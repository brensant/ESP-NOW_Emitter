#include "comms.h"
#include "emitter.h"

#include <WiFi.h>
#include <esp_now.h>

void setup()
{
	Serial.begin(9600);
	WiFi.mode(WIFI_STA);

	pinMode(BUTTON_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onButtonPress, FALLING);

	if (initEspNow() != ESP_OK)
		return;
}

void loop()
{
	if (g_buttonState) {
		Serial.println("Botão pressionado\n");
		g_data.value = !g_data.value;

		// Send message via ESP-NOW
		esp_err_t result = esp_now_send(g_peerInfo.peer_addr, (uint8_t*)&g_data, sizeof g_data);

		if (result == ESP_OK) {
			Serial.println("Sent with success");
		} else {
			Serial.println("Error sending the data");
		}

		g_buttonState = LOW;

		attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onButtonPress, FALLING);
	}

	delay(10);
}
