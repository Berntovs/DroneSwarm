#include <stdbool.h>
#include <stdint.h>

#include "app_error.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "m_mqtt.h"
#include "m_motor.h"
#include "d_encoder2.h"
#include "m_spi.h"
#include "nrf_delay.h"
#include "m_sensors.h"
#include "d_swarm_board.h"

void main(void)
{
  APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
  NRF_LOG_DEFAULT_BACKENDS_INIT();
  
  //ret_code_t err_code = NRF_LOG_INIT(NULL);
  //APP_ERROR_CHECK(err_code);
  //NRF_LOG_DEFAULT_BACKENDS_INIT();


  //board_init();

  sensor_mngr_init();
  hts221_data_init();
  lps22hb_data_init();		
  NRF_LOG_INFO("Inits complete");
  NRF_LOG_FLUSH();

  while(1){
    nrf_delay_ms(1000);
    //get_hts221_data();
    get_lps22hb_data();
    NRF_LOG_INFO("Inside main loop");
    NRF_LOG_FLUSH();
    //mqttsn_loop();
  }
}

/**
 *@}
 **/
