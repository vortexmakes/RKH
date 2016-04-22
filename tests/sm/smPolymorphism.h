/**
 *  \file       smPolymorphism.h
 *  \brief      Helper functions and object defines to facilitate the test of 
 *              production code.
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

#ifndef __SMPOLYMORPHISM_H__
#define __SMPOLYMORPHISM_H__

/* ----------------------------- Include files ----------------------------- */

#include "rkh.h"

/* ---------------------- External C language linkage ---------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
typedef struct Multiple Multiple;

typedef struct MultipleVtbl MultipleVtbl;
struct MultipleVtbl
{
    RKHSmaVtbl super;
    void (*toggle)(Multiple *me);
};

/* -------------------------- External variables --------------------------- */
RKH_SMA_DCLR(singleton);
RKH_SMA_DCLR_TYPE(Multiple, multA);
RKH_SMA_DCLR_TYPE(Multiple, multB);

/* -------------------------- Function prototypes -------------------------- */
void Singleton_ctor(int foo);
int Singleton_getFoo(void);
void Multiple_ctor(Multiple *const me, int foobar, RKHPostFifo postFifo);
int Multiple_getFoobar(Multiple *const me);
void Multiple_postFifoA(RKH_SMA_T *me, const RKH_EVT_T *e, 
                        const void *const sender);
void Multiple_postFifoB(RKH_SMA_T *me, const RKH_EVT_T *e, 
                        const void *const sender);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
