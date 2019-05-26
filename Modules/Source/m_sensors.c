#include <stdint.h>

#include "d_twi.h"
#include "d_BMX160_twi.h"
#include "config.h"

#include "nrf_twi_sensor.h"
#include "nrf_twi_mngr.h"
#include "lps22hb.h"
#include "hts221.h"
#include "d_swarm_board.h"

#include "m_sensors.h"

#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "app_error.h"

int16_t temp_data_buffer;
int16_t temp_hum_buffer;
int16_t RealTemp;

////Declared twi manager for sensors
NRF_TWI_MNGR_DEF(mng_twi_inst, 33, 0);
NRF_TWI_SENSOR_DEF(twi_sensor_inst, &mng_twi_inst, 4);

//HTS221TR 
//NRF_TWI_SENSOR_DEF(twi_sensor_inst, &mng_twi_inst, 4);
//LPS22HB_INSTANCE_DEF(lps22hb_inst, &twi_sensor_inst, 0x5C);
//void HTS221TR_start(void)
//{
//lps22hb_init(&lps22hb_inst);
//}
//static lps22hb_data_t lps22hb_buffer_data;
//
//void get_lps22hb_data(void)
//{
//lps22hb_data_read(&lps22hb_inst, NULL, &lps22hb_buffer_data, 1);
//}


void sensor_mngr_init(void)
{
nrf_drv_twi_config_t sensor_mngr_config = NRF_DRV_TWI_DEFAULT_CONFIG;
sensor_mngr_config.scl = 27;
sensor_mngr_config.sda = 26;
sensor_mngr_config.frequency = NRF_DRV_TWI_FREQ_100K;
sensor_mngr_config.interrupt_priority = APP_IRQ_PRIORITY_LOWEST;
sensor_mngr_config.clear_bus_init = false;

APP_ERROR_CHECK(nrf_twi_mngr_init(&mng_twi_inst, &sensor_mngr_config));
}





//HTS221
HTS221_INSTANCE_DEF(hts221_inst, &twi_sensor_inst, HTS221_BASE_ADDRESS);

uint8_t hts221_who_what;

void hts221_data_init(void)
{
APP_ERROR_CHECK(nrf_twi_sensor_init(&twi_sensor_inst));
APP_ERROR_CHECK(hts221_init(&hts221_inst));
APP_ERROR_CHECK(hts221_avg_cfg(&hts221_inst, HTS221_TEMP_SAMPLES_8, HTS221_HUMIDITY_SAMPLES_16));
hts221_pd_enable(&hts221_inst, true);

//lps22hb_who_am_i_read(&hts221_inst, NULL, &hts221_who_what);
//NRF_LOG_INFO(" Who am i : %d, right: %d ", hts221_inst,HTS221_WHO_AM_I);
}


void print_temp(uint32_t twi_result_t, int16_t *p_data)
{
NRF_LOG_INFO("Raw temp is  : %d ", temp_data_buffer);
RealTemp = hts221_temp_process(&hts221_inst, temp_data_buffer)/8;
NRF_LOG_INFO("Real temp is  : %d ", RealTemp);

}

void get_gts221_data(void)
{
hts221_oneshot(&hts221_inst);
APP_ERROR_CHECK(hts221_temp_read(&hts221_inst, &print_temp, &temp_data_buffer));
}
