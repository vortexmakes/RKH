/*
 * swhdl.h
 *
 * Minimal debouncing switch handler.
 * hardware access.
 *
 */

#ifndef __SWHDL_H__
#define __SWHDL_H__

#include "switch.h"
#include "fsl_gpio_driver.h"

MUInt rawsw1( void );
MUInt rawsw2( void );

#endif
