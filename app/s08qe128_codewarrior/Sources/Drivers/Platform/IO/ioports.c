/*
 *	ioports.c
 *	
 *	Routines for PORTS initialization.
 *
 *	Programmer: Darío S. Baliña.
 *	Date : 26/05/06.
 */

#include "derivative.h"
#include "ioports.h"
#include "sleep.h"

void
ports_init(void)
{
	D_LED0 = 1;
	LED0 = 1;

	D_LED1 = 1;
	LED1 = 1;

	D_LED2 = 1;
	LED2 = 1;

	D_LED3 = 1;
	LED3 = 1;

	D_LED4 = 1;
	LED4 = 1;

	D_LED5 = 1;
	LED5 = 1;

	D_LED6 = 1;
	LED6 = 1;

	D_LED7 = 1;
	LED7 = 1;

	D_SPI_CS = 1;
	SPI_CS = 1;

	D_COM_ENABLE = 1;
	COM_ENABLE = 1;

	D_WIZNET_RST = 1;
	WIZNET_RST = 0;

	D_PSHBUTT0 = 0;
	P_PSHBUTT0 = 1;

	D_PSHBUTT1 = 0;
	P_PSHBUTT1 = 1;

	D_PSHBUTT2 = 0;
	P_PSHBUTT2 = 1;

	D_PSHBUTT3 = 0;
	P_PSHBUTT3 = 1;
}

void
loging_led( void )
{
	LED6 ^= 1;
}
