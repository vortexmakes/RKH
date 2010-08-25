/*
 * 	devflash.c
 */


#include "mytypes.h"
#include "rksys.h"
#include "devflash.h"
#include "rfile.h"
#include "flash.h"
#include <string.h>


enum
{
	CHECK_BAD, CHECK_OK
};


typedef struct
{
	uchar data[ RF_SIZE_EFF_PAGE ];
	ushort checksum;
} PAGE_BUFF_T;


typedef uchar (*RECPROC_T)( void );


static PAGE_BUFF_T page_buff;
static uchar *main_page_addr, *back_page_addr;
static uchar rmain, rback;
static ushort main_check, back_check;


/*
 * 		Recovery true tables:
 *
 * 		rmain: result of checksum from main page.
 * 		rback: result of checksum from backup page.
 *
 *
 * 			rmain		|	rback		|	Process
 *
 * 			CHECK_BAD	|	CHECK_BAD	|	DIR_BAD
 * 			CHECK_BAD	|	CHECK_OK	|	DIR_RECOVERY
 * 			CHECK_OK	|	CHECK_BAD	|	DIR_BACKUP
 * 			CHECK_OK	|	CHECK_OK	|	-> next true table
 *
 *
 * 			Checksum compare true table:
 *
 * 			NOT_MATCH	|	DIR_BACKUP	
 * 			MATCH		|	-> next true table
 *
 *
 * 			Content compare true table:
 *
 * 			NOT_MATCH	|	DIR_BACKUP
 * 			MATCH		|	DIR_OK
 *
 */


static uchar proc_page_in_error( void ),
			 proc_page_recovery( void ),
			 proc_page_backup( void ),
			 proc_page_cmp( void );


static const RECPROC_T recovery[] =
{
	proc_page_in_error,
	proc_page_recovery,
	proc_page_backup,
	proc_page_cmp
};


static
void
devflash_copy_page( uchar *dest_addr, uchar *src_addr )
{
	rkwatchdog();

	memcpy( &page_buff, src_addr, RF_SIZE_PHY_PAGE );
	flash_write_page( dest_addr, &page_buff );

	rkwatchdog();
}


static
uchar
proc_page_in_error( void )
{
	return DIR_BAD;
}


static
uchar
proc_page_recovery( void )
{
	devflash_copy_page( main_page_addr, back_page_addr );
	return DIR_RECOVERY;
}


static
uchar
proc_page_backup( void )
{
	devflash_copy_page( back_page_addr, main_page_addr );
	return DIR_BACKUP;
}


static
uchar
proc_page_cmp( void )
{
	if( main_check != back_check )
		return proc_page_backup();

	if( memcmp( main_page_addr, back_page_addr, RF_SIZE_EFF_PAGE ) == 0 )
		return DIR_OK;
	
	return proc_page_backup();
}


static
ushort
devflash_calculate_page_checksum( void *address, ushort qty )
{
	ushort check, i;
	uchar *p;

	rkwatchdog();

	for( check = 0, i = qty, p = (uchar*)address; i; --i )
		check += *p++;

	return ~check;
}


static
void
devflash_set_main_page_address( uchar page )
{
	main_page_addr = ( page * RF_SIZE_PHY_PAGE ) + RF_FB_ADDRESS;
}


static
uchar
devflash_verify_page_checksum( uchar *pfrom, ushort checksum )
{
	PAGE_BUFF_T *p;

	p = (PAGE_BUFF_T*)pfrom;
	return p->checksum == checksum ? CHECK_OK : CHECK_BAD;
}


void
devflash_format_pages( uchar start_page, uchar qty )
{
	uchar page_ix;

	rkwatchdog();

	devflash_set_main_page_address( page_ix = start_page );

	memset( &page_buff, 0xFF, RF_SIZE_PHY_PAGE );
	page_buff.checksum = (ushort)RF_ERASE_CHECKSUM;

	for( ; page_ix < qty + start_page; 
			++page_ix, main_page_addr += RF_SIZE_PHY_PAGE )
		flash_write_page( main_page_addr, &page_buff );
}


void
devflash_write_data( uchar *desta, uchar destp, uchar *data, ushort size )
{
	rkwatchdog();

	devflash_set_main_page_address( destp );

	memcpy( &page_buff, main_page_addr, RF_SIZE_PHY_PAGE );
	memcpy( page_buff.data + (ushort)desta, data, size );

	page_buff.checksum = devflash_calculate_page_checksum( &page_buff, RF_SIZE_EFF_PAGE );
	flash_write_page( main_page_addr, &page_buff );
}


void
devflash_read_data( uchar *desta, uchar destp, uchar *data, ushort size )
{
	devflash_set_main_page_address( destp );
	memcpy( data, main_page_addr + (ushort)desta, size );
}


uchar
devflash_verify_page( uchar page )
{
	devflash_set_main_page_address( page );
	main_check = devflash_calculate_page_checksum( main_page_addr, RF_SIZE_EFF_PAGE );
	rmain = devflash_verify_page_checksum( main_page_addr, main_check );
	return rmain == CHECK_OK ? PAGE_OK : PAGE_BAD;
}


#if RF_PAGE_DUMP
uchar *
devflash_page_dump( uchar page )
{
	devflash_set_main_page_address( page );
	memcpy( &page_buff, main_page_addr, RF_SIZE_PHY_PAGE );
	return (uchar*)&page_buff;
}
#endif


#if RF_PAGE_DIRTY
void
devflash_page_dirty( uchar page )
{
	PAGE_BUFF_T *p;

	devflash_set_main_page_address( page );
	p = (PAGE_BUFF_T *)main_page_addr;
	page_buff.checksum = ~p->checksum;
	flash_write_page( main_page_addr, &page_buff );
}
#endif


void
devflash_copy_page_from_buff( uchar *dest_addr )
{
	flash_write_page( dest_addr, &page_buff );
}


uchar *
devflash_restore_directory( uchar *status )
{
	uchar r;

	main_page_addr = RF_DIR_MAIN_FB_ADDRESS;
	back_page_addr = RF_DIR_BACK_FB_ADDRESS;

	main_check = devflash_calculate_page_checksum( main_page_addr, RF_SIZE_EFF_PAGE );
	rmain = devflash_verify_page_checksum( main_page_addr, main_check );

	back_check = devflash_calculate_page_checksum( back_page_addr, RF_SIZE_EFF_PAGE );
	rback = devflash_verify_page_checksum( back_page_addr, back_check );

	r = 0;
	r = ( rmain << 1 ) | rback;
	*status = (*recovery[ r ])();

	return main_page_addr;
}
