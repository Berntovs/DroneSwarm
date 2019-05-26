/**
 *
 */
#include <stdbool.h>

/**
 *  DUAL_CHIP_ENABLE "param"
 * @param: bool
 * @info: when this setting is true it will enable the dual chip code
 *        if false then the code will use the single chip code
 */
#define DUAL_CHIP_ENABLE true

/**
 *  SECONDARY_CHIP_MODE "param"
 * @param: bool
 * @info: this setting will only affect the code if DUAL_CHIP_ENABLE is true
 *
 * @info: when true the secondary chip code will compile, and when false the main chip code will compile
 */
#define SECONDARY_CHIP_MODE true

/**
 * ALTERNATIV_TEST_PLATFORM "param"
 * @param: bool
 * @info: this setting will change the pinmap for the test platform
 *        instead of using custom board it will use the DK pinmap
 *        and old swarm board pinmap
 */
#define ALTERNATIV_TEST_PLATFORM true

/**
 * Default values for pwm
 */
#define STATUS_LED_PWM_TOP_VALUE_DEFAULT 200
#define STATUS_LED_PWM_CLOCK_SPEED_DEFAULT NRF_PWM_CLK_250kHz

/**
 * Setting the pwm values
 */
#define STATUS_LED_PWM_TOP_VALUE STATUS_LED_PWM_TOP_VALUE_DEFAULT
#define STATUS_LED_PWM_CLOCK_SPEED STATUS_LED_PWM_CLOCK_SPEED_DEFAULT

/**
 * for enabling the sensors
 */
#define BMX160_ENABLE true
#define LPS22HB_ENABLE true

#define NRF_LOG_USED true

#define GPIO_PIN_NOT_USED 0xff

#define SPI_BUFFER_LENGTH_DEFAULT 10

#define SECONDARY_CHIP_DEFAULT_CONFIG false

#if DUAL_CHIP_ENABLE
#define SECONDARY_CHIP SECONDARY_CHIP_MODE
#else
#define SECONDARY_CHIP SECONDARY_CHIP_DEFAULT_CONFIG
#endif

#if ALTERNATIV_TEST_PLATFORM
#define OLD_SWARM_BOARD_MODE true
#define DEVELOPMENT_KIT_MODE true
#else
#define OLD_SWARM_BOARD_MODE false
#define DEVELOPMENT_KIT_MODE false
#endif
