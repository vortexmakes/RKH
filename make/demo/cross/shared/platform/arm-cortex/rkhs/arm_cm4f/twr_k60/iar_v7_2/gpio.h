/*
 *	gpio.h
 *	
 */

#ifndef __GPIO_H__
#define __GPIO_H__

#include "kinetis.h"
#include "derivative.h"

/*
 * GPIO low level acces macros:
 *  p: port name [ A, B, C ... ]
 *  b: bit [ 0 .. 31 ]
 *  m: mux options, see Digital GPIO properties flags in kinetis.h
 *  d: direction [ KGPIO_PDDR_OUT, KGPIO_PDDR_IN ]
 *  o: if d is output, configuration value [ KGPIO_PDOR_HIGH, KGPIO_PDOR_LOW ]
 */

#define _init_gpio( p, b, m, d, o )	\
		{								\
			KCFG_PINSEL( p, b, m, 1 );	\
			GPIO##p##d(1<<b);			\
			GPIO##p##o(1<<b);			\
		}

#define _set_gpio( p, b, m, d, o )  GPIO##p##_PSOR |= (1<<b)
#define _clr_gpio( p, b, m, d, o )  GPIO##p##_PCOR |= (1<<b)
#define _tgl_gpio( p, b, m, d, o )	GPIO##p##_PTOR |= (1<<b)
				
#define _get_gpio(p,b,m,d,o)		((GPIO##p##_PDIR & (1<<b))!=0)


/*
 * GPIO public access macros
 */

#define init_gpio(x)	_init_gpio(x)
#define set_gpio(x)		_set_gpio(x)
#define clr_gpio(x)		_clr_gpio(x)
#define tgl_gpio(x)		_tgl_gpio(x)
#define get_gpio(x)		_get_gpio(x)

				

/*
 * GPIO definition
 */

#define SW1				KGPIO(A, 19, PORT_PS_UP_ENABLE, KGPIO_PDDR_IN, KGPIO_PDOR_HIGH)	
#define SW2				KGPIO(E, 26, PORT_PS_UP_ENABLE, KGPIO_PDDR_IN, KGPIO_PDOR_HIGH)	

#define LED1			KGPIO(A, 11, 0, KGPIO_PDDR_OUT, KGPIO_PDOR_HIGH)
#define LED2			KGPIO(A, 28, 0, KGPIO_PDDR_OUT, KGPIO_PDOR_HIGH)
#define LED3			KGPIO(A, 29, 0, KGPIO_PDDR_OUT, KGPIO_PDOR_HIGH)
#define LED4			KGPIO(A, 10, 0, KGPIO_PDDR_OUT, KGPIO_PDOR_HIGH)


/* 
 * GPIO access macros
 */

#define init_ioports( x )				\
			{						\
				init_gpio( SW1 );	\
				init_gpio( SW2 );	\
				init_gpio( LED1 );	\
				init_gpio( LED2 );	\
				init_gpio( LED3 );	\
				init_gpio( LED4 );	\
			}

#define set_led(x)	clr_iopin( x )
#define clr_led(x)	set_iopin( x )

void gpio_init(void);


#endif






