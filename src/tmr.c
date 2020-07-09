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

#include <asf.h>
#include "tmr.h"

/*! \brief Size of sysclk_tick_t.
 *
 *  Size of sysclk_tick_t in bits (e.g. unsigned int will give 16).
 *  This value is used to detect counter roll-over.
 */
#define SYSCLK_TICK_SIZE_BITS (sizeof(tmr_tick_t)*8)

/**
* \brief Init an instance of a timer
*
* An instance of a timer must be initialized before it can be used.
*
* \param   pTmr    Pointer to timer struct
* \param   pGetTick    Pointer to function to get system timer tick value
* \param   u16SysTmrTickMs The system timer tick period [ms]
*/
void TMR_vInit(tmr_t *pTmr, pGetSysTmrTick_t pGetTick, uint16_t u16SysTmrTickMs)
{
    pTmr->pGetTick = pGetTick;
    pTmr->u16SysTmrTickMs = u16SysTmrTickMs;
}

/**
 * \brief Start an instance of a timer.
 *
 * The structure for the instance of the timer is updated with the expiry time of the
 * timer, and the timer is started.
 *
 * \param   pTmr    Pointer to timer struct
 * \param   u16TmrPer   Timer timeout value [ms]
 */
void TMR_vStart(tmr_t *pTmr, const uint16_t u16TmrPer)
{
    // Convert interval ms to tick, add current tick time and store
    pTmr->tExpire = pTmr->pGetTick() + (u16TmrPer / pTmr->u16SysTmrTickMs);

    // Update state
    pTmr->eState = SYSCLK_START;
}

void TMR_vStop(tmr_t *pTmr)
{
    // Update state
    pTmr->eState = SYSCLK_STOP;
}

/*! \brief Check if a timer has expired.
 *
 *  How does the roll-over work?
 *
 *  \par
 *  If tTickCounter=65000 and pTimer->tExpire=10 then we actually still need
 *  to go 65536-6500+10 = 546 ticks, although a simple (tTickCounter >
 *  pTimer->tExpire) test will incorrectly show the timer has expired. So,
 *  - ((tTickCounter - pTimer->tExpire) & (1<<(TMR_TICK_SIZE_BITS-1)))
 *  - = ((65000 - 10) & (1<<(16-1)))
 *  - = ((64990) & (1<<15))
 *  - = (0xFDDE & 0x8000)
 *  - != 0 which will return FALSE (this is correct).
 *
 *  \par
 *  When tTickCounter now rolls over to 0 we get
 *  - ((pTimer->tExpire - tTickCounter) & (1<<(TMR_TICK_SIZE_BITS-1)))
 *  - = ((10 - 0) & (1<<(16-1)))
 *  - = (10 & 0x8000)
 *  - = 0 which will return FALSE (this is correct) until (pTimer->tExpire == tTickCounter).
 *
 *  \param *pTimer Pointer to the specific timer structure
 *  \return bool The timer has expired (TRUE) or not (FALSE)
 */
bool TMR_bExpired(tmr_t *pTmr)
{
    tmr_tick_t tTickCounter;

    // See if the timer has been stopped
    if (pTmr->eState == SYSCLK_STOP) { return false; }

    // See if the timer has already expired
    if (pTmr->eState == SYSCLK_EXPIRE) { return true; }

    // Get current tick time
    tTickCounter = pTmr->pGetTick();

    // Has timer expired?
    if(tTickCounter >= pTmr->tExpire) {
        if(((tTickCounter - pTmr->tExpire) & (1 << (SYSCLK_TICK_SIZE_BITS - 1))) != 0) {
            return false;
        }
    } else {
        if(((pTmr->tExpire - tTickCounter) & (1 << (SYSCLK_TICK_SIZE_BITS - 1))) == 0) {
            return false;
        }
    }

    // Update state
    pTmr->eState = SYSCLK_EXPIRE;

    return true;
}