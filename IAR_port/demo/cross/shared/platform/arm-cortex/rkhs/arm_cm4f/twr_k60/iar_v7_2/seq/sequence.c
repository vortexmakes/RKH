/*
 * 	sequence.c
 */

#include <stdio.h>
#include <string.h>

#include "mytypes.h"

#include "sequence.h"
#include "seqchbak.h"
#include "seqlog.h"
#include "seqtbl.h"
#include "seqdefs.h"



/*
 * 	Defines
 */

#define NOT_USED	-1

/*
 * 	Type definitions for parser
 */

typedef struct
{
	MUInt next_state;
	void (*paction)( const MAJOR_T *, SEQ_VT * );
} COND_STATE;

typedef struct
{
	MUInt (*pcond)( SEQ_T * );
	COND_STATE conds_actions[ 4 ];
} STATE;

/*
 * 	Predefinition of action functions
 */

static	void
			load_seq	( const MAJOR_T *, SEQ_VT * ),
			load_sil	( const MAJOR_T *, SEQ_VT * ),
			kill_chn	( const MAJOR_T *, SEQ_VT * ),
			load_rest	( const MAJOR_T *, SEQ_VT * ),
			load_next	( const MAJOR_T *, SEQ_VT * )
;

/*
 * 	Predefinition of test functions
 */

static	MUInt
			tst_sil( SEQ_T * ),
			tst_new( SEQ_T * )
;

/*
 * 	States enumeration
 */

enum
{
	SEQ_RESET, IN_SEQ, IN_SILENCE, IN_PERIOD,
	NUM_STATES
};

/*
 * 	State transition table
 *
 * 	Each test function returns 0, 1, 2 or 3, selecting
 * 	which transition and which action will be selected.
 * 	If pointer to test function is NULL, all selections
 * 	are the same
 */

static const STATE states[] =
{
	{ NULL,											/*	SEQ_RESET	*/
		{
			{ IN_SEQ, 		load_seq	},
		   	{ IN_SEQ,		load_seq 	},
		   	{ IN_SEQ,		load_seq 	},
		   	{ IN_SEQ,		load_seq 	}
		}
	},
	{ tst_sil, 										/*	IN_SEQ		*/
		{
			{ IN_SILENCE,	load_sil	},			/*	toff != 0	*/
		   	{ SEQ_RESET,	kill_chn 	},			/*	is 1shot?	*/
			{ IN_SEQ,		load_seq	},			/*	num != 0	*/
			{ IN_SEQ,		load_next	}			/*	else		*/
	   	}
	},
	{ tst_new,										/*	IN_SILENCE	*/
		{
			{ IN_SEQ,		load_seq	},			/*	--num != 0	*/
			{ SEQ_RESET,	kill_chn 	},			/*	is 1shot?	*/
			{ IN_SEQ,		load_next	},			/*	period <= 0	*/
			{ IN_PERIOD,	load_rest	}			/*	else		*/
	   	}
	},
	{ NULL,											/*	IN_PERIOD	*/
		{
			{ IN_SEQ,		load_next	},
			{ IN_SEQ,		load_next	},
			{ IN_SEQ,		load_next	},
			{ IN_SEQ,		load_next	}
		}
	}
};


/*
 * 	Static variables
 */

static SEQ_VT	sequence_channels[ NUM_SEQ_CHANNELS ];

/*
 * 	Parser action functions
 */

static
void
load_seq( const MAJOR_T *pmajor, SEQ_VT *pwork )
{
	pwork->count_time = pwork->seq_t.ton;
	(*pmajor->phard)( pwork->minor, pwork->seq_t.arg0 & ~UNIQ, pwork->seq_t.arg1 );
	pwork->running = 1;
}

static
void
load_sil( const MAJOR_T *pmajor, SEQ_VT *pwork )
{
	pwork->count_time = pwork->seq_t.toff;
	(*pmajor->phard)( pwork->minor, NO_ARG, NO_ARG );
}

static
void
kill_chn( const MAJOR_T *pmajor, SEQ_VT *pwork )
{
	(*pmajor->phard)( pwork->minor, NO_ARG, NO_ARG );
	pwork->running = 0;
	pwork->code = NOT_USED;
}


