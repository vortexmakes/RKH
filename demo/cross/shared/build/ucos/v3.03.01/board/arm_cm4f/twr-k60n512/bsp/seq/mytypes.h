/*
 * 	mytypes.h
 */

#ifndef __MYTYPES_H__
#define __MYTYPES_H__

typedef unsigned long	ulong;
typedef unsigned char	uchar;
typedef signed char		schar;
typedef unsigned int	uint;
typedef unsigned short	ushort;

#ifdef __TINY_PROC__

typedef uchar			MUInt;
typedef schar			MInt;

#else

typedef uint			MUInt;
typedef int				MInt;

#endif

#endif
