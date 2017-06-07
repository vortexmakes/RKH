/*
 * 	sequence.h
 */

#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__

#include "mytypes.h"

/*
 * 	init_seqs:
 * 		Must be called after hardware initialization
 * 		but before enabling interrupts
 */

void init_seqs( void );

/*
 * 	set_sequence:
 * 		This is the function
 * 		for generating time sequences
 * 		as in tone, ring or leds.
 *
 * 		Arguments:
 * 			major is an index to
 * 				device type given by
 * 				MAJOR_ENUM.
 * 			minor is a bit pattern of
 * 				the devices that has the same
 * 				sequence (Bit order must be
 * 				coordinated with hardware module).
 * 			code is the sequence code for the
 * 				aforementioned device type.
 * 	
 */

void set_sequence( MUInt major, unsigned minor, MUInt code );

#endif