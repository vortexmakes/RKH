/*
 * swhdl.c
 */

#include "derivative.h"
#include "swhdl.h"

uchar
rawsw1( void )
{
	return PTAD_PTAD2;
}

uchar
rawsw2( void )
{
	return PTAD_PTAD3;
}

uchar
rawsw3( void )
{
	return PTDD_PTDD2;
}

uchar
rawsw4( void )
{
	return PTDD_PTDD3;
}
