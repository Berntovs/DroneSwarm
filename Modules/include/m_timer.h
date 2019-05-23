#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "nrfx_timer.h"

void rtc_0_init(void);
void timer_1_init(uint32_t time, nrfx_timer_event_handler_t handler);