/*
 * critical.h
 * ColdFire V1 critical section 
 */

#ifndef __CRITICAL_H__
#define __CRITICAL_H__

#define CRITICAL_METHOD	1	/* Sets a critical section method that the system use */

#define MAX_NESTING_CSECT	8	/* Max. size of nesting critical section */

void init_critical( void );
void enter_critical( void );
void exit_critical( void );

#endif
