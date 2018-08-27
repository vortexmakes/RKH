/*
 *	scibrtbl.c
 */

#include "sci.h"
#include "serdefs.h"

/* 
 * sci_br_tbl:	Maps the Baudrate symbol enum defined in
 * 				in serdefs.h with the constant defined
 * 				in sci.h for seting the uart's MCU.
 */
 
const unsigned short sci_br_tbl[NUM_BAUD] =
{
	UC_B300, UC_B600, UC_B1200, UC_B2400, UC_B4800,
	UC_B9600 , UC_B19200, UC_B38400, UC_B57600
};
