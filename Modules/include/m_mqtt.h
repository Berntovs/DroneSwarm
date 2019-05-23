#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "nrfx_timer.h"

#define STATE_GATEWAY 0
#define STATE_CLIENT 1
#define STATE_PUB 2

void mqttsn_init(void);

void mqttsn_loop(void);

void mqttsn_pub(char message);

void mqttsn_boot(nrf_timer_event_t event_type, void *p_context);

void pub(void);