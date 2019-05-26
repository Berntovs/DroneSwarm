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

//
//
//#if BMX160_ENABLE
//#pragma region
//static struct
//{
//    uint8_t x_low_data;
//    uint8_t x_high_data;
//    uint8_t y_low_data;
//    uint8_t y_high_data;
//    uint8_t z_low_data;
//    uint8_t z_high_data;
//}mag_data;
//
//static struct
//{
//    uint8_t x_low_data;
//    uint8_t x_high_data;
//    uint8_t y_low_data;
//    uint8_t y_high_data;
//    uint8_t z_low_data;
//    uint8_t z_high_data;
//}acc_data;
//
//static struct
//{
//    uint8_t x_low_data;
//    uint8_t x_high_data;
//    uint8_t y_low_data;
//    uint8_t y_high_data;
//    uint8_t z_low_data;
//    uint8_t z_high_data;
//}gyr_data;
//
//
//
//void update_mag_data(void){
//    if (BMX160_chipfound) {
//        get_mag_x_data_low(&mag_data.x_low_data);
//        get_mag_x_data_high(&mag_data.x_high_data);
//        get_mag_y_data_low(&mag_data.y_low_data);
//        get_mag_y_data_high(&mag_data.y_high_data);
//        get_mag_z_data_low(&mag_data.z_low_data);
//        get_mag_z_data_high(&mag_data.z_high_data);
//    }
//}
//
//void update_acc_data(void){
//    if (BMX160_chipfound) {
//        get_acc_x_data_low(&acc_data.x_low_data);
//        get_acc_x_data_high(&acc_data.x_high_data);
//        get_acc_y_data_low(&acc_data.y_low_data);
//        get_acc_y_data_high(&acc_data.y_high_data);
//        get_acc_z_data_low(&acc_data.z_low_data);
//        get_acc_z_data_high(&acc_data.z_high_data);
//    }
//}
//
//void update_gyr_data(void){
//    if (BMX160_chipfound) {
//        get_gyr_x_data_low(&gyr_data.x_low_data);
//        get_gyr_x_data_high(&gyr_data.x_high_data);
//        get_gyr_y_data_low(&gyr_data.y_low_data);
//        get_gyr_y_data_high(&gyr_data.y_high_data);
//        get_gyr_z_data_low(&gyr_data.z_low_data);
//        get_gyr_z_data_high(&gyr_data.z_high_data);
//    }
//}
//#pragma endregion
//#endif
//
//#if LPS22HB_ENABLE
//#pragma region
//
//#pragma endregion
//#endif

////Declared twi manager for sensors
NRF_TWI_MNGR_DEF(mng_twi_inst, 33, 0);

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
NRF_TWI_SENSOR_DEF(twi_sensor_inst, &mng_twi_inst, HTS221_MIN_QUEUE_SIZE);
HTS221_INSTANCE_DEF(hts221_inst, &twi_sensor_inst, 0x5B);

uint8_t hts221_who_what;

void hts221_data_init(void)
{
APP_ERROR_CHECK(nrf_twi_sensor_init(&twi_sensor_inst));
APP_ERROR_CHECK(hts221_init(&hts221_inst));
APP_ERROR_CHECK(hts221_avg_cfg(&hts221_inst, HTS221_TEMP_SAMPLES_8, HTS221_HUMIDITY_SAMPLES_16));
//lps22hb_who_am_i_read(&hts221_inst, NULL, &hts221_who_what);
//NRF_LOG_INFO(" Who am i : %d, right: %d ", hts221_inst,HTS221_WHO_AM_I);
}

uint16_t rawtemp;
uint16_t RealTemp;

void print_temp(uint16_t rawtemp)
{
NRF_LOG_INFO("Raw temp is  : %d ", rawtemp);
RealTemp = hts221_temp_process(&hts221_inst, rawtemp)/8;
NRF_LOG_INFO("Real temp is  : %d ", RealTemp);

}

void get_gts221_data(void)
{

APP_ERROR_CHECK(hts221_temp_read(&hts221_inst, &print_temp, &rawtemp));
}
