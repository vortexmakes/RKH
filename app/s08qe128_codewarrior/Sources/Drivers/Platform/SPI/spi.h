/*
 *	spi.h
 *
 *	Routines for the SPI uC´s peripherical managment.
 *
 *	Programmer: Darío S. Baliña.
 *	Date : 26/05/06.
 */

#ifndef __SPI_H__
#define __SPI_H__

#include "mytypes.h"

#define MASTER			0x10
#define EDGE_AT_START	0x04
#define ACTIVE_LOW		0x08
#define AUTO_CS			0x02

#define SPI_PRESCAL_X1		0x00
#define SPI_PRESCAL_X2		0x10
#define SPI_PRESCAL_X3		0x20
#define SPI_PRESCAL_X4		0x30
#define SPI_PRESCAL_X5		0x40
#define SPI_PRESCAL_X6		0x50
#define SPI_PRESCAL_X7		0x60
#define SPI_PRESCAL_X8		0x70

#define SPI_DIVISOR_X2		0x00
#define SPI_DIVISOR_X4		0x01
#define SPI_DIVISOR_X8		0x02
#define SPI_DIVISOR_X16		0x03
#define SPI_DIVISOR_X32		0x04
#define SPI_DIVISOR_X64		0x05
#define SPI_DIVISOR_X128	0x06
#define SPI_DIVISOR_X256	0x07

void spi_init(void);

MUInt spi_xfer( MUInt byte );

#endif
