#include "m_motor.h"
#include "nrfx_pwm.h"
#include "nrf_pwm.h"
#include "app_error.h"
#include "d_swarm_board.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "nrf_drv_pwm.h"


static nrfx_pwm_t MOTOR_PWM = NRFX_PWM_INSTANCE(1); //Start motor pwm instance

static void pwm_event_handler(nrfx_pwm_evt_type_t event_type);

//static nrf_pwm_values_individual_t Throttle_values; // Struct for Throttle Values
static nrf_pwm_values_individual_t Throttle_values;

void init_motor_pwm(void)
{
    NRF_LOG_INFO("Motor PWM Initalizing");

    nrfx_pwm_config_t const motor_pwm_config =
        {
            .output_pins =
                {
                    MOTOR_A_PWM_PIN | NRFX_PWM_PIN_INVERTED, // Motor 0
                    //PWM_PIN_0,
                    MOTOR_B_PWM_PIN | NRFX_PWM_PIN_INVERTED, // Motor 1
                    NRFX_PWM_PIN_NOT_USED,                   // Channel 2 Not in use
                    NRFX_PWM_PIN_NOT_USED                    // Channel 3 Not in use
                },
            .irq_priority = APP_IRQ_PRIORITY_LOWEST,
            .base_clock = PWM_PRESCALER_PRESCALER_DIV_8, // 2MHz
            .count_mode = PWM_MODE_UPDOWN_Up,            // Up counter, edge-aligned PWM duty cycle
            .top_value = 100,                            //  2Mhz / 100 = 20kHz
            .load_mode = PWM_DECODER_LOAD_Individual,
            .step_mode = PWM_DECODER_MODE_RefreshCount};
    APP_ERROR_CHECK(nrfx_pwm_init(&MOTOR_PWM, &motor_pwm_config, NULL));

    selectdirection.direction = 0;
    speed.speed_a = 0;
    speed.speed_b = 0;

    Throttle_values.channel_0 = 0;
    Throttle_values.channel_1 = 0;
    Throttle_values.channel_2 = 0;
    Throttle_values.channel_3 = 0;

    nrf_gpio_cfg_output(MOTOR_A_IN_1_PIN);
    nrf_gpio_cfg_output(MOTOR_A_IN_2_PIN);
    nrf_gpio_cfg_output(MOTOR_B_IN_1_PIN);
    nrf_gpio_cfg_output(MOTOR_B_IN_2_PIN);
}

void motor_direction(motor_direction_t *selectdirection)
{
    //Possible to use switch case?
    switch (selectdirection->direction)
    {
    //Full stop
    case 0:
        nrf_gpio_pin_clear(MOTOR_A_IN_1_PIN);
        nrf_gpio_pin_clear(MOTOR_A_IN_2_PIN);
        nrf_gpio_pin_clear(MOTOR_B_IN_1_PIN);
        nrf_gpio_pin_clear(MOTOR_B_IN_2_PIN);
        break;

    //Forward
    case 1:
        nrf_gpio_pin_set(MOTOR_A_IN_1_PIN);
        nrf_gpio_pin_clear(MOTOR_A_IN_2_PIN);
        nrf_gpio_pin_set(MOTOR_B_IN_1_PIN);
        nrf_gpio_pin_clear(MOTOR_B_IN_2_PIN);
        break;

    //Reverse
    case 2:
        nrf_gpio_pin_clear(MOTOR_A_IN_1_PIN);
        nrf_gpio_pin_set(MOTOR_A_IN_2_PIN);
        nrf_gpio_pin_clear(MOTOR_B_IN_1_PIN);
        nrf_gpio_pin_set(MOTOR_B_IN_2_PIN);
        break;

    //Turn CW
    case 3:
        nrf_gpio_pin_set(MOTOR_A_IN_1_PIN);
        nrf_gpio_pin_clear(MOTOR_A_IN_2_PIN);
        nrf_gpio_pin_clear(MOTOR_B_IN_1_PIN);
        nrf_gpio_pin_set(MOTOR_B_IN_2_PIN);
        break;

    //Turn CCW
    case 4:
        nrf_gpio_pin_clear(MOTOR_A_IN_1_PIN);
        nrf_gpio_pin_set(MOTOR_A_IN_2_PIN);
        nrf_gpio_pin_set(MOTOR_B_IN_1_PIN);
        nrf_gpio_pin_clear(MOTOR_B_IN_2_PIN);
        break;

    default:
        // No implementation needed.
        break;
    }
}

void motor_speed(motor_speed_t *speed)
{
    //Throttle_values.channel_0 = 100 -(uint16_t)speed->speedA;
    Throttle_values.channel_0 = 100 - speed->speed_a;
    Throttle_values.channel_1 = 100 - speed->speed_a;
}

void motor_run(void)
{
    nrf_pwm_sequence_t const seq =
        {
            .values.p_individual = &Throttle_values,
            .length = NRF_PWM_VALUES_LENGTH(Throttle_values),
            .repeats = 0,
            .end_delay = 0};
    nrfx_pwm_simple_playback(&MOTOR_PWM, &seq, 1, NRFX_PWM_FLAG_LOOP);
}
