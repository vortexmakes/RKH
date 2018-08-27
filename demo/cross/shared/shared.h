/**
 *  \file       shared.h
 *  \brief      Server and client event definitions.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.12.15  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __SHARED_H__
#define __SHARED_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* ................................ Signals ................................ */
typedef enum Signals Signals;
enum Signals
{
    REQ,        /* client request */
    START,      /* use server */
    DONE,       /* release server  */
    TOUT_REQ,   /* timer expired */
    TOUT_USING, /* timer expired */
    PAUSE,      /* press the key 'p' on the keyboard */
    TERM        /* press the key escape on the keyboard */
};

/* ................................. Events ................................ */
typedef struct
{
    RKH_EVT_T e;    /** base structure */
    rui8_t clino;   /** client number (ID) */
} ReqEvt;

typedef struct
{
    RKH_EVT_T e;    /** base structure */
    rui8_t clino;   /** client number (ID) */
} StartEvt;

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
