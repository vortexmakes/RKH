/**
 *  \file       aotest.h
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

#ifndef __AOTEST_H__
#define __AOTEST_H__

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
    A, B, C, D, E, F, G, H, I,
    TERMINATE,
    AOTEST_NUM_EVENTS
};

/* Declare HSM */
RKH_SMA_DCLR(aotest);

/* Declare states and pseudostates */
RKH_DCLR_COMP_STATE s, s1, s2, s21;
RKH_DCLR_BASIC_STATE s11, s211;

/* ------------------------------- Data types ------------------------------ */

typedef struct aoTest aoTest;
struct aoTest      /* SMA derived from RKH_SMA_T structure */
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
