/*
 * 	ffdata.c
 */


#include "rfile.h"
#include "ffdata.h"
#include "rksys.h"


/*
 * 	The memory layout of file flash system is wired, the
 * 	first two pages stores the directory and its backup, the remains 
 * 	pages stores the files.
 *
 * 	Example of typical memory layout:
 *
 * 	Storage		-	Page ix
 *
 * 	-----------		RF_DIR_MAIN_PAGE = 0
 * 	0 - dir	
 * 	-----------		RF_DIR_MAIN_PAGE = 1
 * 	1 - dir back	
 * 	-----------		FILE0_BEGIN_PAGE = RF_FILE_PAGE_BASE = 2
 * 	2 - file 0
 * 	3 -	file 0		FILE0_NUMBER_PAGES = 3
 * 	4 - file 0
 * 	-----------		FILE1_BEGIN_PAGE = FILE0_BEGIN_PAGE + FILE0_NUMBER_PAGES
 * 	5 - file 1
 * 	6 -	file 1		FILE1_NUMBER_PAGES = 3
 * 	7 - file 1
 * 	-----------		FILE2_BEGIN_PAGE = FILE1_BEGIN_PAGE + FILE1_NUMBER_PAGES	
 * 	8 - file 1
 * 	9 -	file 1		FILE2_NUMBER_PAGES = 3
 * 	10- file 1
 * 	-----------		...
 */

#define FF0_NUM_PAGES			6
#define FF1_NUM_PAGES			1
#define FF2_NUM_PAGES			2


#define FF0_BEGIN_PAGE			RF_FILE_PAGE_BASE
#define FF1_BEGIN_PAGE			(FF0_NUM_PAGES+FF0_BEGIN_PAGE)
#define FF2_BEGIN_PAGE			(FF1_NUM_PAGES+FF1_BEGIN_PAGE)


/*
 *	Files directory. Any software module intending to use a flash file
 *	must first create a file structure into directory. When a file 
 *	is first created, it's assigned an associated unique descriptor, 
 *	access type, a number of flash pages, a begin page, and size of 
 *	register. Therefore, each file of that must be defined by means 
 *	'CREATE_FFILE' macro. The file descriptor are defined in 'ffdata.h' 
 *	file.
 */

CREATE_DIR =
{ 
	CREATE_FFILE( FFD0, QFILE_TYPE, FF0_NUM_PAGES, FF0_BEGIN_PAGE, sizeof( TRACE_EVENT_T) ), 
	CREATE_FFILE( FFD1, QFILE_TYPE, FF1_NUM_PAGES, FF1_BEGIN_PAGE, 10 ),
	CREATE_FFILE( FFD2, RFILE_TYPE, FF2_NUM_PAGES, FF2_BEGIN_PAGE, 10 )
};
