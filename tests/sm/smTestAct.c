/**
 *  \file       smTestAct.c
 *  \ingroup    Test
 *
 *  \brief      Production code.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.11.11  LeFr  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */

#include <stdio.h>
#include "rkh.h"
#include "bsp.h"
#include "smTest.h"
#include "smTestAct.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */

/* Defines the state machine's initializing action */
void
smTest_init(SmTest *const me)
{
    me->foo = 0;
}

/* Defines effect action */
void
smTest_tr11(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void
smTest_tr12(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void
smTest_tr13(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void
smTest_tr14(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void
smTest_tr15(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_tr21(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_tr22(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_tr23(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_tr31(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_tr32(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_tr33(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_tr41(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_tr42(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_tr43(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_tr51(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_tr52(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_tr53(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_tr54(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

/* Defines entry actions */
void 
smTest_nS0(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_nS1(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_nS2(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_nS3(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_nS21(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_nS22(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_nS221(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_nS31(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

/* Defines exit actions */
void 
smTest_xS0(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_xS1(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_xS2(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_xS3(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_xS21(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_xS22(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_xS221(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smTest_xS31(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

/* Defines guards */
rbool_t
smTest_falseGuard(SmTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
    return RKH_FALSE;
}

/* ------------------------------ End of file ------------------------------ */
