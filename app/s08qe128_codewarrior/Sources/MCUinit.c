/*
 * 	MCUInit.c
 *
 */


#include <MC9S08QE128.h>               /* I/O map for MC9S08QE128CLK */
#include "rti.h"


void 
MCU_init( void )
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
	ICSC2 = 0x36;                        /* Initialization of the ICS control register 2 */

	while(!ICSSC_OSCINIT) {              /* Wait until the initialization of the external crystal oscillator is completed */
	{asm sta SRS;}                      /* Reset watchdog counter */
	}

	/* ICSC1: CLKS=0,RDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
	ICSC1 = 0x1A;                        /* Initialization of the ICS control register 1 */

	while(ICSSC_IREFST!=0);
	while(ICSSC_CLKST!=0);

	/* ICSSC: DRST_DRS=2,DMX32=0 */
	ICSSC = (ICSSC & (unsigned char)~0x60) | (unsigned char)0x80; /* Initialization of the ICS status and control */

#if 1
	while((ICSSC & 0xC4) != 0x80) {      /* Wait until the FLL switches to High range DCO mode */
	{asm sta SRS;}                      /* Reset watchdog counter */
	}
#endif

	/* Common initialization of the CPU registers */
	/* SCGC2: DBG=1,FLS=1,IRQ=1,KBI=1,ACMP=1,RTC=1,SPI2=1,SPI1=1 */
	SCGC2 = 0xFF;                                      

	PTASE |= (unsigned char)0xDF;                               
	PTBSE = 0xFF;                                      
	PTCSE = 0xFF;                                      
	PTDSE = 0xFF;                                      
	PTESE = 0xFF;                                      
	PTFSE = 0xFF;                                      
	PTGSE = 0xFF;                                      
	PTHSE = 0xFF;                                      
	PTJSE = 0xFF;                                      
	PTADS = 0x00;                                      
	PTBDS = 0x00;                                      
	PTCDS = 0x00;                                      
	PTDDS = 0x00;                                      
	PTEDS = 0x00;                                      
	PTFDS = 0x00;                                      
	PTGDS = 0x00;                                      
	PTHDS = 0x00;                                     
	PTJDS = 0x00;

	/* SCGC1: TPM3=1,TPM2=1,TPM1=1,ADC=1,IIC2=1,IIC1=1,SCI2=1,SCI1=1 */
	SCGC1 = 0xFF;                                      

	/* ### Init_COP init code */
	SRS = 0xFF;                          /* Clear WatchDog counter */

	/* ### Init_RTC init code */

	/* RTCMOD: RTCMOD=0x20 */

	RTCMOD = 0x20;                                      

	/* RTCSC: RTIF=1,RTCLKS=2,RTIE=0,RTCPS=8 */
	RTCSC = 0xD8;                                

	/* ### Init_TPM init code */

	/* TPM1SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=0,PS2=0,PS1=0,PS0=0 */
	TPM1SC = 0x00;			/* Stop and reset counter */
	TPM1MOD = 0x00;			/* Period value setting */
	(void)(TPM1SC == 0);		/* Overflow int. flag clearing (first part) */

#if 0
	TPM1SC = 0x10;		/* clock source: 32KHz */
#else
	TPM1SC = 0x0f;		/* clock source: bus frequency */
#endif

	/* Flash setup */

	FSTAT = 0x30;
	FCDIV = 0x4F;
}
