/*
 * 	contick.h
 */


#include "mytypes.h"


/*
 * 	is_cmd_timeout:
 *
 * 	Tests a command shell timer.
 */

MUInt is_cmd_timeout( void );


/*
 * 	set_cmd_timeout:
 *
 * 	It set the command shell abort time.
 */

void set_cmd_timeout( MUInt tout );


/*
 * 	upgrade_cmd_timer:
 *
 * 	Upgrades command timer. Generally, this function is called from	ISR.
 */

void upgrade_cmd_timer( void );
