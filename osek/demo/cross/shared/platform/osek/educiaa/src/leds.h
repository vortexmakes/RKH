/*
 * leds.h
 */

#ifndef __LEDS_H__
#define __LEDS_H__

#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
#include "types.h"


/*
 * EduCIAA Leds map on "/dev/dio/out/0"
 */

#define LED0R_MASK	0x01	/* GPIO5[0]  */
#define LED0G_MASK	0x02	/* GPIO5[1]  */
#define LED0B_MASK	0x04	/* GPIO5[2]  */
#define LED1_MASK	0x08	/* GPIO0[14] */
#define LED2_MASK	0x10	/* GPIO1[11] */
#define LED3_MASK	0x20	/* GPIO1[12] */

void init_leds( void );
void set_led( uint8_t lmask, boolean st );


/* RGB Led control */

typedef enum
{
	RGB_BLACK,
	RGB_WHITE,
	RGB_RED,
	RGB_LIME,
	RGB_BLUE,
	RGB_YELLOW,
	RGB_CYAN,
	RGB_MAGENTA
} RGB_COLOR_IDX;

void set_rgb_led( RGB_COLOR_IDX idx );

#endif
