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

//hts221 variables
int16_t temp_data_buffer;
int16_t hum_data_buffer;
int16_t RealTemp;
int16_t RealHum;

//lps22hb variables
int32_t lps22hbpressure;
int16_t lps22hbtemperature;
lps22hb_data_t lps22hb_raw_data;

////Declared twi manager for sensors
NRF_TWI_MNGR_DEF(mng_twi_inst, 33, 0);
NRF_TWI_SENSOR_DEF(twi_sensor_inst, &mng_twi_inst, 4);



//twi sensor manager init
void sensor_mngr_init(void)
{
nrf_drv_twi_config_t sensor_mngr_config = NRF_DRV_TWI_DEFAULT_CONFIG;
sensor_mngr_config.scl = 27;
sensor_mngr_config.sda = 26;
sensor_mngr_config.frequency = NRF_DRV_TWI_FREQ_100K;
sensor_mngr_config.interrupt_priority = APP_IRQ_PRIORITY_LOWEST;
sensor_mngr_config.clear_bus_init = false;

APP_ERROR_CHECK(nrf_twi_mngr_init(&mng_twi_inst, &sensor_mngr_config));

APP_ERROR_CHECK(nrf_twi_sensor_init(&twi_sensor_inst));
}





//HTS221
HTS221_INSTANCE_DEF(hts221_inst, &twi_sensor_inst, HTS221_BASE_ADDRESS);

uint8_t hts221_who_what;

void hts221_data_init(void)
{
//APP_ERROR_CHECK(nrf_twi_sensor_init(&twi_sensor_inst));
APP_ERROR_CHECK(hts221_init(&hts221_inst));
APP_ERROR_CHECK(hts221_avg_cfg(&hts221_inst, HTS221_TEMP_SAMPLES_8, HTS221_HUMIDITY_SAMPLES_16));
hts221_pd_enable(&hts221_inst, true);

}


void print_hts211_temp(uint32_t twi_result_t, int16_t *p_data)
{
NRF_LOG_INFO("Raw temp is  : %d ", temp_data_buffer);
RealTemp = hts221_temp_process(&hts221_inst, temp_data_buffer)/8;
NRF_LOG_INFO("Real temperature is  : %d ", RealTemp);

}

void print_hts211_hum(uint32_t twi_result_t, int16_t *p_data)
{
NRF_LOG_INFO("Raw hum is  : %d ", hum_data_buffer);
RealHum = hts221_hum_process(&hts221_inst, hum_data_buffer)/2;
NRF_LOG_INFO("Real humidity is  : %d ", RealHum);

}

void get_hts221_data(void)
{
hts221_oneshot(&hts221_inst);
APP_ERROR_CHECK(hts221_temp_read(&hts221_inst, &print_hts211_temp, &temp_data_buffer));
APP_ERROR_CHECK(hts221_hum_read(&hts221_inst, &print_hts211_hum, &hum_data_buffer));
}

//lps22hb
//LPS22HB_BASE_ADDRESS_HIGH
LPS22HB_INSTANCE_DEF(lps22hb_inst, &twi_sensor_inst, LPS22HB_BASE_ADDRESS_LOW);

uint8_t lps22hb_who_what;

void lps22hb_data_init(void)
{
lps22hb_init(&lps22hb_inst);
//LPS22HB_LPFP_ODR_DIV_9,
//LPS22HB_LPFP_ODR_DIV_20
//LPS22HB_DATA_CFG(&lps22hb_inst, LPS22HB_ODR_10HZ, false, false);
//lps22hb_cfg_commit(&lps22hb_inst);
//hts221_pd_enable(&hts221_inst, true);

}


void print_lps22hb_data(uint32_t twi_result_t, lps22hb_data_t *p_raw_data)
{
NRF_LOG_INFO("Raw pressure is  : %d ", lps22hb_raw_data.pressure);
NRF_LOG_INFO("Raw temperature is  : %d ", lps22hb_raw_data.temperature);
lps22hb_data_decode(&lps22hb_raw_data, 1);
lps22hbpressure = lps22hb_raw_data.pressure/4096;
lps22hbtemperature = lps22hb_raw_data.temperature/100;
NRF_LOG_INFO("Real pressure is  : %d ", lps22hbpressure);
NRF_LOG_INFO("Real temperature is  : %d ", lps22hbtemperature);
}



void get_lps22hb_data(void)
{
lps22hb_oneshot(&lps22hb_inst);
lps22hb_data_read(&lps22hb_inst, &print_lps22hb_data, &lps22hb_raw_data, 1);

}