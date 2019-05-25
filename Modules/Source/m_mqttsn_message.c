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


uint8_t motor_speeed[] ={1, 100, 65};
uint8_t motor_off[] = {1, 0, 0};
uint8_t get_range[] = {3};
uint8_t blank[];
uint8_t buffer[10];
void message_decoder(uint8_t *p_packet)
{
    //char *out;cJSON *json;
   // json = cJSON_Parse(p_packet);
    //char *id = cJSON_Print(json);
    uint8_t id = p_packet[0];
    switch (id)
    {
    case '1':

    spim_0_transfer(motor_speeed);
        break;

    case '2':
    spim_0_transfer(motor_off);
        
        break;
    case '3':
    /*spim_0_transfer(get_range);
    nrf_delay_ms(10);
    spim_0_transfer(blank);
    get_rx_buf(&buffer);*/
    
        break;
    default:
        //NRF_LOG_INFO("Command not reconised, command = %s, len: %s", json, id);
        break;
    }
        
       // NRF_LOG_INFO("Command not reconised, command = %s, len: %s", p_packet, id);
        
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