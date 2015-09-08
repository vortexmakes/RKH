/*
 * swhdl.c
 */

#include "gpio.h"
#include "swhdl.h"

MUInt
rawsw1( void )
{
	return get_gpio(SW1);
}

MUInt
rawsw2( void )
{
	return get_gpio(SW2);
}
