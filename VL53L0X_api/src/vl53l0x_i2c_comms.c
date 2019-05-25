#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "nrfx_twim.h"
#include "app_error.h"
#include "app_util_platform.h"
#include "nrf_log.h"
#include "vl53l0x_i2c_platform.h"
#include "vl53l0x_def.h"

const nrfx_twim_t tof_twim = NRFX_TWIM_INSTANCE(1);

//#define I2C_DEBUG

int VL53L0X_i2c_init(void)
{
  ret_code_t err_code;

  const nrfx_twim_config_t tof_twim_config = {
      .scl = TOF_SCL_PIN,
      .sda = TOF_SDA_PIN,
      .frequency = NRF_TWIM_FREQ_400K,
      .interrupt_priority = APP_IRQ_PRIORITY_LOW,
      .hold_bus_uninit = false};

  err_code = nrfx_twim_init(&tof_twim, &tof_twim_config, NULL, NULL);
  APP_ERROR_CHECK(err_code);

  nrfx_twim_enable(&tof_twim);

  NRF_LOG_RAW_INFO("[SUCCESS] Time-of-flight TWIM enabled. \n");
}

int VL53L0X_write_multi(uint8_t deviceAddress, uint8_t index, uint8_t *pdata, uint32_t count)
{
  static uint8_t merge_array[32] = {0};

  uint32_t err_code;
  uint8_t i;

  merge_array[0] = index;

  for (i = 0; i < count; i++)
  {
    merge_array[i + 1] = pdata[i];
  }

  err_code = nrfx_twim_tx(&tof_twim, deviceAddress, merge_array, count + 1, false);
  APP_ERROR_CHECK(err_code);

  return VL53L0X_ERROR_NONE;
}

int VL53L0X_read_multi(uint8_t deviceAddress, uint8_t index, uint8_t *pdata, uint32_t count)
{

  uint32_t err_code;
  err_code = nrfx_twim_tx(&tof_twim, deviceAddress, &index, 1, false);
  APP_ERROR_CHECK(err_code);

  err_code = nrfx_twim_rx(&tof_twim, deviceAddress, pdata, count);
  APP_ERROR_CHECK(err_code);

  return VL53L0X_ERROR_NONE;
}

int VL53L0X_write_byte(uint8_t deviceAddress, uint8_t index, uint8_t data)
{
  return VL53L0X_write_multi(deviceAddress, index, &data, 1);
}

int VL53L0X_write_word(uint8_t deviceAddress, uint8_t index, uint16_t data)
{
  uint8_t buff[2];
  buff[1] = data & 0xFF;
  buff[0] = data >> 8;
  return VL53L0X_write_multi(deviceAddress, index, buff, 2);
}

int VL53L0X_write_dword(uint8_t deviceAddress, uint8_t index, uint32_t data)
{
  uint8_t buff[4];

  buff[3] = data & 0xFF;
  buff[2] = data >> 8;
  buff[1] = data >> 16;
  buff[0] = data >> 24;

  return VL53L0X_write_multi(deviceAddress, index, buff, 4);
}

int VL53L0X_read_byte(uint8_t deviceAddress, uint8_t index, uint8_t *data)
{
  return VL53L0X_read_multi(deviceAddress, index, data, 1);
}

int VL53L0X_read_word(uint8_t deviceAddress, uint8_t index, uint16_t *data)
{
  uint8_t buff[2];
  int r = VL53L0X_read_multi(deviceAddress, index, buff, 2);

  uint16_t tmp;
  tmp = buff[0];
  tmp <<= 8;
  tmp |= buff[1];
  *data = tmp;

  return r;
}

int VL53L0X_read_dword(uint8_t deviceAddress, uint8_t index, uint32_t *data)
{
  uint8_t buff[4];
  int r = VL53L0X_read_multi(deviceAddress, index, buff, 4);

  uint32_t tmp;
  tmp = buff[0];
  tmp <<= 8;
  tmp |= buff[1];
  tmp <<= 8;
  tmp |= buff[2];
  tmp <<= 8;
  tmp |= buff[3];

  *data = tmp;

  return r;
}

