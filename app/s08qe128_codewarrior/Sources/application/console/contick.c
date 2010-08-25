/*
 * 	contick.c
 */


#include "mytypes.h"
#include "console.h"


#if CON_CONFIG_CMD_TOUT	

static MUInt tcmd;


MUInt
is_cmd_timeout( void )
{
	return tcmd == 0;
}


void 
set_cmd_timeout( MUInt tout )
{
	tcmd = tout < CON_CONFIG_CMD_TOUT_MIN ? CON_CONFIG_CMD_TOUT_MIN : tout;
}


void 
upgrade_cmd_timer( void )
{
	if( tcmd != 0 )
		--tcmd;
}


#endif
