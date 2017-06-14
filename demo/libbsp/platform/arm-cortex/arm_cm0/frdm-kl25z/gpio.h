/*
 *	gpio.h
 *	
 */

#ifndef __GPIO_H__
#define __GPIO_H__

#include "derivative.h"

/*
 * GPIO low level acces macros:
 *  p: port
 *  x: bit
 */

#define _init_iopin( p, x, d )	\
			{								\
				if( d )						\
					p##_PDDR |= x;		\
				else						\
					p##_PDDR &= ~x;		\
			}

#define init_iopin(p,x,d)	_init_iopin(p,x,d)

#define _set_iopin( p, x, d )  \
				p##_PSOR |= x
#define set_iopin(p,x,d)	_set_iopin(p,x,d)
				
#define _clr_iopin( p, x, d )  \
				p##_PCOR |= x
#define clr_iopin(p,x,d)	_clr_iopin(p,x,d)
				

/*
 * GPIO definition
 *   	(name)			port, bit, dir
 */

#define LED_R			GPIOB, 0x00040000, 1
#define LED_G			GPIOB, 0x00080000, 1
#define LED_B			GPIOD, 0x00000002, 1


/* 
 * GPIO access macros
 */

#define init_led( x )				\
			{						\
				init_iopin( x );	\
			}

#define set_led(x)	clr_iopin( x )
#define clr_led(x)	set_iopin( x )

void gpio_init(void);


#endif






