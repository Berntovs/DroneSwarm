#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "nrfx_gpiote.h"
#include "d_encoder.h"
#include "swarm_board.h"
#include "nrf_log.h"

static encoder_ticks_t encodercounter =
    {
        .leftmotorticks = 0,
        .rightmotorticks = 0,
};

//Code that runs when encoder interrupt triggers, encodercounter wont increase unless functions is in main
void encoderintnerrupt(nrfx_gpiote_pin_t input, nrf_gpiote_polarity_t action)
{

    if (input == ENCODER_LEFT_PIN)
    {

        encodercounter.leftmotorticks++;

        //nrf_gpio_pin_set(LED_1);
    }
    else if (input == ENCODER_RIGHT_PIN)
    {
        encodercounter.rightmotorticks++;
    }
}

//Configure interrupt for Encoders
void gpio_init(void)
{
    ret_code_t err_code;

    err_code = nrfx_gpiote_init();
    APP_ERROR_CHECK(err_code);
    //Input config
    //Settings for using buttons on DK, check for what works with real encoder
    //nrfx_gpiote_in_config_t encoder_interrupt = NRFX_GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
    nrfx_gpiote_in_config_t encoder_interrupt = NRFX_GPIOTE_CONFIG_IN_SENSE_LOTOHI(true);
    encoder_interrupt.pull = NRF_GPIO_PIN_NOPULL;

    //Init left encoder pin
    err_code = nrfx_gpiote_in_init(ENCODER_LEFT_PIN, &encoder_interrupt, encoderintnerrupt);
    APP_ERROR_CHECK(err_code);
    //Init right encoder pin
    err_code = nrfx_gpiote_in_init(ENCODER_RIGHT_PIN, &encoder_interrupt, encoderintnerrupt);
    APP_ERROR_CHECK(err_code);
    //Enable events
    nrfx_gpiote_in_event_enable(ENCODER_LEFT_PIN, true);
    nrfx_gpiote_in_event_enable(ENCODER_RIGHT_PIN, true);
}

encoder_ticks_t get_leftmotor_ticks(void)
{
    return encodercounter;
}


