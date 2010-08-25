/*
 * 	sertable.c
 */

#include "mytypes.h"

#include "sertable.h"
#include "serdefs.h"
#include "slog.h"
#include "qdata.h"


const COM_T serial_default[ NUM_CHANNELS ] =
{
	{ { B57600, BIT8, NO_PAR }, com1_init, com1_sendchar, SHELL_QUEUE 	},
	{ {	B57600,	BIT8, NO_PAR }, com2_init, com2_sendchar, SHELL_QUEUE	}
};
