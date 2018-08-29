/**
 *  \file       smTestSignals.h
 *  \ingroup    Test
 *
 *  \brief      Signal defintions for sm test state machines.
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

#ifndef __SMTESTSIGNALS_H__
#define __SMTESTSIGNALS_H__

/* ----------------------------- Include files ----------------------------- */
/* ---------------------- External C language linkage ---------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
enum
{
    A, B, C, D, E, F, G, H, I, TERMINATE,
    SMTEST_NUM_EVENTS
};

/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */

#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */

#endif

/* ------------------------------ End of file ------------------------------ */
