/*
 * 	ffile.h
 *    
 *	Implements a very simple flash file system. It offers a typical
 *  file system abstraction and interface. The files are stored as
 *  a collection of records. Programs read and write whole records,
 *  rather than bytes or arbitrary byte ranges, and can seek to a
 *  record boundary but not within records.
 *
 *  The directory and files are created in compile time using the 
 *  'CREATE_DIR' and 'CREATE_FFILE' macros respectively. Generally, 
 *  the directory and files are declared on 'ffdata' file.
 *
 *  This module not implements a dynamic wear levelling.
 */


#ifndef __FFILE_H__
#define __FFILE_H__


#include "mytypes.h"
#include "rfile.h"


#define FF_AUTO_FILE_FORMAT			1
#define FF_FILE_FORMAT				1
#define FF_TELL						0


enum
{
	FQFILE_OK, FQFILE_EMPTY, FQFILE_FULL
};


enum
{
	FRFILE_OK, FRFILE_EOF, FRFILE_ERROR
};


enum
{
	READ_ACCESS, WRITE_ACCESS
};


enum
{
	RFILE_ACCESS, QFILE_ACCESS
};


enum
{
	OPEN_FROM_END, OPEN_FROM_BEGINNING 
};


enum
{
	READ_BACKWARD, READ_FORWARD
};


typedef MUInt FFD_T;


/*
 * 	ffile_init:
 *
 * 	Initializes internal data structures and restores directory from
 * 	flash. Also, the entire flash partition is scanned for a failed 
 * 	sector. If found then the flash sector is formatted.
 */

void ffile_init( void );


/*
 *	ffile_get_file_info:
 *
 *	Retrieves the current file information.
 *
 * 	Arguments:
 *
 * 	'ffd': 		file descriptor.
 *
 * 	Returns:
 *
 * 	A pointer to flash file data structure.
 */

FFILE_T *ffile_get_file_info( FFD_T ffd );


/*
 *	ffile_is_corrupted:
 *
 *	Returns the status of file during initializing process.
 *
 * 	Arguments:
 *
 * 	'ffd': 		file descriptor.
 *
 * 	Returns:
 *
 * 	FRFILE_OK if the entire file wasn't corrupted during initializing process, 
 * 	FRFILE_ERROR otherwise.
 */

MUInt ffile_is_corrupted( FFD_T ffd );


/*
 * 	ffile_file_format:
 *
 * 	Erase file. On this process, the whole file data content is 
 * 	set to one.
 *
 * 	Arguments:
 *
 * 	'ffd': 		file descriptor.
 */

void ffile_file_format( FFD_T ffd );


/*
 * 	ffile_is_eof:
 *	
 *	Checks whether an end-of-file indicator has been set for a file.
 *
 * 	Arguments:
 *
 * 	'ffd': file descriptor.
 *
 * 	Returns:
 *
 * 	A true (1) value if the end of file was reached, otherwise
 * 	false value (0).
 */

MUInt ffile_is_eof( FFD_T ffd );


/*
 * 	ffile_queue_open_as_random:
 *
 * 	Sets temporarily the queue file specified by 'ffd' as a random file 
 * 	to read a register from queue without remove it. Also, sets the file 
 * 	position to the oldest or newest register. 
 * 	If 'ffile_queue_insert' or 'ffile_queue_remove' function is invoked 
 * 	the file is back to queue mode.
 *
 * 	Arguments:
 *
 * 	'ffd': 		file descriptor.
 * 	'from': 	from oldest or newest register, OPEN_FROM_BEGINNING or 
 * 				OPEN_FROM_END respectively.
 */

void ffile_queue_open_as_random( FFD_T ffd, uchar from );


/*
 * 	ffile_tell:
 *
 * 	Returns the current position of the file specified by 'ffd'. This 
 * 	position defines the register that will be read or written by the 
 * 	next I/O operation on the file. 
 *
 * 	Arguments:
 *
 * 	'ffd': 		file descriptor.
 *
 * 	Returns:
 *
 *	A current file position.
 */

