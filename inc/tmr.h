/*
 * This is a software timer module used when we want to wait a little but not 
 * use a full RTOS thread.
 *
 * Each timer is just a struct with a source value and an expiry counter. The
 * sources are registered when the MCU is started up, and can be anything from
 * SysTick, a actual Timer module in the micro. A Source is actually just a 
 * function that returns a number.
 *
 * How to use:
 * To use this timer the user creates a tmr_t struct, then calls the TMR_vCreate
 * function along with the source for this timer. To start the timer, call the
 * TMR_vStart function with a duration. Then periodically call TMR_bIsExpired
 * to check if the timer is expired.
 * 
 * When these functions are called, the Source's function will be called to get
 * a tick count.
 *
 */
#ifndef _TMR_H
#define _TMR_H

#include <stdint.h>
#include <stdbool.h>




/*
 * Timer GetTick Function. Any source that is registered  
 */
typedef uint32_t ( * pGetSysTmrTick_t)(void);


// Timer states.
typedef enum {
    SYSCLK_START,         ///< Timer is running
    SYSCLK_EXPIRE,        ///< Timer has expired
} sysclk_state_e;


/* 
 * This enum defines different timer types so that each struct doesn't need a callback function.
 * Add more values here so you can refere to them easier.
*/
typedef enum {
	TMR_SOURCE_SYSTICK = 0,
} timer_source_t;


/*! \brief Type definition for the timer structure
 *
 *  An instance of this structure is used for every event that needs to be timed.
 */
typedef struct {
	// Source of the ticks. This sets which function to call
	timer_source_t	source;		
	
	// The counter value when this timer will expire 
	uint32_t		expire_time; 
	
	// Current state of the timer
	sysclk_state_e  eState;      
} tmr_t;


void TMR_vRegisterSource(timer_source_t source, pGetSysTmrTick_t function);

void TMR_vCreate(tmr_t *pTmr, const timer_source_t source);
void TMR_vStart(tmr_t *pTmr, const uint16_t period);
bool TMR_bIsExpired(tmr_t *pTmr);

#endif
