/**
 *  \file       smPseudoTest.h
 *  \ingroup    Test
 *
 *  \brief      State machine to facilitate the test of production code.
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
/* --------------------------------- Module -------------------------------- */

#ifndef __SMPSEUDOTEST_H__
#define __SMPSEUDOTEST_H__

/* ----------------------------- Include files ----------------------------- */

#include "rkh.h"

/* ---------------------- External C language linkage ---------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */

/* Signals */
enum
{
    A, B, C, D, E, F, G, H, I, TERMINATE,
    SMTEST_NUM_EVENTS
};

/* Declare HSM */
RKH_SMA_DCLR(smPseudoTest);

/* Declare states and pseudostates */
RKH_DCLR_COMP_STATE smPT_s1, smPT_s12, smPT_s2;
RKH_DCLR_BASIC_STATE smPT_waiting, smPT_s0, smPT_s11, 
                     smPT_s121, smPT_s122, smPT_s21, smPT_s22;
RKH_DCLR_SHIST_STATE smPT_s1Hist;
RKH_DCLR_DHIST_STATE smPT_s12Hist;
RKH_DCLR_SHIST_STATE smPT_s2Hist;

/* ------------------------------- Data types ------------------------------ */

typedef struct SmPseudoTest SmPseudoTest;
struct SmPseudoTest      /* SMA derived from RKH_SMA_T structure */
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
