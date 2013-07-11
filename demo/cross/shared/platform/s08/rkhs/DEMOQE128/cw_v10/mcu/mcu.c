/*
** ###################################################################
**     This code is generated by the Device Initialization Tool.
**     It is overwritten during code generation.
**     USER MODIFICATION ARE NOT PRESERVED IN THIS FILE.
**
**     Project   : s08qe128
**     Processor : MC9S08QE128CLK
**     Version   : Bean 01.001, Driver 01.03, CPU db: 3.00.000
**     Datasheet : MC9S08QE128RM Rev. 1.0 Draft F
**     Date/Time : 06/03/2009, 10:04 a.m.
**     Abstract  :
**         This module contains device initialization code 
**         for selected on-chip peripherals.
**     Contents  :
**         Function "MCU_init" initializes selected peripherals
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2006
**     UNIS, spol s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################
*/


#include "rkh.h"
#include "rkhtim.h"
#include "derivative.h"
#include "gpio.h"

void 
mcu_init( unsigned char tick_ms )
{
	/* ### MC9S08QE128_80 "Cpu" init code ... */
	/*  PE initialization code after reset */
	/* Common initialization of the write once registers */
	/* SOPT1: COPE=0,COPT=1,STOPE=0,RSTOPE=0,BKGDPE=1,RSTPE=1 */
	SOPT1 = 0x43;                                      
	/* SOPT2: COPCLKS=0,SPI1PS=0,ACIC2=0,IIC1PS=0,ACIC1=0 */
	SOPT2 = 0x00;                                      
	/* SPMSC1: LVDF=0,LVDACK=0,LVDIE=0,LVDRE=1,LVDSE=1,LVDE=0,BGBE=0 */
	SPMSC1 = 0x18;                                      
	/* SPMSC2: LPR=0,LPRS=0,LPWUI=0,PPDF=0,PPDACK=0,PPDE=1,PPDC=0 */
	SPMSC2 = 0x02;                                      
	/* SPMSC3: LVDV=0,LVWV=0,LVWIE=0 */
	SPMSC3 &= (unsigned char)~0x38;                     

	/*  System clock initialization */

	/* ICSC2: BDIV=0,RANGE=1,HGO=1,LP=0,EREFS=1,ERCLKEN=1,EREFSTEN=0 */
	ICSC2 = 0x36;    /* Initialization of the ICS control register 2 */

	/* Wait until the initialization of the external crystal oscillator is completed */
	while(!ICSSC_OSCINIT)
	{        
		{asm sta SRS;}   /* Reset watchdog counter */
	}

	/* ICSC1: CLKS=0,RDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
	ICSC1 = 0x1A;    /* Initialization of the ICS control register 1 */

	while(ICSSC_IREFST!=0);
	while(ICSSC_CLKST!=0);

	/* ICSSC: DRST_DRS=2,DMX32=0 */
	/* Initialization of the ICS status and control */
	ICSSC = (ICSSC & (unsigned char)~0x60) | (unsigned char)0x80; 

	/* Wait until the FLL switches to High range DCO mode */
	while((ICSSC & 0xC4) != 0x80)
	{     
		{asm sta SRS;}  /* Reset watchdog counter */
	}

	/* Common initialization of the CPU registers */
	/* SCGC2: DBG=1,FLS=1,IRQ=1,KBI=1,ACMP=1,RTC=1,SPI2=1,SPI1=1 */
	SCGC2 = 0xFF;                                      

	/* IO initialization */


	/* SCGC1: TPM3=1,TPM2=1,TPM1=1,ADC=1,IIC2=1,IIC1=1,SCI2=1,SCI1=1 */
	SCGC1 = 0xFF;                                      

	/* RTI: for system tick */ 
	RTCMOD = (unsigned char)(tick_ms - 1);
	RTCSC = 0x98; 	/* 1KHz low Power Oscilator, x1 Prescaler, RTI IRQ enable */

	/* TPM1:  for time stamp count */
	TPM1SC = 0x00;			/* Stop and reset counter */
	TPM1MOD = 0xFFFF;		/* Period value setting */
	(void)(TPM1SC == 0);	/* Overflow int. flag clearing (first part) */

	TPM1SC = 0x0f;			/* clock source: bus frequency */
}


/*
 * System Tick
 */

void
interrupt VectorNumber_Vrtc 
l_isr_tick( void )
{
	RTCSC_RTIF = 1;

	toggle_iopin( LED2 );

	RKH_TIM_TICK( &l_isr_tick );
}


/*
 * Time Stamp Counter 
 */

unsigned long time_stamp;

void
interrupt VectorNumber_Vtpm1ovf
isrVtpm1ovf( void )
{
	TPM1SC &= ~0x80;

	time_stamp += TPM1MOD;
}

unsigned long
get_ts( void )
{
	unsigned long t;

	t = TPM1CNT; 
	
	if( TPM1SC_TOF )
		t += TPM1MOD;
	
	return time_stamp + t;
}


