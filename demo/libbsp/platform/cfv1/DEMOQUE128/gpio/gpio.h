/*
 *	ioports.h
 *	
 *	Routines for PORTS initialization.
 *
 *	Programmer: Darío S. Baliña.
 *	Date : 26/05/06.
 */

#ifndef __IO_H__
#define __IO_H__

#include "derivative.h"

/*
 * GPIO low level acces macros:
 *  p: port
 *  b: bit
 *  d: direction
 *  u: pullup
 *  x: if output, initial level
 *  v: set level
 */

#define _init_iopin( p, b, d, u, x )	\
			{							\
				p##D_##p##D##b## = x;	\
				p##DD_##p##DD##b## = d;	\
				p##PE_##p##PE##b## = u;	\
			}

#define init_iopin(p)	_init_iopin(p)

#define _set_iopin( p, b, d, u, x, v )  \
				p##D_##p##D##b## = v 
#define set_iopin(p,v)	_set_iopin(p,v)
				
#define _toggle_iopin( p, b, d, u, x )	\
				p##D_##p##D##b## ^= 1
#define toggle_iopin(p)	_toggle_iopin(p)

#define _read_iopin( p, b, d, u, x )	\
				p##D_##p##D##b
#define read_iopin(p)	_read_iopin(p)

enum
{
	PIN_DIR_IN, PIN_DIR_OUT
};

enum
{
	PIN_LOW, PIN_HIGH
};

enum
{
	PIN_PE_DIS, PIN_PE_ENA
};


/*
 * GPIO definition
 *   	(name)			port,bit,dir,pullup,level
 */

#define PSHBUTT1		PTA, 2, PIN_DIR_IN, PIN_PE_ENA, PIN_LOW
#define PSHBUTT2		PTA, 3, PIN_DIR_IN, PIN_PE_ENA, PIN_LOW
#define PSHBUTT3		PTD, 2, PIN_DIR_IN, PIN_PE_ENA, PIN_LOW
#define PSHBUTT4		PTD, 3, PIN_DIR_IN, PIN_PE_ENA, PIN_LOW

#define COM_ENABLE		PTC, 5, PIN_DIR_OUT, PIN_PE_DIS, PIN_LOW

#define LED1			PTC, 0, PIN_DIR_OUT, PIN_PE_DIS, PIN_HIGH
#define LED2			PTC, 1, PIN_DIR_OUT, PIN_PE_DIS, PIN_HIGH
#define LED3			PTC, 2, PIN_DIR_OUT, PIN_PE_DIS, PIN_HIGH
#define LED4			PTC, 3, PIN_DIR_OUT, PIN_PE_DIS, PIN_HIGH
#define LED5			PTC, 4, PIN_DIR_OUT, PIN_PE_DIS, PIN_HIGH
#define LED6			PTC, 5, PIN_DIR_OUT, PIN_PE_DIS, PIN_HIGH
#define LED7			PTE, 6, PIN_DIR_OUT, PIN_PE_DIS, PIN_HIGH
#define LED8			PTE, 7, PIN_DIR_OUT, PIN_PE_DIS, PIN_HIGH


/* 
 * GPIO access macros
 */

#define init_pshbuts()					\
			{							\
				init_iopin( PSHBUTT1 );	\
				init_iopin( PSHBUTT2 );	\
				init_iopin( PSHBUTT3 );	\
				init_iopin( PSHBUTT4 );	\
			}

#define init_leds()					\
			{						\
				init_iopin( LED1 );	\
				init_iopin( LED2 );	\
				init_iopin( LED3 );	\
				init_iopin( LED4 );	\
				init_iopin( LED5 );	\
				init_iopin( LED6 );	\
				init_iopin( LED7 );	\
				init_iopin( LED8 );	\
			}

#define set_led(x,b)	set_iopin( x, b )

#define init_comen()	init_iopin( COM_ENABLE )

#define set_comen(b)	set_iopin( COM_ENABLE, b )

void gpio_init(void);


#endif






