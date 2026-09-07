#ifndef COMMS_H
# define COMMS_H

# define ESPNOW_CHANNEL 0

// Estrutura dos dados enviados
typedef struct s_data
{
	char a[32];
	int b;
	float c;
	bool d;
} t_data;

#endif // COMMS_H
