/*
 *	serial.c
 */

#include "rkh.h"
#include "serial.h"
#include "sertable.h"
#include <string.h>


static
const COM_T *
verify_serial_channel( ruint channel )
{
	return &serial_default[ channel ];
}


void
serial_init( ruint channel )
{
	const COM_T *psd;

	psd = verify_serial_channel( channel );
	(*psd->init)( &psd->comsets );
}


void
put_nchar( ruint channel, const unsigned char *p, rui16_t qty )
{
	const COM_T *psd;

	psd = verify_serial_channel( channel );

	for( ; qty; qty--, ++p )
	{
		(*psd->send_char)( *p );
	}
}


void
put_string( ruint channel, const char *p )
{
	put_nchar( channel, (unsigned char*)p, (rui16_t)strlen( p ) );
}


void
put_char( ruint channel, const unsigned char c )
{
	const COM_T *psd;

	psd = verify_serial_channel( channel );
	(*psd->send_char)( c );
}


