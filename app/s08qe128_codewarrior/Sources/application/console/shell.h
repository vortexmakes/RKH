/*
 * shell.h
 */


#ifndef __SHELL_H__
#define __SHELL_H__


#include "task.h"
#include "event.h"
#include "mytypes.h"
#include "queue.h"


#define SHELL_QUEUE_SIZE 			16
#define SHELL_QUEUE_BYTE_SIZE		SHELL_QUEUE_SIZE*sizeof( char )


DECLARE_TASK( shell );
DECLARE_QUEUE_ARRAY( shell_queue, SHELL_QUEUE_BYTE_SIZE );


#endif
