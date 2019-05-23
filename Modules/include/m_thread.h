#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "thread_utils.h"

#define STATE_CHANGE_TIME_OUT 1000

otInstance *get_thread_instance(void);
void thread_loop(void);
void thread_setup(void);
void thread_connection_setup(void);