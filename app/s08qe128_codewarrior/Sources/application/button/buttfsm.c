/*
 *	buttfsm.c
 */


#include "mytypes.h"
#include "event.h"
#include "evtdata.h"
#include "fsm.h"
#include "fsmdata.h"
#include "buttfsma.h"
#include "buttfsm.h"
#include <stdlib.h>


CREATE_TRANSITION( trans_st00 )
{
	{ 	FSM_ANY,		&pst3,		NULL,			check_super_state	}
};

CREATE_TRANSITION( trans_st0 )
{
	{	BUTTON0,		&pst0,		set_leds,		check_super_state	},
	{ 	FSM_ANY,		&st0,		NULL,			NULL				}
};

CREATE_TRANSITION( trans_pst0 )
{
	{	SSTATE0_COND,	&pst1,		set_leds0,		check_super_state	},
	{	SSTATE1_COND,	&st1,		set_leds1,		NULL				},
	{	ELSE,			NULL,		NULL,			NULL				}
};

CREATE_TRANSITION( trans_pst1 )
{
	{	SSTATE0_COND,	&pst2,		set_leds0,		check_super_state	},
	{	SSTATE1_COND,	&st1,		set_leds1,		NULL				},
	{	ELSE,			NULL,		NULL,			NULL				}
};

CREATE_TRANSITION( trans_pst2 )
{
	{	SSTATE0_COND,	&st1,		set_leds0,		NULL				},
	{	SSTATE1_COND,	&st2,		set_leds1,		NULL				},
	{	ELSE,			NULL,		NULL,			NULL				}
};

CREATE_TRANSITION( trans_pst3 )
{
	{	SSTATE0_COND,	&pst0,		set_leds0,		check_super_state	},
	{	SSTATE1_COND,	&st2,		set_leds1,		NULL				},
	{	ELSE,			NULL,		NULL,			NULL				}
};

CREATE_TRANSITION( trans_st1 )
{
	{	BUTTON0,		&st3,		go_back_state1,	NULL				},
	{	BUTTON1,		&st2,		set_leds,		NULL				},
	{	FSM_ANY,		&st1,		NULL,			NULL 				}
};

CREATE_TRANSITION( trans_st2 )
{
	{	BUTTON0,		&st3,		go_back_state2,	NULL				},
	{	BUTTON1,		&st1,		system_crash,	NULL				},
	{	FSM_ANY,		&st2,		NULL,			NULL 				}
};

CREATE_TRANSITION( trans_st3 )
{
	{	BUTTON1,		&hst0,		set_leds,		NULL				},
	{	FSM_ANY,		&st3,		NULL,			NULL 				}
};

CREATE_TRANSITION( trans_hst0 )
{
	{	FSM_ANY,		NULL,		NULL,			NULL 				}
};


CREATE_STATE( st00,	trans_st00,	NULL,	INITIAL_STATE,	0 );
CREATE_STATE( st0, 	trans_st0, 	NULL,	NORMAL_STATE, 	1 );
CREATE_STATE( st1, 	trans_st1, 	NULL,	NORMAL_STATE, 	2 );
CREATE_STATE( st2,	trans_st2, 	NULL,	NORMAL_STATE, 	3 );
CREATE_STATE( st3,	trans_st3, 	NULL,	NORMAL_STATE, 	4 );
CREATE_STATE( pst0, trans_pst0,	NULL, 	COND_STATE, 	5 );
CREATE_STATE( hst0, trans_hst0,	NULL, 	HISTORY_STATE, 	6 );
CREATE_STATE( pst1, trans_pst1,	NULL, 	COND_STATE, 	7 );
CREATE_STATE( pst2, trans_pst2,	NULL, 	COND_STATE, 	8 );
CREATE_STATE( pst3, trans_pst3,	NULL, 	COND_STATE, 	9 );
