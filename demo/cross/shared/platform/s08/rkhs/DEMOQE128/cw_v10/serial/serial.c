/*
 *	serial.c
 */

#include "rkh.h"
#include "serial.h"
#include "sertable.h"
#include <string.h>


static
const COM_T *
verify_serial_channel( HUInt channel )
{
	return &serial_default[ channel ];
}


void
serial_init( HUInt channel )
{
	const COM_T *psd;

	psd = verify_serial_channel( channel );
	(*psd->init)( &psd->comsets );
}


void
put_nchar( HUInt channel, const unsigned char *p, rkhui16_t qty )
{
	const COM_T *psd;

	psd = verify_serial_channel( channel );

	for( ; qty; qty--, ++p )
	{
		(*psd->send_char)( *p );
	}
}


void
put_string( HUInt channel, const char *p )
{
	put_nchar( channel, (unsigned char*)p, (rkhui16_t)strlen( p ) );
}


void
put_char( HUInt channel, const unsigned char c )
{
	const COM_T *psd;

	psd = verify_serial_channel( channel );
	(*psd->send_char)( c );
}


