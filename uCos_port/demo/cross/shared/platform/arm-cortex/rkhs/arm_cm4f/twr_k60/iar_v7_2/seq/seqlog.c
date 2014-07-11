/*
 * 	seqlog.c
 * 		Logical implementation of hardware
 * 		routines related to sequences
 * 		Now tones, rings and leds
 */

#include "mytypes.h"
#include "seqlog.h"
#include "genled.h"
#include "gpio.h"

volatile MUInt sem;

void
ctrl_led( MUInt l, MUInt ctrl )
{
	if( ctrl == LED_ON )
	{
		switch( l )
		{
			case 0:
				clr_gpio( LED1 );
				break;

			case 1:
				clr_gpio( LED2 );
				break;
	
			case 2:
				clr_gpio( LED3 );
				break;
	
			case 3:
				clr_gpio( LED4 );
				break;

			default:
				break;
		}
	}
	else
	{
		switch( l )
		{
			case 0:
				set_gpio( LED1 );
				break;

			case 1:
				set_gpio( LED2 );
				break;
	
			case 2:
				set_gpio( LED3 );
				break;
	
			case 3:
				set_gpio( LED4 );
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
