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
RKH_DCLR_COMP_STATE		S1,S3,S11;
RKH_DCLR_BASIC_STATE	S2,S31,S32,S111,S112,S12;
RKH_DCLR_COND_STATE		C1,C2;
RKH_DCLR_CHOICE_STATE	CH;
RKH_DCLR_DHIST_STATE	DH;
RKH_DCLR_SHIST_STATE	H;

/* ........................ Declares initial action ........................ */
void my_init(const RKH_SMA_T *me, RKH_EVT_T *pe);

/* ........................ Declares effect actions ........................ */
void set_x1(const RKH_SMA_T *me, RKH_EVT_T *pe);
void set_y_2(const RKH_SMA_T *me, RKH_EVT_T *pe);
void set_y_1(const RKH_SMA_T *me, RKH_EVT_T *pe);
void dummy_act(const RKH_SMA_T *me, RKH_EVT_T *pe);
void show_data(const RKH_SMA_T *me, RKH_EVT_T *pe);
void terminate(const RKH_SMA_T *me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
void set_x_1(const RKH_SMA_T *me);
void set_x_2(const RKH_SMA_T *me);
void set_x_3(const RKH_SMA_T *me);
void set_y_0(const RKH_SMA_T *me);

/* ......................... Declares exit actions ......................... */
void dummy_exit(const RKH_SMA_T *me);

/* ............................ Declares guards ............................ */
rbool_t y_0(const RKH_SMA_T *me, RKH_EVT_T *pe);
rbool_t y_1(const RKH_SMA_T *me, RKH_EVT_T *pe);
rbool_t y_2(const RKH_SMA_T *me, RKH_EVT_T *pe);
rbool_t x1(const RKH_SMA_T *me, RKH_EVT_T *pe);
rbool_t x2_or_x3(const RKH_SMA_T *me, RKH_EVT_T *pe);

/* ........................ States and pseudostates ........................ */
RKH_CREATE_BASIC_STATE(S2, NULL, NULL,  RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(S2)
    RKH_TRINT(FOUR,    NULL,       dummy_act),
    RKH_TRINT(SIX,     NULL,       show_data),
    RKH_TRINT(TERM,    NULL,       terminate),
    RKH_TRREG(ONE,     x1,         dummy_act,  &S1),
    RKH_TRREG(TWO,     NULL,       NULL,       &S2),
    RKH_TRREG(THREE,   NULL,       dummy_act,  &C2),
RKH_END_TRANS_TABLE

RKH_CREATE_COMP_STATE(S1, set_y_0, dummy_exit,  RKH_ROOT, &S11, &DH);
RKH_CREATE_TRANS_TABLE(S1)
    RKH_TRINT(SIX,     NULL,       show_data),
    RKH_TRINT(TERM,    NULL,       terminate),
    RKH_TRREG(TWO,     NULL,       set_y_2,    &S2),
    RKH_TRREG(THREE,   NULL,       NULL,       &S3),
    RKH_TRREG(FIVE,    NULL,       NULL,       &S12),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(S12, set_x_3, NULL, &S1, NULL);
RKH_CREATE_TRANS_TABLE(S12)
    RKH_TRREG(FOUR,    NULL,       set_y_1,    &S2),
RKH_END_TRANS_TABLE

RKH_CREATE_COMP_STATE(S11, NULL, NULL, &S1, &S111, &H);
RKH_CREATE_TRANS_TABLE(S11)
    RKH_TRREG(TWO,     NULL,       NULL,       &S112),
    RKH_TRREG(FOUR,    NULL,       NULL,       &S12),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(S111, set_x_1, NULL, &S11, NULL);
RKH_CREATE_TRANS_TABLE(S111)
    RKH_TRREG(ONE,     NULL,       NULL,       &S112),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(S112, set_x_2, NULL, &S11, NULL);
RKH_CREATE_TRANS_TABLE(S112)
    RKH_TRREG(ONE,     NULL,       NULL,       &S111),
    RKH_TRREG(TWO,     NULL,       NULL,       &S11),
    RKH_TRREG(THREE,   NULL,       set_x1,     &CH),
RKH_END_TRANS_TABLE

RKH_CREATE_SHALLOW_HISTORY_STATE(H, &S11, NULL, NULL, NULL);
RKH_CREATE_DEEP_HISTORY_STATE(DH, &S1, NULL, NULL, NULL);

RKH_CREATE_COMP_STATE(S3, NULL, NULL,  RKH_ROOT, &S31,  NULL);
RKH_CREATE_TRANS_TABLE(S3)
    RKH_TRINT(SIX,     NULL,       show_data),
    RKH_TRINT(TERM,    NULL,       terminate),
    RKH_TRREG(TWO,     NULL,       NULL,       &C1),
    RKH_TRREG(THREE,   NULL,       NULL,       &S3),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(S31, NULL, NULL, &S3, NULL);
RKH_CREATE_TRANS_TABLE(S31)
    RKH_TRREG(ONE,     NULL,       NULL,       &S32),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(S32, NULL, NULL, &S3, NULL);
RKH_CREATE_TRANS_TABLE(S32)
    RKH_TRREG(ONE,     NULL,       NULL,       &S31),
    RKH_TRREG(THREE,   NULL,       NULL,       &S2),
RKH_END_TRANS_TABLE

RKH_CREATE_CHOICE_STATE(CH);
RKH_CREATE_BRANCH_TABLE(CH)
    RKH_BRANCH(x1,     dummy_act,      &S3),
    RKH_BRANCH(ELSE,   dummy_act,      &S32),
RKH_END_BRANCH_TABLE

RKH_CREATE_COND_STATE(C1);
RKH_CREATE_BRANCH_TABLE(C1)
    RKH_BRANCH(y_1,    NULL,           &H),
    RKH_BRANCH(y_2,    dummy_act,      &DH),
    RKH_BRANCH(y_0,    NULL,           &S1),
RKH_END_BRANCH_TABLE

RKH_CREATE_COND_STATE(C2);
RKH_CREATE_BRANCH_TABLE(C2)
    RKH_BRANCH(x1,         dummy_act,  &S3),
    RKH_BRANCH(x2_or_x3,   dummy_act,  &CH),
    RKH_BRANCH(ELSE,       NULL,       &S2),
RKH_END_BRANCH_TABLE

/* ............................. Active object ............................. */
struct MySm
{
    RKH_SMA_T sma;  /* base structure */
    rui8_t x;       /* private member */
    rui8_t y;       /* private member */
};                  /* SMA derived from RKH_SMA_T structure */

RKH_SMA_CREATE(MySm, my, 0, HCAL, &S1, my_init, NULL);
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

    RKH_TR_FWK_OBJ(&S1);
    RKH_TR_FWK_OBJ(my);
    RKH_TR_FWK_OBJ(&my->equeue);
    RKH_TR_FWK_OBJ(&S1);
    RKH_TR_FWK_OBJ(&S11);
    RKH_TR_FWK_OBJ(&S111);
    RKH_TR_FWK_OBJ(&S112);
    RKH_TR_FWK_OBJ(&S12);
    RKH_TR_FWK_OBJ(&S2);
    RKH_TR_FWK_OBJ(&S3);
    RKH_TR_FWK_OBJ(&S31);
    RKH_TR_FWK_OBJ(&S32);
    RKH_TR_FWK_OBJ(&C1);
    RKH_TR_FWK_OBJ(&C2);
    RKH_TR_FWK_OBJ(&CH);
    RKH_TR_FWK_OBJ(&DH);
    RKH_TR_FWK_OBJ(&H);

    RKH_TR_FWK_SIG(ZERO);
    RKH_TR_FWK_SIG(ONE);
    RKH_TR_FWK_SIG(TWO);
    RKH_TR_FWK_SIG(THREE);
    RKH_TR_FWK_SIG(FOUR);
    RKH_TR_FWK_SIG(FIVE);
    RKH_TR_FWK_SIG(SIX);
    RKH_TR_FWK_SIG(TERM);

    realMe->x = realMe->y = 0;
}

/* ............................ Effect actions ............................. */
void
set_x1(const RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)pe;
    ((MySm *)(me))->x = 1;
}

