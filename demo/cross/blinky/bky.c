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
 *	Defines SMA (active object) 'blinky'.
 */

RKH_SMA_CREATE( BKYSM_T, blinky, 0, HCAL, &led_on, blinky_init, NULL );


/*
 *	Defines states and pseudostates.
 */

#if 0
RKH_CREATE_BASIC_STATE( led_on, NULL, NULL, RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( led_on )

	RKH_TRREG( TIMEOUT, NULL, 	blinky_led_off,		&led_off ),

RKH_END_TRANS_TABLE
#else

#define RKH_DECLARE_TR_TBL( name ) \
			extern RKHROM RKH_TR_T name##_trtbl[]

#define RKH_INIT_BASIC_STATE( name, en, ex, parent, prepro ) \
			{ \
				{ \
					{MKBASE(RKH_BASIC, name)}, 	/* RKH_BASE_T */ \
					MKST(en, ex, parent) \
				}, 								/* RKH_STATE_T */ \
				MKBASIC(name, prepro) \
			}									/* RKH_BASIC_STATE_T */ \


#define BLINKY_BASIC_STATE( type_t, name, en, ex, parent, title ) \
			RKH_DECLARE_TR_TBL( name ); \
			\
			RKHROM type_t name = \
			{ \
				RKH_INIT_BASIC_STATE( name, en, ex, parent, NULL ), \
				title \
			}

BLINKY_BASIC_STATE( BKY_ST_T, led_on, NULL, NULL, RKH_ROOT, "Menu 1" );
RKH_CREATE_TRANS_TABLE( led_on )

	RKH_TRREG( TIMEOUT, NULL, 	blinky_led_off,		&led_off ),

RKH_END_TRANS_TABLE

#endif

RKH_CREATE_BASIC_STATE( led_off, NULL, NULL, RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( led_off )

	RKH_TRREG( TIMEOUT,	NULL,	blinky_led_on,		&led_on ),

RKH_END_TRANS_TABLE
