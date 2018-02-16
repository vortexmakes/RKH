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
void smTest_init(SmTest *const me);

/* ........................ Declares effect actions ........................ */
void smTest_tr1(SmTest *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
void smTest_nS0(SmTest *const me);
void smTest_nS1(SmTest *const me);
void smTest_nS11(SmTest *const me);
void smTest_nS12(SmTest *const me);

/* ......................... Declares exit actions ......................... */
void smTest_xS0(SmTest *const me);
void smTest_xS1(SmTest *const me);
void smTest_xS11(SmTest *const me);
void smTest_xS12(SmTest *const me);

/* ............................ Declares guards ............................ */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
