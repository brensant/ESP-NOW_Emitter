#ifndef EMITTER_H
# define EMITTER_H

# include "comms.h"
# include "esp_now.h"

# include <stdint.h>

class Emitter {
  public:
	Emitter(const uint8_t* peerMac);

	esp_err_t init();
	esp_err_t send(t_ctrl_pckt& packet);

  private:
	// O ESP-NOW exige callback sem `this`, portanto precisa ser static.
	static void onSent(const uint8_t* macAddr, esp_now_send_status_t status);

	esp_now_peer_info_t m_peer;
	uint16_t            m_nextPacketId;
};

#endif // EMITTER_H
