/*
 *	myact.c
 */


#include <stdio.h>
#include "rkhsm.h"
#include "my.h"
#include "myevt.h"

	
static MYHDATA_T *pd;


/*
 *	Defines HSM init function
 */

void 
my_init( const struct rkh_t *ph )
{
	pd = rkh_get_data( ph );
	pd->x = pd->y = 0;
}


/*
 *	Defines state entry functions
 */


void
set_x_1( const struct rkh_t *ph )
{
	pd = rkh_get_data( ph );
	pd->x = 1;
}


void
set_x_2( const struct rkh_t *ph )
{
	pd = rkh_get_data( ph );
	pd->x = 2;
}


void
set_x_3( const struct rkh_t *ph )
{
	pd = rkh_get_data( ph );
	pd->x = 3;
}


void
set_y_0( const struct rkh_t *ph )
{
	pd = rkh_get_data( ph );
	pd->y = 0;
}


/*
 *	Defines state exit functions
 */

void 
dummy_exit( const struct rkh_t *ph )
{
}


/*
 *	Defines state preprocessor functions
 */



/*
 *	Defines transition action functions
 */


void
set_y_2( const struct rkh_t *ph, RKHEVT_T *pe )
{
	pd = rkh_get_data( ph );
	pd->y = 2;
	printf( "action: %s()\n", __FUNCTION__ );
	printf( "event.ts = %05d\n", (( MYEVT_T* )pe )->ts );
	printf( "data.x = %02d - data.y = %02d\n", pd->x, pd->y );
}


void
set_y_1( const struct rkh_t *ph, RKHEVT_T *pe )
{
	pd = rkh_get_data( ph );
	pd->y = 1;
	printf( "action: %s()\n", __FUNCTION__ );
	printf( "event.ts = %05d\n", (( MYEVT_T* )pe )->ts );
	printf( "data.x = %02d - data.y = %02d\n", pd->x, pd->y );
}


void
dummy_act( const struct rkh_t *ph, RKHEVT_T *pe )
{
}


/*
 *	Defines branch functions
 */


RKHE_T
get_y( const struct rkh_t *ph, RKHEVT_T *pe )
{
	pd = rkh_get_data( ph );

	switch( pd->y )
	{
		case 1:
			return ( RKHE_T )Y1;
		case 2:
			return ( RKHE_T )Y2;
		default:
			return ( RKHE_T )pd->y;
	}
}


RKHE_T
get_x( const struct rkh_t *ph, RKHEVT_T *pe )
{
	pd = rkh_get_data( ph );

	if( pd->x == 2 || pd->x == 3 )
		return ( RKHE_T )X2_OR_X3;
	else
		return ( RKHE_T )X1;
}


/*
 *	Defines guard functions
 */


HUInt
x_equal_1( const struct rkh_t *ph, RKHEVT_T *pe )
{
	pd = rkh_get_data( ph );

	return pd->x == 1 ? RKH_GTRUE : RKH_GFALSE;
}
