/**
 * \file
 *
 * \brief General timer functions
 *
 * Polled software timers typically used for debouncing, functions that need to
 * wait, etc. The timers are built upon a system-level timer (e.g. Timer0), and
 * for each instance the following needs to be specified at init:
 *
 * - A GetSysTmrTick() function that returns the current system timer value
 * - The system timer tick period
 *
 *  @{
 *
 */
#ifndef _TMR_H
#define _TMR_H

#include <stdint.h>
#include <stdbool.h>

/**
 * \brief Type definition for the system timer tick
 *
 * The timer counts the number of system timer ticks. E.g. system timer that 
 * occurs every 10ms can be used to time a period of up to 655 seconds max.
 */
typedef uint16_t tmr_tick_t;

/**
 * \brief Type definition for function to return current system timer tick
 * value.
 */
typedef tmr_tick_t ( * pGetSysTmrTick_t)(void);


// Timer states.
typedef enum {
    SYSCLK_STOP = 0,      ///< Timer is stopped
    SYSCLK_START,         ///< Timer is running
    SYSCLK_EXPIRE,        ///< Timer has expired
} sysclk_state_e;


/*! \brief Type definition for the timer structure
 *
 *  An instance of this structure is used for every event that needs to be timed.
 */
typedef struct {
    pGetSysTmrTick_t pGetTick;      // Pointer to function to get current system timer
    uint16_t u16SysTmrTickMs;       // System timer Timer period in ms
    sysclk_state_e eState;      ///< Current state of the timer
    tmr_tick_t tExpire;     ///< The value when the timer will expire
} tmr_t;


void TMR_vInit(tmr_t *pTmr, pGetSysTmrTick_t pGetTick, uint16_t u16SysTmrTickMs);
void TMR_vStart(tmr_t *pTmr, const uint16_t u16TmrPer);
bool TMR_bExpired(tmr_t *pTmr);
void TMR_vStop(tmr_t *pTmr);

#endif
