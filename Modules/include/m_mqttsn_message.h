#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define SEND_XY 0x01

typedef struct
{
    uint8_t command;
    uint8_t data;
    uint8_t data_length;
} message_t;

void message_decoder(message_t *p_message);