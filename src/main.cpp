#include "comms.h"

#include <esp_now.h>
#include <WiFi.h>

esp_now_peer_info_t g_peer_info = {
	.peer_addr = { 0xA0, 0xA3, 0xB3, 0x29, 0x38, 0x14 }, // Endereço MAC do robô
	.channel = ESPNOW_CHANNEL,
	.encrypt = false
};

// Callback para o envio de dados
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
	Serial.print("\r\nLast Packet Send Status:\t");
	Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
	Serial.begin(9600);

	WiFi.mode(WIFI_STA);

	// Inicializa ESP-NOW
	if (esp_now_init() != ESP_OK) {
		Serial.println("Error initializing ESP-NOW");
		return;
	}

	// Associa o callback de envio
	esp_now_register_send_cb(esp_now_send_cb_t(OnDataSent));

	// Add peer
	if (esp_now_add_peer(&g_peer_info) != ESP_OK){
		Serial.println("Failed to add peer");
		return;
	}
}

void loop() {
	t_data data = {
		.a = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '\0'},
		.b = random(1, 20),
		.c = 3.14F,
		.d = true
	};

	// Send message via ESP-NOW
	esp_err_t result = esp_now_send(g_peer_info.peer_addr, (const uint8_t *)&data, sizeof(data));

	if (result == ESP_OK)
		Serial.println("Sent with success");
	else
		Serial.println("Error sending the data");

	data.d = !data.d;

	delay(2000);
}

// #include <Arduino.h>

// void setup() {
// 	Serial.begin(9600);
// }

// void loop() {
// 	Serial.println("Hello");
// 	delay(1000);
// }

// #include <esp_now.h>
// #include <WiFi.h>

// // REPLACE WITH YOUR RECEIVER MAC Address
// uint8_t broadcastAddress[] = { 0xA0, 0xA3, 0xB3, 0x29, 0x38, 0x14 };

// // Structure example to send data
// // Must match the receiver structure
// typedef struct struct_message {
//   char a[32];
//   int b;
//   float c;
//   bool d;
// } struct_message;

// // Create a struct_message called myData
// struct_message myData;

// esp_now_peer_info_t peerInfo;

// // callback when data is sent
// void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//   Serial.print("\r\nLast Packet Send Status:\t");
//   Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
// }

// void setup() {
//   // Init Serial Monitor
//   Serial.begin(115200);

//   // Set device as a Wi-Fi Station
//   WiFi.mode(WIFI_STA);

//   // Init ESP-NOW
//   if (esp_now_init() != ESP_OK) {
//     Serial.println("Error initializing ESP-NOW");
//     return;
//   }

//   // Once ESPNow is successfully Init, we will register for Send CB to
//   // get the status of Trasnmitted packet
//   esp_now_register_send_cb(esp_now_send_cb_t(OnDataSent));

//   // Register peer
//   memcpy(peerInfo.peer_addr, broadcastAddress, 6);
//   peerInfo.channel = 0;
//   peerInfo.encrypt = false;

//   // Add peer
//   if (esp_now_add_peer(&peerInfo) != ESP_OK){
//     Serial.println("Failed to add peer");
//     return;
//   }
// }

// void loop() {
//   // Set values to send
//   strcpy(myData.a, "THIS IS A CHAR");
//   myData.b = random(1,20);
//   myData.c = 1.2;
//   myData.d = false;

//   // Send message via ESP-NOW
//   esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

//   if (result == ESP_OK) {
//     Serial.println("Sent with success");
//   }
//   else {
//     Serial.println("Error sending the data");
//   }
//   delay(2000);
// }
