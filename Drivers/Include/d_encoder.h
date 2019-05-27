#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "swarm_board.h"

#define ENCODER_LEFT_PIN MOTOR_ENCODER_A1_PIN // pin for encoder on left motor
#define ENCODER_RIGHT_PIN MOTOR_ENCODER_B1_PIN // pin for encoder on right motor

typedef struct
{
  uint32_t leftmotorticks;
  uint32_t rightmotorticks;
} encoder_ticks_t;

/**
 * @brief function for starting the encoder interupt
 */
void encoder_init(void);

/**
 * @brief function for getting the tick count on both motors
 *
 * @return encoder_ticks_t gives the stuct with motor encoder ticks
 */
encoder_ticks_t get_ticks(void);

