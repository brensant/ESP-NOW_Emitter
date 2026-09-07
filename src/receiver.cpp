/* #include "comms.h"

#include <esp_now.h>
#include <WiFi.h>

t_data data;

// Callback para o recebimento de dados
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
	memcpy(&data, incomingData, sizeof(data));
	Serial.print("Bytes received: ");
	Serial.println(len);
	Serial.print("Char: ");
	Serial.println(data.a);
	Serial.print("Int: ");
	Serial.println(data.b);
	Serial.print("Float: ");
	Serial.println(data.c);
	Serial.print("Bool: ");
	Serial.println(data.d);
	Serial.println();
}

void setup() {
	Serial.begin(9600);

	WiFi.mode(WIFI_STA);

	// Inicializa ESP-NOW
	if (esp_now_init() != ESP_OK) {
		Serial.println("Error initializing ESP-NOW");
		return;
	}

	// Associa o callback de recebimento
	esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}

void loop() {

}
 */
