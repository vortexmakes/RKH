/*
 * stack.c
 */

#include "enaint.h"
#include "stack.h"
#include "ioports.h"
#include "cop.h"
#include "reset.h"

#ifdef TEST_SP

#define MIN_ABSOLUTE_STACK	0x0E5D	// Must be adjusted to linker map 
									// see mem_status address as aproximation
static unsigned short stack;

void
test_sp( void )
{

	sem_disable();

	asm{
		PSHH
		PSHX
		TSX
		STHX  stack;
		PULX
		PULH
	}

	if( stack <= MIN_ABSOLUTE_STACK )
		reset_now();

	sem_enable();
}
#endif
