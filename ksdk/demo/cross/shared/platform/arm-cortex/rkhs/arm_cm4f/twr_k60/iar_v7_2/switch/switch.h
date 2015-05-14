/*
 * switch.h
 */

#ifndef __SWITCH_H__
#define __SWITCH_H__

#include "mytypes.h"

typedef struct
{
	uchar state;
	MUInt (*rawsw)(void);
	MUInt debsw;
}SWITCH_ST;

enum
{
	SW_RELEASED,
	SW_PRESSED
};

enum
{
	SW1_SWITCH,
	SW2_SWITCH,
	SWITCHS_NUM
};

void switch_tick( void );
uchar get_switch_state( uchar who );

#endif
