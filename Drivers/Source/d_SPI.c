#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "nrf_spi.h"
#include "app_error.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "swarm_board.h"
#include "config.h"
#include "m_motor.h"
#include "nrfx_spim.h"
#include "nrfx_spis.h"
#include "d_spi.h"
#include "m_tof.h"
#include "vl53l0x_api.h"

static uint8_t rx_buf[SPI_BUFFER_LENGTH];
static uint8_t tx_buf[SPI_BUFFER_LENGTH];

static nrfx_spim_t spim_3 = NRFX_SPIM_INSTANCE(3);
static nrfx_spis_t spis_2 = NRFX_SPIS_INSTANCE(2);

void spim_3_event_handler(nrfx_spim_evt_t const *p_event, void *p_context)
{
  if (p_event->type == NRFX_SPIM_EVENT_DONE)
  {
    NRF_LOG_INFO(" Transfer completed. Received data");
  }
}

void spim_3_transfer(uint8_t *p_tx_data)
{
  nrfx_spim_xfer_desc_t spim_3_desc = NRFX_SPIM_XFER_TRX(p_tx_data, SPI_BUFFER_LENGTH, rx_buf, SPI_BUFFER_LENGTH);
  APP_ERROR_CHECK(nrfx_spim_xfer(&spim_3, &spim_3_desc, 0));
}

void spim_3_init(void)
{
  ret_code_t err_code;

  nrfx_spim_config_t spim_3_config = NRFX_SPIM_DEFAULT_CONFIG;
  spim_3_config.sck_pin = SPIM_3_SCK_PIN;
  spim_3_config.mosi_pin = SPIM_3_MOSI_PIN;
  spim_3_config.miso_pin = SPIM_3_MISO_PIN;
  spim_3_config.ss_pin = SPIM_3_CS_PIN;

  err_code = nrfx_spim_init(&spim_3, &spim_3_config, NULL, NULL);
  APP_ERROR_CHECK(err_code);

  NRF_LOG_RAW_INFO("[SUCCESS] SPIM_0 is enabled \n");
}

static uint8_t a = 0;
VL53L0X_RangingMeasurementData_t dat_tof;

void spis_2_event_handler(nrfx_spis_evt_t const *p_event, void *p_context)
{
  if (p_event->evt_type == NRFX_SPIS_XFER_DONE)
  {
    uint8_t id = rx_buf[0];
    switch (id)
    {
    case 1:
      selectdirection.direction = rx_buf[1];
          motor_direction(&selectdirection);
      motor_run();
      break;

    default:
      break;
    }
    NRF_LOG_INFO(" Transfer received %d,%d,%d ", rx_buf[0], rx_buf[1], rx_buf[2]);
    nrfx_spis_buffers_set(&spis_2, tx_buf, SPI_BUFFER_LENGTH, rx_buf, SPI_BUFFER_LENGTH);
    NRF_LOG_FLUSH();
  }
  NRF_LOG_INFO("hey");
}

void spis_2_init(void)
{
  ret_code_t err_code;

  nrfx_spis_config_t spis_2_config = NRFX_SPIS_DEFAULT_CONFIG;
  spis_2_config.sck_pin = SPIS_2_SCK_PIN;
  spis_2_config.mosi_pin = SPIS_2_MOSI_PIN;
  spis_2_config.miso_pin = SPIS_2_MISO_PIN;
  spis_2_config.csn_pin = SPIS_2_CS_PIN;

  err_code = nrfx_spis_init(&spis_2, &spis_2_config, spis_2_event_handler, NULL);
  APP_ERROR_CHECK(err_code);
  nrfx_spis_buffers_set(&spis_2, tx_buf, SPI_BUFFER_LENGTH, rx_buf, SPI_BUFFER_LENGTH);
  NRF_LOG_RAW_INFO("[SUCCESS] SPIM_0 is enabled \n");
}
