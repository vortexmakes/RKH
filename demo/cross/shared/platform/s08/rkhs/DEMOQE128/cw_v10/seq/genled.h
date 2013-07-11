/*
 * 	genled.h
 */

#ifndef __GENLED_H__
#define __GENLED_H__

#include "mytypes.h"
#include "sequence.h"
#include "seqlog.h"
#include "seqdefs.h"

#define CLI0_LED	0x01
#define CLI1_LED	0x02
#define CLI2_LED	0x04
#define CLI3_LED	0x08
#define CLI4_LED	0x10
#define CLI5_LED	0x20
#define CLI6_LED	0x40
#define	SRV_LED		0x80

#define set_sled(ch,x)	set_sequence(MAJOR_LED,(ch),(x))

#endif