ushort ffile_tell( FFD_T ffd );


/*
 * 	ffile_seek:
 *
 * 	Changes the current position of the file specified by 'ffd'. This 
 * 	position defines the register that will be read or written by 
 * 	the next I/O operation on the file.
 *
 * 	Arguments:
 *
 * 	'ffd': 		file descriptor.
 * 	'offset': 	compute the new file position relative to the start of 
 * 				the file. The value of offset must not be negative. 
 */

void ffile_seek( FFD_T ffd, ushort offset );


/*
 * 	ffile_queue_insert:
 * 	
 * 	Inserts a register on a queue file. The register is filled by copy, not 
 *	by reference.
 *
 * 	Arguments:
 *
 * 	'ffd': 		file descriptor.
 * 	'preg': 	pointer to the register that is to be placed on the 
 * 				queue file. The size of the registers queue file will 
 * 				hold was defined when the file was created.
 *
 * 	Returns:
 *
 * 	FQFILE_OK if the element was successfully inserted, 
 *	otherwise error code.
 */

MUInt ffile_queue_insert( FFD_T ffd, void *preg );


/*
 * 	ffile_queue_remove:
 *
 * 	Removes a register from a queue file. The register is received by copy 
 * 	so a buffer of adequate size must be provided. The number of bytes copied 
 * 	into the buffer was defined when the queue file was created.
 *
 * 	Arguments:
 *
 * 	'ffd':		file descriptor.
 * 	'preg': 	pointer to the buffer into which the received item will be 
 * 				copied.
 *
 * 	Returns:
 *
 * 	FQFILE_OK if an element was successfully removed from the 
 * 	file, otherwise error code.
 */

MUInt ffile_queue_remove( FFD_T ffd, void *preg );


/*
 * 	ffile_queue_random_read:
 *  
 *  Allows to read a register from a queue file without remove it. It's does 
 *  as a random read access. Before to call it the 'ffile_queue_open_as_random'
 *  function must be invoked to set random position to oldest or newest register.
 *  The parameter 'dir' sets the direction of current read, if it's set to 
 *  READ_FORWARD then the file position is advanced on this function call else
 *  the file position is back.
 *
 *  The element is received by copy so a buffer of adequate size must be 
 *  provided. The number of bytes copied into the buffer was defined when 
 *  the queue file was created.
 *
 * 	Arguments:
 *
 *  'ffd':		file descriptor.
 * 	'dir':		read direction.
 * 	'preg': 	pointer to the buffer into which the received item will be 
 * 				copied.
 *
 * 	Returns:
 *
 * 	FQFILE_OK if an element was successfully read from the 
 * 	file, otherwise error code.
 */
	
MUInt ffile_queue_random_read( FFD_T ffd, uchar dir, void *preg );


/*
 * 	ffile_random_access:
 *
 * 	Read or write registers of a given size from or to a file. The access
 * 	operation is specified by 'op' argument: READ_ACCESS or WRITE_ACCESS.
 * 	
 * 	On read access: reads 'rqty' registers from the file into the buffer 
 * 	specified by 'preg' pointer.
 *
 * 	On write access: writes 'rqty' register to the file from the buffer 
 * 	specified by 'preg' pointer.
 *
 * 	Arguments:
 *
 *  'ffd':		file descriptor.
 *  'op':		type of random access: READ_ACCESS or WRITE_ACCESS.
 * 	'preg': 	on read access: pointer to the buffer into which the 
 * 				received registers will be copied.
 * 				on write access: pointer to a buffer that contains 
 * 				the registers that to write.
 * 	'rqty':		number of registers to read or write.
 *
 * 	Returns:
 *
 * 	On read access: the positive number of complete registers successfully 
 * 	read; this value may be less than the requested number of registers,
 * 	otherwise a negative error code whether file was reached the end of file.
 *
 * 	On write access: the positive number of complete registers successfully 
 * 	written; if an error occurs, this is less than 'rqty'.
 */

int ffile_random_access( FFD_T ffd, uchar op, void *preg, ushort rqty );


#endif
