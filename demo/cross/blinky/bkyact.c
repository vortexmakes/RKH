/*
 *	bkyact.c
 */


#include "rkh.h"
#include "bky.h"
#include "bkyact.h"
#include "bsp.h"
#include <stdio.h>


#define CBKY( sm_ )		(( BKYSM_T* )(sm_))


/*
 * 	Declare and allocate the 'e_tout' event.
 * 	The 'e_tout' event with TIMEOUT signal never changes, so it can be 
 * 	statically allocated just once by means of RKH_ROM_STATIC_EVENT() macro.
 */

static RKH_ROM_STATIC_EVENT( e_tout, TIMEOUT );


/*
 * 	Declare and allocate the 'blktim' timer, which is responsible for 
 * 	toggling the LED posting the TIMEOUT signal event to active object 
 * 	'blinky'.
 */

RKH_TMR_T bkytim;


/*
 *	Defines HSM init function
 */

void 
blinky_init(BKYSM_T *const me)
{
	RKH_TMR_INIT(&bkytim, &e_tout, NULL);
	blinky_led_on(me, NULL);
}


/*
 *	Defines transition action functions
 */

void
blinky_led_on(BKYSM_T *const me, RKH_EVT_T *pe )
{
	(void)pe;

	RKH_TMR_ONESHOT( &bkytim, RKH_UPCAST(RKH_SMA_T, me), LED_ON_TIME );
	bsp_led_on();
	++CBKY(me)->cnt;
}


void
blinky_led_off(BKYSM_T *const me, RKH_EVT_T *pe )
{
	(void)me;
	(void)pe;

	RKH_TMR_ONESHOT( &bkytim, blinky, LED_OFF_TIME );
	bsp_led_off();
}
