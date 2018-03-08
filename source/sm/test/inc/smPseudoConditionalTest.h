/**
 *  \file       smPseudoConditionalTest.h
 *  \ingroup    Test
 *
 *  \brief      State machine to facilitate the test of production code.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.06.05  LeFr  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __SMPSEUDOCONDITIONALTEST_H__
#define __SMPSEUDOCONDITIONALTEST_H__

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
    SMPSEUDOCONDITIONALTEST_NUM_EVENTS
};

/* Declare HSM */
RKH_SMA_DCLR(smPseudoConditionalTest);

/* Declare states and pseudostates */
RKH_DCLR_COMP_STATE smPCT_s1;
RKH_DCLR_BASIC_STATE smPCT_waiting, smPCT_s0, smPCT_s11, smPCT_s12, smPCT_s2;
RKH_DCLR_CHOICE_STATE smPCT_choice1, smPCT_choice2, smPCT_choice3, 
                      smPCT_choice4, smPCT_choice5, smPCT_choice6;

/* ------------------------------- Data types ------------------------------ */
typedef struct SmPseudoConditionalTest SmPseudoConditionalTest;
struct SmPseudoConditionalTest      /* SMA derived from RKH_SMA_T structure */
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
