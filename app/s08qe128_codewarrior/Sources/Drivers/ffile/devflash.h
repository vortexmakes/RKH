/*
 * 	devflash.h
 */


#ifndef __DEVFLASH_H__
#define __DEVFLASH_H__


#include "mytypes.h"
#include "rfile.h"


enum
{
	DIR_OK,	DIR_BAD, DIR_RECOVERY, DIR_BACKUP
};


uchar *devflash_restore_directory( uchar *status );
void devflash_write_data( uchar *desta, uchar destp, uchar *data, ushort size );
void devflash_read_data( uchar *desta, uchar destp, uchar *data, ushort size );
void devflash_copy_page_from_buff( uchar *dest_addr );
void devflash_format_pages( uchar start_page, uchar qty );
uchar devflash_verify_page( uchar page );
uchar *devflash_page_dump( uchar page );
void devflash_page_dirty( uchar page );


#endif