void
set_y_2(const RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)pe;
    ((MySm *)(me))->y = 2;
}

void
set_y_1(const RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)pe;
    ((MySm *)(me))->y = 1;
}

void
dummy_act(const RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void
show_data(const RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void
terminate(const RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
    rkh_fwk_exit();
}

/* ............................. Entry actions ............................. */
void
set_x_1(const RKH_SMA_T *me)
{
    ((MySm *)(me))->x = 1;
}

void
set_x_2(const RKH_SMA_T *me)
{
    ((MySm *)(me))->x = 2;
}

void
set_x_3(const RKH_SMA_T *me)
{
    ((MySm *)(me))->x = 3;
}

void
set_y_0(const RKH_SMA_T *me)
{
    ((MySm *)(me))->y = 0;
}

/* ............................. Exit actions .............................. */
void
dummy_exit(const RKH_SMA_T *me)
{
    (void)me;
}

/* ................................ Guards ................................. */
rbool_t
y_0(const RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)pe;
    return ((MySm *)(me))->y == 0 ? RKH_GTRUE : RKH_GFALSE;
}

rbool_t
y_1(const RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)pe;
    return ((MySm *)(me))->y == 1 ? RKH_GTRUE : RKH_GFALSE;
}

rbool_t
y_2(const RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)pe;
    return ((MySm *)(me))->y == 2 ? RKH_GTRUE : RKH_GFALSE;
}

rbool_t
x1(const RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)pe;
    return ((MySm *)(me))->x == 1 ? RKH_GTRUE : RKH_GFALSE;
}

rbool_t
x2_or_x3(const RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)pe;
    return (((MySm *)(me))->x == 2 || ((MySm *)(me))->x == 3) ? 
           RKH_GTRUE : RKH_GFALSE;
}

/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
