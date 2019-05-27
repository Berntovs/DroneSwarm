#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "nrfx_timer.h"

/**
 * @brief Function for starting the RTC with instance 0
 */
void rtc_0_init(void);

/**
 * @brief Function for starting the timer with instance 1
 *
 * @param[in] time the time between each interupt
 * @param[in/out] interupt handler
 */
void timer_1_init(uint32_t time, nrfx_timer_event_handler_t handler);

/**
 * @brief Function for stopping the timer with instance 1
 */
void timer_1_uninit(void);