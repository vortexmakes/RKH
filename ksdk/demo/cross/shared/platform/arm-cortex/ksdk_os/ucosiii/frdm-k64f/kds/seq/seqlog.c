/*
 * 	seqlog.c
 * 		Logical implementation of hardware
 * 		routines related to sequences
 * 		Now tones, rings and leds
 */

#include "mytypes.h"
#include "seqlog.h"
#include "genled.h"
#include "board.h"

volatile MUInt sem;

static uint32_t cli_leds[] =
					{
						BOARD_GPIO_LED_RED ,
						BOARD_GPIO_LED_BLUE,
						BOARD_GPIO_LED_GREEN,
					};

void
ctrl_led( MUInt l, MUInt ctrl )
{
	if( ctrl == LED_ON )
	{
		switch( l )
		{
			case 0:
			case 1:
			case 2:
				GPIO_DRV_ClearPinOutput( cli_leds[l] );
			default:
				break;
		}
	}
	else
	{
		switch( l )
		{
			case 0:
			case 1:
			case 2:
				GPIO_DRV_SetPinOutput( cli_leds[l] );
				break;
			default:
				break;
		}
	}				
}

void
set_hard_leds( unsigned short minor, MUInt arga, MUInt argb )
{
		MUInt i;
	
		(void)argb;
       
		for( i = 0; i < NUM_LEDS_CHN; ++i )
		{
			if( ( minor >> i ) & 0x01 )
				ctrl_led( i, arga );
		}
}


void
wait_for_semaphore( void )
{
	for( sem = 1; sem; );
}
