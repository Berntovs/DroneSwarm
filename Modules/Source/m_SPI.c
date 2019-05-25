#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "nrf_spi.h"
#include "app_error.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "d_swarm_board.h"
#include "config.h"
#include "m_motor.h"
#include "nrfx_spim.h"
#include "nrfx_spis.h"
#include "m_spi.h"

#if SECONDARY_CHIP
static uint8_t rx_buf[SPIM_0_BUFFER_LENGTH];
static uint8_t tx_buf[SPIM_0_BUFFER_LENGTH];
static nrfx_spim_t spim_0 = NRFX_SPIM_INSTANCE(0);
void spim_0_event_handler(nrfx_spim_evt_t const *p_event, void *p_context)
{
  if (p_event->type == NRFX_SPIM_EVENT_DONE)
  {
    NRF_LOG_INFO(" Transfer completed. Received data");
  }
}

void spim_0_transfer(uint8_t *p_tx_data, uint8_t tx_data_length)
{
  //for (uint8_t i = 0; i < tx_data_length; i++)
  //{
  // tx_buf[0] = p_tx_data[0];
  //}
  nrfx_spim_xfer_desc_t spim_0_desc = NRFX_SPIM_XFER_TRX(p_tx_data, SPIM_0_BUFFER_LENGTH, rx_buf, SPIM_0_BUFFER_LENGTH);
  APP_ERROR_CHECK(nrfx_spim_xfer(&spim_0, &spim_0_desc, 0));
}

void spim_0_init(void)
{
  ret_code_t err_code;

  nrfx_spim_config_t spim_0_config = NRFX_SPIM_DEFAULT_CONFIG;
  spim_0_config.sck_pin = SPIM_0_SCK_PIN;
  spim_0_config.mosi_pin = SPIM_0_MOSI_PIN;
  spim_0_config.miso_pin = SPIM_0_MISO_PIN;
  spim_0_config.ss_pin = SPIM_0_CS_PIN;

  err_code = nrfx_spim_init(&spim_0, &spim_0_config, NULL, NULL);
  APP_ERROR_CHECK(err_code);

  NRF_LOG_RAW_INFO("[SUCCESS] SPIM_0 is enabled \n");
}

#else
static uint8_t rx_buf[SPIS_0_BUFFER_LENGTH];
static uint8_t tx_buf[SPIS_0_BUFFER_LENGTH];
static nrfx_spis_t spis_0 = NRFX_SPIS_INSTANCE(2);
void spis_0_event_handler(nrfx_spis_evt_t const *p_event, void *p_context)
{
  if (p_event->evt_type == NRFX_SPIS_XFER_DONE)
  {
    uint8_t id = rx_buf[0];
    switch (id)
    {
    case send_motor_speed:
      speed.speed_a = (rx_buf[1] << 8) | (rx_buf[2]);
      speed.speed_b = (rx_buf[3] << 8) | (rx_buf[4]);
      motor_speed(&speed);
      break;

    default:
      break;
    }
    NRF_LOG_INFO(" Transfer received %d,%d,%d ", rx_buf[0], rx_buf[1], rx_buf[2]);
    nrfx_spis_buffers_set(&spis_0, tx_buf, SPIS_0_BUFFER_LENGTH, rx_buf, SPIS_0_BUFFER_LENGTH);
    NRF_LOG_FLUSH();
  }
}

void spis_0_init(void)
{
  ret_code_t err_code;

  nrfx_spis_config_t spis_0_config = NRFX_SPIS_DEFAULT_CONFIG;
  spis_0_config.sck_pin = SPIS_0_SCK_PIN;
  spis_0_config.mosi_pin = SPIS_0_MOSI_PIN;
  spis_0_config.miso_pin = SPIS_0_MISO_PIN;
  spis_0_config.csn_pin = SPIS_0_CS_PIN;

  err_code = nrfx_spis_init(&spis_0, &spis_0_config, spis_0_event_handler, NULL);
  APP_ERROR_CHECK(err_code);
  nrfx_spis_buffers_set(&spis_0, tx_buf, SPIS_0_BUFFER_LENGTH, rx_buf, SPIS_0_BUFFER_LENGTH);
  NRF_LOG_RAW_INFO("[SUCCESS] SPIM_0 is enabled \n");
}
#endif
