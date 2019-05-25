#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "mqttsn_client.h"

#define SEND_XY 0x01
#define SET_MOTOR_SPEED 0x02

void message_decoder(uint8_t *p_packet);