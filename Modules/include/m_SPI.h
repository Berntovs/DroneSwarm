#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "nrfx_spim.h"
#include "nrfx_spis.h"
#include "config.h"

#define SPIM_0_MOSI_PIN UART_RX_PIN
#define SPIM_0_MISO_PIN UART_TX_PIN
#define SPIM_0_CS_PIN UART_CTS_PIN
#define SPIM_0_SCK_PIN UART_RTS_PIN

#define SPIS_0_MOSI_PIN UART_TX_PIN
#define SPIS_0_MISO_PIN UART_RX_PIN
#define SPIS_0_CS_PIN UART_CTS_PIN
#define SPIS_0_SCK_PIN UART_RTS_PIN

#define SPIS_0_BUFFER_LENGTH SPI_BUFFER_LENGTH_DEFAULT
#define SPIM_0_BUFFER_LENGTH SPI_BUFFER_LENGTH_DEFAULT

typedef enum
{
    send_motor_speed = 1,
    get_xy_cor,
    get_sensor_data
} spi_command_t;

#if SECONDARY_CHIP
void spim_0_init(void);
void spim_0_transfer(uint8_t *p_tx_data, uint8_t tx_data_length);
#else
void spis_0_init(void);
#endif

