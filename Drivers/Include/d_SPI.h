#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "nrfx_spim.h"
#include "nrfx_spis.h"
#include "config.h"

#define SPIM_3_MOSI_PIN UART_RX_PIN //1,15
#define SPIM_3_MISO_PIN UART_TX_PIN //1,14
#define SPIM_3_CS_PIN UART_CTS_PIN  //1,13
#define SPIM_3_SCK_PIN UART_RTS_PIN //1,12

#define SPIS_2_MOSI_PIN UART_RTS_PIN //shld mosi
#define SPIS_2_MISO_PIN UART_TX_PIN  //shld miso
#define SPIS_2_CS_PIN UART_CTS_PIN   //shld cs
#define SPIS_2_SCK_PIN UART_RX_PIN   //shld sck

#define SPI_BUFFER_LENGTH SPI_BUFFER_LENGTH_DEFAULT

/**
 * @brief commands for the spi dualchip
 */
typedef enum
{
    start_motor = 1,
    stop_motor,
    turn_ccw,
    turn_cw
} spi_command_t;

/**
 * @brief Function for initialize the spim 3 instance
 */
void spim_3_init(void);

/**
 * @brief Function for initialize the spis 2 instance
 */
void spis_2_init(void);

/**
 * @brief Function for sending data to slave, aswell for reciving data
 *
 * @param[in] p_tx_data pointer to data that is to be transferd
 *
 * @info this function will fill the rx_buffer with data from slave every time its called
 *
 * @info the total number of bytes that is transfered is defined by SPI_BUFFER_LENGTH
 */
void spim_3_transfer(uint8_t *p_tx_data);



