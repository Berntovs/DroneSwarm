#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "app_error.h"
#include "nrfx_timer.h"

#include "mqttsn_client.h"
#include "m_mqttsn_message.h"
#include "m_thread.h"
#include "m_mqtt.h"
#include "m_timer.h"
//nasty fix at mqttsn_client.c line 351
//to make it work again comment the line back in
#define SEARCH_GATEWAY_TIMEOUT 5 /**< MQTT-SN Gateway discovery procedure timeout in [s]. */

static mqttsn_client_t      m_client;                                       /**< An MQTT-SN client instance. */
static mqttsn_remote_t      m_gateway_addr;                                 /**< A gateway address. */
static uint8_t              m_gateway_id;                                   /**< A gateway ID. */
static mqttsn_connect_opt_t m_connect_opt;                                  /**< Connect options for the MQTT-SN client. */
static bool                 m_subscribed       = 0;                         /**< Current subscription state. */
static uint16_t             m_msg_id           = 0;                         /**< Message ID thrown with MQTTSN_EVENT_TIMEOUT. */
static char                 m_client_id[]      = "nRF52840_subscriber";     /**< The MQTT-SN Client's ID. */
static char                 m_topic_name[]     = "nRF52840_resources/led3"; /**< Name of the topic corresponding to subscriber's BSP_LED_2. */
static mqttsn_topic_t       m_topic            =                            /**< Topic corresponding to subscriber's BSP_LED_2. */
{
    .p_topic_name = (unsigned char *)m_topic_name,
    .topic_id     = 0,
};

static uint8_t status = 0;

/***************************************************************************************************
 * @section MQTT-SN
 **************************************************************************************************/

/**@brief Initializes MQTT-SN client's connection options.
 */
static void connect_opt_init(void)
{
    m_connect_opt.alive_duration = MQTTSN_DEFAULT_ALIVE_DURATION,
    m_connect_opt.clean_session = MQTTSN_DEFAULT_CLEAN_SESSION_FLAG,
    m_connect_opt.will_flag = MQTTSN_DEFAULT_WILL_FLAG,
    m_connect_opt.client_id_len = strlen(m_client_id),

    memcpy(m_connect_opt.p_client_id, (unsigned char *)m_client_id, m_connect_opt.client_id_len);
}

/**@brief Processes GWINFO message from a gateway.
 *
 * @details This function updates MQTT-SN Gateway information.
 *
 * @param[in]    p_event  Pointer to MQTT-SN event.
 */
static void gateway_info_callback(mqttsn_event_t *p_event)
{
    m_gateway_addr = *(p_event->event_data.connected.p_gateway_addr);
    m_gateway_id = p_event->event_data.connected.gateway_id;
}

/**@brief Processes CONNACK message from a gateway.
 *
 * @details This function launches the topic registration procedure if necessary.
 */
static void connected_callback(void)
{
    uint32_t err_code = mqttsn_client_topic_register(&m_client,
                                                     m_topic.p_topic_name,
                                                     strlen(m_topic_name),
                                                     &m_msg_id);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("REGISTER message could not be sent. Error code: 0x%x\r\n", err_code);
    }
}

/**@brief Processes DISCONNECT message from a gateway. */
static void disconnected_callback(void)
{
}

/**@brief Processes REGACK message from a gateway.
 *
 * @param[in] p_event Pointer to MQTT-SN event.
 */
static void regack_callback(mqttsn_event_t *p_event)
{
    m_topic.topic_id = p_event->event_data.registered.packet.topic.topic_id;
    NRF_LOG_INFO("MQTT-SN event: Topic has been registered with ID: %d.\r\n",
                 p_event->event_data.registered.packet.topic.topic_id);
}
/**@brief Processes data published by a broker.
 *
 * @
 */
static void received_callback(mqttsn_event_t * p_event)
{
    if (p_event->event_data.published.packet.topic.topic_id == m_topic.topic_id)
    {
        uint8_t dat[10] = {0,0,0,0,0,0,0,0,0,0}; 
        for(uint8_t i = 0; i <= 10; i++){
          dat[i] =p_event->event_data.published.p_payload[i];
        }
        NRF_LOG_INFO("MQTT-SN event: Content to subscribed topic received. %s\r\n",p_event->event_data.published.p_payload);
        message_decoder(dat);
    }
    else
    {
        NRF_LOG_INFO("MQTT-SN event: Content to unsubscribed topic received. Dropping packet.\r\n");
    }
}

/**@brief Processes retransmission limit reached event. */
static void timeout_callback(mqttsn_event_t *p_event)
{
    NRF_LOG_INFO("MQTT-SN event: Timed-out message: %d. Message ID: %d.\r\n",
                 p_event->event_data.error.msg_type,
                 p_event->event_data.error.msg_id);
}

/**@brief Processes results of gateway discovery procedure. */
static void searchgw_timeout_callback(mqttsn_event_t *p_event)
{
    NRF_LOG_INFO("MQTT-SN event: Gateway discovery result: 0x%x.\r\n", p_event->event_data.discovery);
}

