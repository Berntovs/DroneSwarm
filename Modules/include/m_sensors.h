/**
 * @important because of an unknown issue with twi mangagersome manual fixes needed to be made in the SDK
 *             - on line 41 in nrf_twi_mngr.c
 *             - was changed from "#if NRF_MODULE_ENABLED(NRF_TWI_MNGR)" to "#if NRF_MODULE_ENABLED(NRF_TWI_MNGR)|1"
 *
 *             - also on line 41 in nrf_queue.c
 *             - was changes from "#if NRF_MODULE_ENABLED(NRF_QUEUE)" to "#if NRF_MODULE_ENABLED(NRF_QUEUE)|1"
 *
 * @important Because of an issue with flash memory placement, a custom flash_placement.xml was created
 *             - the fix for this was to add a new line between 8 and 9
 *             - new line: "<ProgramSection alignment="4" keep="Yes" load="Yes" name=".nrf_queue" inputsections="*(.nrf_queue*)" address_symbol="__start_nrf_queue" end_symbol="__stop_nrf_queue" />"
 */

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief function for starting the twi instance
 */
void sensor_mngr_init(void);

/**
 * @brief function for starting the hts221 sensor
 */
void hts221_data_init(void);

/**
 * @brief function for collecting data from the hts221 sensor
 */
void get_hts221_data(void);

/**
 * @brief function for starting the lps22hb sensor
 */
void lps22hb_data_init(void);

/**
 * @brief function for collecting data from the lps22hb sensor
 */
void get_lps22hb_data(void);

/**
 * @brief function for returning the real data
 *
 * @param[in] id what data to collect
 *
 * @return int16_t the real data
 */
int16_t collect_hts221_data(uint8_t id);
