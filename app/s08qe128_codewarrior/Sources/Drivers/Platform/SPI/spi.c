/*
 *	spi.c
 *
 *	Routines for the SPI peripherical management.
 *
 *	Programmer: Darío S. Baliña.
 *	Date : 26/05/06.
 */

#include "derivative.h"
#include "mytypes.h"
#include "spi.h"

void
spi_init(void)
{
#if 0
  /* ### Init_SPI init code */
  /* SPI1C1: SPIE=0,SPE=0,SPTIE=0,MSTR=0,CPOL=0,CPHA=0,SSOE=0,LSBFE=0 */
  SPI1C1 = 0x00;                       /* Disable the SPI1 module clearing the SPRF flag */
  /* SPI1C2: MODFEN=0,BIDIROE=0,SPISWAI=0,SPC0=0 */
  SPI1C2 = 0x00;                                      
  /* SPI1BR: SPPR2=0,SPPR1=0,SPPR0=0,SPR2=0,SPR1=0,SPR0=0 */
  SPI1BR = 0x00;                                      
  (void)(SPI1S == 0);                  /* Dummy read of the SPI1S registr to clear the MODF flag */
  /* SPI1C1: SPIE=0,SPE=1,SPTIE=0,MSTR=1,CPOL=0,CPHA=0,SSOE=0,LSBFE=0 */
  SPI1C1 = 0x50;                                      
                                      
#endif

#ifdef __GB60__
	SPI1C1_MSTR = 1;
	SPI1C1_CPOL = 1;
	SPI1C1_CPHA = 1;
	SPI1C1_SSOE = 0;
	SPI1C1_LSBFE = 0;
	
	SPI1C2_MODFEN = 0;
	
	SPI1BR = SPI_PRESCAL_X4;
	
	SPI1C1_SPE = 1;
#endif
	
	
}

MUInt
spi_xfer( MUInt byte )
{
	while( !SPI1S_SPTEF );

	SPI1D = byte;

	while( !SPI1S_SPRF );
	
	return SPI1D;
}


