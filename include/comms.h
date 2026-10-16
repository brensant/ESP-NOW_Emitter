#ifndef COMMS_H
# define COMMS_H

# include "esp_now.h"

# include <stdint.h>

# define ESPNOW_CHANNEL 0

# define EMITTER_MAC { 0xA0, 0xA3, 0xB3, 0x29, 0x76, 0xA8 }
# define RECEIVER_MAC { 0xA0, 0xA3, 0xB3, 0x29, 0x38, 0x14 }

typedef struct s_flags {
	unsigned int direcao: 1;
	unsigned int arma: 1;
	unsigned int sentidoArma: 1;
} t_flags;

typedef struct s_espnow_data {
	uint8_t value;
	uint16_t packetId;
	uint8_t  acelerador; // Y
	uint8_t  direcao;    // X
	t_flags  flags;
} t_espnow_data;

typedef t_espnow_data t_ctrl_pckt;

#endif // COMMS_H
