/**
 *  \file       smPseudoTestAct.h
 *  \ingroup    Test
 *
 *  \brief      Production code.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */

#ifndef __SMPSEUDOTESTACT_H__
#define __SMPSEUDOTESTACT_H__

/* ----------------------------- Include files ----------------------------- */

#include "rkh.h"
#include "smPseudoTest.h"

/* ---------------------- External C language linkage ---------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */

/* ============================ Initial action ============================= */
/* ============================ Effect actions ============================= */
void smPT_trS2History(SmPseudoTest *const me, RKH_EVT_T *pe);

/* ============================= Entry actions ============================= */
/* ============================= Exit actions ============================== */
/* ================================ Guards ================================= */
rbool_t smPT_trueGuard(SmPseudoTest *const me, RKH_EVT_T *pe);

/* -------------------- External C language linkage end -------------------- */

#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */

#endif

/* ------------------------------ End of file ------------------------------ */
