#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "nrfx_spim.h"
#include "nrfx_spis.h"
#include "app_error.h"
#include "nrf_log.h"
#include "d_swarm_board.h"

#include "m_spi.h"

static const nrfx_spim_t spim_0 = NRFX_SPIM_INSTANCE(0);
static const nrfx_spis_t spis_0 = NRFX_SPIS_INSTANCE(0);

static uint8_t SPI_data_rx;
static uint8_t _tx_buf;
static uint8_t rx_data;

void spis_0_event_handler(nrfx_spis_evt_t const *p_event, void *p_context)
{
}

void spi_1_transfer(nrfx_spim_t *spi_instance, uint8_t tx_data)
{
  _tx_buf = tx_data;
  static nrfx_spim_xfer_desc_t simp_transf_desc = //NRFX_SPIM_SINGLE_XFER(tx_data, lengthof(tx_data), rx_data, 8);
      {
          .p_tx_buffer = &_tx_buf,
          .tx_length = 8,
          .p_rx_buffer = &rx_data,
          .rx_length = 8};
  APP_ERROR_CHECK(nrfx_spim_xfer(spi_instance, &simp_transf_desc, 0));
}

void spim_0_init(void)
{
  ret_code_t err_code;

  nrfx_spim_config_t spim_0_config = {
      .sck_pin = SPIM_0_SCK_PIN,
      .mosi_pin = SPIM_0_MOSI_PIN,
      .miso_pin = SPIM_0_MISO_PIN,
      .ss_pin = SPIM_0_CS_PIN,
      .irq_priority = NRFX_SPIM_DEFAULT_CONFIG_IRQ_PRIORITY,
      .orc = 0xFF,
      .frequency = NRF_SPI_FREQ_4M,
      .mode = NRF_SPI_MODE_0,
      .bit_order = NRF_SPI_BIT_ORDER_MSB_FIRST,
  };
  err_code = nrfx_spim_init(&spim_0, &spim_0_config, NULL, NULL);
  APP_ERROR_CHECK(err_code);

  NRF_LOG_RAW_INFO("[SUCCESS] SPI enabled for shield interface. \n")
}

void spis_0_init(void)
{
  ret_code_t err_code;

  nrfx_spis_config_t spis_0_config = {
      .sck_pin = SPIS_0_SCK_PIN,
      .mosi_pin = SPIS_0_MOSI_PIN,
      .miso_pin = SPIS_0_MISO_PIN,
      .ss_pin = SPIS_0_CS_PIN,
      .irq_priority = NRFX_SPIM_DEFAULT_CONFIG_IRQ_PRIORITY,
      .orc = 0xFF,
      .frequency = NRF_SPI_FREQ_4M,
      .mode = NRF_SPI_MODE_0,
      .bit_order = NRF_SPI_BIT_ORDER_MSB_FIRST,
  };

  nrfx_spis_init(&spis_0, &spis_0_config, spis_0_event_handler, NULL);
}