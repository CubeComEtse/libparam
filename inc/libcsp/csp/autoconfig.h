/*
 * autoconfig.h
 *
 * Created: 9/22/2025 9:45:17 AM
 *  Author: Adriaan van der Westhuizen
 */ 

#ifndef CSP_AUTOCONFIG_H_
#define CSP_AUTOCONFIG_H_

#include <machine/endian.h>

/* 
 * Primary configuration defines for libcsp.
 */

#define CSP_POSIX                       0
#define CSP_ZEPHYR                      0
#define CSP_FREERTOS                    1

#define CSP_HAVE_STDIO                  1
#define CSP_ENABLE_CSP_PRINT            0
#define CSP_PRINT_STDIO                 0

#define CSP_REPRODUCIBLE_BUILDS         0   // Reproducible build

#define CSP_QFIFO_LEN                   15  // Length of incoming queue for router task
#define CSP_PORT_MAX_BIND               16  // Maximum number of bindable ports
#define CSP_CONN_RXQUEUE_LEN            16  // Number of packets in connection queue
#define CSP_CONN_MAX                    8   // Number of new connections on socket queue
#define CSP_BUFFER_SIZE                 256 // Bytes in each packet buffer
#define CSP_BUFFER_COUNT                15  // Number of total packet buffers
#define CSP_RDP_MAX_WINDOW              5   // Max window size for RDP
#define CSP_RTABLE_SIZE                 10  // Number of elements in routing table

#define CSP_USE_RDP                     1
#define CSP_USE_HMAC                    1
#define CSP_USE_PROMISC                 0
#define CSP_USE_RTABLE                  0

#define CSP_HAVE_LIBSOCKETCAN           0
#define CSP_HAVE_LIBZMQ                 0

/* 
 * These appear in the csp_autoconfig.h.in file, but not in the CMakeLists.txt.
 * No clue what they are for since they don't seem to be used .
 */

#define CSP_BUFFER_ZERO_CLEAR           1
#define CSP_FIXUP_V1_ZMQ_LITTLE_ENDIAN  0

/* 
 * Define some macros for libscp to platform-specific endian functions.
 */

#define htobe16(x) __bswap16 (x)
#define htole16(x) (x)
#define be16toh(x) __bswap16 (x)
#define le16toh(x) (x)

#define htobe32(x) __bswap32 (x)
#define htole32(x) (x)
#define be32toh(x) __bswap32 (x)
#define le32toh(x) (x)

#define htobe64(x) __bswap64 (x)
#define htole64(x) (x)
#define be64toh(x) __bswap64 (x)
#define le64toh(x) (x)

#endif /* CSP_AUTOCONFIG_H_ */