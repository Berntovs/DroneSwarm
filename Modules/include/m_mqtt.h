#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "nrfx_timer.h"

#define STATE_GATEWAY 0
#define STATE_CLIENT 1
#define STATE_PUB 2

/**
 * @brief This function start the thread stack aswell as mqtt
 */
void mqttsn_init(void);

/**
 * @brief Function for processing all pending tasks
 */
void mqttsn_loop(void);

/**
 * @brief Simple transfer function, will send message with predefined topic
 */
void mqttsn_pub(char message);

/**
 * @brief Function to be used with a timer as the interupt handler
 *
 * @info This handler will connect the gateway aswell as the client
 */
void mqttsn_boot(nrf_timer_event_t event_type, void *p_context);

/**
 * @brief simple function for creating a subscription to a mqtt topic
 *
 * @info pre-determant topic
 */
void sub(void);