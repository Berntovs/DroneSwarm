#include <stdint.h>

#include "d_twi.h"
#include "d_BMX160_twi.h"
#include "config.h"

#include "nrf_twi_sensor.h"
#include "nrf_twi_mngr.h"
//Pressude and temperature sensor
#include "lps22hb.h"
//Gas sensor
#include "ccs811.h"
#include "d_swarm_board.h"

#include "m_sensors.h"

#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

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
NRF_TWI_MNGR_DEF(mng_twi_inst, 4, 0);

//HTS221TR 
NRF_TWI_SENSOR_DEF(twi_sensor_inst, &mng_twi_inst, 4);
LPS22HB_INSTANCE_DEF(lps22hb_inst, &twi_sensor_inst, 0x5C);
CCS811_INSTANCE_DEF(ccs811_inst, &twi_sensor_inst, CCS811_BASE_ADDRESS_LOW);


void sensor_mngr_init(void)
{
nrf_drv_twi_config_t sensor_mngr_config = NRF_DRV_TWI_DEFAULT_CONFIG;
sensor_mngr_config.scl = SCL_PIN;
sensor_mngr_config.sda = SDA_PIN;

nrf_twi_mngr_init(&mng_twi_inst, &sensor_mngr_config);
nrf_twi_sensor_init(&twi_sensor_inst);

}
//void HTS221TR_whoami_uc(ret_code_t result, void * p_register_data
//{
//NRF_LOG_INFO("%d" , result);
//}
uint8_t whoami_lps22hb;

void HTS221TR_start(void)
{
lps22hb_sw_reset(&lps22hb_inst);
lps22hb_init(&lps22hb_inst);
}

static lps22hb_data_t lps22hb_buffer_data;
void get_lps22hb_data(void)
{
lps22hb_data_read(&lps22hb_inst, NULL, &lps22hb_buffer_data, 1);
lps22hb_data_decode(&lps22hb_buffer_data, 1);
NRF_LOG_INFO("Temp: %d", lps22hb_buffer_data.temperature);
NRF_LOG_INFO("Pressure: %d", lps22hb_buffer_data.pressure);
lps22hb_who_am_i_read(&lps22hb_inst, NULL, &whoami_lps22hb);
NRF_LOG_INFO(" Who am i : %d, right: %d ", whoami_lps22hb,LPS22HB_WHO_AM_I);
}

void ccs811_start(void)
{
css811_init(&ccs811_inst);
css811_drive_mode_set(&ccs811_inst, 1, true, false);
}

static ccs811_alg_data_t ccs811_buffer_data;
void get_ccs811_data(void)
{
ccs811_alg_data_read(&ccs811_inst, NULL, &ccs811_buffer_data, 5);
ccs811_alg_data_process(&ccs811_buffer_data);
NRF_LOG_INFO("Gas sensor eco2 reads : %d " , ccs811_buffer_data.eco2);
}
