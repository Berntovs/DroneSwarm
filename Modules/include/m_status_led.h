/**
 *
 *
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include "config.h"

// default configuration
#ifndef STATUS_LED_PWM_TOP_VALUE
    #define STATUS_LED_PWM_TOP_VALUE 200
#endif
#ifndef STATUS_LED_PWM_CLOCK_SPEED
    #define STATUS_LED_PWM_CLOCK_SPEED NRF_PWM_CLK_250kHz
#endif

#define DUTY_CYCLE_CONVERSION(_input, _topvalue) ((_input) / (100) * _topvalue)

/**
 * @brief function for starting the status led 1 pwm driver
 */
void status_led_1_init(void);

/**
 * @brief function for starting the status led 2 pwm driver
 */
void status_led_2_init(void);

/**
 * @brief function for setting the colour on status led 1
 *
 * @param[in] _r change the red colour, from 0 to 100
 * @param[in] _g change the blue colour, from 0 to 100
 * @param[in] _b change the green colour, from 0 to 100
 */
void change_color_led_1(uint8_t _r, uint8_t _g, uint8_t _b);

/**
 * @brief function for setting the colour on status led 2
 *
 * @param[in] _r change the red colour, from 0 to 100
 * @param[in] _g change the blue colour, from 0 to 100
 * @param[in] _b change the green colour, from 0 to 100
 */
void change_color_led_2(uint8_t _r, uint8_t _g, uint8_t _b);

/**
 * @brief Simple function for selecting a predefined color on status led 1
 *
 * @param _led_mode number from 0 to 4
 */
void status_led_1_mode(uint8_t _led_mode);

/**
 * @brief Simple function for selecting a predefined color on status led 2
 *
 * @param _led_mode number from 0 to 4
 */
void status_led_1_mode(uint8_t _led_mode);