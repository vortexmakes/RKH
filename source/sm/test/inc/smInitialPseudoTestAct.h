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
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
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
void smIPT_init(SmInitialPseudoTest *const me);

/* ........................ Declares effect actions ........................ */
void smIPT_tr1(SmInitialPseudoTest *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
void smIPT_nS0(SmInitialPseudoTest *const me);
void smIPT_nS1(SmInitialPseudoTest *const me);
void smIPT_nS11(SmInitialPseudoTest *const me);
void smIPT_nS12(SmInitialPseudoTest *const me);
void smIPT_nS2(SmInitialPseudoTest *const me);
void smIPT_nS21(SmInitialPseudoTest *const me);
void smIPT_nS211(SmInitialPseudoTest *const me);

/* ......................... Declares exit actions ......................... */
void smIPT_xS0(SmInitialPseudoTest *const me);
void smIPT_xS1(SmInitialPseudoTest *const me);
void smIPT_xS11(SmInitialPseudoTest *const me);
void smIPT_xS12(SmInitialPseudoTest *const me);
void smIPT_xS2(SmInitialPseudoTest *const me);
void smIPT_xS21(SmInitialPseudoTest *const me);
void smIPT_xS211(SmInitialPseudoTest *const me);

/* ............................ Declares guards ............................ */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
