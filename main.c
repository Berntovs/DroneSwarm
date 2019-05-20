//
//
//#include <stdbool.h>
//#include <stdint.h>
//#include <string.h>
//
//#include "app_scheduler.h"
//#include "app_timer.h"
//#include "bsp_thread.h"
//#include "nrf_log.h"
//#include "nrf_log_ctrl.h"
//#include "nrf_log_default_backends.h"
//
//#include "mqttsn_client.h"
//#include "thread_utils.h"
//
//#include <openthread/thread.h>
//
//
//int main(int argc, char *argv[])
//{
//
//
//    while (true)
//    {
//
//    }
//}





///////////////////////////////////////////////////////
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"
#include "d_encoder2.h"
#include "nrfx_pwm.h"


#include "nrf.h"
#include "nrfx.h"
#include "nrfx_gpiote.h"
#include "app_error.h"
#include "boards.h"
#include "m_motor.h"
#include "m_location.h"
#include "nrf_drv_pwm.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_delay.h"
//#include "config.h"








//Code that runs when encoder interrupt triggers, encodercounter wont increase unless functions is in main
void encoderintnerrupt(nrfx_gpiote_pin_t input,  nrf_gpiote_polarity_t action)
{

    if(input == encoderA_left)
    {
        
        encodercounter.leftmotorticks++;
        NRF_LOG_INFO("Left press");
        //nrf_gpio_pin_set(LED_1);
        
     }
    else if(input == encoderA_right)
    {   
        encodercounter.rightmotorticks++;
        NRF_LOG_INFO("right press");
    }
}



/**
 * @brief Function for application main entry.
 */
int main(void)
{
    ///////////////////////////////////Debugging///////////////////////////////////
    nrf_gpio_cfg_output(LED_1);
    nrf_gpio_cfg_output(LED_2);
    nrf_gpio_cfg_output(LED_3);
    nrf_gpio_cfg_output(LED_4);

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();
    NRF_LOG_INFO("Encoder test started");

    //Init interrupts
    gpio_init();

    ///////////////////////////////////Motor///////////////////////////////////
    //Init motor pwm
    init_motor_pwm();


    while (true)
    {
        ///////////////////////////////////Debugging///////////////////////////////////
        NRF_LOG_FLUSH();
        //NRF_LOG_INFO("Left is %d .", left);
        NRF_LOG_INFO("Left struct is %d .", encodercounter.leftmotorticks);
        NRF_LOG_INFO("Right struct is %d .", encodercounter.rightmotorticks);
        //NRF_LOG_INFO("Right is %d .", right);
        //nrf_gpio_pin_clear(LED_3);
        nrf_delay_ms(500);
        nrf_gpio_pin_set(LED_3);
        nrf_delay_ms(500);
        //__SEV();
        //__WFE();
        //__WFE();
        ///////////////////////////////////Motor///////////////////////////////////
        motor_direction(&selectdirection);
        motor_speed(&speed);
        motor_run();
        nrf_delay_ms(1000);
        NRF_LOG_INFO("motordirection is %d .", selectdirection.direction);
        ///////////////////////////////////Motor test///////////////////////////////////
//        selectdirection.direction = 1;
//        speed.speedA = 80;
//        motor_direction(&selectdirection);
//        motor_speed(&speed);l
//        motor_run();
//        nrf_delay_ms(1000);
//        selectdirection.direction = 2;
//        speed.speeda = 80;
//        motor_direction(&selectdirection);
//        motor_speed(&speed);
//        motor_run();
//        nrf_delay_ms(1000);
//        selectdirection.direction = 1;
//        speed.speeda = 80;
//        motor_direction(&selectdirection);
//        motor_speed(&speed);
//        motor_run();
//        nrf_delay_ms(1000);
        ///////////////////////////////////location test///////////////////////////////////
          selectdirection.direction = 1;
          NRF_LOG_INFO("motordirection is %d .", selectdirection.direction);
          location_service(&selectdirection, &encodercounter, &location_and_angle);
          nrf_delay_ms(500);
          //NRF_LOG_INFO("Angle is %d .", location_and_angle.angle);
          NRF_LOG_INFO("x is %d .", location_and_angle.xlocation);
          NRF_LOG_INFO("y is %d .", location_and_angle.ylocation);
          encodercounter.leftmotorticks = encodercounter.leftmotorticks + 10;
          encodercounter.rightmotorticks = encodercounter.rightmotorticks + 10;



    }
}


/** @} */
