/*
 * button.h
 */


#ifndef __BUTTON_H__
#define __BUTTON_H__


#include "task.h"
#include "event.h"
#include "mytypes.h"
#include "queue.h"


#define BUTTON_QUEUE_SIZE 			6
#define BUTTON_QUEUE_BYTE_SIZE		BUTTON_QUEUE_SIZE*sizeof( EVT_T )


DECLARE_TASK( button );
DECLARE_QUEUE_ARRAY( button_queue, BUTTON_QUEUE_BYTE_SIZE );


#endif
