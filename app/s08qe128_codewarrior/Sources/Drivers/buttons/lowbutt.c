/*
 * 	lowbutt.c
 */


#include "mytypes.h"
#include "ioports.h"
#include "qdata.h"
#include "queue.h"
#include "evtdata.h"
#include "fsmdata.h"
#include "sigdata.h"
#include "eflag.h"


enum
{
	RELEASED, PRESSED, POSSREL, POSSPRE
};


enum
{
	PRESS, RELEASE
};


enum
{
	BUTT0, BUTT1, BUTT2, BUTT3,
	NUM_BUTTS
};


typedef struct butt_t
{
	uchar state;
	uchar bevt;
	void (*pact)( struct butt_t *pb );
} BUTT_T;


static EVT_T evt = { 0,	BUTT, BUTTFSM };
extern EFD_T logef;


static
void
butt_signal( BUTT_T *pb )
{
	queue_insert( SIGNAL_QUEUE, &(pb->bevt) );
}


static
void
butt_queue( BUTT_T *pb )
{
	evt.param = pb->bevt;
	queue_insert( BUTTON_QUEUE, &evt );
}


static
void
butt_eflag( BUTT_T *pb )
{
	eflag_set_flags( logef, pb->bevt, FLAG_SET );
}


static BUTT_T buttons[] = 
{ 
	{ 	RELEASED, 	BUTTON0, 	butt_queue	},
	{ 	RELEASED,	BUTTON1,	butt_queue	},
	{ 	RELEASED,	0x02,		butt_eflag  },
	{ 	RELEASED,	SIG0, 		butt_signal	}
};


static
uchar
get_button_status( uchar bix )
{
	switch( bix )
	{
		case BUTT0:
			return PSHBUTT0;
		case BUTT1:
			return PSHBUTT1;
		case BUTT2:
			return PSHBUTT2;
		case BUTT3:
			return PSHBUTT3;
	};
}


static
void
button_machine( uchar bix, uchar in )
{
	BUTT_T *pbutt;

	pbutt = &buttons[ bix ]; 

	switch( pbutt->state )
	{
		case RELEASED:
			if( in == PRESS )
				pbutt->state = POSSPRE;
			break;
		case PRESSED:
			if( in == RELEASE )
				pbutt->state = POSSREL;
			break;
		case POSSREL:
				pbutt->state = in == RELEASE ? RELEASED : PRESSED;
			break;
		case POSSPRE:
			if( in == PRESS )
			{
				pbutt->state = PRESSED;
				(*pbutt->pact)( pbutt );
			}
			else
				pbutt->state = RELEASED;
			break;
	};
}


void
lowbutt_process( void )
{
	uchar bix;

	for( bix = BUTT0; bix < NUM_BUTTS; ++bix )
		button_machine( bix, get_button_status( bix ) );
}
