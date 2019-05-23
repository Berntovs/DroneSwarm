#include <stdint.h>
#include <stdbool.h>

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "m_mqtt.h"

#include "d_swarm_board.h"
#include "config.h"

void board_init(void)
{
#if DUAL_CHIP_ENABLE
#if SECONDARY_CHIP
    secondary_chip_init();
#else
    main_chip_init();
#endif
#else
    single_chip_init();
#endif
}

/**
 * log_init() ->  start log module
 * mqttsn_init() -> start mqttsn and thread
 */

void secondary_chip_init(void)
{
#if NRF_LOG_USED
    log_init();
#endif
    mqttsn_init();
}

void main_chip_init(void)
{

#if NRF_LOG_USED
    log_init();
#endif
}

void single_chip_init(void)
{
    mqttsn_init();
#if NRF_LOG_USED
    log_init();
#endif
}

void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}