/**@brief Function for handling MQTT-SN events. */
void mqttsn_evt_handler(mqttsn_client_t *p_client, mqttsn_event_t *p_event)
{
    switch (p_event->event_id)
    {
    case MQTTSN_EVENT_GATEWAY_FOUND:
        NRF_LOG_INFO("MQTT-SN event: Client has found an active gateway.\r\n");
        gateway_info_callback(p_event);
        status = 1;
        break;

    case MQTTSN_EVENT_CONNECTED:
        NRF_LOG_INFO("MQTT-SN event: Client connected.\r\n");
        connected_callback();
        status = 2;
        break;

    case MQTTSN_EVENT_DISCONNECT_PERMIT:
        NRF_LOG_INFO("MQTT-SN event: Client disconnected.\r\n");
        disconnected_callback();
        break;

    case MQTTSN_EVENT_REGISTERED:
        NRF_LOG_INFO("MQTT-SN event: Client registered topic.\r\n");
        regack_callback(p_event);
        break;

    case MQTTSN_EVENT_SUBSCRIBED:
        NRF_LOG_INFO("MQTT-SN event: Client subscribed to topic.\r\n");
        break;

    case MQTTSN_EVENT_UNSUBSCRIBED:
        NRF_LOG_INFO("MQTT-SN event: Client unsubscribed to topic.\r\n");
        break;

    case MQTTSN_EVENT_RECEIVED:
        NRF_LOG_INFO("MQTT-SN event: Client received content.\r\n");
        received_callback(p_event);
        break;

    case MQTTSN_EVENT_PUBLISHED:
        NRF_LOG_INFO("MQTT-SN event: Client has successfully published content.\r\n");
        break;

    case MQTTSN_EVENT_TIMEOUT:
        NRF_LOG_INFO("MQTT-SN event: Retransmission retries limit has been reached.\r\n");
        timeout_callback(p_event);
        break;

    case MQTTSN_EVENT_SEARCHGW_TIMEOUT:
        NRF_LOG_INFO("MQTT-SN event: Gateway discovery procedure has finished.\r\n");
        searchgw_timeout_callback(p_event);
        break;

    default:
        break;
    }
}
/**
 * @dependency: mqttsn_init is dependent on status_led_1_init();
 *
 */

void mqttsn_init(void)
{
    uint32_t err_code;
    thread_setup();

    err_code = mqttsn_client_init(&m_client,
                                  MQTTSN_DEFAULT_CLIENT_PORT,
                                  mqttsn_evt_handler,
                                  get_thread_instance());
    APP_ERROR_CHECK(err_code);

    connect_opt_init();

    timer_1_init(2000, mqttsn_boot);
}

void mqttsn_loop(void)
{
    thread_loop();
}

void mqttsn_pub(char message)
{
    if (status == 2)
    {
        uint32_t err_code = mqttsn_client_publish(&m_client, m_topic.topic_id, &message, 1, &m_msg_id);
        if (err_code != NRF_SUCCESS)
        {
            NRF_LOG_ERROR("PUBLISH message could not be sent. Error code: 0x%x\r\n", err_code)
        }
        {
            NRF_LOG_ERROR("NOT READY TO PUBLISH");
        }
    }
}
static char m = 'a';

void pub(void)
{
    if (status == 2)
    {
        uint32_t err_code;
        err_code = mqttsn_client_publish(&m_client, m_topic.topic_id, &m, 1, &m_msg_id);
        if (err_code != NRF_SUCCESS)
        {
            NRF_LOG_ERROR("PUBLISH message could not be sent. Error code: 0x%x\r\n", err_code);
        }
    }
}

void sub(void){
if(status == 2){
        uint32_t err_code = mqttsn_client_subscribe(&m_client, m_topic.p_topic_name, 4, &m_msg_id);
        if (err_code != NRF_SUCCESS)
        {
            NRF_LOG_ERROR("SUBSCRIBE message could not be sent.\r\n");
        }else{
          status ++;
        }
        }
}

/**
 * void mqttsn_boot(nrf_timer_event_t event_type, void *p_context)
 * Function to be used as interupt handler for timer interupts
 * This function will connect the the device to gateway and the client
 */

void mqttsn_boot(nrf_timer_event_t event_type, void *p_context)
{
    mqttsn_loop();
    uint32_t err_code;
    switch (status)
    {
    case STATE_GATEWAY:
        err_code = mqttsn_client_search_gateway(&m_client, SEARCH_GATEWAY_TIMEOUT);
        NRF_LOG_INFO("Gateway message sending");
        if (err_code != NRF_SUCCESS)
        {
            NRF_LOG_ERROR("SEARCH GATEWAY message could not be sent. Error: 0x%x\r\n", err_code);
        }
        break;
    case STATE_CLIENT:
        if (mqttsn_client_state_get(&m_client) == MQTTSN_CLIENT_CONNECTED)
        {
            err_code = mqttsn_client_disconnect(&m_client);
            if (err_code != NRF_SUCCESS)
            {
                NRF_LOG_ERROR("DISCONNECT message could not be sent. Error: 0x%x\r\n", err_code);
            }
        }
        else
        {
            err_code = mqttsn_client_connect(&m_client, &m_gateway_addr, m_gateway_id, &m_connect_opt);
            if (err_code != NRF_SUCCESS)
            {
                NRF_LOG_ERROR("CONNECT message could not be sent. Error: 0x%x\r\n", err_code);
            }
        }
        break;
    case STATE_PUB:
        sub();
        break;
    case 3:
        timer_1_uninit();
        break;

    default:
        break;
    }
    NRF_LOG_FLUSH();
    mqttsn_loop();
}