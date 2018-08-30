/**
 *  \file       smPseudoConditionalTestAct.h
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
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */

#ifndef __SMPSEUDOCONDITIONALTESTACT_H__
#define __SMPSEUDOCONDITIONALTESTACT_H__

/* ----------------------------- Include files ----------------------------- */

#include "rkh.h"
#include "smPseudoConditionalTest.h"

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
void smPCT_tr1(SmPseudoConditionalTest *const me, RKH_EVT_T *pe);
void smPCT_tr2(SmPseudoConditionalTest *const me, RKH_EVT_T *pe);
void smPCT_tr3(SmPseudoConditionalTest *const me, RKH_EVT_T *pe);
void smPCT_tr4(SmPseudoConditionalTest *const me, RKH_EVT_T *pe);
void smPCT_setCondition(SmPseudoConditionalTest *const me, RKH_EVT_T *pe);

/* ============================= Entry actions ============================= */
/* ============================= Exit actions ============================== */
/* ================================ Guards ================================= */
rbool_t smPCT_onEventA(SmPseudoConditionalTest *const me, RKH_EVT_T *pe);
rbool_t smPCT_onEventD(SmPseudoConditionalTest *const me, RKH_EVT_T *pe);
rbool_t smPCT_guardTrue(SmPseudoConditionalTest *const me, RKH_EVT_T *pe);

/* -------------------- External C language linkage end -------------------- */

#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */

#endif

/* ------------------------------ End of file ------------------------------ */
