/*
 * swhdl.c
 */

//#include "fsl_gpio_driver.h"
#include "board.h"
#include "swhdl.h"


MUInt
rawsw1( void )
{
	return GPIO_DRV_ReadPinInput(kGpioSW2);
}

MUInt
rawsw2( void )
{
	return GPIO_DRV_ReadPinInput(kGpioSW3);
}
