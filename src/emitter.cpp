#include "emitter.h"

#include <Arduino.h>

const esp_now_peer_info_t g_peerInfo = { .peer_addr = RECEIVER_MAC };
t_espnow_data             g_data;
volatile bool             g_buttonState = LOW;

void sendCallback(const uint8_t* mac_addr, esp_now_send_status_t status)
{
	Serial.printf("\r\nLast Packet Send Status:\t%s\n",
	              status == ESP_NOW_SEND_SUCCESS ? "Delivery Success"
	                                             : "Delivery Fail");
}

/*
 * Rotina de serviço de interrupt.
 */
void onButtonPress()
{
	if (!g_buttonState) {
		g_buttonState = HIGH;

		detachInterrupt(digitalPinToInterrupt(BUTTON_PIN));
	}
}

/**
 * Inicializa o ESP-NOW, registra callback de envio e registra o MAC do receptor na lista de peers.
 */
esp_err_t initEspNow() {
	if (esp_now_init() != ESP_OK) {
		Serial.println("Error initializing ESP-NOW");
		return (ESP_FAIL);
	}

	if (esp_now_register_send_cb(sendCallback) != ESP_OK) {
		esp_now_deinit();
		Serial.println("Error ao registrar callback no emissor");
		return (ESP_FAIL);
	}

	if (esp_now_add_peer(&g_peerInfo) != ESP_OK) {
		esp_now_deinit();
		Serial.println("Failed to add peer");
		return (ESP_FAIL);
	}

	return (ESP_OK);
}
