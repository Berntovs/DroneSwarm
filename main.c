#include <stdbool.h>
#include "m_mqtt.h"
#include "app_error.h"
#include "nrf_delay.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}
char m = '1';
int main(int argc, char *argv[])
{
  log_init();
  mqttsn_init();
      nrf_delay_ms(1000);
  while (true)
  {
    mqttsn_loop();
  }
}

/**
 *@}
 **/
