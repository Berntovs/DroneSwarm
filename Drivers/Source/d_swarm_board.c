#include <stdint.h>
#include <stdbool.h>

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "m_mqtt.h"

#include "m_status_led.h"
#include "m_tof.h"
#include "m_SPI.h"
#include "m_motor.h"
#include "d_encoder2.h"

#include "d_swarm_board.h"
#include "config.h"

void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}

/**
 * modules that can be initelized
 *
 * log_init() ->  start log module
 * mqttsn_init() -> start mqttsn and thread
 * timer_1_init(time[ms], event handler) -> for starting timer 1 with inturupt with given time and handler
 * status_led_1_init() -> start status led 1
 * status_led_2_init() -> start status led 2
 * app_tof_init() -> start all Vl53L0X sensors
 * spim_0_init() -> start spim
 * spis_0_init() -> start spis
 */

void secondary_chip_init(void)
{
    log_init();
    status_led_1_init();
    spim_0_init();
    //mqttsn_init();                   // dependent of status led 1 init

}

void main_chip_init(void)
{
    log_init();
    status_led_1_init();
    status_led_2_init();
    status_led_1_mode(1);
    app_tof_init();
    gpio_init();
    init_motor_pwm();
    motor_run();
    spis_0_init();
}

void single_chip_init(void)
{
    log_init();
    status_led_1_init();
    app_tof_init();
    gpio_init();
    init_motor_pwm();
    motor_run();
    mqttsn_init();                   // dependent of status led 1 init
   // timer_1_init(2000, mqttsn_boot); // dependent on mqttsn_init
}

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