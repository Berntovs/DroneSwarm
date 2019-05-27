#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "thread_utils.h"

#define STATE_CHANGE_TIME_OUT 100

/**
 * @brief Function for getting the thread instance
 *
 * @return otInstance* the thread instance
 */
otInstance *get_thread_instance(void);

/**
 * @brief Function for processing the thread stack and sceduled events
 */
void thread_loop(void);

/**
 * @brief Function for initilizing thread and dependencies
 */
void thread_setup(void);
