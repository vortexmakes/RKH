/*
 * 	cmdrksys.c
 */


#include "mytypes.h"
#include "command.h"
#include "conser.h"
#include "task.h"
#include "tdata.h"
#include "rksys.h"
#include <string.h>
#include <stdlib.h>


#define NUM_CON_RKSYS_CMDS			11


typedef struct
{
	char *cn;
	uchar cns;
	uchar (*pcf)( char *pa );
} TCMD_T;


static uchar	ts_cmd( char *pa ),
				tr_cmd( char *pa ),
				tk_cmd( char *pa ),
				ti_cmd( char *pa ),
				tinfo_cmd( char *pa ),
				itr_cmd( char *pa ),
				satr_cmd( char *pa ),
				sotr_cmd( char *pa ),
				gtr_cmd( char *pa ),
				ftr_cmd( char *pa ),
				gstr_cmd( char *pa );


static const TCMD_T tcmds[ NUM_CON_RKSYS_CMDS ] =
{
	{	"ts",		2,		ts_cmd	 	},
	{	"tr",		2,		tr_cmd		},
	{	"tk",		2,		tk_cmd		},
	{	"ti",		2,		ti_cmd		},
	{	"tinfo",	5,		tinfo_cmd	},
	{	"itr",		3,		NULL		},
	{	"satr",		4,		NULL		},
	{	"sotr",		4,		NULL		},
	{	"gtr",		3,		NULL		},
	{	"ftr",		3,		NULL		},
	{	"gstr",		4,		NULL		}
};


static const char *tstates[] =
{
	"BLOCKED", "READY", "SUSPEND", "ZOMBIE"
};


static
MInt
get_task_id( char *p )
{
	MInt tid;

	if( ( tid = (MInt)atoi( p ) ) < RKSYS_TASK_NUM_TASKS )
		return tid;

	conser_puts( "Wrong task id. Use tinfo command.\r\n" );
	return -1;
}


static
MUInt
get_trace_param( char *p )
{
	if( strncmp( p, "s", 1 ) == 0 )
		return 2;
	if( strncmp( p, "u", 1 ) == 0 )
		return 1;

	conser_puts( "Wrong trace parameter. Use trinfo command.\r\n" );
	return -1;
}


static
uchar
ts_cmd( char *pa )
{
	uchar tid;

	if( ( tid = get_task_id( pa ) ) < 0 )
		return 1;
	else
	{
		if( task_suspend( task_identify( tid ) ) )
			conser_printf(( COM2, "Task %d cannot be suspended\r\n", tid ));
		else
			conser_printf(( COM2, "Task %d suspended\r\n", tid ));
	}
	return 0;
}


static
uchar
tr_cmd( char *pa )
{
	uchar tid;

	if( ( tid = get_task_id( pa ) ) < 0 )
		return 1;
	else
	{
		if( task_resume( task_identify( tid ) ) )
			conser_printf(( COM2, "Task %d cannot be resumed\r\n", tid ));
		else
			conser_printf(( COM2, "Task %d resumed\r\n", tid ));
	}
	return 0;
}


static
uchar
tk_cmd( char *pa )
{
	uchar tid;

	if( ( tid = get_task_id( pa ) ) < 0 )
		return 1;
	else
	{
		if( task_kill( task_identify( tid ) ) )
			conser_printf(( COM2, "Task %d cannot be killed\r\n", tid ));
		else
			conser_printf(( COM2, "Task %d killed\r\n", tid ));
	}
	return 0;
}


static
uchar
ti_cmd( char *pa )
{
	TASK_T *pt;
	uchar tid;

	if( ( tid = get_task_id( pa ) ) < 0 )
		return 1;
	else
	{
		pt = task_identify( tid );
		task_init( pt, pt->pftask , RKSYS_TASK_BLOCKED );
		conser_printf(( COM2, "Task %d re-created\r\n", tid ));
	}
	return 0;
}


static
uchar
tinfo_cmd( char *pa )
{
	TASK_T *pt;
	uchar tid;

	conser_printf(( COM2, "\r\nTname\t\tTid\t\tTstate\t\t\r\n" ));

	for( tid = 0; tid < RKSYS_TASK_NUM_TASKS; ++tid )
	{
		pt = task_identify( tid );
		conser_printf(( COM2, "\r\n%s\t\t%d\t\t%s\r\n", 
									pt->pftask->ns, tid, 
									tstates[ pt->task_state ] ));
	}
	return 0;
}


static
uchar
itr_cmd( char *pa )
{
	rktrace_init();
	return 0;
}


static
uchar
satr_cmd( char *pa )
{
#if RKSYS_TRACE == 1
	MUInt param;

	if( ( param = get_trace_param( pa ) ) < 0 )
		return 1;

	trace_start_stop( param, TRACE_START );
#endif
	return 0;
}


static
uchar
sotr_cmd( char *pa )
{
#if RKSYS_TRACE == 1
	MUInt param;

	if( ( param = get_trace_param( pa ) ) < 0 )
		return 1;

	trace_start_stop( param, TRACE_STOP );
#endif
	return 0;
}


static
uchar
gtr_cmd( char *pa )
{
#if RKSYS_TRACE == 1
	TRACE_EVENT_T te;

		if( trace_getnext_event( &te ) == TRACE_STREAM_OK )
			conser_printf(( COM2, "te = \t%d\t%d\t%d\t%d\n", 
													te.event, te.ds.ds0.d0,
													te.ds.ds0.d1, te.d2 ));
#endif
	return 0;
}


static
uchar
ftr_cmd( char *pa )
{
#if RKSYS_TRACE == 1
	TRACE_EVENT_T te;

		while( trace_getnext_event( &te ) == TRACE_STREAM_OK )
		{
			trace_getnext_event( &te );
			conser_printf(( COM2, "te = \t%d\t%d\t%d\t%d\n", 
													te.event, te.ds.ds0.d0,
													te.ds.ds0.d1, te.d2 ));
		}
#endif
	return 0;
}


static
uchar
gstr_cmd( char *pa )
{
#if RKSYS_TRACE == 1
		conser_printf(( COM2, "stored trace events = %i\r\n", 
													trace_get_status() ));
#endif
	return 0;
}


static
uchar
find_exec_rksys_cmd( char *pc, char *pa )
{
	const TCMD_T *p;

	for( p = tcmds; p < tcmds + NUM_CON_RKSYS_CMDS; ++p )
		if( strncmp( pc, p->cn, p->cns ) == 0 )
			return (*p->pcf)( pa );

	return 1;
}


MInt 
do_rksys( const CMD_TABLE *p, MUInt argc, char *argv[] )
{
	if( argc < 2 || find_exec_rksys_cmd( argv[ 1 ], argv[ 2 ] ) )
	{
		conser_printf(( COM2, "Usage: %s\r\n", p->usage ));
		return 1;
	}

	return 0;
}
