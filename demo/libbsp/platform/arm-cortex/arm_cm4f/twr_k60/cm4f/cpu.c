/**
 * cpu.c
 */

#include "bsp.h"
#include "cpu.h"
#include "MCUinit.h"
#include "rkh.h"

uint32_t mcu_coreclk_hz;
uint32_t mcu_busclk_hz;
uint32_t mcu_fbusclk_hz;
uint32_t mcu_flshclk_hz;

#if defined( RKH_USE_TRC_SENDER )
static rui8_t l_isr_tick;
#endif

static
int
fll_mfactor( void )
{
	switch( MCG_C4_DRST_DRS_VAL )
	{
		case 0:
			return MCG_C4_DMX32 ? 732 : 640;
		case 1:
			return MCG_C4_DMX32 ? 1464 : 1280;
		case 2:
			return MCG_C4_DMX32 ? 2197 : 1920;
		case 3:
			return MCG_C4_DMX32 ? 2929 : 2560;
		default:
			return MCG_C4_DMX32 ? 732 : 640;
	}
}

void
cpu_init( void )
{
	MCU_init();

	mcu_coreclk_hz = ( RTCXTAL * fll_mfactor() ) / MCU_CORECLK_DIV;
	mcu_busclk_hz = mcu_coreclk_hz / MCU_BUSCLK_DIV;
	mcu_fbusclk_hz = mcu_coreclk_hz / MCU_FBUSCLK_DIV;
	mcu_flshclk_hz = mcu_coreclk_hz / MCU_FLSHCLK_DIV;
}


void
systick_init( uint32_t tick_hz )
{
  /* SYST_CSR: COUNTFLAG=0,CLKSOURCE=0,TICKINT=0,ENABLE=0 */
  SYST_CSR = (uint32_t)0x00UL;                  
  /* SYST_RVR: RELOAD=0x000176E8 */
  SYST_RVR = mcu_coreclk_hz / tick_hz; //(uint32_t)0x000EA510UL;                  
  /* SYST_CVR: CURRENT=0 */
  SYST_CVR = (uint32_t)0x00UL;                  
  /* SYST_CSR: COUNTFLAG=0,CLKSOURCE=1,TICKINT=1,ENABLE=1 */
  SYST_CSR = (uint32_t)0x07UL;                  

  /* SCB_SHPR3: PRI_15=0x30 */
  SCB_SHPR3 |= ( ( KERNEL_IRQ_PRIO << 4 ) << 24 );
  
  Cpu_SetBASEPRI(KERNEL_IRQ_PRIO);
}


void
isr_systick( void )
{
	RKH_TIM_TICK( &l_isr_tick );
}

void
cpu_reset( void )
{
    uint32_t temp_AIRCR=SCB_AIRCR;

	temp_AIRCR = SCB_AIRCR & SCB_AIRCR_VECTKEY_MASK;
	temp_AIRCR |= SCB_AIRCR_VECTKEY(0xFA05);
	SCB_AIRCR = temp_AIRCR;
  	while(1)
  		;
}

#define  DEM_CR_TRCENA        (1 << 24)
#define  DWT_CR_CYCCNTENA     (1 <<  0)


void
cpu_tstmr_init ( void )
{
	DEMCR		|= DEM_CR_TRCENA;
	DWT_CYCCNT	= 0u;
	DWT_CTRL	|= DWT_CR_CYCCNTENA;
}


uint32_t
cpu_tstmr_read( void )
{
    return DWT_CYCCNT;
}

