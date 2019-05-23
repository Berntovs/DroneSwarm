#define SECONDARY_CHIP_DEFAULT_CONFIG false

/**
 * Configureing the SECONDARY_CHIP setting
 * if only using one chip the setting will default to faulse
 */
#if DUAL_CHIP_ENABLE
#define SECONDARY_CHIP SECONDARY_CHIP_MODE
#else
#define SECONDARY_CHIP SECONDARY_CHIP_DEFAULT_CONFIG
#endif

#define STATUS_LED_PWM_TOP_VALUE_DEFAULT 200

#define STATUS_LED_PWM_CLOCK_SPEED_DEFAULT NRF_PWM_CLK_250kHz