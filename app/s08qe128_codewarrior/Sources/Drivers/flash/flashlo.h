/*
 * 	flashlo.h
 * 		Lower level routines
 * 		for flash programming
 */

#include "mytypes.h"

void prepare_erase_flash( void *pflash );    
void erase_flash( void *pflash );
void close_erase_flash( void *pflash );
		
void prepare_program_flash( void *pflash );
void program_flash_byte( void *pflash, MUInt byte );
void close_program_flash( void *pflash );

