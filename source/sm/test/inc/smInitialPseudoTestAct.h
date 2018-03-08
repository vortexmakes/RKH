/**
 *  \file       smInitialPseudoTestAct.h
 *  \ingroup    Test
 *
 *  \brief      Production code.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.02.16  LeFr  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __SMINITIALPSEUDOTESTACT_H__
#define __SMINITIALPSEUDOTESTACT_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "smInitialPseudoTest.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* ........................ Declares initial action ........................ */
void smIPT_init(SmInitialPseudoTest *const me, RKH_EVT_T *pe);

/* ........................ Declares effect actions ........................ */
void smIPT_tr1(SmInitialPseudoTest *const me, RKH_EVT_T *pe);
void smIPT_tr2(SmInitialPseudoTest *const me, RKH_EVT_T *pe);
void smIPT_tr3(SmInitialPseudoTest *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
void smIPT_nS0(SmInitialPseudoTest *const me);
void smIPT_nS1(SmInitialPseudoTest *const me);
void smIPT_nS11(SmInitialPseudoTest *const me);
void smIPT_nS12(SmInitialPseudoTest *const me);
void smIPT_nS2(SmInitialPseudoTest *const me);
void smIPT_nS21(SmInitialPseudoTest *const me);
void smIPT_nS211(SmInitialPseudoTest *const me);
void smIPT_nS3(SmInitialPseudoTest *const me);
void smIPT_nS31(SmInitialPseudoTest *const me);
void smIPT_nS32(SmInitialPseudoTest *const me);
void smIPT_nS33(SmInitialPseudoTest *const me);
void smIPT_nS331(SmInitialPseudoTest *const me);
void smIPT_nS4(SmInitialPseudoTest *const me);
void smIPT_nS41(SmInitialPseudoTest *const me);
void smIPT_nS411(SmInitialPseudoTest *const me);
void smIPT_nS5(SmInitialPseudoTest *const me);
void smIPT_nS51(SmInitialPseudoTest *const me);
void smIPT_nS511(SmInitialPseudoTest *const me);
void smIPT_nS512(SmInitialPseudoTest *const me);
void smIPT_nS5121(SmInitialPseudoTest *const me);
void smIPT_nS52(SmInitialPseudoTest *const me);
void smIPT_nS6(SmInitialPseudoTest *const me);
void smIPT_nS61(SmInitialPseudoTest *const me);
void smIPT_nS611(SmInitialPseudoTest *const me);
void smIPT_nS612(SmInitialPseudoTest *const me);
void smIPT_nS6121(SmInitialPseudoTest *const me);
void smIPT_nS62(SmInitialPseudoTest *const me);
void smI0_nS0(SmInitialPseudoTest *const me);
void smI1_nS0(SmInitialPseudoTest *const me);
void smI1_nS01(SmInitialPseudoTest *const me);
void smI2_nS0(SmInitialPseudoTest *const me);
void smI2_nS01(SmInitialPseudoTest *const me);
void smI3_nS0(SmInitialPseudoTest *const me);
void smI3_nS01(SmInitialPseudoTest *const me);
void smI3_nS011(SmInitialPseudoTest *const me);
void smI4_nS0(SmInitialPseudoTest *const me);
void smI4_nS1(SmInitialPseudoTest *const me);
void smI4_nS11(SmInitialPseudoTest *const me);
void smI5_nS0(SmInitialPseudoTest *const me);
void smI5_nS1(SmInitialPseudoTest *const me);
void smI5_nS11(SmInitialPseudoTest *const me);

/* ......................... Declares exit actions ......................... */
void smIPT_xS0(SmInitialPseudoTest *const me);
void smIPT_xS1(SmInitialPseudoTest *const me);
void smIPT_xS11(SmInitialPseudoTest *const me);
void smIPT_xS12(SmInitialPseudoTest *const me);
void smIPT_xS2(SmInitialPseudoTest *const me);
void smIPT_xS21(SmInitialPseudoTest *const me);
void smIPT_xS211(SmInitialPseudoTest *const me);
void smIPT_xS3(SmInitialPseudoTest *const me);
void smIPT_xS31(SmInitialPseudoTest *const me);
void smIPT_xS32(SmInitialPseudoTest *const me);
void smIPT_xS33(SmInitialPseudoTest *const me);
void smIPT_xS331(SmInitialPseudoTest *const me);
void smIPT_xS4(SmInitialPseudoTest *const me);
void smIPT_xS41(SmInitialPseudoTest *const me);
void smIPT_xS411(SmInitialPseudoTest *const me);
void smIPT_xS5(SmInitialPseudoTest *const me);
void smIPT_xS51(SmInitialPseudoTest *const me);
void smIPT_xS511(SmInitialPseudoTest *const me);
void smIPT_xS512(SmInitialPseudoTest *const me);
void smIPT_xS5121(SmInitialPseudoTest *const me);
void smIPT_xS52(SmInitialPseudoTest *const me);
void smIPT_xS6(SmInitialPseudoTest *const me);
void smIPT_xS61(SmInitialPseudoTest *const me);
void smIPT_xS611(SmInitialPseudoTest *const me);
void smIPT_xS612(SmInitialPseudoTest *const me);
void smIPT_xS6121(SmInitialPseudoTest *const me);
void smIPT_xS62(SmInitialPseudoTest *const me);

/* ............................ Declares guards ............................ */
rbool_t smIPT_isC1(const RKH_SM_T *sma, RKH_EVT_T *pe);
rbool_t smIPT_isC2(const RKH_SM_T *sma, RKH_EVT_T *pe);
rbool_t smIPT_isC3(const RKH_SM_T *sma, RKH_EVT_T *pe);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
