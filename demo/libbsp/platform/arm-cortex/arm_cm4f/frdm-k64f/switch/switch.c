/*
 * switch.c
 *
 * Minimal debouncing switch handler.
 * hardware access.
 *
 */

#include "rkh.h"
#include "switch.h"
#include "swhdl.h"
#include "bsp.h"
#include "shared.h"


static RKH_ROM_STATIC_EVENT( e_pause, PAUSE );
static SWITCH_ST switchs[SWITCHS_NUM] = 
{
	{ 0, rawsw1,	SW_RELEASED },
	{ 0, rawsw2,	SW_RELEASED },
};

void bsp_publish( const RKH_EVT_T *e );

#define SWITCH_EVT(s__, st__)					\
			do {								\
				if((st__) == SW_RELEASED)		\
					return;						\
				if((s__) == SW1_SWITCH)			\
					bsp_publish( &e_pause );	\
			} while(0)

			
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
			SWITCH_EVT( s, p->debsw );
		}
		else if( ( p->state == 0x00 ) && (p->debsw != SW_RELEASED) )
		{
			p->debsw = SW_RELEASED;
			SWITCH_EVT( s, p->debsw );
		}
	}

}


MUInt
get_switch_state( MUInt who )
{
	return switchs[who].debsw;
}
