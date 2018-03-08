/**
 *  \file       smTest.h
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
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */

#ifndef __SMTEST_H__
#define __SMTEST_H__

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
RKH_SMA_DCLR(smTest);

/* Declare states and pseudostates */
RKH_DCLR_COMP_STATE s2, s22, s3, s221, s222, s2221;
RKH_DCLR_BASIC_STATE waiting, s0, s1, s21, s2211, s22211, s31, s4, s5;
RKH_DCLR_FINAL_STATE s2Final;

/* ------------------------------- Data types ------------------------------ */

typedef struct SmTest SmTest;
struct SmTest      /* SMA derived from RKH_SMA_T structure */
{
    RKH_SMA_T sma;  /* base structure */
    rui8_t foo;     /* private member */
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
