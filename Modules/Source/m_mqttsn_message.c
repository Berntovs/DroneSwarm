#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "nrf_log.h"
#include "mqttsn_client.h"
#include "m_SPI.h"
#include "config.h"

#include "m_mqttsn_message.h"
uint8_t mes[10] = {1,1,1,1,1,1,1,1,1};
#if DUAL_CHIP_ENABLE
void message_decoder(uint8_t *p_packet)
{
    uint8_t id = p_packet[0];
    switch (id)
    {
    case '1':
    spim_0_transfer(mes, 1);
        break;

    case SET_MOTOR_SPEED:
        
        break;

    default:
        NRF_LOG_INFO("Command not reconised, command = %s, len: %d", p_packet, id);
        break;
    }
        
        NRF_LOG_INFO("Command not reconised, command = %s, len: %d", p_packet, id);
        
}
#else
void message_decoder(mqttsn_packet_t *p_packet)
{
    uint8_t data[p_packet->len] = p_packet->p_data;
    uint8_t id = data[0];
    switch (id)
    {
    case SEND_XY:
        break;

    case SET_MOTOR_SPEED:

        break;

    default:
        NRF_LOG_INFO("Command not reconised, command = %d", id);
        break;
    }
}
#endif