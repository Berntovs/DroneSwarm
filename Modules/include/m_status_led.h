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

void status_led_1_init(void);

void status_led_2_init(void);

void change_color_led_1(uint8_t _r, uint8_t _g, uint8_t _b);

void change_color_led_2(uint8_t _r, uint8_t _g, uint8_t _b);

void status_led_1_mode(uint8_t _led_mode);

void status_led_1_mode(uint8_t _led_mode);