/*
 *	ioports.c
 *	
 *	Routines for PORTS initialization.
 *
 *	Programmer: Darío S. Baliña.
 *	Date : 26/05/06.
 */

#include "derivative.h"
#include "gpio.h"

void
gpio_init(void)
{
	init_leds();
	init_pshbuts();
	init_comen();
}

