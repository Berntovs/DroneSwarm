#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "nrf_log.h"
#include "mqttsn_client.h"
#include "m_SPI.h"
#include "config.h"
#include "cJSON.h"
#include "nrf_delay.h"
#include "mqttsn_client.h"

#include "m_mqttsn_message.h"

#if DUAL_CHIP_ENABLE

uint8_t motor_speeed[] = {1, 100, 65};
uint8_t motor_off[] = {1, 0, 0};
uint8_t get_range[] = {3};
uint8_t blank[];
uint8_t buffer[10];

void message_decoder(const char *  p_packet)
{


    int8_t id = p_packet[0];
    switch (id)
    {
    case '1':
        NRF_LOG_INFO("Command reconised, command = %d", id);
        spim_3_transfer(motor_speeed);
        break;

    case '2':
        spim_3_transfer(motor_off);
        NRF_LOG_INFO("Command reconised, command = %d", id);
        break;
    case '3':
        NRF_LOG_INFO("Command reconised, command = %d", id);
        break;
    default:
        NRF_LOG_INFO("Command not reconised, command = %d", id);
        break;
    }
    cJSON_Delete(json_packet);
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