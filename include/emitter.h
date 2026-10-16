#ifndef EMITTER_H
# define EMITTER_H

# include "comms.h"
# include "esp_now.h"

# include <stdint.h>

# define BUTTON_PIN 0

void sendCallback(const uint8_t* mac_addr, esp_now_send_status_t status);

esp_err_t initEspNow();

void onButtonPress();

extern const esp_now_peer_info_t g_peerInfo;
extern t_ctrl_pckt               g_data;
extern volatile bool             g_buttonState;

#endif // EMITTER_H
