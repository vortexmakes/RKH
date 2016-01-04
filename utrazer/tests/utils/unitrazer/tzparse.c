/*
 *	file: trazer.c
 */


#include "rkhtype.h"
#include "rkhtrc.h"
#include "tzparse.h"
#include <stdio.h>

static rui32_t lastnseq;
rui16_t TSTAMP_TICK_HZ;


#define CTE( te )	((const struct tre_t*)(te))

#define PARSER_MAX_SIZE_BUF			512
#define TRZ_RKH_CFG_TRC_NSEQ_EN		0
#define TRZ_RKH_CFG_TRC_CHK_EN		1


static rui8_t *trb;				
static char fmt[ 1024 ];

static rui8_t state = PARSER_WFLAG;
static unsigned char tr[ PARSER_MAX_SIZE_BUF ], *ptr, trix;
static char symstr[ 16 ];
static unsigned long curr_tstamp;


#define start_assemble()    \
        {                   \
            trb = tr + 1;   \
        }


static
unsigned long
assemble( int size )
{
	int n, sh;
	unsigned long d;

	for( d = 0, n = size, sh = 0; n; --n, sh += 8  )
		d |= ( unsigned long )( *trb++ << sh );
	return d;
}


static
char *
assemble_str( void  )
{
	char *p;

	for( p = symstr; *trb != '\0'; ++p, ++trb )
		*p = *trb;
	
	*p = '\0';
	return symstr;
}


static
void
parser_init( void )
{
	ptr = tr;
	trix = 0;
}


static
void
parser_collect( rui8_t d )
{
	if( ++trix > PARSER_MAX_SIZE_BUF )
	{
		state = PARSER_WFLAG;
		return;
	}
	*ptr++ = d;
}


static
int
parser_chk( void )
{
	rui8_t *p, chk;
	int i;
	if( TRZ_RKH_CFG_TRC_CHK_EN == 1 )
	{
		for( chk = 0, p = tr, i = trix; i--; ++p )
			chk = (rui8_t)( chk + *p );
		return chk == 0;	
	}
	return 1;
}


static
void
utFail( UtrzProcessOut *p )
{
    char *s;

    p->status = UT_PROC_FAIL;

    start_assemble();
   	p->line = assemble( 4 );
    s = assemble_str();

    strncpy( p->msg, s, UT_SIZEOF_MSG  );
}


static
void
utSuccess( UtrzProcessOut *p )
{
    p->status = UT_PROC_SUCCESS;
}

static
void
utProcFail( UtrzProcessOut *p )
{
    p->status = UT_PROC_FAIL;
    p->line = 0;
    strncpy( p->msg, "Trace stream checksum Error", UT_SIZEOF_MSG );
}


static
void
parser( UtrzProcessOut *p )
{
    switch( tr[0] )
    {
        case RKH_TE_UT_FAIL:
            utFail( p );
            break;
        case RKH_TE_UT_SUCCESS:
            utSuccess( p );
            break;
		default:
			break;
    }
}


void
trazer_init( void )
{
	parser_init();
	state = PARSER_COLLECT;
}


void
trazer_parse( rui8_t d, UtrzProcessOut *p )
{
	switch( state )
	{
		case PARSER_WFLAG:
			if( d == RKH_FLG )
			{
				parser_init();
				state = PARSER_COLLECT;
			}
			break;
		case PARSER_COLLECT:
			if( d == RKH_FLG )
			{
				if( trix > 0 )
				{
					if( parser_chk() )
					{
						parser( p );
					}
					else
					{
                        utProcFail( p );
					}
				}

				parser_init();
			}
			else if( d == RKH_ESC )
				state = PARSER_ESCAPING;
			else
				parser_collect( d );
			break;
		case PARSER_ESCAPING:
			if( d == RKH_FLG )
			{
				parser_init();
				state = PARSER_COLLECT;
			}
			else
			{
				parser_collect( (rui8_t)(d ^ RKH_XOR) );
				state = PARSER_COLLECT;
			}
			break;
		default:
			break;
	}
}



