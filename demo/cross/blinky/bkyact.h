/*
 *	bkyact.h
 */


#ifndef __BKYACT_H__
#define __BKYACT_H__


#include "rkh.h"
#include "bky.h"


/*
 *	Defines HSM init function
 */

void blinky_init(BKYSM_T *const me);


/*
 *	Defines transition action functions
 */

void blinky_led_on(BKYSM_T *const me, RKH_EVT_T *pe );
void blinky_led_off(BKYSM_T *const me, RKH_EVT_T *pe );


#endif
