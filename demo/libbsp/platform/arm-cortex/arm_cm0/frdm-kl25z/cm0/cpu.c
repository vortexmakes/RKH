/**
 * cpu.c
 */

#include "bsp.h"
#include "cpu.h"
#include "rkh.h"


#if __cplusplus
extern "C" {
#endif
extern uint32_t __vector_table[];
extern unsigned long _estack;
extern void __thumb_startup(void);
#if __cplusplus
}
#endif


uint32_t mcu_coreclk_hz;
uint32_t mcu_busclk_hz;
uint32_t mcu_flshclk_hz;
uint32_t fll_clock_hz;
uint32_t uart0_clk_hz;

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


int
fee_dfactor( void )
{
	switch( MCG_C1_FRDIV_VAL )
	{
		case 0:
			return MCG_C2_RANGE0_B ? 32 : 1;
		case 1:
			return MCG_C2_RANGE0_B ? 64 : 2;
		case 2:
			return MCG_C2_RANGE0_B ? 128 : 4;
		case 3:
			return MCG_C2_RANGE0_B ? 256 : 8;
		case 4:
			return MCG_C2_RANGE0_B ? 512 : 16;
		case 5:
			return MCG_C2_RANGE0_B ? 1024 : 32;
		case 6:
			return MCG_C2_RANGE0_B ? 1280 : 64;
		case 7:
		default:
			return MCG_C2_RANGE0_B ? 1536 : 128;
	}
	

}


/*
 *	__init_hardware:
 *			Reset handler
 */
void __init_hardware()
{
	SCB_VTOR = (uint32_t)__vector_table; /* Set the interrupt vector table position */
	
	// Disable the Watchdog because it may reset the core before entering main().
	SIM_COPC = 0;
}


/*
 *     init_clocks:
 *         Initialization code for clock source.
 */
void init_clocks(void)
{
	/* System clock initialization */
	/* SIM_SCGC5: PORTD=1,PORTB=1,PORTA=1 */
	SIM_SCGC5 |= (uint32_t)0x1600UL;     /* Enable clock gate for ports to enable pin routing */
	/* SIM_CLKDIV1: OUTDIV1=0,OUTDIV4=1 */
	SIM_CLKDIV1 = (uint32_t)0x00010000UL; /* Update system prescalers */
	/* SIM_SOPT2: PLLFLLSEL=0 */
	SIM_SOPT2 &= (uint32_t)~0x00010000UL; /* Select FLL as a clock source for various peripherals */
	/* SIM_SOPT1: OSC32KSEL=3 */
	SIM_SOPT1 |= (uint32_t)0x000C0000UL; /* LPO 1kHz oscillator drives 32 kHz clock for various peripherals */
	/* SIM_SOPT2: TPMSRC=1 */
	SIM_SOPT2 = (uint32_t)((SIM_SOPT2 & (uint32_t)~0x02000000UL) | (uint32_t)0x01000000UL); /* Set the TPM clock */
	/* SIM_SOPT2: UART0SRC = 1 PLL/FLL clock source */
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);
	/* PORTA_PCR18: ISF=0,MUX=0 */
	PORTA_PCR18 &= (uint32_t)~0x01000700UL;                      
	/* PORTA_PCR19: ISF=0,MUX=0 */
	PORTA_PCR19 &= (uint32_t)~0x01000700UL;                      
	/* Switch to FEE Mode */
	/* MCG_C2: LOCRE0=0,RANGE0=2,HGO0=0,EREFS0=1,LP=0,IRCS=0 */
	MCG_C2 = (uint8_t)0x24U;                          
	/* OSC0_CR: ERCLKEN=0,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
	OSC0_CR = (uint8_t)0x00U;                          
	/* MCG_C1: CLKS=0,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
	MCG_C1 = (uint8_t)0x1AU;                          
	/* MCG_C4: DMX32=0,DRST_DRS=1 */
	MCG_C4 = (uint8_t)((MCG_C4 & (uint8_t)~(uint8_t)0xC0U) | (uint8_t)0x20U);
	/* MCG_C5: PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=0 */
	MCG_C5 = (uint8_t)0x00U;                          
	/* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
	MCG_C6 = (uint8_t)0x00U;                          
	while((MCG_S & MCG_S_IREFST_MASK) != 0x00U) { /* Check that the source of the FLL reference clock is the external reference clock. */
	}
	while((MCG_S & 0x0CU) != 0x00U) {    /* Wait until output of the FLL is selected */
	}
}


