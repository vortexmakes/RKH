/**
 *  \file       smInitialPseudoTest.h
 *  \ingroup    Test
 *
 *  \brief      State machine to facilitate the test of production code.
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
#ifndef __SMINITIALPSEUDOTEST_H__
#define __SMINITIALPSEUDOTEST_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ................................ Signals ................................ */
enum
{
    A, B, C, TERMINATE,
    SMIPT_NUM_EVENTS
};

/* ................................. Events ................................ */
/* ........................ Declares active object ......................... */
RKH_SMA_DCLR(smInitialPseudoTest);

/* ............................ Declares vertex ............................ */
RKH_DCLR_BASIC_STATE smPT_s0, smPT_s11, smPT_s12;
RKH_DCLR_COMP_STATE smPT_s1;
RKH_DCLR_SHIST_STATE smPT_s1Hist;

/* ------------------------------- Data types ------------------------------ */
typedef struct SmInitialPseudoTest SmInitialPseudoTest;
struct SmInitialPseudoTest      /* SMA derived from RKH_SMA_T structure */
{
    RKH_SMA_T sma;
    rui8_t foo;
};

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
