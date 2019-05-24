#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "nrfx_spim.h"
#include "nrfx_spis.h"

#define SPIM_0_MOSI_PIN UART_RX_PIN
#define SPIM_0_MISO_PIN UART_TX_PIN
#define SPIM_0_CS_PIN UART_CTS_PIN
#define SPIM_0_SCK_PIN UART_RTS_PIN

#define SPIS_0_MOSI_PIN UART_TX_PIN
#define SPIS_0_MISO_PIN UART_RX_PIN
#define SPIS_0_CS_PIN UART_CTS_PIN
#define SPIS_0_SCK_PIN UART_RTS_PIN