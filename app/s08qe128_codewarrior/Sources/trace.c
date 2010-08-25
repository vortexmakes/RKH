/*
 * 	trace.c
 */


#include "mytypes.h"
#include "rksys.h"
#include "ffdata.h"
#include "ffile.h"
#include "rkutils.h"


#if RKSYS_TRACE


#include "trace.h"


typedef struct
{
	unsigned enable:1;
	unsigned print:1;
	unsigned log:1;
	unsigned res:5;
} TRSET_T;


static TRACE_EVENT_T trace_stream[ NUM_OF_TRACES ];
static TRACE_EVENT_T *trace_stream_in, *trace_stream_out;
static ushort trace_count;

static TRSET_T tracing[ NUM_TRACE_TYPE ];


static
TRSET_T *
trace_get_type( uchar trtype )
{
	return &tracing[ trtype ];
}


static
uchar
is_trace_enabled( uchar evt )
{
	TRSET_T *p;

	p = trace_get_type( evt >> 6 );

	return p->enable;
}


static
uchar
insert_trace_to_stream( TRACE_EVENT_T *p )
{
	enter_critical();

	*trace_stream_in = *p;

	if( ++trace_stream_in >= trace_stream + NUM_OF_TRACES )
		trace_stream_in = trace_stream;

	++trace_count;
	exit_critical();

	return TRACE_STREAM_OK;
}


static
uchar
remove_trace_from_stream( TRACE_EVENT_T *p )
{
	if( trace_count == 0 )
		return TRACE_STREAM_EMPTY;

	enter_critical();
	*p = *trace_stream_out;

	if( ++trace_stream_out >= trace_stream + NUM_OF_TRACES )
		trace_stream_out = trace_stream;

	--trace_count;
	exit_critical();

	return TRACE_STREAM_OK;
}


void
trace_init( void )
{
	enter_critical();
	trace_stream_in = trace_stream_out = trace_stream;
	trace_count = 0;
	exit_critical();
}


void
trace_config( uchar trtype, uchar log, uchar print )
{
	TRSET_T *p;

	p = trace_get_type( trtype );

	enter_critical();
	p->log = log;
	p->print = print;
	exit_critical();
}


void 
trace_start_stop( uchar trtype, uchar opt )
{
	TRSET_T *p;

	p = trace_get_type( trtype );

	enter_critical();
	p->enable = opt;
	exit_critical();
}


void 
trace_event0( uchar event, uchar d0, uchar d1, uchar d2 )
{
	TRACE_EVENT_T te;

	if( is_trace_enabled( event ) == TRACE_STOP )
		return;

	te.event = event;
	te.ds.ds0.d0 = d0;
	te.ds.ds0.d1 = d1;
	te.d2 = d2;
	rktrace_set_ts( &te.ts );

	insert_trace_to_stream( &te );
}


void 
trace_event1( uchar event, ushort d01, uchar d2 )
{
	TRACE_EVENT_T te;

	if( is_trace_enabled( event ) == TRACE_STOP )
		return;

	te.event = event;
	te.ds.d01 = d01;
	te.d2 = d2;
	rktrace_set_ts( &te.ts );

	insert_trace_to_stream( &te );
}


uchar
trace_getnext_event( TRACE_EVENT_T *p )
{
	return remove_trace_from_stream( p );
}


ushort
trace_get_status( void )
{
	return trace_count;
}


void
trace_flush( void )
{
	TRACE_EVENT_T te;
	TRSET_T *p;

	while( trace_count != 0 )
	{
		trace_getnext_event( &te );
		p = trace_get_type( te.event >> 6 );
		rkwatchdog();
		
		if( p->print == TRACE_PRINT )
		#if RKSYS_TRACE_PRINT == 1
		{
			#if RKSYS_TRACE_TS == 1
			dprint(( COM1, "te = \t%X\t%d\t%d\t%d - %d/%d/20%02d %d:%d:%d\n", 
						te.event, te.ds.ds0.d0, te.ds.ds0.d1, te.d2,
							te.ts.tm_mday, te.ts.tm_mon, te.ts.tm_year,
								te.ts.tm_hour, te.ts.tm_min, te.ts.tm_sec ));
			#else
			dprint(( COM1, "te = \t%X\t%d\t%d\t%d\n", 
						te.event, te.ds.ds0.d0, te.ds.ds0.d1, te.d2 ));
			#endif
		}
		#endif

		if( p->log == TRACE_LOG )
			ffile_queue_insert( FFD0, &te );
	}
}


#endif
