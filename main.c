/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
 *
 * @defgroup thread_mqttsn_publisher_example_main main.c
 * @{
 * @ingroup thread_mqttsn_publisher_example
 * @brief Thread MQTT-SN Client Publisher Example Application main file.
 *
 * @details This example demonstrates an MQTT-SN client publisher application that enables to toggle
 *          BSP_LED_2 on a board with related MQTT-SN client subscriber application via MQTT-SN messages.
 *
 */
#include <stdbool.h>
#include <stdint.h>

#include "app_error.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "d_swarm_board.h"
#include "m_mqtt.h"
#include "m_tof.h"
#include "m_status_led.h"
#include "vl53l0x_def.h"
#include "m_motor.h"
#include "d_encoder2.h"
#include "m_spi.h"
#include "nrf_delay.h"

VL53L0X_RangingMeasurementData_t dat;
void main(void)
{
  ret_code_t err_code = NRF_LOG_INIT(NULL);
  APP_ERROR_CHECK(err_code);

  NRF_LOG_DEFAULT_BACKENDS_INIT();
#if SECONDARY_CHIP
  uint8_t data_tx[5] = {send_motor_speed, 0,50,0,50};
  spim_0_init();

  while (true)
  {
     spim_0_transfer(data_tx, 5);
      nrf_delay_ms(1000);
  }
#else
  //spis_0_init();
  app_tof_init();
  gpio_init();
  init_motor_pwm();
  motor_run();

  selectdirection.direction = 1;
  motor_direction(&selectdirection);

  while (true)
  {
    data1();
    data2();
    app_tof_get_range(&dat, 1);
    NRF_LOG_INFO("range: %d", dat.RangeMilliMeter);
    NRF_LOG_FLUSH();
    nrf_delay_ms(200);
  }

#endif
}

/**
 *@}
 **/
