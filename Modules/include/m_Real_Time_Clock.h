#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "nrfx_timer.h"

/**
 * @brief Function for starting the RTC with instance 0
 *
 * @info based on rtc_init
 */
void rtc_0_init(void);

/**
 * @brief Function for starting RTC
 *
 * @param[in/out] timer_instance takes inn the instance for the RTC
 */
void rtc_init(nrfx_timer_t * timer_instance);

/**
 * @brief Function for getting the current time in ticks
 *
 * @return uint32_t returns the ticks
 */
uint32_t rtc_get_current_time_ticks(void);

/**
 * @brief Function for getting the current time in ms
 *
 * @return float returns the time in ms
 */
float rtc_get_current_time_ms(void);

/**
 * @brief Function for getting the time difference
 *
 * @param[in] prev_time takes in the previus time
 *
 * @return float returns the difference
 */
float rtc_get_delta_time_sec(float * prev_time);