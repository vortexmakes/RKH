/*
 * 	rfile.h
 */


#ifndef __RFILE_H__
#define __RFILE_H__


#include "mytypes.h"


/*
 * 	Sets the flash base address of storage area.
 */

#define RF_FB_ADDRESS			(uchar*)0x4000


/*
 * 	Sets the physical size of page in bytes.
 */

#define RF_SIZE_PHY_PAGE		512


/*
 * 	Each page stores a 16-bits checksum. It's stored in the last 
 * 	2 position of page. Thus, the effective storage	area of a page 
 * 	is calculated as:
 *
 * 	RF_SIZE_EFF_PAGE = RF_SIZE_PHY_PAGE - RF_SIZE_CHECKSUM
 */

#define RF_SIZE_CHECKSUM		2	/* in bytes */
#define RF_SIZE_EFF_PAGE		(RF_SIZE_PHY_PAGE-RF_SIZE_CHECKSUM)
#define RF_PAGE_CHECKSUM_POS	RF_SIZE_EFF_PAGE


/*
 * 	Generally, the erased flash page sets all bits to one. Therefore,
 * 	the checksum of recently erased page is calculated as:
 */

#define RF_ERASE_CHECKSUM		(ushort)(~(RF_SIZE_EFF_PAGE*0xFF))


#define RF_DIR_MAIN_PAGE		0
#define RF_DIR_BACK_PAGE		(RF_DIR_MAIN_PAGE+1)
#define RF_FILE_PAGE_BASE		(RF_DIR_BACK_PAGE+1)


/*
 * 	The address base of storage area is automatically calculated.
 */

#define RF_DIR_MAIN_FB_ADDRESS	((uchar*)((RF_DIR_MAIN_PAGE*RF_SIZE_PHY_PAGE)+RF_FB_ADDRESS))
#define RF_DIR_BACK_FB_ADDRESS	((uchar*)((RF_DIR_BACK_PAGE*RF_SIZE_PHY_PAGE)+RF_FB_ADDRESS))
#define RF_FILE_FB_ADDRESS		((uchar*)((RF_FILE_PAGE_BASE*RF_SIZE_PHY_PAGE)+RF_FB_ADDRESS))


/*
 * 	Misc. macro that includes code to use.
 */

#define RF_PAGE_DUMP			0
#define RF_PAGE_DIRTY			0


/*
 *	Macro that creates a new flash file structure into directory.
 *
 * 	Arguments:
 *
 * 	'fd':	file descriptor. Represents a new flash file into directory.
 * 	't': 	type of flash file. It can have the following values: 
 * 			QFILE_TYPE or RFILE_TYPE. The file type allows to determine 
 * 			whether the file access is queue or random.
 * 	'np': 	number of pages. It's defines the size of file.
 * 	'bp': 	begin page.
 *	'sr': 	size of register. Number of bytes each register in the file 
 *			will require. Registers are stored by copy, not by reference, 
 *			so this is the number of bytes that will be stored for each written 
 *			register. Each register on the file must be the same size.
 */

#define CREATE_FFILE( fd, t, np, bp, sr )								\
																		\
{ fd, t, 0, np, bp, (uchar*)(((bp)*RF_SIZE_PHY_PAGE)+RF_FB_ADDRESS), 	\
	sr, RF_SIZE_EFF_PAGE/(sr), (RF_SIZE_EFF_PAGE/(sr))*np, 0, 0, 0 }


/*
 * 	Macro that creates the default directory.
 */

#define CREATE_DIR		const FFILE_T defdir[]


/*
 * 	Macro that declares the default directory.
 *
 * 	Arguments:
 *
 * 	'nf':	number of files.
 */

#define DECLARE_DIR(nf)		const FFILE_T defdir[ nf ]


enum
{
	PAGE_BAD, PAGE_OK
};


enum
{
	QFILE_TYPE, RFILE_TYPE
};


typedef struct
{
	unsigned fd:4;				/* file descriptor */
	unsigned type:4;			/* type of file access */
	uchar page_error;			/* number of page in error */
	uchar num_pages;			/* number of pages */
	uchar begin_page;			/* first page relative to directory page */
	uchar *start_address;		/* absolute base address */
	uchar size_reg;				/* register size in bytes */
	ushort num_regs_per_page;	/* number of register per page */
	ushort num_regs;			/* maximum number of registers */
	ushort in;					/* points to the next place of stored register */
	ushort out;					/* points to the free next place */
	ushort qty;					/* number of registers currently in the file */
	ushort pos;					/* points to currently position */
	ushort pos_qty;				/* number of registers currently in the random file */
} FFILE_T;


typedef struct
{
	FFILE_T *pf;
	unsigned op:1;
	unsigned tacc:1;
	unsigned res:6;
	void *ptofrom;
	ushort currpos;
	ushort rqty;
} RACC_T;


void rfile_init_directory( void );
void rfile_update_directory( FFILE_T *pf );
void rfile_file_format( FFILE_T *pf );
void rfile_access_register( RACC_T *pra );
FFILE_T *rfile_get_file( uchar fd );


#endif