static
void
load_rest( const MAJOR_T *pmajor, SEQ_VT *pwork )
{
	(*pmajor->phard)( pwork->minor, NO_ARG, NO_ARG );
	pwork->count_time = pwork->seq_t.period;
}

static
void
load_next( const MAJOR_T *pmajor, SEQ_VT *pwork )
{
	pwork->seq_t = pmajor->pseq_t[ pwork->seq_t.index ];	/*	Transfer data from table to RAM	*/
	pwork->running = 0;
	pwork->count_time = pwork->seq_t.ton;
	(*pmajor->phard)( pwork->minor, pwork->seq_t.arg0 & ~UNIQ, pwork->seq_t.arg1 );	
	pwork->running = 1;
}

/*
 * 	Test functions
 * 		Return condition <0-3>.
 */

static
MUInt
tst_sil( SEQ_T *pimage )
{
	return pimage->toff ? 0 : ( pimage->index < 0 ? 1 : ( pimage->num_pulse ? 2 : 3 ) );
}

static
MUInt
tst_new( SEQ_T *pimage )
{
	return pimage->num_pulse && --pimage->num_pulse ? 0 : ( pimage->index < 0 ? 1 : ( pimage->period <= 0 ? 2 : 3 ) );
}

/*
 * 	parse function
 */

static
void
parse( const MAJOR_T *pmajor, SEQ_VT *pwork )
{
	const STATE *p;
	const COND_STATE *q;
	
	p = &states[ pwork->state ];
	q = &p->conds_actions[ p->pcond == NULL ? 0 : (*p->pcond)( &pwork->seq_t ) ];
	pwork->state = q->next_state;
	if( q->paction != NULL )
		(*q->paction)( pmajor, pwork );
}


/*
 * 	Functions to install and destroy sequences
 */


/*
 * 	is_continuous_sequence:
 * 		Determines if sequence for 'code' in
 * 		'major' is continuous or one-shot
 */

static
MInt
is_continuous_sequence( MUInt major, MUInt code )
{
	return ( majors_t[ major ].pseq_t[ code ].arg0 & UNIQ ) == 0;
}	
	

static
unsigned
kill_devices( SEQ_VT *p, unsigned minor )
{
	unsigned to_switch_off;
	
	if( ( to_switch_off = ( p->minor & minor ) ) != 0 )				/* 	some to shut off ?	*/
	{
		minor &= ~p->minor;			/*	Devices that remains to shut off					*/
		( *majors_t[ p->major ].phard )( to_switch_off, NO_ARG, NO_ARG );	/* shut it off!	*/
		p->minor &= ~to_switch_off;	/*	Set in slot which devices are still running			*/
		if( p->minor == 0 )			/*	Are there devices running with this code ?			*/
		{
			p->running = 0;			/*	Dispose slot, free channel							*/
			p->code = NOT_USED;
		}
	}
	return minor;
}

static
void
install_new( MUInt major, unsigned minor, MUInt code )
{
	SEQ_VT *p, *prun;
	unsigned minor_to_off;

	if( minor == 0 )
		return;
	prun = NULL;							/*	to remember running slot							*/
	minor_to_off = minor;					/*	devices to shut off		   							*/

			/*	
			 *	Sweep all channels.
			 *	Kill devices running with different code
			 *	Remember which channel has the same code
			 *	and which channel is free
			 */

	for( p = sequence_channels; p < sequence_channels + NUM_SEQ_CHANNELS ; ++p )
	{
		if( p->code == NOT_USED )			/*	slot free ?											*/
			continue;
		if( p->major != major )				/*	if not same major number, not interested !			*/
			continue;
		if( code != 0 && p->code == code )	/*	Same code executing ?								*/
			prun = p;						/*	Remember which slot has same code					*/
		else if( minor_to_off != 0 )
			minor_to_off = kill_devices( p, minor_to_off );
	}
	if( code == 0 )							/*	If kill code, done !								*/
		return;
	/*
	 * 	Exists an slot with the same code and sequence
	 *	is continuous?
	 *	If true, then add devices !
	 */

	if( prun != NULL && is_continuous_sequence( major, code ) )
	{
		prun->minor |= minor;
		return;
	}

 	/*	
	 *	There is no code or sequence is not continuous.
	 *	If exists a free slot, contruct a new sequence
	 */
	for( p = sequence_channels; p < sequence_channels + NUM_SEQ_CHANNELS ; ++p )
	{
		if( p->code == NOT_USED )			/*	slot free ?											*/
		{
			p->running	= 0;
			p->major	= major;
			p->code		= code;
			p->minor	= minor;
			p->state	= SEQ_RESET;
			p->seq_t	= majors_t[ major ].pseq_t[ code ];
			parse( &majors_t[ major ], p );
			break;
		}
	}
}

