#include "Emitter.h"

#include <Arduino.h>

#include <cstring>

/********************************* LIFECYCLE **********************************/

Emitter::Emitter(const uint8_t* peerMac)
  : m_nextPacketId(0)
{
	memset(&m_peer, 0, sizeof m_peer);
	memcpy(m_peer.peer_addr, peerMac, ESP_NOW_ETH_ALEN);
	m_peer.channel = ESPNOW_CHANNEL;
	m_peer.encrypt = false;
}

Emitter::~Emitter()
{
}

/************************** STATIC MEMBER FUNCTIONS ***************************/

void Emitter::onSent(const uint8_t* macAddr, esp_now_send_status_t status)
{
	if (status != ESP_NOW_SEND_SUCCESS)
		Serial.println("Delivery Fail");
}

/************************ NON-STATIC MEMBER FUNCTIONS *************************/

esp_err_t Emitter::init()
{
	if (esp_now_init() != ESP_OK) {
		Serial.println("Error initializing ESP-NOW");
		return (ESP_FAIL);
	}

	if (esp_now_register_send_cb(onSent) != ESP_OK) {
		esp_now_deinit();
		Serial.println("Error registering send callback");
		return (ESP_FAIL);
	}

	if (esp_now_add_peer(&m_peer) != ESP_OK) {
		esp_now_deinit();
		Serial.println("Failed to add peer");
		return (ESP_FAIL);
	}

	return (ESP_OK);
}

esp_err_t Emitter::send(t_ctrl_pckt& packet)
{
	packet.packetId = m_nextPacketId++;

	return (esp_now_send(m_peer.peer_addr, (const uint8_t*)&packet, sizeof packet));
}
