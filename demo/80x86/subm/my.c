/**
 *  \file       my.c
 *  \brief      Example application.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.12.06  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "my.h"

/* ----------------------------- Local macros ------------------------------ */
/* ......................... Declares active object ........................ */
typedef struct MySm MySm;

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_COMP_STATE		S1;
RKH_DCLR_BASIC_STATE	S11,S13,S3,SB1,SB2;
RKH_DCLR_SUBM_STATE		S12,S2;
RKH_DCLR_REF_SUBM		SB;
RKH_DCLR_REF_EXPNT		EXPNT1,EXPNT2;
RKH_DCLR_REF_ENPNT		ENPNT;
RKH_DCLR_ENPNT			ENS12,ENS2;

/* ........................ Declares initial action ........................ */
void my_init(const RKH_SMA_T *me, RKH_EVT_T *pe);

/* ........................ Declares effect actions ........................ */
void act1( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void act2( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void act3( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void act4( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void act5( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void act6( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void act7( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void act8( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );
void terminate( const struct RKH_SMA_T *sma, RKH_EVT_T *pe );

/* ......................... Declares entry actions ........................ */
/* ......................... Declares exit actions ......................... */
/* ............................ Declares guards ............................ */
/* ........................ States and pseudostates ........................ */
RKH_CREATE_COMP_STATE( S1, NULL, NULL, RKH_ROOT, &S11, NULL );
RKH_CREATE_TRANS_TABLE( S1 )
	RKH_TRINT( TERM, 	NULL, 	terminate ),
	RKH_TRREG( THREE, 	NULL, 	NULL, 	&ENS2 ),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE( S11, NULL, NULL, &S1, NULL );
RKH_CREATE_TRANS_TABLE( S11 )
	RKH_TRREG( ONE, 	NULL, 	act5, 	&S12 ),
	RKH_TRREG( TWO, 	NULL, 	NULL,	&ENS12 ),
	RKH_TRREG( FOUR, 	NULL, 	NULL,	&S11 ),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE( S13, NULL, NULL, &S1, NULL );
RKH_CREATE_TRANS_TABLE( S13 )
	RKH_TRREG( ONE, 	NULL, 	NULL, 	&S1 ),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE( S3, NULL, NULL, RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( S3 )
	RKH_TRINT( TERM, 	NULL, 	terminate ),
	RKH_TRREG( ONE, 	NULL, 	NULL, 	&S1 ),
RKH_END_TRANS_TABLE


/* ----- Define submachine 'SB' ----- */

RKH_CREATE_REF_SUBMACHINE( SB, &SB1, NULL );

RKH_CREATE_BASIC_STATE( SB1, NULL, NULL, &SB, NULL );
RKH_CREATE_TRANS_TABLE( SB1 )
	RKH_TRREG( FOUR, 	NULL, 	NULL, 	&SB2 ),
	RKH_TRREG( FIVE, 	NULL, 	act6, 	&EXPNT1 ),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE( SB2, NULL, NULL, &SB, NULL );
RKH_CREATE_TRANS_TABLE( SB2 )
	RKH_TRREG( FOUR, 	NULL, 	NULL, 	&SB1 ),
	RKH_TRREG( FIVE, 	NULL, 	act7, 	&EXPNT2 ),
RKH_END_TRANS_TABLE

RKH_CREATE_REF_EXPNT( EXPNT1, 0, &SB );
RKH_CREATE_REF_EXPNT( EXPNT2, 1, &SB );
RKH_CREATE_REF_ENPNT( ENPNT, act8, &SB1, &SB );


/* ----- Define submachine state 'S12' ----- */

RKH_CREATE_SUBMACHINE_STATE( S12, NULL, NULL, &S1, &SB );

RKH_CREATE_TRANS_TABLE( S12 )
	RKH_TRINT( TERM, 	NULL, 	terminate ),
	RKH_TRREG( THREE,	NULL, 	NULL, 	&S1 ),
RKH_END_TRANS_TABLE

RKH_CREATE_EX_CNNPNT_TABLE( S12 )
	RKH_EX_CNNPNT( EX1S12, &EXPNT1, act1, &S13 ),
	RKH_EX_CNNPNT( EX2S12, &EXPNT2, act2, &S3 ),
RKH_END_EX_CNNPNT_TABLE

RKH_EN_CNNPNT( ENS12, &ENPNT, &S12 );


/* ----- Define submachine state 'S2' ----- */

RKH_CREATE_SUBMACHINE_STATE( S2, NULL, NULL, RKH_ROOT, &SB );

RKH_CREATE_TRANS_TABLE( S2 )
	RKH_TRINT( TERM, 	NULL, 	terminate ),
RKH_END_TRANS_TABLE

RKH_CREATE_EX_CNNPNT_TABLE( S2 )
	RKH_EX_CNNPNT( EX1S2, &EXPNT1, act3, &S1 ),
	RKH_EX_CNNPNT( EX2S2, &EXPNT2, act4, &S3 ),
RKH_END_EX_CNNPNT_TABLE

RKH_EN_CNNPNT( ENS2, &ENPNT, &S2 );

/* ............................. Active object ............................. */
struct MySm
{
    RKH_SMA_T sma;  /* base structure */
    rui8_t x;       /* private member */
    rui8_t y;       /* private member */
};                  /* SMA derived from RKH_SMA_T structure */

RKH_SMA_CREATE( MySm, my, 0, HCAL, &S1, my_init, NULL );
RKH_SMA_DEF_PTR(my);

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ............................ Initial action ............................. */
void
my_init(const RKH_SMA_T *me, RKH_EVT_T *pe)
{
    MySm *realMe = ((MySm *)(me));

    RKH_TR_FWK_AO(my);
    RKH_TR_FWK_QUEUE(&RKH_UPCAST(RKH_SMA_T, me)->equeue);
    RKH_TR_FWK_STATE(me, &S1);
    RKH_TR_FWK_STATE(me, &S11);
    RKH_TR_FWK_STATE(me, &S12);
    RKH_TR_FWK_STATE(me, &S13);
    RKH_TR_FWK_STATE(me, &S2);
    RKH_TR_FWK_STATE(me, &S3);
    RKH_TR_FWK_STATE(me, &SB);
    RKH_TR_FWK_STATE(me, &SB1);
    RKH_TR_FWK_STATE(me, &SB2);
    RKH_TR_FWK_OBJ(&EXPNT1);
    RKH_TR_FWK_OBJ(&EXPNT2);
    RKH_TR_FWK_OBJ(&ENPNT);
    RKH_TR_FWK_OBJ(&ENS12);
    RKH_TR_FWK_OBJ(&ENS2);

    RKH_TR_FWK_SIG(ZERO);
    RKH_TR_FWK_SIG(ONE);
    RKH_TR_FWK_SIG(TWO);
    RKH_TR_FWK_SIG(THREE);
    RKH_TR_FWK_SIG(FOUR);
    RKH_TR_FWK_SIG(FIVE);
    RKH_TR_FWK_SIG(SIX);
    RKH_TR_FWK_SIG(TERM);

    RKH_TR_FWK_FUN(&my_init);
    RKH_TR_FWK_FUN(&act1);
    RKH_TR_FWK_FUN(&act2);
    RKH_TR_FWK_FUN(&act3);
    RKH_TR_FWK_FUN(&act4);
    RKH_TR_FWK_FUN(&act5);
    RKH_TR_FWK_FUN(&act6);
    RKH_TR_FWK_FUN(&act7);
    RKH_TR_FWK_FUN(&act8);
    RKH_TR_FWK_FUN(&terminate);

    realMe->x = realMe->y = 0;
}

/* ............................ Effect actions ............................. */
void
act1( const struct RKH_SMA_T *sma, RKH_EVT_T *pe )
{
	(void)sma;
	(void)pe;
}

void
act2( const struct RKH_SMA_T *sma, RKH_EVT_T *pe )
{
	(void)sma;
	(void)pe;
}

void
act3( const struct RKH_SMA_T *sma, RKH_EVT_T *pe )
{
	(void)sma;
	(void)pe;
}

void
act4( const struct RKH_SMA_T *sma, RKH_EVT_T *pe )
{
	(void)sma;
	(void)pe;
}

void
act5( const struct RKH_SMA_T *sma, RKH_EVT_T *pe )
{
	(void)sma;
	(void)pe;
}

void
act6( const struct RKH_SMA_T *sma, RKH_EVT_T *pe )
{
	(void)sma;
	(void)pe;
}

void
act7( const struct RKH_SMA_T *sma, RKH_EVT_T *pe )
{
	(void)sma;
	(void)pe;
}

void
act8( const struct RKH_SMA_T *sma, RKH_EVT_T *pe )
{
	(void)sma;
	(void)pe;
}

void 
terminate( const struct RKH_SMA_T *sma, RKH_EVT_T *pe )
{
	(void)sma;
	(void)pe;
	rkh_fwk_exit();
}

/* ............................. Entry actions ............................. */
/* ............................. Exit actions .............................. */
/* ................................ Guards ................................. */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
