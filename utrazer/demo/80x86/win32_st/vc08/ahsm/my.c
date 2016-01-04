/*
 *	my.c
 */


#include "rkh.h"


/*
 *	Include file of HSM definitions.
 */

#include "my.h"


/*
 *	Include file of action/guard definitions
 */

#include "myact.h"


/*
 *	Defines SMA "my".
 */

RKH_SMA_CREATE( MYSM_T, my, 0, HCAL, &S1, my_init, NULL );


/*
 *	Defines states and pseudostates.
 */

RKH_CREATE_BASIC_STATE( S2, NULL, NULL,  RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( S2 )

	RKH_TRINT( FOUR, 	NULL, 		dummy_act ),
	RKH_TRINT( SIX, 	NULL, 		show_data ),
	RKH_TRINT( TERM, 	NULL, 		terminate ),
	RKH_TRREG( ONE, 	x1,			dummy_act, 	&S1 ),
	RKH_TRREG( TWO, 	NULL, 		NULL, 		&S2 ),
	RKH_TRREG( THREE, 	NULL, 		dummy_act,	&C2 ),

RKH_END_TRANS_TABLE

RKH_CREATE_COMP_STATE( S1, set_y_0, dummy_exit,  RKH_ROOT, &S11, &DH );
RKH_CREATE_TRANS_TABLE( S1 )

	RKH_TRINT( SIX, 	NULL, 		show_data ),
	RKH_TRINT( TERM, 	NULL, 		terminate ),
	RKH_TRREG( TWO, 	NULL, 		set_y_2,	&S2 ),
	RKH_TRREG( THREE, 	NULL, 		NULL, 		&S3 ),
	RKH_TRREG( FIVE, 	NULL, 		NULL, 		&S12 ),

RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE( S12, set_x_3, NULL, &S1, NULL );
RKH_CREATE_TRANS_TABLE( S12 )

	RKH_TRREG( FOUR, 	NULL, 		set_y_1, 	&S2 ),

RKH_END_TRANS_TABLE

RKH_CREATE_COMP_STATE( S11, NULL, NULL, &S1, &S111, &H );
RKH_CREATE_TRANS_TABLE( S11 )

	RKH_TRREG( TWO, 	NULL, 		NULL, 		&S112 ),
	RKH_TRREG( FOUR, 	NULL, 		NULL, 		&S12 ),

RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE( S111, set_x_1, NULL, &S11, NULL );
RKH_CREATE_TRANS_TABLE( S111 )

	RKH_TRREG( ONE, 	NULL, 		NULL, 		&S112 ),

RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE( S112, set_x_2, NULL, &S11, NULL );
RKH_CREATE_TRANS_TABLE( S112 )

	RKH_TRREG( ONE, 	NULL, 		NULL,		&S111 ),
	RKH_TRREG( TWO, 	NULL, 		NULL, 		&S11 ),
	RKH_TRREG( THREE, 	NULL, 		set_x1,		&CH ),

RKH_END_TRANS_TABLE

RKH_CREATE_SHALLOW_HISTORY_STATE( H, &S11 );
RKH_CREATE_DEEP_HISTORY_STATE( DH, &S1 );

RKH_CREATE_COMP_STATE( S3, NULL, NULL,  RKH_ROOT, &S31,  NULL );
RKH_CREATE_TRANS_TABLE( S3 )

	RKH_TRINT( SIX, 	NULL, 		show_data ),
	RKH_TRINT( TERM, 	NULL, 		terminate ),
	RKH_TRREG( TWO, 	NULL, 		NULL, 		&C1 ),
	RKH_TRREG( THREE, 	NULL, 		NULL, 		&S3 ),

RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE( S31, NULL, NULL, &S3, NULL );
RKH_CREATE_TRANS_TABLE( S31 )

	RKH_TRREG( ONE, 	NULL, 		NULL, 		&S32 ),

RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE( S32, NULL, NULL, &S3, NULL );
RKH_CREATE_TRANS_TABLE( S32 )

	RKH_TRREG( ONE, 	NULL, 		NULL, 		&S31 ),
	RKH_TRREG( THREE, 	NULL, 		NULL,		&S2 ),

RKH_END_TRANS_TABLE


RKH_CREATE_CHOICE_STATE( CH );
RKH_CREATE_BRANCH_TABLE( CH )

	RKH_BRANCH( x1, 	dummy_act, 		&S3 ),
	RKH_BRANCH( ELSE, 	dummy_act, 		&S32 ),

RKH_END_BRANCH_TABLE


RKH_CREATE_COND_STATE( C1 );
RKH_CREATE_BRANCH_TABLE( C1 )

	RKH_BRANCH( y_1, 	NULL, 			&H ),
	RKH_BRANCH( y_2, 	dummy_act, 		&DH ),
	RKH_BRANCH( y_0, 	NULL, 			&S1 ),

RKH_END_BRANCH_TABLE

RKH_CREATE_COND_STATE( C2 );
RKH_CREATE_BRANCH_TABLE( C2 )

	RKH_BRANCH( x1, 		dummy_act, 	&S3 ),
	RKH_BRANCH( x2_or_x3, 	dummy_act,	&CH ),
	RKH_BRANCH( ELSE, 		NULL, 		&S2 ),

RKH_END_BRANCH_TABLE
