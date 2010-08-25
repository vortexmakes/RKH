/*
 * 	rfile.c
 */


#include "mytypes.h"
#include "rfile.h"
#include "ffile.h"
#include "devflash.h"
#include "ffdata.h"
#include <string.h>


static FFILE_T dir[ NUM_FLASH_FILES ];
static uchar *reg_addr, page_num;


void
rfile_file_format( FFILE_T *pf )
{
	devflash_format_pages( pf->begin_page, pf->num_pages );
	pf->pos = pf->in = pf->out = pf->qty = 0;
	rfile_update_directory( pf );
}


void
rfile_init_directory( void )
{
	uchar file, page, page_error, *p, r;
	FFILE_T *pf;

	p = devflash_restore_directory( &r );
	memcpy( dir, r != DIR_BAD ? p:(uchar*)defdir, sizeof( FFILE_T )*NUM_FLASH_FILES );

	for( file = 0, pf = dir; file < NUM_FLASH_FILES; ++file, ++pf )
	{
		for( page = page_error = 0;	page < pf->num_pages; ++page )
			if( devflash_verify_page( page + pf->begin_page ) == PAGE_BAD )
				++page_error;

		pf->page_error = page_error;

		#if FF_AUTO_FILE_FORMAT == 1
		{
			if( pf->page_error == pf->num_pages )
				rfile_file_format( pf );
		}
		#endif
		rfile_update_directory( pf );
	}
}


void
rfile_update_directory( FFILE_T *pf )
{
	devflash_write_data( (uchar*)(pf->fd * sizeof( FFILE_T )), RF_DIR_MAIN_PAGE, 
			(uchar*)pf, sizeof( FFILE_T ) );
	devflash_copy_page_from_buff( RF_DIR_BACK_FB_ADDRESS );
}


void
rfile_access_register( RACC_T *pra )
{
	ushort numregs, /* number of register to access */
		   remregs, /* number of remainded register in current page */
		   posreg, 	/* register position in page */
		   nrpp;	/* number of registers per page */
	uchar *pdata;	/* pointer to data to write or read */


	nrpp = pra->pf->num_regs_per_page;
	posreg = pra->currpos % nrpp;
	page_num = pra->currpos/nrpp + pra->pf->begin_page;

	numregs = pra->rqty;
	remregs = numregs > (nrpp - posreg) ? (nrpp - posreg) : numregs;
	pdata = pra->ptofrom;

	while( numregs > 0 )
	{
		reg_addr = (uchar*)( posreg * pra->pf->size_reg );
		if( pra->op == READ_ACCESS )
			devflash_read_data( reg_addr, page_num, pdata, pra->pf->size_reg * remregs );
		else
			devflash_write_data( reg_addr, page_num, pdata, pra->pf->size_reg * remregs );

		numregs -= remregs;
		pdata += ( remregs * pra->pf->size_reg );
		++page_num;
		remregs = numregs > nrpp ? nrpp : numregs;
		posreg = 0;
	}
}


FFILE_T *
rfile_get_file( uchar fd )
{
	return &dir[ fd ];
}
