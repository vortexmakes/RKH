/*
 *	my.c
 */


#include "rkhsm.h"


/*
 *	Include file of event definitions.
 */

#include "myevt.h"


/*
 *	Include file of HSM definitions.
 */

#include "my.h"


/*
 *	Include file of action/guard definitions
 */

#include "myact.h"


/*
 *	Defines HSM's data.
 */

static MYHDATA_T mydata;


/*
 *	Defines HSM.
 */

RKH_CREATE_HSM( my, 0, HCAL, &S1, my_init, &mydata );


/*
 *	Defines state transition tables
 */

RKH_CREATE_TRANS_TABLE( S2 ) =
{
	RKH_TRREG( ONE, x_equal_1, dummy_act, &S1 ),
	RKH_TRREG( TWO, NULL, NULL, &S2 ),
	RKH_TRREG( THREE, NULL, NULL, &C2 ),
	RKH_TRINT( FOUR, NULL, dummy_act ),
	RKH_END_TRANS_TABLE
};

RKH_CREATE_TRANS_TABLE( S1 ) =
{
	RKH_TRREG( THREE, NULL, NULL, &S3 ),
	RKH_TRREG( TWO, NULL, set_y_2, &S2 ),
	RKH_END_TRANS_TABLE
};

RKH_CREATE_TRANS_TABLE( S12 ) =
{
	RKH_TRREG( ONE, NULL, NULL, &J ),
	RKH_TRREG( FOUR, NULL, set_y_1, &S2 ),
	RKH_END_TRANS_TABLE
};

RKH_CREATE_TRANS_TABLE( S11 ) =
{
	RKH_TRREG( FOUR, NULL, NULL, &S12 ),
	RKH_END_TRANS_TABLE
};

RKH_CREATE_TRANS_TABLE( S111 ) =
{
	RKH_TRREG( ONE, NULL, NULL, &S112 ),
	RKH_END_TRANS_TABLE
};

RKH_CREATE_TRANS_TABLE( S112 ) =
{
	RKH_TRREG( ONE, NULL, NULL, &S111 ),
	RKH_TRREG( THREE, NULL, NULL, &J ),
	RKH_END_TRANS_TABLE
};

RKH_CREATE_TRANS_TABLE( S3 ) =
{
	RKH_TRREG( TWO, NULL, NULL, &C1 ),
	RKH_TRREG( THREE, NULL, NULL, &S3 ),
	RKH_END_TRANS_TABLE
};

RKH_CREATE_TRANS_TABLE( S31 ) =
{
	RKH_TRREG( ONE, NULL, NULL, &S32 ),
	RKH_END_TRANS_TABLE
};

RKH_CREATE_TRANS_TABLE( S32 ) =
{
	RKH_TRREG( ONE, NULL, NULL, &S31 ),
	RKH_END_TRANS_TABLE
};


/*
 *	Defines branch tables
 */

RKH_CREATE_BRANCH_TABLE( C1 ) =
{
	RKH_BRANCH( Y1, NULL, &H ),
	RKH_BRANCH( Y2, dummy_act, &DH ),
	RKH_END_BRANCH_TABLE
};


RKH_CREATE_BRANCH_TABLE( C2 ) =
{
	RKH_BRANCH( X1, dummy_act, &S3 ),
	RKH_BRANCH( X2_OR_X3, NULL, &S32 ),
	RKH_END_BRANCH_TABLE
};


/*
 *	Defines states and pseudostates.
 */


RKH_CREATE_BASIC_STATE( S2, 0, NULL, NULL,  RKH_ROOT, NULL );

RKH_CREATE_COMP_STATE( S1, 0, set_y_0, dummy_exit,  RKH_ROOT, &S11, &DH );
	RKH_CREATE_BASIC_STATE( S12, 0, set_x_3, NULL, &S1, NULL );
	RKH_CREATE_COMP_STATE( S11, 0, NULL, NULL, &S1, &S111, &H );
		RKH_CREATE_BASIC_STATE( S111, 0, set_x_1, NULL, &S11, NULL );
		RKH_CREATE_BASIC_STATE( S112, 0, set_x_2, NULL, &S11, NULL );
		RKH_CREATE_SHALLOW_HISTORY_STATE( H, 0, &S11 );
	RKH_CREATE_DEEP_HISTORY_STATE( DH, 0, &S1 );

RKH_CREATE_COMP_STATE( S3, 0, NULL, NULL,  RKH_ROOT, &S31,  NULL );
	RKH_CREATE_BASIC_STATE( S31, 0, NULL, NULL, &S3, NULL );
	RKH_CREATE_BASIC_STATE( S32, 0, NULL, NULL, &S3, NULL );

RKH_CREATE_JUNCTION_STATE( J, 0, NULL, &S3 );
RKH_CREATE_COND_STATE( C1, 0, get_y );
RKH_CREATE_COND_STATE( C2, 0, get_x );
