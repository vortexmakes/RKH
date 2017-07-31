/**
 *  \file       smPseudoTestAct.c
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
#include "smPseudoTest.h"
#include "smPseudoTestAct.h"

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
smPT_trS2History(SmPseudoTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
}

/* ============================= Entry actions ============================= */
/* ============================= Exit actions ============================== */
/* ================================ Guards ================================= */
rbool_t 
smPT_trueGuard(SmPseudoTest *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
    return RKH_TRUE;
}

/* ------------------------------ End of file ------------------------------ */
