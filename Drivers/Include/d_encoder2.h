#include "nrfx_gpiote.h"
#include "d_swarm_board.h"


#define encoderA_left	 MOTOR_ENCODER_A1_PIN
#define encoderA_right	 MOTOR_ENCODER_B1_PIN


typedef struct
{
  uint32_t leftmotorticks;
  uint32_t rightmotorticks;
}encoder_ticks_t;


void encoderintnerrupt(nrfx_gpiote_pin_t input,  nrf_gpiote_polarity_t action);
void gpio_init(void);

void data1(void);
void data2(void);