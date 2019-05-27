#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "nrf_gpio.h"
#include "nrfx_pwm.h"
#include "nrf_pwm.h"


//Select direction
// Stop
// 1 Forward
// 2 Reverse
// 3 Turn CW
// 4 Turn CCW
typedef struct
{
  int direction;
}motor_direction_t;

typedef struct
{
  uint16_t speed_a;
  uint16_t speed_b;
}motor_speed_t;

static motor_direction_t selectdirection;

static motor_speed_t speed;

/**
 * @brief function for setting motor direction
 *
 * @param[in] takes in the direction
 * @value encoder_ticks_t:
 *      - 0 = stop
 *      - 1 = forward
 *      - 2 = reverse
 *      - 3 = CW
 *      - 4 = CCW
 */
void motor_direction(motor_direction_t *direction);

/**
 * @brief setting motor speed
 *
 * @param[in] speed takes in pointer for the motor_speed_t
 */
void motor_speed(motor_speed_t *speed);

/**
 * @brief function for starting the requierd pwm
 */
void init_motor_pwm(void);

/**
 * @brief for updateing the motor values
 *
 * @info needs to be called after each motor speed and motor direction
 */
void motor_run(void);

