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

#include "tmr.h"
#include <assert.h>

static pGetSysTmrTick_t _sources[8];


void TMR_vRegisterSource(timer_source_t source, pGetSysTmrTick_t function){
	_sources[source] = function;
}


void TMR_vCreate(tmr_t *pTmr, const timer_source_t source)
{
	pTmr->source = source;
	pTmr->eState = SYSCLK_EXPIRE;
}


void TMR_vStart(tmr_t *pTmr, const uint16_t period){
	assert(_sources[pTmr->source]);
	pTmr->eState = SYSCLK_START;
	pTmr->expire_time = _sources[pTmr->source]()+ period;
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
#define SYSCLK_TICK_SIZE_BITS 32
bool TMR_bIsExpired(tmr_t *pTmr)
{
    // See if the timer has already expired
    if (pTmr->eState == SYSCLK_EXPIRE) { return true; }

    // Get current tick time
	assert(_sources[pTmr->source]);
    uint32_t tTickCounter = _sources[pTmr->source]();

    // Has timer expired?
    if(tTickCounter >= pTmr->expire_time) {
        if(((tTickCounter - pTmr->expire_time) & (1 << (SYSCLK_TICK_SIZE_BITS - 1))) != 0) {
            return false;
        }
    } else {
        if(((pTmr->expire_time - tTickCounter) & (1 << (SYSCLK_TICK_SIZE_BITS - 1))) == 0) {
            return false;
        }
    }

    // Update state
    pTmr->eState = SYSCLK_EXPIRE;

    return true;
}