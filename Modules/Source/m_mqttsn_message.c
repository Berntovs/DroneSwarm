#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "nrf_log.h"

#include "m_mqttsn_message.h"

void message_decoder(message_t *p_message)
{
    uint8_t id = p_message->command; // id of message
    switch (id)
    {
    case SEND_XY:  // meassage id
        /* code */ // what todo when its recived this id
        break;

    default:
        NRF_LOG_INFO("Command not reconised, command = %d", id);
        break;
    }
}