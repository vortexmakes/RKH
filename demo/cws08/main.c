/*
 * main.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rkh.h"
#include "my.h"
#include "myevt.h"


static const RKHE_T event_list[] = { ONE, ONE, RKH_ANY };
static MYEVT_T mye;

void
main( void )
{
	const RKHE_T *pe;
	
	rkh_init_hsm( my );

	for( pe = event_list; *pe != RKH_ANY; ++pe  )
	{
		rkh_set_static_event( &mye, *pe );
		mye.ts = 0;
		rkh_engine( my, ( RKHEVT_T *)&mye );
	}	
}
