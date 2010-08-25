/*
 *	serial.c
 */

#include "mytypes.h"
#include "watchdog.h"
#include "serial.h"
#include "sertable.h"
#include "ioports.h"
#include <string.h>


static
const COM_T *
verify_serial_channel( MUInt channel )
{
	return &serial_default[ channel ];
}


void
serial_init( MUInt channel )
{
	const COM_T *psd;

	psd = verify_serial_channel( channel );
	(*psd->init)( &psd->comsets );
}


void
put_nchar( MUInt channel, const uchar *p, ushort qty )
{
	const COM_T *psd;

	psd = verify_serial_channel( channel );

	for( ; qty; qty--, ++p )
	{
		(*psd->send_char)( *p );
		kick_watchdog();
	}
}


void
put_string( MUInt channel, const char *p )
{
	put_nchar( channel, (uchar*)p, (MUInt)strlen( p ) );
}


void
put_char( MUInt channel, const uchar c )
{
	const COM_T *psd;

	psd = verify_serial_channel( channel );
	(*psd->send_char)( c );
}


MUInt
get_char( MUInt channel, char *c )
{
	const COM_T *psd;

	psd = verify_serial_channel( channel );
	return queue_remove( psd->qd, c );
}
