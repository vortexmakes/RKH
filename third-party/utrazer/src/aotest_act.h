/**
 *  \file       aotest_act.h
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

#ifndef __AOTEST_ACT_H__
#define __AOTEST_ACT_H__

/* ----------------------------- Include files ----------------------------- */

#include "rkh.h"

/* ---------------------- External C language linkage ---------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */

/* Defines HSM init function */
void aotest_init(aoTest *const me);

/*
 * Defines transition action functions
 */
void foo_set2zero(aoTest *const me, RKH_EVT_T *pe);
void foo_set2one(aoTest *const me, RKH_EVT_T *pe);

/*
 * Defines guards functions
 */
rbool_t foo_isn_zero(aoTest*const me, RKH_EVT_T *pe);
rbool_t foo_is_zero(aoTest *const me, RKH_EVT_T *pe);

/* -------------------- External C language linkage end -------------------- */

#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */

#endif

/* ------------------------------ End of file ------------------------------ */
