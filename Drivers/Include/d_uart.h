#include <stdbool.h>
#include <stdint.h>

/**
 * @brief init function for uarte, must be called before using uart
 */
void uart_init(void);

/**
 * @brief simple read function, takes in pointer to buffer
 *
 * @param[out]  data array, must be atleast 4 in length
 */
void uart_rx(uint8_t *data);

/**
 * @brief simple transfer function, takes in pointer to buffer
 *
 * @param[in]  data array, must be atleast 4 in length
 */
void uart_tx(uint8_t *data);