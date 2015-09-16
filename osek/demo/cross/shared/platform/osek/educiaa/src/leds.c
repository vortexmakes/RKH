/*
 * leds.c
 * EDU-CIAA leds control
 */


#include "leds.h"


static int32_t fd_leds;

void
init_leds( void )
{
	fd_leds = ciaaPOSIX_open("/dev/dio/out/0", O_RDWR);
}


void
set_led( uint8 lmask, boolean st )
{
   uint8 outputs;

   /* set output on */
   ciaaPOSIX_read(fd_leds, &outputs, 1);

   if( st )
	   outputs |= lmask;
   else
	   outputs &= ~lmask;


   ciaaPOSIX_write(fd_leds, &outputs, 1);
}


/*
 * RGB Led control
 */

typedef struct
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} RGB_COLOR_ST;


static const RGB_COLOR_ST rgb_colors[] = {	
											{ 0, 0, 0 }, /* black   */
											{ 1, 1, 1 }, /* white   */
											{ 1, 0, 0 }, /* red     */
											{ 0, 1, 0 }, /* lime    */
											{ 0, 0, 1 }, /* blue    */
											{ 1, 1, 0 }, /* yellow  */
											{ 0, 1, 1 }, /* cyan    */
											{ 1, 0, 1 }  /* magenta */
										 };

void
set_rgb_led( RGB_COLOR_IDX idx )
{
	set_led( LED0R_MASK, rgb_colors[idx].r  );
	set_led( LED0G_MASK, rgb_colors[idx].g  );
	set_led( LED0B_MASK, rgb_colors[idx].b  );
}



