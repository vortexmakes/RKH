/**
 * cpu.h
 */

#ifndef __CPU_H__
#define __CPU_H__

#include <MK60D10.h>
#include "arm_cm4.h"

#define RTCXTAL				32768	

#define IRQ_NONCORE_NUMBER_BASE		(INT_SysTick + 1)
#define IRQ_NUMBER(x)				(x-IRQ_NONCORE_NUMBER_BASE)

#define MCG_C4_DRST_DRS_VAL		((MCG_C4 & MCG_C4_DRST_DRS_MASK)>>MCG_C4_DRST_DRS_SHIFT)
#define MCG_C4_DMX32			((MCG_C4 & MCG_C4_DMX32_MASK)!=0)

#define MCU_CORECLK_DIV	(((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK)>>SIM_CLKDIV1_OUTDIV1_SHIFT)+1)
#define MCU_BUSCLK_DIV	(((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV2_MASK)>>SIM_CLKDIV1_OUTDIV2_SHIFT)+1)
#define MCU_FBUSCLK_DIV	(((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV3_MASK)>>SIM_CLKDIV1_OUTDIV3_SHIFT)+1)
#define MCU_FLSHCLK_DIV	(((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK)>>SIM_CLKDIV1_OUTDIV4_SHIFT)+1)


#define MCU_TS_RATE_HZ			(95977472) // mcu_coreclk_hz

extern uint32_t mcu_coreclk_hz;
extern uint32_t mcu_busclk_hz;
extern uint32_t mcu_fbusclk_hz;
extern uint32_t mcu_flshclk_hz;

void cpu_init( void );

void systick_init( uint32_t tick_hz );
void isr_systick( void );

void cpu_tstmr_init ( void );
uint32_t cpu_tstmr_read( void );

void cpu_reset( void );

#endif
