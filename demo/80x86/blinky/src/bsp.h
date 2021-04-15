/**
 *  \file       bsp.h
 *  \brief      BSP for 80x86 OS Linux Blinky Demo
 */

/* -------------------------- Development history -------------------------- */
/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 *  DaBa  Dario Baliña       dariosb@gmail.com
 */

/* --------------------------------- Module -------------------------------- */
#ifndef __BSP_H__
#define __BSP_H__

/* ----------------------------- Include files ----------------------------- */
#include "bsp_common.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
void bsp_ledOn(void);
void bsp_ledOff(void);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ File footer ------------------------------ */
