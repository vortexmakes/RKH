/*
 * 	main.c
 */
 

#include "initsys.h"
#include "schdr.h"
#include "rksys.h"


#define forever()	for(;;)


void
main( void )
{
	init_system();
	
	forever()
		scheduler();
}
