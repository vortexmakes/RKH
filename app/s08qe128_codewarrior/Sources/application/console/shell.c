/*
 * 	shell.c
 */


#include "mytypes.h"
#include "rksys.h"
#include "rkutils.h"
#include "evtdata.h"
#include "qdata.h"
#include "tdata.h"
#include "shell.h"
#include "console.h"
#include "serial.h"

#include <stdlib.h>


static void shell_init( void );
static void shell_task( SCHDR_MSG_T *pmsg );


CREATE_QUEUE_ARRAY( shell_queue, SHELL_QUEUE_BYTE_SIZE );
static CREATE_QUEUE_LIST( shell ) = { SHELL_QUEUE, END_QUEUE_LIST };
CREATE_TCB(	shell, shell_task, task_set_que_list( shell), 
				shell_init, 1, 2, SHELL, "shell", NULL );


static
void 
shell_init( void )
{
	init_command_shell();
}


static
void
shell_task( SCHDR_MSG_T *pmsg )
{
	char c;
	
	if( get_char( COM2, &c ) != 0  )
		return;

	rkwatchdog();
	if( command_shell( c ) == CON_ABORT_SHELL )
		task_suspend( shell );
}
