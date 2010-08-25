/*
 * fsmdata.c
 */

#include "fsm.h"
#include <stdlib.h>


/*	Include files of software modules that uses FSM */

#include "buttfsm.h"
#include "buttfsma.h"


#if RKSYS_FSM

/*
 *	Register of FSMs. Any software module intending to use a FSM
 *	must first create a fsm structure into FSMs register. When a FSM 
 *	is first created, it is assigned an associated unique descriptor and 
 *	initial state. Therefore, each element of that must be defined by 
 *	means 'CREATE_FSM' macro. The queue descriptors are defined in 
 *	'fsmdata.h' file. 
 */

CREATE_FSMS_REGISTER
{
	CREATE_FSM(	&st00 )
};

#endif
