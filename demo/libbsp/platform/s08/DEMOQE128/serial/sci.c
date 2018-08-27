/*
 *	sci.c
 *	Routines handle SCI service
 *
 *	Programmer: Darío S. Baliña.
 *	Date : 29/05/06.
 */

#include "derivative.h"
#include "gpio.h"
#include "sci.h"
#include "serdefs.h"
#include "scibrtbl.h"


/*	SCIS1 bits definition 	*/

#define OVRN		0x08
#define NF			0x04
#define FE			0x02
#define PERR		0x01


void 
com1_init( COMSET_T const *p )
{
	rui16_t *pbaud;

	while( !SCI1S1_TC || !SCI1S1_TDRE )
		;

	pbaud = (rui16_t*)&SCI1BDH;

	SCI1C2_RIE = 0;
	SCI1C2_TE = 0;								/* disable transmit channel */
	SCI1C2_RE = 0;								/* and receive channel */

	SCI1C1 = 0;									/* set bits to default */

	SCI1C1_PE = p->parity != NO_PAR;			/* parity enable */
	SCI1C1_PT = p->parity == ODD_PAR;			/* set parity type */

	if( p->parity != NO_PAR && p->bits == BIT8 )
		SCI1C1_M = 1;			/* 9-bits */
	else
		SCI1C1_M = 0;			/* 8-bits */

	*pbaud = sci_br_tbl[ p->baud ];

	SCI1C2_TE = 1;
	SCI1C2_RE = 1;
	SCI1C2_RIE = 1;

	set_comen( PIN_HIGH );
}


void 
com2_init( COMSET_T const *p )
{
	rui16_t *pbaud;

	while( !SCI2S1_TC || !SCI2S1_TDRE )
		;
  
	pbaud = (rui16_t*)&SCI2BDH;
	
	SCI2C2_RIE = 0;
	SCI2C2_TE = 0;
	SCI2C2_RE = 0;

	SCI2C1 = 0;		/* set bits to default */

	SCI2C1_PE = p->parity == NO_PAR ? 0 : 1;	/* parity enable */
	SCI2C1_PT = p->parity == EVEN_PAR ? 0 : 1;	/* set parity type */

	if( p->parity != NO_PAR && p->bits == BIT8 )
		SCI2C1_M = 1;			/* 9-bits */
	else
		SCI2C1_M = 0;

	*pbaud = sci_br_tbl[ p->baud ];

	SCI2C2_TE = 1;
	SCI2C2_RE = 1;
	SCI2C2_RIE = 1;
}


void
com1_sendchar( unsigned char c )
{
  	while( !SCI1S1_TDRE )
  		;

	SCI1D = c;

	while( !SCI1S1_TC )
		;
}


void
com2_sendchar( unsigned char c )
{
  	while( !SCI2S1_TDRE )
		;

	SCI2D = c;

	while( !SCI2S1_TC )
		;
}


void
interrupt VectorNumber_Vsci1rx
com1_rcv_isr( void )
{
	volatile unsigned char data;

	if( SCI1S1 & (OVRN|PERR|FE|NF))
	{
		data = SCI1D;
		return;
	}

  	data = SCI1D;	
}


void
interrupt VectorNumber_Vsci2rx
com2_rcv_isr( void )
{
	volatile unsigned char data;
	
	data = SCI2S1;
	data = SCI2C3;
	data = SCI2D;
}


#if SCI_ENADIS_INTERRUPT

void 
disable_rcv_interrupt( MUInt ch )
{
	if( ch == COM2 )
	{
		SCI2C2_RIE = 0;
		SCI2C2_RE = 0;
	}
	else
	{
		SCI1C2_RIE = 0;
		SCI1C2_RE = 0;
	}
}


void 
enable_rcv_interrupt( MUInt ch )
{
	volatile MUInt data;

	if( ch == COM2 )
	{
		while( !SCI2S1_TC || !SCI2S1_TDRE )
			;
		data = SCI2D;
		SCI2C2_RE = 1;
		SCI2C2_RIE = 1;
	}
	else
	{
		while( !SCI1S1_TC || !SCI1S1_TDRE )
			;
		data = SCI1D;
		SCI1C2_RE = 1;
		SCI1C2_RIE = 1;
	}
}

#endif
