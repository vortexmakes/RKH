/*
 * sigdata.h
 */


#ifndef __SIGDATA_H__
#define __SIGDATA_H__


#include "signal.h"


/* Defines available signal numbers */

enum
{
	SIG0, SIG1
};


SIG_T *verify_signal( MUInt sd );


#endif
