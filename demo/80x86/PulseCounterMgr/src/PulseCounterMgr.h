/**
 *  \file       PulseCounterMgr.h
 *  \brief      PulseCounterMgr application. It demonstrates how to implement
 *              a pulseCounterMgr reactive Active Object.
 */

/* -------------------------- Development history -------------------------- */
/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __PULSECOUNTERMGR_H__
#define __PULSECOUNTERMGR_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
#define TIME_PER           RKH_TIME_MS(1000)
#define NUM_PULSE_COUNTERS 4
#define TACTMIN            RKH_TIME_MS(1000)
#define TACTMAX            RKH_TIME_MS(1000)
#define TINACTMAX          RKH_TIME_MS(1000)

/* ........................ Declares active object ......................... */
RKH_SMA_DCLR(pulseCounterMgr);

/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
void PulseCounterMgr_ctor(int baz);
int PulseCounterMgr_getBaz(void);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