/*
 * 	Public functions
 */

/*
 * 	init_seqs:
 * 		To be called after hardware initialization
 * 		but before enabling interrupts
 */

void
init_seqs( void )
{
	SEQ_VT *p;

//	memset( sequence_channels, 0, sizeof( sequence_channels ) ); 
	for( p = sequence_channels; p < sequence_channels + NUM_SEQ_CHANNELS ; ++p )
		p->code = NOT_USED;	
	
}

#if 0
static
MUInt
count_minors( unsigned minor_pattern )
{
	MUInt num;

	for( num = 0 ; minor_pattern > 0 ; minor_pattern >>= 1 )
		if( minor_pattern & 1 )
			++num;
	return num;
}
#endif

/*
 * 	set_sequence:
 * 		This is the sole function
 * 		for generating time sequences
 * 		as in tone, ring or leds.
 *
 * 		Arguments:
 * 			major is an index to
 * 				device type given by
 * 				MAJOR_ENUM.
 * 			minor is a bit pattern of
 * 				the devices that has the same
 * 				sequence (Bit order must be
 * 				coordinated with hardware module).
 * 			code is the sequence code for the
 * 				aforementioned device type.
 * 	
 */

void
set_sequence( MUInt major, unsigned minor, MUInt code )
{
  //const MAJOR_T *pmajor;
  //MUInt minors_num, minors_max, seqs_max;

  //pmajor		= &majors_t[ major ];
  //minors_max	= pmajor->minors_num;
  //minors_num	= count_minors( minor );
  //seqs_max	= pmajor->seqs_num;
  wait_for_semaphore();
  install_new( major, minor, code );
}


#define BASE_INTER	10000
#define HUNDRED_MS	(unsigned int)(100000L/BASE_INTER)

static MUInt waiting_100ms( unsigned short counter );
static MUInt (*pfinter)( unsigned short counter ) = waiting_100ms;
static SEQ_VT *pdi;
static MUInt count, freeze_count;

static
MUInt
sweep_interrupt( unsigned short counter )
{
	if( counter >= NUM_SEQ_CHANNELS )
	{
		pfinter = waiting_100ms;
		return freeze_count = count;
	}
	if( pdi->running )
	{
		--pdi->seq_t.period;
		if( --pdi->count_time == 0 )
			parse( &majors_t[ pdi->major ], pdi);
		++count;
	}
	++pdi;
	return freeze_count;
}

static
MUInt
waiting_100ms( unsigned short counter )
{
	if( counter != 0 )
		return freeze_count;
	pdi = sequence_channels;
	count = 0;
	return (*(pfinter = sweep_interrupt))( counter );
}


/*
 * 	sequence_interrupt:
 * 		Function called from background
 * 		in periods of 2 mseg.
 * 		Sweeps all channels that are assigned and active
 * 		Decrements period and count_time and if
 * 		count_time reaches 0, call parser
 * 		In each interrupt, and begining in the
 * 		100 msec. slot, sweeps only one channel
 */
void
sequence_interrupt( void )
{
	MUInt status;
	static unsigned short interrupt_counter = 1;

        sem = 0;
	status = (*pfinter)( interrupt_counter );
        (void)status;
	if( ++interrupt_counter >= HUNDRED_MS )
		interrupt_counter = 0;
}


