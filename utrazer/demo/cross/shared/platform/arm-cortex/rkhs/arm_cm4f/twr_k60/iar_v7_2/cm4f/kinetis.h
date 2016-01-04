/*
 * kinetis.h
 *
 * Usefull macros and definitions for working with
 * Kinetis MCU Peripherals
 */

#ifndef __KINETIS_H__
#define __KINETIS_H__

/* 
 * Power up a module (enable clock to it)
 * reg: SCGC[1..7]
 * module: Module specific mask
 */

#define KSET_PCLKE(reg, module)		SIM_##reg |= (module)      

/* 
 * Power down a module (enable clock to it)
 * reg: SCGC[1..7]
 * module: Module specific mask
 */

#define KSET_PCLKD(reg, module)		SIM_##reg &= ~(module)


/*
 * Configure PORT Pin Mux Alternative
 * port: [ A..D ]
 * pin: [ 0..23 ]
 * function: Mux Alternative | Digital GPIO properties
 * enable: 1/0 - Activate / deactivate function
 */

#define KCFG_PINSEL(port, pin, function,enable) 						\
		{																\
				SIM_SCGC5 |= SIM_SCGC5_PORT##port##_MASK;				\
				PORT##port##_PCR##pin = (enable != 0) ? function : 0;	\
		}


/*
 * Digital GPIO properties
 */

/* Digital Input pins properties */

#define PORT_PE				0x00000002  			/* enable pull if input */
#define PORT_PS_DOWN_ENABLE	(0x00000000 | PORT_PE)	/* pull-down if enabled */
#define PORT_PS_UP_ENABLE	(0x00000001 | PORT_PE)	/* pull-up if enabled */
#define PORT_PFE			0x00000010		/* passive filter enabled */ 
											/* (disable for signals > 2MHz) */
/* Digital Output pins properties */

#define PORT_SRE_FAST		0x00000000		/* fast slew-rate */
#define PORT_SRE_SLOW		0x00000004		/* slow slew-rate */
#define PORT_ODE			0x00000020		/* open-drain enabled */
#define PORT_DSE_LOW		0x00000000		/* digital strength low */
#define PORT_DSE_HIGH		0x00000040		/* digital strength high */

#define KGPIO_PDDR_OUT		_PDDR |=
#define KGPIO_PDDR_IN		_PDDR &=~

#define KGPIO_PDOR_HIGH		_PDOR |=
#define KGPIO_PDOR_LOW		_PDOR &=~

/*
 * GPIO definition
 *  p: port name [ A, B, C ... ]
 *  b: bit [ 0 .. 31 ]
 *  m: mux options, see Digital GPIO properties flags in kinetis.h
 *  d: direction [ KGPIO_PDDR_OUT, KGPIO_PDDR_IN ]
 *  o: if d is output, configuration value [ KGPIO_PDOR_HIGH, KGPIO_PDOR_LOW ]
 */

#define KGPIO(p,b,m,d,o)	p,b,(PORT_MUX_GPIO|m),d,o


/*
 * Peripheric specific definition
 *  p: port name [ A, B, C ... ]
 *  b: bit [ 0 .. 31 ]
 *  m: mux options, see Digital GPIO properties flags in kinetis.h
 *  e: 1/0 - Activate / deactivate function
 */

#define KPRPH(p,b,m,e)		KCFG_PINSEL(p,b,m,e)

/*
 * Pin Mux Alternative
 */

#define PORT_MUX_ANALOG		0x00000000
#define PORT_MUX_GPIO		0x00000100
#define PORT_MUX_ALT2		0x00000200
#define PORT_MUX_ALT3		0x00000300
#define PORT_MUX_ALT4		0x00000400
#define PORT_MUX_ALT5		0x00000500
#define PORT_MUX_ALT6		0x00000600
#define PORT_MUX_ALT7		0x00000700


#endif