/*
 *     init_peripherals 
 *         Device initialization code for selected peripherals.
 */
void init_peripherals(void)
{
	/* Initialization of the SIM module */
	/* PORTA_PCR4: ISF=0,MUX=7 */
	PORTA_PCR4 = (uint32_t)((PORTA_PCR4 & (uint32_t)~0x01000000UL) | (uint32_t)0x0700UL);
	/* Initialization of the RCM module */
	/* RCM_RPFW: RSTFLTSEL=0 */
	RCM_RPFW &= (uint8_t)~(uint8_t)0x1FU;                           
	/* RCM_RPFC: RSTFLTSS=0,RSTFLTSRW=0 */
	RCM_RPFC &= (uint8_t)~(uint8_t)0x07U;                           
	/* Initialization of the PMC module */
	/* PMC_LVDSC1: LVDACK=1,LVDIE=0,LVDRE=1,LVDV=0 */
	PMC_LVDSC1 = (uint8_t)((PMC_LVDSC1 & (uint8_t)~(uint8_t)0x23U) | (uint8_t)0x50U);
	/* PMC_LVDSC2: LVWACK=1,LVWIE=0,LVWV=0 */
	PMC_LVDSC2 = (uint8_t)((PMC_LVDSC2 & (uint8_t)~(uint8_t)0x23U) | (uint8_t)0x40U);
	/* PMC_REGSC: BGEN=0,ACKISO=0,BGBE=0 */
	PMC_REGSC &= (uint8_t)~(uint8_t)0x19U;                           
	/* SMC_PMPROT: AVLP=0,ALLS=0,AVLLS=0 */
	SMC_PMPROT = (uint8_t)0x00U;         /* Setup Power mode protection register */
	/* Common initialization of the CPU registers */
	/* SCB_SHPR3: PRI_15=0 */
	SCB_SHPR3 &= (uint32_t)~0xFF000000UL;                      
	/* PORTB_PCR18: ISF=0,MUX=1 */
	PORTB_PCR18 = (uint32_t)((PORTB_PCR18 & (uint32_t)~0x01000600UL) | (uint32_t)0x0100UL);
	/* PORTB_PCR19: ISF=0,MUX=1 */
	PORTB_PCR19 = (uint32_t)((PORTB_PCR19 & (uint32_t)~0x01000600UL) | (uint32_t)0x0100UL);
	/* PORTD_PCR1: ISF=0,MUX=1 */
	PORTD_PCR1 = (uint32_t)((PORTD_PCR1 & (uint32_t)~0x01000600UL) | (uint32_t)0x0100UL);
	/* PORTA_PCR20: ISF=0,MUX=7 */
	PORTA_PCR20 = (uint32_t)((PORTA_PCR20 & (uint32_t)~0x01000000UL) | (uint32_t)0x0700UL);

	/* PORTA_PCR1: ISF=0,MUX=2 */ /* U0_RX */
	PORTA_PCR1 = (uint32_t)((PORTA_PCR1 & (uint32_t)~0x01000400UL) | (uint32_t)0x0200UL);
	/* PORTC_PCR1: ISF=0,MUX=2 */ /* U0_TX */
	PORTA_PCR2 = (uint32_t)((PORTA_PCR2 & (uint32_t)~0x01000400UL) | (uint32_t)0x0200UL);
	/* NVIC_IPR1: PRI_6=0 */
	NVIC_IPR1 &= (uint32_t)~0x00FF0000UL;                      
}



