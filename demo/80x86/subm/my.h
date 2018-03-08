/**
 *  \file       my.h
 *  \brief      Example application.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.12.06  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __MY_H__
#define __MY_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ................................ Signals ................................ */
typedef enum Signals Signals;
enum Signals
{
    ZERO,       /* press the key '0' on the keyboard */
    ONE,        /* press the key '1' on the keyboard */
    TWO,        /* press the key '2' on the keyboard */
    THREE,      /* press the key '3' on the keyboard */
    FOUR,       /* press the key '4' on the keyboard */
    FIVE,       /* press the key '5' on the keyboard */
    SIX,        /* press the key '6' on the keyboard */
    TERM        /* press the key escape on the keyboard */
};

/* ................................. Events ................................ */
typedef struct
{
    RKH_EVT_T event;
    rui16_t ts;
} MyEvt;

/* ........................ Declares active object ......................... */
RKH_SMA_DCLR(my);

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
