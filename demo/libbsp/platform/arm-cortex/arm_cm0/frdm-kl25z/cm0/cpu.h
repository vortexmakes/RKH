/**
 * cpu.h
 */

#ifndef __CPU_H__
#define __CPU_H__

#include "arm_cm0.h"
#include "derivative.h"

#define EXTAL						8000000UL	

#define IRQ_NONCORE_NUMBER_BASE		(INT_SysTick + 1)
#define IRQ_NUMBER(x)				(x-IRQ_NONCORE_NUMBER_BASE)

#define MCG_C4_DRST_DRS_VAL		((MCG_C4 & MCG_C4_DRST_DRS_MASK)>>MCG_C4_DRST_DRS_SHIFT)
#define MCG_C4_DMX32			((MCG_C4 & MCG_C4_DMX32_MASK)!=0)
#define MCG_C1_FRDIV_VAL		((MCG_C1 & MCG_C1_FRDIV_MASK)>>MCG_C1_FRDIV_SHIFT)
#define MCG_C2_RANGE0_B			((MCG_C2 & MCG_C2_RANGE0_MASK)!=0)

#define MCU_CORECLK_DIV	(((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK)>>SIM_CLKDIV1_OUTDIV1_SHIFT)+1)
#define MCU_BUSCLK_DIV	(((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK)>>SIM_CLKDIV1_OUTDIV4_SHIFT)+1)
#define MCU_FLSHCLK_DIV	MCU_BUSCLK_DIV

#define MCU_TS_RATE_HZ			(40000000)

extern uint32_t mcu_coreclk_hz;
extern uint32_t mcu_busclk_hz;
extern uint32_t mcu_flshclk_hz;
extern uint32_t uart0_clk_hz;

void cpu_init( void );

void systick_init( uint32_t tick_hz );
void isr_systick( void );

void cpu_tstmr_init ( void );
uint32_t cpu_tstmr_read( void );

void cpu_reset( void );

#endif
