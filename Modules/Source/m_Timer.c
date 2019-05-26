#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "nrf_log.h"
#include "nrfx_rtc.h"
#include "nrfx_timer.h"

#include "m_timer.h"


nrfx_timer_t timer_0 = NRFX_TIMER_INSTANCE(0);
nrfx_timer_t timer_1 = NRFX_TIMER_INSTANCE(2);

static nrfx_timer_t rtc_timer;

void rtc_event_handler(nrf_timer_event_t event_type, void* p_context){

}



void rtc_init(nrfx_timer_t * timer_instance)
{
    uint32_t err_code;
    rtc_timer = *timer_instance;
    static nrfx_timer_config_t rtc_cfg =
    {
        .frequency = NRF_TIMER_FREQ_16MHz,
        .mode      = NRF_TIMER_MODE_TIMER,
        .bit_width = NRF_TIMER_BIT_WIDTH_32,
    };

    err_code = nrfx_timer_init(timer_instance, &rtc_cfg, rtc_event_handler);
    APP_ERROR_CHECK(err_code);

    nrfx_timer_enable(timer_instance);

    NRF_LOG_RAW_INFO("[SUCCESS] Real time clock enabled. \n");
    }

void rtc_0_init(void)
{
  rtc_init(&timer_0);
}

uint32_t rtc_get_current_time_ticks(void)
{
  return nrfx_timer_capture(&rtc_timer, NRF_TIMER_CC_CHANNEL1);
}


float rtc_get_current_time_ms(void)
{
  static float ms_per_tick = (1.0f / 16000000.0f) * 1000.0f;

  return ms_per_tick * (float)rtc_get_current_time_ticks();
}

float rtc_get_delta_time_sec(float * prev_time)
{
    float delta_time;
    uint32_t current_time  = rtc_get_current_time_ms();

    delta_time = ((float)current_time - *prev_time) / 1000.0f;

    *prev_time = current_time;

    return delta_time;
}






void timer_1_init(uint32_t time, nrfx_timer_event_handler_t handler)
{
uint32_t time_ms = time;
uint32_t ticks;
uint32_t err_code = NRF_SUCCESS;


nrfx_timer_config_t timer_cfg = NRFX_TIMER_DEFAULT_CONFIG;
timer_cfg.frequency = NRF_TIMER_FREQ_31250Hz;
timer_cfg.bit_width = 3;
err_code = nrfx_timer_init(&timer_1, &timer_cfg, handler);
APP_ERROR_CHECK(err_code);

ticks = nrfx_timer_ms_to_ticks(&timer_1, time_ms);

nrfx_timer_extended_compare(
  &timer_1, NRF_TIMER_CC_CHANNEL1, ticks, NRF_TIMER_SHORT_COMPARE1_CLEAR_MASK, true);

//nrfx_timer_compare(&timer_1, 1, ticks, 1);
nrfx_timer_enable(&timer_1);
}

void timer_1_uninit(void){
nrfx_timer_uninit(&timer_1);
}