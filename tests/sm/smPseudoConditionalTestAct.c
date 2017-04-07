/**
 *  \file       smPseudoConditionalTestAct.c
 *  \ingroup    Test
 *
 *  \brief      Production code.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.06.05  LeFr  v1.0.00  Initial version
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
#include "smPseudoConditionalTest.h"
#include "smPseudoConditionalTestAct.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */

/* ============================ Initial action ============================= */
/* ============================ Effect actions ============================= */
void 
smPCT_tr1(SmPseudoConditionalTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smPCT_tr2(SmPseudoConditionalTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

void 
smPCT_setCondition(SmPseudoConditionalTest *const me, RKH_EVT_T *pe)
{
    me->foo = (pe->e == A) ? 1 : 0;
}

/* ============================= Entry actions ============================= */
/* ============================= Exit actions ============================== */
/* ================================ Guards ================================= */
rbool_t 
smPCT_onEventA(SmPseudoConditionalTest *const me, RKH_EVT_T *pe)
{
    return (me->foo == 1) ? RKH_TRUE : RKH_FALSE;
}

/* ------------------------------ End of file ------------------------------ */
