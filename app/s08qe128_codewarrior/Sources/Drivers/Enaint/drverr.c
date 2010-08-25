/*
 * 	drverr.c
 * 		Central module to manage the
 * 		driver errors
 */

#include "drverr.h"
#include "reset.h"


/*
 * 	Public functions
 */

void
fatal( char *file, int line, MUInt error )
{
	reset_now();
}

