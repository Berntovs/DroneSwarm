#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "app_scheduler.h"
#include "app_timer.h"
#include "bsp_thread.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "m_Real_Time_Clock.h"

#include "mqttsn_client.h"
#include "thread_utils.h"

#include "m_mqtt.h"
#include "m_thread.h"
#include "m_Real_Time_Clock.h"

#include <openthread/thread.h>

#define SCHED_QUEUE_SIZE 32                                   /**< Maximum number of events in the scheduler queue. */
#define SCHED_EVENT_DATA_SIZE APP_TIMER_SCHED_EVENT_DATA_SIZE /**< Maximum app_scheduler event size. */

///////////////temporary placement//////////////

////////////////////////////////////////////////
float time_between_state_change = 0;

void scheduler_init(void)
{
    APP_SCHED_INIT(SCHED_EVENT_DATA_SIZE, SCHED_QUEUE_SIZE);
}

static void state_changed_callback(uint32_t flags, void *p_context)
{
    time_between_state_change = 0;
    NRF_LOG_INFO("State changed! Flags: 0x%08x Current role: %d\r\n",
                 flags, otThreadGetDeviceRole(p_context));
    NRF_LOG_FLUSH();
}
static void bsp_event_handler(bsp_event_t event)
{
    if (otThreadGetDeviceRole(thread_ot_instance_get()) < OT_DEVICE_ROLE_CHILD)
    {
        (void)event;
        return;
    }
}
/**@brief Function for initializing the Thread Stack.
 */
void thread_instance_init(void)
{
    thread_configuration_t thread_configuration =
        {
            .radio_mode = THREAD_RADIO_MODE_RX_ON_WHEN_IDLE,
            .autocommissioning = true,
        };

    thread_init(&thread_configuration);
    thread_cli_init();
    thread_state_changed_callback_set(state_changed_callback);
}

static void timer_init(void)
{
    uint32_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);
}

void thread_setup(void)
{
    rtc_0_init();
    timer_init();
    scheduler_init();
    thread_instance_init();
    bsp_init(0, bsp_event_handler);
    APP_ERROR_CHECK(bsp_thread_init(thread_ot_instance_get()));
    thread_connection_setup();
}

otInstance *get_thread_instance(void)
{
    return thread_ot_instance_get();
}

void thread_loop(void)
{
    thread_process();
    app_sched_execute();

    if (NRF_LOG_PROCESS() == false)
    {
        //thread_sleep();
    }
}

void thread_connection_setup(void)
{
    while (time_between_state_change <= STATE_CHANGE_TIME_OUT)
    {
        thread_loop();
        time_between_state_change = rtc_get_current_time_ms();
    }
    NRF_LOG_INFO("State decided!");
    NRF_LOG_FLUSH();
}