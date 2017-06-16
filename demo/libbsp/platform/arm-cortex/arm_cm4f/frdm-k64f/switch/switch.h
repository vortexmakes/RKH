/*
 * switch.h
 *
 * Minimal debouncing switch handler
 *
 */

#ifndef __SWITCH_H__
#define __SWITCH_H__

#ifdef __TINY_PROC__
	typedef unsigned char	MUInt;
	typedef signed char		MInt;
#else
	typedef unsigned int	MUInt;
	typedef signed int		MInt;
#endif


typedef struct
{
	unsigned char state;
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
MUInt get_switch_state( MUInt who );

#endif
