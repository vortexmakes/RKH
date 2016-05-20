/**
 *  \file       bkliny.h
 *  \brief      Example application.
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
#ifndef __BLINKY_H__
#define __BLINKY_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "blinky.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
#define LED_OFF_TIME            RKH_TIME_SEC(2)
#define LED_ON_TIME             RKH_TIME_SEC(2)

/* -------------------------------- Constants ------------------------------ */
/* ================================ Signals ================================ */
enum
{
	TIMEOUT,		/* 'blktim' timeout */
	TERMINATE,		/* press the key escape on the keyboard */
	BLINKY_NUM_EVENTS
};

/* ======================== Declares active object ========================= */
RKH_SMA_DCLR(blinky);

/* =================== Declares states and pseudostates ==================== */
RKH_DCLR_BASIC_STATE ledOff, ledOn;

/* ------------------------------- Data types ------------------------------ */
typedef struct Blinky Blinky;

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* ============================ Initial action ============================= */
void blinky_init(Blinky *const me);

/* ============================ Effect actions ============================= */
void blinky_ledOn(Blinky *const me, RKH_EVT_T *pe );
void blinky_ledOff(Blinky *const me, RKH_EVT_T *pe );

/* ============================= Entry actions ============================= */
/* ============================= Exit actions ============================== */
/* ================================ Guards ================================= */

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