void
cpu_init( void )
{
	init_clocks();
	mcu_coreclk_hz = ( EXTAL / fee_dfactor() ) * fll_mfactor();
	mcu_busclk_hz = mcu_coreclk_hz / MCU_BUSCLK_DIV;
	mcu_flshclk_hz = mcu_coreclk_hz / MCU_FLSHCLK_DIV;
	fll_clock_hz = mcu_coreclk_hz;
	uart0_clk_hz = fll_clock_hz;
	init_peripherals();	
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
	RKH_TIM_TICK( 0 );
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


#define LPTMR_USE_IRCLK 0 
#define LPTMR_USE_LPOCLK 1
#define LPTMR_USE_ERCLK32 2
#define LPTMR_USE_OSCERCLK 3

void
cpu_tstmr_init ( void )
{
    SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;

	LPTMR0_CSR = 0;

    LPTMR0_PSR = ( LPTMR_PSR_PRESCALE(0) 
                 | LPTMR_PSR_PBYP_MASK
                 | LPTMR_PSR_PCS(LPTMR_USE_LPOCLK)); 
            
    LPTMR0_CMR = LPTMR_CMR_COMPARE(0xFFFF);  //Set compare value

    LPTMR0_CSR |= LPTMR_CSR_TEN_MASK;   //Turn on LPT and start counting
}


uint32_t
cpu_tstmr_read( void )
{
	LPTMR0_CNR = 0xFF;
    return LPTMR0_CNR;
}


/*
 *	Default_Handler
 *		Default interrupt handler
 */
void Default_Handler( void )
{
	__asm("bkpt");
}


/* Weak definitions of handlers point to Default_Handler if not implemented */
void NMI_Handler() __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler() __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler() __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler() __attribute__ ((weak, alias("Default_Handler")));
//void SysTick_Handler() __attribute__ ((weak, alias("Default_Handler")));
void DMA0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA2_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA3_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MCM_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void FTFL_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PMC_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void LLW_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void I2C0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void I2C1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void SPI0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART2_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void ADC0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void CMP0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void FTM0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void FTM1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void FTM2_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void RTC_Alarm_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void RTC_Seconds_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PIT_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void USBOTG_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DAC0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void TSI0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MCG_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void LPTimer_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PORTA_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PORTD_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));


/* The Interrupt Vector Table */
void (* const InterruptVector[])() __attribute__ ((section(".vectortable"))) = {
    /* Processor exceptions */
    (void(*)(void)) &_estack,
    __thumb_startup,
    NMI_Handler,
    HardFault_Handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    SVC_Handler,
    0,
    0,
    PendSV_Handler,
    isr_systick,

    /* Interrupts */
    DMA0_IRQHandler, /* DMA Channel 0 Transfer Complete and Error */
    DMA1_IRQHandler, /* DMA Channel 1 Transfer Complete and Error */
    DMA2_IRQHandler, /* DMA Channel 2 Transfer Complete and Error */
    DMA3_IRQHandler, /* DMA Channel 3 Transfer Complete and Error */
    MCM_IRQHandler, /* Normal Interrupt */
    FTFL_IRQHandler, /* FTFL Interrupt */
    PMC_IRQHandler, /* PMC Interrupt */
    LLW_IRQHandler, /* Low Leakage Wake-up */
    I2C0_IRQHandler, /* I2C0 interrupt */
    I2C1_IRQHandler, /* I2C1 interrupt */
    SPI0_IRQHandler, /* SPI0 Interrupt */
    SPI1_IRQHandler, /* SPI1 Interrupt */
    UART0_IRQHandler, /* UART0 Status and Error interrupt */
    UART1_IRQHandler, /* UART1 Status and Error interrupt */
    UART2_IRQHandler, /* UART2 Status and Error interrupt */
    ADC0_IRQHandler, /* ADC0 interrupt */
    CMP0_IRQHandler, /* CMP0 interrupt */
    FTM0_IRQHandler, /* FTM0 fault, overflow and channels interrupt */
    FTM1_IRQHandler, /* FTM1 fault, overflow and channels interrupt */
    FTM2_IRQHandler, /* FTM2 fault, overflow and channels interrupt */
    RTC_Alarm_IRQHandler, /* RTC Alarm interrupt */
    RTC_Seconds_IRQHandler, /* RTC Seconds interrupt */
    PIT_IRQHandler, /* PIT timer all channels interrupt */
    Default_Handler, /* Reserved interrupt 39/23 */
    USBOTG_IRQHandler, /* USB interrupt */
    DAC0_IRQHandler, /* DAC0 interrupt */
    TSI0_IRQHandler, /* TSI0 Interrupt */
    MCG_IRQHandler, /* MCG Interrupt */
    LPTimer_IRQHandler, /* LPTimer interrupt */
    Default_Handler, /* Reserved interrupt 45/29 */
    PORTA_IRQHandler, /* Port A interrupt */
    PORTD_IRQHandler /* Port D interrupt */
};


