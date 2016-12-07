/**
 *  \file       myact.c
 *  \brief      Example application.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.03.17  LeFr  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include <stdio.h>
#include "rkh.h"
#include "my.h"
#include "myact.h"

/* ----------------------------- Local macros ------------------------------ */
#define CMY(s)          ((MYSM_T*)(s))

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
/* ............................ Initial action ............................. */
void
my_init(const struct RKH_SMA_T *me)
{
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

    CMY(me)->x = CMY(me)->y = 0;
}

/* ............................ Effect actions ............................. */
void
set_x1(const struct RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)pe;
    CMY(me)->x = 1;
}

void
set_y_2(const struct RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)pe;
    CMY(me)->y = 2;
}

void
set_y_1(const struct RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)pe;
    CMY(me)->y = 1;
}

void
dummy_act(const struct RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void
show_data(const struct RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void
terminate(const struct RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
    rkh_fwk_exit();
}

/* ............................. Entry actions ............................. */
void
set_x_1(const struct RKH_SMA_T *me)
{
    CMY(me)->x = 1;
}

void
set_x_2(const struct RKH_SMA_T *me)
{
    CMY(me)->x = 2;
}

void
set_x_3(const struct RKH_SMA_T *me)
{
    CMY(me)->x = 3;
}

void
set_y_0(const struct RKH_SMA_T *me)
{
    CMY(me)->y = 0;
}

/* ............................. Exit actions .............................. */
void
dummy_exit(const struct RKH_SMA_T *me)
{
    (void)me;
}

/* ................................ Guards ................................. */
rbool_t
y_0(const struct RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)pe;
    return CMY(me)->y == 0 ? RKH_GTRUE : RKH_GFALSE;
}

rbool_t
y_1(const struct RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)pe;
    return CMY(me)->y == 1 ? RKH_GTRUE : RKH_GFALSE;
}

rbool_t
y_2(const struct RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)pe;
    return CMY(me)->y == 2 ? RKH_GTRUE : RKH_GFALSE;
}

rbool_t
x1(const struct RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)pe;
    return CMY(me)->x == 1 ? RKH_GTRUE : RKH_GFALSE;
}

rbool_t
x2_or_x3(const struct RKH_SMA_T *me, RKH_EVT_T *pe)
{
    (void)pe;
    return CMY(me)->x == 2 || CMY(me)->x == 3 ? RKH_GTRUE : RKH_GFALSE;
}

/* ------------------------------ End of file ------------------------------ */
