#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "app_error.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#include "m_sensors.h"
#include "d_mqtt.h"
#include "m_JSON.h"

#include "swarm_board.h"
#include "m_ascii_converter.h"

void main(void)
{
    board_init();
    nrf_delay_ms(1000);
    while (1)
    {
        mqttsn_loop();
        NRF_LOG_FLUSH();
    }
}

/**
 *@}
 **/
