/*
 *	gpio.h
 *	
 */

#ifndef __GPIO_H__
#define __GPIO_H__

#include "lpc17xx.h"

/*
 * GPIO low level acces macros:
 *  p: port
 *  x: bit
 */

#define _init_iopin( p, x )	\
			{							\
				LPC_##p->FIODIR = x;		\
			}

#define init_iopin(p,x)	_init_iopin(p,x)

#define _set_iopin( p, x )  \
				LPC_##p->FIOSET = x
#define set_iopin(p,x)	_set_iopin(p,x)
				
#define _clr_iopin( p, x )  \
				LPC_##p->FIOCLR = x
#define clr_iopin(p,x)	_clr_iopin(p,x)
				

/*
 * GPIO definition
 *   	(name)			port, bit
 */

#define LED1			GPIO0, 0x00400000


/* 
 * GPIO access macros
 */

#define init_led( x )				\
			{						\
				init_iopin( x );	\
			}

#define set_led(x)	set_iopin( x )
#define clr_led(x)	clr_iopin( x )

void gpio_init(void);


#endif






