/*
 * 	genled.h
 */

#ifndef __GENLED_H__
#define __GENLED_H__

#include "mytypes.h"
#include "sequence.h"
#include "seqlog.h"
#include "seqdefs.h"

#define set_led(ch,x)	set_sequence(MAJOR_LED,(ch),(x))

#endif
