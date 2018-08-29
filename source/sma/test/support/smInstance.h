/**
 *  \file       smInstance.h
 *  \brief      Helper functions and object defines to facilitate the test of 
 *              production code.
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

#ifndef __SMINSTANCE_H__
#define __SMINSTANCE_H__

/* ----------------------------- Include files ----------------------------- */

#include "rkh.h"

/* ---------------------- External C language linkage ---------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
typedef struct PublicSingle PublicSingle;
struct PublicSingle
{
    RKH_SMA_T ao;
    int foo;
};

typedef struct Opaque Opaque;

typedef struct PublicStateMachine PublicStateMachine;
struct PublicStateMachine
{
    RKH_SM_T sm;
    int foo;
};

typedef struct PublicComposite PublicComposite;
struct PublicComposite
{
    RKH_SMA_T ao;
    int foo;
    RKH_SM_T itsReactivePart;
};

typedef struct PublicCompositeA PublicCompositeA;
struct PublicCompositeA
{
    RKH_SMA_T ao;
    int foo;
    PublicStateMachine itsReactivePart;
};

/* -------------------------- External variables --------------------------- */
RKH_SMA_DCLR(single);
RKH_SMA_DCLR_TYPE(PublicSingle, publicSingle);
RKH_SMA_DCLR_TYPE(Opaque, opaque);
RKH_SMA_DCLR_TYPE(PublicSingle, single0);
RKH_ARRAY_SMA_DCLR_TYPE(PublicSingle, arrayOfSingles, 4);
RKH_SM_DCLR(stateMachine);
RKH_SM_DCLR_TYPE(PublicStateMachine, publicStateMachine);

RKH_SMA_DCLR(composite);
RKH_SM_DCLR(region);

RKH_SMA_DCLR_TYPE(PublicComposite, publicComposite);
RKH_SM_DCLR(publicRegion);

RKH_SMA_DCLR_TYPE(PublicCompositeA, publicCompositeA);
RKH_SM_DCLR(publicRegionA);

/* -------------------------- Function prototypes -------------------------- */
void Single_ctor(int foo);
int Single_getFoo(void);

void PublicSingle_ctor(int foo);

void Opaque_ctor(Opaque *const me, int foo);
int Opaque_getFoo(Opaque *const me);

void MultiplePublicSingle_ctor(PublicSingle *const me, int foo);

void Composite_ctor(int foo);
int Composite_getFoo(void);
RKH_SM_T *Composite_getItsReactivePart(void);

void PublicComposite_ctor(PublicComposite *const me, int foo);

void PublicCompositeA_ctor(PublicCompositeA *const me, int actObjFoo, 
                           int smFoo);

PublicSingle *PublicSingle_dynCtor(int foo);
void PublicSingle_dynDtor(PublicSingle *const me);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */

#endif

/* ------------------------------ End of file ------------------------------ */
