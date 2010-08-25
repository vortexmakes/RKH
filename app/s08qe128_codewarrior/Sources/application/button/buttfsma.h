/*
 * 	buttfsma.h
 */


#include "mytypes.h"
#include "event.h"


void buttfsm_init( void );
void set_leds( EVT_T *pevt );
void set_leds0( EVT_T *pevt );
void set_leds1( EVT_T *pevt );
void go_back_state1( EVT_T *pevt );
void go_back_state2( EVT_T *pevt );
void system_crash( EVT_T *pevt );
uchar check_super_state( void );
