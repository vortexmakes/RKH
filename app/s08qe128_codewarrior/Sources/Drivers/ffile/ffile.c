/*
 * 	ffile.c
 */


#include "mytypes.h"
#include "rfile.h"
#include "ffile.h"


static RACC_T ra;


#define ffile_prepare_access( p, o, ta, pd, pos, q )	\
{														\
	ra.pf = p;											\
	ra.op = o;											\
	ra.tacc = ta;										\
	ra.ptofrom = pd;									\
	ra.currpos = pos;									\
	ra.rqty = q;										\
}


void
ffile_init( void )
{
	rfile_init_directory();
}


FFILE_T *
ffile_get_file_info( FFD_T ffd )
{
	return rfile_get_file( ffd );
}


#if FF_FILE_FORMAT == 1

void
ffile_file_format( FFD_T ffd )
{
	FFILE_T *p;

	p = ffile_get_file_info( ffd );
	p->page_error = 0;
	rfile_file_format( p );
}

#endif


MUInt
ffile_queue_insert( FFD_T ffd, void *preg )
{
	FFILE_T *p;

	p = ffile_get_file_info( ffd );

	if( p->qty >= p->num_regs )
		return FQFILE_FULL;

	ffile_prepare_access( p, WRITE_ACCESS, QFILE_ACCESS, preg, p->in, 1 );
	rfile_access_register( &ra );

	if( ++p->in >= p->num_regs )
		p->in = 0;

	++p->qty;
	rfile_update_directory( p );

	return FQFILE_OK;
}


MUInt
ffile_queue_remove( FFD_T ffd, void *preg )
{
	FFILE_T *p;

	p = ffile_get_file_info( ffd );

	if( p->qty == 0 )
		return FQFILE_EMPTY;

	ffile_prepare_access( p, READ_ACCESS, QFILE_ACCESS, preg, p->out, 1 );
	rfile_access_register( &ra );

	if( ++p->out >= p->num_regs )
		p->out = 0;

	--p->qty;
	rfile_update_directory( p );

	return FQFILE_OK;
}


int
ffile_random_access( FFD_T ffd, uchar op, void *preg, ushort rqty )
{
	FFILE_T *p;
	ushort rregs_in_file, aqty;

	p = ffile_get_file_info( ffd );

	if( p->pos >= p->num_regs )
		return -FRFILE_EOF;

	rregs_in_file = p->num_regs - p->pos;
	aqty = rqty > rregs_in_file ? rregs_in_file : rqty;

	ffile_prepare_access( p, op, RFILE_ACCESS, preg, p->pos, aqty );
	rfile_access_register( &ra );

	p->pos += aqty;

	rfile_update_directory( p );
	return (int)aqty;
}


MUInt
ffile_queue_random_read( FFD_T ffd, uchar dir, void *preg )
{
	FFILE_T *p;

	p = ffile_get_file_info( ffd );

	if( p->pos_qty == 0 )
		return FQFILE_EMPTY;

	ffile_prepare_access( p, READ_ACCESS, RFILE_ACCESS, preg, p->pos, 1 );
	rfile_access_register( &ra );

	if( dir == READ_FORWARD )
	{
		if( ++p->pos >= p->num_regs )
			p->pos = 0;
	}
	else
	{
		if( (short)--p->pos < 0 )
			p->pos = p->num_regs - 1;
	}

	--p->pos_qty;

	return FQFILE_OK;
}


#if FF_TELL	== 1

ushort
ffile_tell( FFD_T ffd )
{
	FFILE_T *p;

	p = ffile_get_file_info( ffd );

	return p->pos;
}

#endif


void
ffile_seek( FFD_T ffd, ushort offset )
{
	FFILE_T *p;

	p = ffile_get_file_info( ffd );

	p->pos = offset;
	rfile_update_directory( p );
}


void 
ffile_queue_open_as_random( FFD_T ffd, uchar from )
{
	FFILE_T *p;

	p = ffile_get_file_info( ffd );

	if( from == OPEN_FROM_BEGINNING )
		p->pos = p->out;
	else
		p->pos = p->in == 0 ? p->num_regs - 1 : p->in - 1;

	p->pos_qty = p->qty;
	rfile_update_directory( p );
}


uchar
ffile_is_eof( FFD_T ffd )
{
	FFILE_T *p;

	p = ffile_get_file_info( ffd );

	if( p->type == QFILE_TYPE )
		return p->qty == 0;
	else
		return p->pos >= p->num_regs;
}


MUInt 
ffile_is_corrupted( FFD_T ffd )
{
	FFILE_T *p;

	p = ffile_get_file_info( ffd );

	return p->page_error == p->num_pages ? FRFILE_ERROR : FRFILE_OK;
}
