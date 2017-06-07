/*
 * 	seqtbl.h
 * 		Tables of sequences
 * 		To be included only in file 'sequence.c'
 * 		Change sequences only in these tables
 */

#ifndef __SEQTBL_H__
#define __SEQTBL_H__

#include "mytypes.h"
#include "sequence.h"
#include "seqdefs.h"

#define ONE_SHOT	-1
#define UNIQ		0x80

typedef struct
{
	unsigned char	arg0;			/* Sequence argument #1: enum					*/
	unsigned char	arg1;			/* Sequence argument #2: enum					*/
	int 			ton;			/* ton in 0,1 s									*/
	int 			toff;			/* toff in 0,1 s								*/
	unsigned char	num_pulse;		/* quantity of pulses							*/
	int 			period;			/* period in 0.1 s - if 0 == one shot			*/
	signed char 	index;			/* Index to following sequence. <0 for one shot	*/
} SEQ_T;

typedef struct
{
	void (*phard)( unsigned short minor, MUInt arg0, MUInt arg1 );	/*	Hardware routine			*/
	const SEQ_T		*pseq_t;							/*	Pointer to sequence table	*/
	unsigned char	minors_num;							/*  Number of minor devices		*/
	unsigned char	seqs_num;							/*	Numer of sequences in major	*/
} MAJOR_T;

/*
 * 	Type definitions for channel
 */

typedef struct
{
	signed	 char	code;
	unsigned char 	major;
	unsigned int	minor;
	unsigned char 	running;
	unsigned char 	state;
	unsigned int	count_time;
	SEQ_T		seq_t;
} SEQ_VT;

extern const MAJOR_T majors_t[ NUM_MAJOR ];

#endif
