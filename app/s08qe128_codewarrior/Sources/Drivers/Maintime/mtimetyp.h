/*
 * 	mtimetyp.h
 * 		Types for Main Timer
 */

#include "mytypes.h"

typedef struct
{
	unsigned short timer;
	void (* const *ptimeact)( void );
} TIMER_CHAIN;