/*#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
//#include "nrfx_twim.h"
#include "nrfx_twim.h"

#include "app_error.h"
#include "app_util_platform.h"
#include "nrf_log.h"
#include "vl53l0x_i2c_platform.h"
#include "vl53l0x_def.h"

const nrfx_twim_t tof_twim = NRFX_TWIM_INSTANCE(1);

//#define I2C_DEBUG

int VL53L0X_i2c_init(void) {
  ret_code_t err_code;

  const nrfx_twim_config_t tof_twim_config = {
     .scl                = TOF_SCL_PIN,
     .sda                = TOF_SDA_PIN,
     .frequency          = NRF_TWIM_FREQ_400K,
     .interrupt_priority = APP_IRQ_PRIORITY_LOW,
     .hold_bus_uninit     = false
  };

  err_code = nrfx_twim_init(&tof_twim, &tof_twim_config, NULL, NULL);
  APP_ERROR_CHECK(err_code);

  nrfx_twim_enable(&tof_twim);

 // NRF_LOG_RAW_INFO("[SUCCESS] Time-of-flight TWIM enabled. \n");
}

int VL53L0X_write_multi(uint8_t deviceAddress, uint8_t index, uint8_t *pdata, uint32_t count) {

  uint32_t err_code;
  uint8_t i;
  uint8_t merge_array[count+1];
  merge_array[0] = index;

  for(i = 0; i < count; i++)
  {
    merge_array[i+1] = pdata[i];
  }

  err_code = nrfx_twim_tx(&tof_twim, deviceAddress, merge_array, count+1, false);
  APP_ERROR_CHECK(err_code);

  return VL53L0X_ERROR_NONE;
}

int VL53L0X_read_multi(uint8_t deviceAddress, uint8_t index, uint8_t *pdata, uint32_t count) {

  uint32_t err_code;
  err_code = nrfx_twim_tx(&tof_twim, deviceAddress, &index, 1, false);
  APP_ERROR_CHECK(err_code);

  err_code = nrfx_twim_rx(&tof_twim, deviceAddress, pdata, count);
  APP_ERROR_CHECK(err_code);

  return VL53L0X_ERROR_NONE;
}

int VL53L0X_write_byte(uint8_t deviceAddress, uint8_t index, uint8_t data) {
  return VL53L0X_write_multi(deviceAddress, index, &data, 1);
}

int VL53L0X_write_word(uint8_t deviceAddress, uint8_t index, uint16_t data) {
  uint8_t buff[2];
  buff[1] = data & 0xFF;
  buff[0] = data >> 8;
  return VL53L0X_write_multi(deviceAddress, index, buff, 2);
}

int VL53L0X_write_dword(uint8_t deviceAddress, uint8_t index, uint32_t data) {
  uint8_t buff[4];

  buff[3] = data & 0xFF;
  buff[2] = data >> 8;
  buff[1] = data >> 16;
  buff[0] = data >> 24;

  return VL53L0X_write_multi(deviceAddress, index, buff, 4);
}

int VL53L0X_read_byte(uint8_t deviceAddress, uint8_t index, uint8_t *data) {
  return VL53L0X_read_multi(deviceAddress, index, data, 1);
}

int VL53L0X_read_word(uint8_t deviceAddress, uint8_t index, uint16_t *data) {
  uint8_t buff[2];
  int r = VL53L0X_read_multi(deviceAddress, index, buff, 2);

  uint16_t tmp;
  tmp = buff[0];
  tmp <<= 8;
  tmp |= buff[1];
  *data = tmp;

  return r;
}

int VL53L0X_read_dword(uint8_t deviceAddress, uint8_t index, uint32_t *data) {
  uint8_t buff[4];
  int r = VL53L0X_read_multi(deviceAddress, index, buff, 4);

  uint32_t tmp;
  tmp = buff[0];
  tmp <<= 8;
  tmp |= buff[1];
  tmp <<= 8;
  tmp |= buff[2];
  tmp <<= 8;
  tmp |= buff[3];

  *data = tmp;

  return r;
}*/
