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
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
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
    A, B, C, D, E, F, TERMINATE,
    SMIPT_NUM_EVENTS
};

/* ................................. Events ................................ */
/* ........................ Declares active object ......................... */
RKH_SMA_DCLR(smInitialPseudoTest);

/* ............................ Declares vertex ............................ */
RKH_DCLR_BASIC_STATE smIPT_s0, smIPT_s11, smIPT_s12, smIPT_s211, smIPT_s31,
                     smIPT_s32, smIPT_s331, smIPT_s411, smIPT_s52, smIPT_s511,
                     smIPT_s611, smIPT_s6121, smIPT_s62, smIPT_s5121;
RKH_DCLR_COMP_STATE smIPT_s1, smIPT_s2, smIPT_s21, smIPT_s3, smIPT_s33,
                    smIPT_s4, smIPT_s41, smIPT_s5, smIPT_s51, smIPT_s6, 
                    smIPT_s61, smIPT_s612, smIPT_s512;
RKH_DCLR_SHIST_STATE smIPT_s1Hist, smIPT_s2Hist, smIPT_s4Hist;
RKH_DCLR_DHIST_STATE smIPT_s3Hist;
RKH_DCLR_CHOICE_STATE smIPT_choice1;
RKH_DCLR_COND_STATE smIPT_junction1;

/* ........................ Declares state machines ........................ */
RKH_SM_DCLR(smInitial0);
RKH_DCLR_BASIC_STATE smI0_s0;

/* ........................ Declares state machines ........................ */
RKH_SM_DCLR(smInitial1);
RKH_DCLR_BASIC_STATE smI1_s01;
RKH_DCLR_COMP_STATE smI1_s0;

/* ........................ Declares state machines ........................ */
RKH_SM_DCLR(smInitial2);
RKH_DCLR_BASIC_STATE smI2_s01;
RKH_DCLR_COMP_STATE smI2_s0;

/* ........................ Declares state machines ........................ */
RKH_SM_DCLR(smInitial3);
RKH_DCLR_BASIC_STATE smI3_s011;
RKH_DCLR_COMP_STATE smI3_s0, smI3_s01;

/* ........................ Declares state machines ........................ */
RKH_SM_DCLR(smInitial4);
RKH_DCLR_BASIC_STATE smI4_s0, smI4_s11;
RKH_DCLR_COMP_STATE smI4_s1;
RKH_DCLR_COND_STATE smI4_junction1;

/* ........................ Declares state machines ........................ */
RKH_SM_DCLR(smInitial5);
RKH_DCLR_BASIC_STATE smI5_s0, smI5_s11;
RKH_DCLR_COMP_STATE smI5_s1;
RKH_DCLR_CHOICE_STATE smI5_branch1;

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
