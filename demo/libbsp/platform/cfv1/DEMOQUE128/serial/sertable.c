/*
 * 	sertable.c
 */

#include "rkh.h"

#include "sertable.h"
#include "serdefs.h"
#include "slog.h"


const COM_T serial_default[ NUM_CHANNELS ] =
{
	{ { B57600, BIT8, NO_PAR }, com1_init, com1_sendchar },
	{ {	B57600,	BIT8, NO_PAR }, com2_init, com2_sendchar }
};
