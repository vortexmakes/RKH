/*
 * 	flash.c
 * 		Logical level of flash programming
 */

#include <string.h>
#include <stdio.h>

#include "mytypes.h"

#include "flash.h"
#include "rfile.h"
#include "flashlo.h"
#include "watchdog.h"

#define RETRIES				5
#define EQUAL				0
#define PHYS_BLOCK_SIZE		RF_SIZE_PHY_PAGE

/*
 * 	write_flash:
 * 		Erases and program flash in 'pto'
 * 		with data in 'pfrom'for one block
 * 		At end, verifies contents of flash
 * 		against ram
 * 		Retries RETRIES times
 */

void
flash_write_page( void *pto, const void *pfrom )
{
	const unsigned char *q;
	int count;
	unsigned char *rto;
	MUInt retry;

	for( retry = 0 ; retry < RETRIES ; ++retry )
	{
		rto = pto;
		prepare_erase_flash( pto );

		kick_watchdog();
		erase_flash( pto );
		close_erase_flash( pto );
		
		prepare_program_flash( pto );
		q = (const unsigned char *)pfrom;
		kick_watchdog();

		for( count = 0 ; count < PHYS_BLOCK_SIZE ; ++count, ++rto, ++q )
			program_flash_byte( rto, *q );

		kick_watchdog();
		close_program_flash( pto );
		
		if( memcmp( pto, pfrom, PHYS_BLOCK_SIZE ) == EQUAL )
			return;
	}
}
