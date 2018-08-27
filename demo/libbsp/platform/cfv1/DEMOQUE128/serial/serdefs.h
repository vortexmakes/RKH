/*
 * 	serdefs.h
 */

#ifndef __SERDEFS_H__
#define __SERDEFS_H__

#include "rkh.h"

enum
{
	COM1, COM2,
	NUM_CHANNELS
};

enum
{
	B300, B600, B1200, B2400, B4800, B9600, B19200,
	B38400, B57600,
	NUM_BAUD
};

enum
{
	BIT8, BIT7,
	NUM_BITS
};

enum
{
	NO_PAR, EVEN_PAR, ODD_PAR, HIGH_PAR, LOW_PAR,
	NUM_PAR
};

enum
{
	ONE_BIT_STOP, TWO_BIT_STOP
};

typedef struct
{
	unsigned baud:4;
	unsigned bits:1;
	unsigned parity:3;
} COMSET_T;

typedef struct
{
	COMSET_T comsets;
	void (*init)( COMSET_T const *p );
	void (*send_char)( unsigned char c );
} COM_T;

#endif
