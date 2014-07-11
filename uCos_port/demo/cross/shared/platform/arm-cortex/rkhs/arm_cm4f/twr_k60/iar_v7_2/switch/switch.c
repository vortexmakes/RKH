/*
 * switch.c
 */

#include "mytypes.h"
#include "swhdl.h"
#include "switch.h"
#include "bsp.h"

static SWITCH_ST switchs[SWITCHS_NUM] = 
{
	{ 0, rawsw1,	SW_RELEASED },
	{ 0, rawsw2,	SW_RELEASED },
};

void
switch_tick( void )
{
	SWITCH_ST *p;
	MUInt s;

	for( s = 0, p = switchs; p < &switchs[SWITCHS_NUM]; ++p, ++s ) 
	{
		p->state = (p->state<<1) | !(p->rawsw()); 
		if( (p->state == 0xFF) && (p->debsw != SW_PRESSED) )
		{
			p->debsw = SW_PRESSED;
			bsp_switch_evt( s, SW_PRESSED );
		}
		else if( ( p->state == 0x00 ) && (p->debsw != SW_RELEASED) )
		{
			p->debsw = SW_RELEASED;
			bsp_switch_evt( s, SW_RELEASED);
		}
	}

}

uchar
get_switch_state( uchar who )
{
	return switchs[who].debsw;
}
