/*
 * 	drverr.h
 * 		Central module to manage the
 * 		driver errors
 */

#include "mytypes.h"

/*
 * 	Error codes
 */


enum
{
	ERR_OK,
	INT_STK_OFLOW, ENA_WOUT_DISA,
	BAD_MAJOR, BAD_MINORS, BAD_CODE,
	BAD_CHANNEL,
	NVFLASH_PART_OVER,
	NVFLASH_PAR_OVFLOW,
	FLASH_BAD_WRITE,
	NUM_FATAL_ERRORS
};

/*
 * 	Macros
 */

#define fatal_driver(x)	fatal( __FILE__, __LINE__, (x) )

/*
 * 	Public functions
 */

void fatal( char *file, int line, MUInt error );
