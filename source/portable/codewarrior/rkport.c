/*
 * 	rkport.c
 */


#include "rksys.h"


static unsigned int ccr_sp;
static unsigned char ccr_sp_mem[ RKSYS_MAX_NESTING_CSECT ];


#if RKSYS_CRITICAL_METHOD == 1

void
rkinit_critical( void )
{
	asm ldhx @ccr_sp_mem;
	asm	sthx ccr_sp;
}


void 
rkenter_critical( void )
{
	asm tpa;			/* transfer CCR to A */
	asm sei;			/* disable interrupts */
	asm ldhx ccr_sp;
	asm sta  ,x;		/* save old interrupt status */
	asm	aix	 #1;
	asm	sthx ccr_sp;
}


void 
rkexit_critical( void )
{
	asm ldhx ccr_sp;
	asm	aix	 #-1;
	asm	sthx ccr_sp;
	asm lda  ,x;		/* get old interrupt status */
	asm tap;			/* transfer A to CCR */
}

#endif


#if RKSYS_CRITICAL_METHOD == 2

static unsigned char top;

void
rkinit_critical( void )
{
	asm ldhx @ccr_sp_mem;
	asm	sthx ccr_sp;
	asm clra;
	asm sta  top;
}


void 
rkenter_critical( void )
{
asm
{
	tpa							/* transfer CCR to A */
	sei							/* disable interrupts */
;
	psha
	lda  RKSYS_MAX_NESTING_CSECT
	cmp  top
	pula
	bge  l0						/* is there room? */
;
	ldhx ccr_sp
	sta  ,x
	aix  #1
	sthx ccr_sp
	lda	 top
	inca
	sta  top
	rts
;
l0:	tap
}
}


void 
rkexit_critical( void )
{
asm
{
	lda  top
	tsta
	beq  l0
;
	deca
	sta  top
;
	ldhx ccr_sp
	aix	 #-1
	sthx ccr_sp
	lda  ,x						/* get old interrupt status */	
	tap							/* transfer A to CCR */
	rts
;
l0: rts
}
}

#endif
