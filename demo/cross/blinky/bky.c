/*
 *	bky.c
 */


#include "rkh.h"


/*
 *	Include file of HSM definitions.
 */

#include "bky.h"


/*
 *	Include file of action/guard definitions
 */

#include "bkyact.h"


/*
 *	Defines SMA (active object) 'bky'.
 */

RKH_SMA_CREATE( BKYSM_T, 0, blinky, 0, HCAL, &led_on, blinky_init, NULL );


/*
 *	Defines states and pseudostates.
 */

RKH_CREATE_BASIC_STATE( led_on, 0, NULL, NULL, RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( led_on )

	RKH_TRREG( TIMEOUT, NULL, 	blinky_led_off,		&led_off ),

RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE( led_off, 1, NULL, NULL, RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( led_off )

	RKH_TRREG( TIMEOUT,	NULL,	blinky_led_on,		&led_on ),

RKH_END_TRANS_TABLE
