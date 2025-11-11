/**
 * @file cants_config.h
 *
 */

/**
 * @addtogroup CAN-TS
 * @{
 */

#ifndef CANTS_CONFIG_H_
#define CANTS_CONFIG_H_

#define cants_assert(x)

/* for placing global data into it's own section */
#ifndef GLOBAL
#define GLOBAL
#endif
#ifndef GLOBAL_RO
#define GLOBAL_RO
#endif
#ifndef TASK_FUNC
#define TASK_FUNC
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
#endif

#define CANTS_NODE_ID                   0x20        /**< address of this node */
#define CANTS_KEEPALIVE_ID              0x01        /**< broadcast ID on which keep-alive messages are sent */
#define CANTS_TIME_ID                   0           /**< broadcast ID on which time sync messages are sent */
#define CANTS_ERROR_ID                  2           /**< broadcast ID on which error UTM messages are sent */
#define CANTS_WARNING_ID                4           /**< broadcast ID on which warning UTM messages are sent */

#define MAX_SB_SESSIONS                 1           /**< number of maximum supported simultaneous SB sessions */
#define MAX_GB_SESSIONS                 1           /**< number of maximum supported simultaneous GB sessions */
#define SB_TIMEOUT                      2000        /**< SB session timeout from last valid packet received */
#define SB_WRITING_INTERVAL             20          /**< how often to check if data processing was completed */
#define GB_TIMEOUT                      2000        /**< GB session timeout from last valid packet received */
#define GB_BURST_SIZE                   10          /**< maximum number of data transfer frames sent in one burst */
#define GB_BURST_INTERVAL               15          /**< how often to send burst of GB data transfer frames */
#define ADDRESS_TYPE                    uint32_t    /**< GB/SB address type */

#define CLIENT_ENABLED                  0
#define CLIENT_TRIES                    3
#define CLIENT_RESPONSE_TIMEOUT         1000
#define CLIENT_SB_REPORT_DELAY          10
#define CLIENT_SB_REPORT_RETRY          30
#define CLIENT_SB_MAX_DONE_TIMEOUT      3000        /**< maximum SB done bit timeout */

/* task stack sizes and priorities */
#define DISPATCHER_STACK_SIZE           configMINIMAL_STACK_SIZE
#define DISPATCHER_PRIORITY             (tskIDLE_PRIORITY + 2)

#define TC_STACK_SIZE                   configMINIMAL_STACK_SIZE
#define TC_PRIORITY                     (tskIDLE_PRIORITY + 1)

#define TM_STACK_SIZE                   configMINIMAL_STACK_SIZE
#define TM_PRIORITY                     (tskIDLE_PRIORITY + 1)

#define SETBLOCK_STACK_SIZE             configMINIMAL_STACK_SIZE
#define SETBLOCK_PRIORITY               (tskIDLE_PRIORITY + 2)

#define GETBLOCK_STACK_SIZE             configMINIMAL_STACK_SIZE
#define GETBLOCK_PRIORITY               (tskIDLE_PRIORITY + 1)

#define CLIENT_STACK_SIZE               configMINIMAL_STACK_SIZE
#define CLIENT_PRIORITY                 (tskIDLE_PRIORITY + 1)

/* queue lengths */
#define DISPATCHER_QUEUE_LEN            64
#define TC_QUEUE_LEN                    5
#define TM_QUEUE_LEN                    5
#define SETBLOCK_QUEUE_LEN              64
#define GETBLOCK_QUEUE_LEN              5
#define REQUEST_QUEUE_LEN               5
#define RESPONSE_QUEUE_LEN              64

#endif

/**
 * @}
 */
