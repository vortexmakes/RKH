/*
 *	sci.h
 *	Routines handle SCI service
 *
 *	Programmer: Darío S. Baliña.
 *	Date : 29/05/06.
 */

#ifndef __SCI_H__
#define __SCI_H__

#include "serdefs.h"


//#define __16MHz__
#ifdef __16MHz__

#define	UC_B300		0xD05	// 0.0% error
#define	UC_B600		0xC83	// 0.0% error
#define	UC_B1200	0x341	// 0.0% error
#define	UC_B2400	0x1A1	// 0.1% error
#define	UC_B4800 	0xD0	// 0.2% error
#define	UC_B9600	0x68	// 0.2% error
#define	UC_B19200	0x34	// 0.2% error
#define	UC_B38400	0x32	// 0.2% error
#define	UC_B57600	0x11	// 2.1% error

#endif

//#define __16_384MHz__
#ifdef __16_384MHz__

#define	UC_B300		0xD55	// 0.0% error
#define	UC_B600		0x6AB	// 0.0% error
#define	UC_B1200	0x355	// 0.0% error
#define	UC_B2400	0x1AB	// 0.1% error
#define	UC_B4800	0xD5	// 0.2% error
#define	UC_B9600	0x6B	// 0.3% error
#define	UC_B19200	0x35	// 0.6% error
#define	UC_B38400	0x1B	// 1.2% error
#define	UC_B57600	0x12	// 1.2% error

#endif

#define __24_576MHz__
#ifdef __24_576MHz__

#define	UC_B300		0x1400	// 0.0% error
#define	UC_B600		0xA00	// 0.0% error
#define	UC_B1200	0x500	// 0.0% error
#define	UC_B2400	0x280	// 0.0% error
#define	UC_B4800	0x140	// 0.0% error
#define	UC_B9600	0xA0	// 0.0% error
#define	UC_B19200	0x50	// 0.0% error
#define	UC_B38400	0x28	// 0.0% error
#define	UC_B57600	0x1B	// 1.2% error

#endif


#define SCI_ENADIS_INTERRUPT		0

void com1_rcv_isr( void );
void com2_rcv_isr( void );
void disable_rcv_interrupt( ruint ch );
void enable_rcv_interrupt( ruint ch );


#endif
