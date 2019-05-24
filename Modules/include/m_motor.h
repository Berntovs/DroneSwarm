#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "nrf_gpio.h"
//#include "nrf_drv_pwm.h"
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
  uint16_t speed;
}motor_speed_t;


//Initial motor direction and speed
 static motor_direction_t selectdirection =
 {
 .direction = 0,
 };

 static motor_speed_t speed =
 {
 .speed = 0,
 };

void motor_direction(motor_direction_t *direction);
void motor_speed(motor_speed_t *speed);
void init_motor_pwm(void);

void motor_run(void);



//Example main
// int main(void)
// {

//         //Create struct named motors and insert values
//     init_motor_pwm();

//     static motor_direction_t direction =
//     {
//     .motor0forward = 0,
//     .motor1forward = 1
//     };

//     static motor_speed_t speed =
//     {
//     .speedA = 100,
//     .speedB = 20,
//     };

//     for (;;) // Neverending loop
//    {
//       motor_direction(&direction);
//       motor_speed(&speed);
//       motor_run();

//    }
// }