/*
 * 	serlog.h
 */

#include "mytypes.h"
#include "serdefs.h"

void serlog_init( const COM_T *p );
void serlog_sendchar( const COM_T *p, const unsigned char *c );
