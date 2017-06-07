/* Based on CPU DB MC9S08QE128_80, version 3.00.066 (RegistersPrg V2.32) */
/*
** ###################################################################
**     Filename  : mc9s08qe128.h
**     Processor : MC9S08QE128CLK
**     FileFormat: V2.32
**     DataSheet : MC9S08QE128RM Rev. 2 6/2007
**     Compiler  : CodeWarrior compiler
**     Date/Time : 5.10.2010, 13:55
**     Abstract  :
**         This header implements the mapping of I/O devices.
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
**
**     CPU Registers Revisions:
**               - none
**
**     File-Format-Revisions:
**      - 22.01.2007, V2.12 :
**               - Changes have not affected this file (because they are related to another family)
**      - 01.03.2007, V2.13 :
**               - Flash commands constants values converted to HEX format
**      - 02.03.2007, V2.14 :
**               - Interrupt vector numbers added into .H, see VectorNumber_*
**      - 26.03.2007, V2.15 :
**               - Changes have not affected this file (because they are related to another family)
**      - 10.05.2007, V2.16 :
**               - Fixed flash commands definition for ColdFireV1 assembler (equ -> .equ)
**      - 05.06.2007, V2.17 :
**               - Changes have not affected this file (because they are related to another family)
**      - 19.07.2007, V2.18 :
**               - Improved number of blanked lines inside register structures
**      - 06.08.2007, V2.19 :
**               - CPUDB revisions generated ahead of the file-format revisions.
**      - 11.09.2007, V2.20 :
**               - Added comment about initialization of unbonded pins.
**      - 02.01.2008, V2.21 :
**               - Changes have not affected this file (because they are related to another family)
**      - 13.02.2008, V2.22 :
**               - Changes have not affected this file (because they are related to another family)
**      - 20.02.2008, V2.23 :
**               - Changes have not affected this file (because they are related to another family)
**      - 03.07.2008, V2.24 :
**               - Added support for bits with name starting with number (like "1HZ")
**      - 28.11.2008, V2.25 :
**               - StandBy RAM array declaration for ANSI-C added
**      - 1.12.2008, V2.26 :
**               - Duplication of bit (or bit-group) name with register name is not marked as a problem, if register is internal only and it is not displayed in I/O map.
**      - 17.3.2009, V2.27 :
**               - Merged bit-group is not generated, if the name matches with another bit name in the register
**      - 6.4.2009, V2.28 :
**               - Fixed generation of merged bits for bit-groups with a digit at the end, if group-name is defined in CPUDB
**      - 3.8.2009, V2.29 :
**               - If there is just one bits group matching register name, single bits are not generated
**      - 10.9.2009, V2.30 :
**               - Fixed generation of registers arrays.
**      - 15.10.2009, V2.31 :
**               - HCS08 family: Bits and bit-groups are published for 16-bit registers: 8-bit overlay registers are required.
**      - 18.05.2010, V2.32 :
**               - MISRA compliance: U/UL suffixes added to all numbers (_MASK,_BITNUM and addresses)
**
**     Not all general-purpose I/O pins are available on all packages or on all mask sets of a specific
**     derivative device. To avoid extra current drain from floating input pins, the user’s reset
**     initialization routine in the application program must either enable on-chip pull-up devices
**     or change the direction of unconnected pins to outputs so the pins do not float.
** ###################################################################
*/

#ifndef _MC9S08QE128_H
#define _MC9S08QE128_H

/*lint -save  -e950 -esym(960,18.4) -e46 -esym(961,19.7) Disable MISRA rule (1.1,18.4,6.4,19.7) checking. */
/* Types definition */
typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned long dword;
typedef unsigned long dlong[2];

/* Watchdog reset macro */
#ifndef __RESET_WATCHDOG
#ifdef _lint
  #define __RESET_WATCHDOG()  /* empty */
#else
  #define __RESET_WATCHDOG() {asm sta SRS;}
#endif
#endif /* __RESET_WATCHDOG */

#define REG_BASE 0x0000                /* Base address for the I/O register block */


#pragma MESSAGE DISABLE C1106 /* WARNING C1106: Non-standard bitfield type */

/**************** interrupt vector numbers ****************/
#define VectorNumber_Vtpm3ovf           31U
#define VectorNumber_Vtpm3ch5           30U
#define VectorNumber_Vtpm3ch4           29U
#define VectorNumber_Vtpm3ch3           28U
#define VectorNumber_Vtpm3ch2           27U
#define VectorNumber_Vtpm3ch1           26U
#define VectorNumber_Vtpm3ch0           25U
#define VectorNumber_Vrtc               24U
#define VectorNumber_Vsci2tx            23U
#define VectorNumber_Vsci2rx            22U
#define VectorNumber_Vsci2err           21U
#define VectorNumber_Vacmpx             20U
#define VectorNumber_Vadc               19U
#define VectorNumber_Vkeyboard          18U
#define VectorNumber_Viicx              17U
#define VectorNumber_Vsci1tx            16U
#define VectorNumber_Vsci1rx            15U
#define VectorNumber_Vsci1err           14U
#define VectorNumber_Vspi1              13U
#define VectorNumber_Vspi2              12U
#define VectorNumber_Vtpm2ovf           11U
#define VectorNumber_Vtpm2ch2           10U
#define VectorNumber_Vtpm2ch1           9U
#define VectorNumber_Vtpm2ch0           8U
#define VectorNumber_Vtpm1ovf           7U
#define VectorNumber_Vtpm1ch2           6U
#define VectorNumber_Vtpm1ch1           5U
#define VectorNumber_Vtpm1ch0           4U
#define VectorNumber_Vlvd               3U
#define VectorNumber_Virq               2U
#define VectorNumber_Vswi               1U
#define VectorNumber_Vreset             0U

/**************** interrupt vector table ****************/
#define Vtpm3ovf                        0xFFC0U
#define Vtpm3ch5                        0xFFC2U
#define Vtpm3ch4                        0xFFC4U
#define Vtpm3ch3                        0xFFC6U
#define Vtpm3ch2                        0xFFC8U
#define Vtpm3ch1                        0xFFCAU
#define Vtpm3ch0                        0xFFCCU
#define Vrtc                            0xFFCEU
#define Vsci2tx                         0xFFD0U
#define Vsci2rx                         0xFFD2U
#define Vsci2err                        0xFFD4U
#define Vacmpx                          0xFFD6U
#define Vadc                            0xFFD8U
#define Vkeyboard                       0xFFDAU
#define Viicx                           0xFFDCU
#define Vsci1tx                         0xFFDEU
#define Vsci1rx                         0xFFE0U
#define Vsci1err                        0xFFE2U
#define Vspi1                           0xFFE4U
#define Vspi2                           0xFFE6U
#define Vtpm2ovf                        0xFFE8U
#define Vtpm2ch2                        0xFFEAU
#define Vtpm2ch1                        0xFFECU
#define Vtpm2ch0                        0xFFEEU
#define Vtpm1ovf                        0xFFF0U
#define Vtpm1ch2                        0xFFF2U
#define Vtpm1ch1                        0xFFF4U
#define Vtpm1ch0                        0xFFF6U
#define Vlvd                            0xFFF8U
#define Virq                            0xFFFAU
#define Vswi                            0xFFFCU
#define Vreset                          0xFFFEU

/**************** registers I/O map ****************/

/*** PTAD - Port A Data Register; 0x00000000 ***/
typedef union {
  byte Byte;
  struct {
    byte PTAD0       :1;                                       /* Port A Data Register Bit 0 */
    byte PTAD1       :1;                                       /* Port A Data Register Bit 1 */
    byte PTAD2       :1;                                       /* Port A Data Register Bit 2 */
    byte PTAD3       :1;                                       /* Port A Data Register Bit 3 */
    byte PTAD4       :1;                                       /* Port A Data Register Bit 4 */
    byte PTAD5       :1;                                       /* Port A Data Register Bit 5 */
    byte PTAD6       :1;                                       /* Port A Data Register Bit 6 */
    byte PTAD7       :1;                                       /* Port A Data Register Bit 7 */
  } Bits;
} PTADSTR;
extern volatile PTADSTR _PTAD @0x00000000;
#define PTAD                            _PTAD.Byte
#define PTAD_PTAD0                      _PTAD.Bits.PTAD0
#define PTAD_PTAD1                      _PTAD.Bits.PTAD1
#define PTAD_PTAD2                      _PTAD.Bits.PTAD2
#define PTAD_PTAD3                      _PTAD.Bits.PTAD3
#define PTAD_PTAD4                      _PTAD.Bits.PTAD4
#define PTAD_PTAD5                      _PTAD.Bits.PTAD5
#define PTAD_PTAD6                      _PTAD.Bits.PTAD6
#define PTAD_PTAD7                      _PTAD.Bits.PTAD7

#define PTAD_PTAD0_MASK                 1U
#define PTAD_PTAD1_MASK                 2U
#define PTAD_PTAD2_MASK                 4U
#define PTAD_PTAD3_MASK                 8U
#define PTAD_PTAD4_MASK                 16U
#define PTAD_PTAD5_MASK                 32U
#define PTAD_PTAD6_MASK                 64U
#define PTAD_PTAD7_MASK                 128U


/*** PTADD - Port A Data Direction Register; 0x00000001 ***/
typedef union {
  byte Byte;
  struct {
    byte PTADD0      :1;                                       /* Data Direction for Port A Bit 0 */
    byte PTADD1      :1;                                       /* Data Direction for Port A Bit 1 */
    byte PTADD2      :1;                                       /* Data Direction for Port A Bit 2 */
    byte PTADD3      :1;                                       /* Data Direction for Port A Bit 3 */
    byte PTADD4      :1;                                       /* Data Direction for Port A Bit 4 */
    byte PTADD5      :1;                                       /* Data Direction for Port A Bit 5 */
    byte PTADD6      :1;                                       /* Data Direction for Port A Bit 6 */
    byte PTADD7      :1;                                       /* Data Direction for Port A Bit 7 */
  } Bits;
} PTADDSTR;
extern volatile PTADDSTR _PTADD @0x00000001;
#define PTADD                           _PTADD.Byte
#define PTADD_PTADD0                    _PTADD.Bits.PTADD0
#define PTADD_PTADD1                    _PTADD.Bits.PTADD1
#define PTADD_PTADD2                    _PTADD.Bits.PTADD2
#define PTADD_PTADD3                    _PTADD.Bits.PTADD3
#define PTADD_PTADD4                    _PTADD.Bits.PTADD4
#define PTADD_PTADD5                    _PTADD.Bits.PTADD5
#define PTADD_PTADD6                    _PTADD.Bits.PTADD6
#define PTADD_PTADD7                    _PTADD.Bits.PTADD7

#define PTADD_PTADD0_MASK               1U
#define PTADD_PTADD1_MASK               2U
#define PTADD_PTADD2_MASK               4U
#define PTADD_PTADD3_MASK               8U
#define PTADD_PTADD4_MASK               16U
#define PTADD_PTADD5_MASK               32U
#define PTADD_PTADD6_MASK               64U
#define PTADD_PTADD7_MASK               128U


/*** PTBD - Port B Data Register; 0x00000002 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBD0       :1;                                       /* Port B Data Register Bit 0 */
    byte PTBD1       :1;                                       /* Port B Data Register Bit 1 */
    byte PTBD2       :1;                                       /* Port B Data Register Bit 2 */
    byte PTBD3       :1;                                       /* Port B Data Register Bit 3 */
    byte PTBD4       :1;                                       /* Port B Data Register Bit 4 */
    byte PTBD5       :1;                                       /* Port B Data Register Bit 5 */
    byte PTBD6       :1;                                       /* Port B Data Register Bit 6 */
    byte PTBD7       :1;                                       /* Port B Data Register Bit 7 */
  } Bits;
} PTBDSTR;
extern volatile PTBDSTR _PTBD @0x00000002;
#define PTBD                            _PTBD.Byte
#define PTBD_PTBD0                      _PTBD.Bits.PTBD0
#define PTBD_PTBD1                      _PTBD.Bits.PTBD1
#define PTBD_PTBD2                      _PTBD.Bits.PTBD2
#define PTBD_PTBD3                      _PTBD.Bits.PTBD3
#define PTBD_PTBD4                      _PTBD.Bits.PTBD4
#define PTBD_PTBD5                      _PTBD.Bits.PTBD5
#define PTBD_PTBD6                      _PTBD.Bits.PTBD6
#define PTBD_PTBD7                      _PTBD.Bits.PTBD7

#define PTBD_PTBD0_MASK                 1U
#define PTBD_PTBD1_MASK                 2U
#define PTBD_PTBD2_MASK                 4U
#define PTBD_PTBD3_MASK                 8U
#define PTBD_PTBD4_MASK                 16U
#define PTBD_PTBD5_MASK                 32U
#define PTBD_PTBD6_MASK                 64U
#define PTBD_PTBD7_MASK                 128U


/*** PTBDD - Port B Data Direction Register; 0x00000003 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBDD0      :1;                                       /* Data Direction for Port B Bit 0 */
    byte PTBDD1      :1;                                       /* Data Direction for Port B Bit 1 */
    byte PTBDD2      :1;                                       /* Data Direction for Port B Bit 2 */
    byte PTBDD3      :1;                                       /* Data Direction for Port B Bit 3 */
    byte PTBDD4      :1;                                       /* Data Direction for Port B Bit 4 */
    byte PTBDD5      :1;                                       /* Data Direction for Port B Bit 5 */
    byte PTBDD6      :1;                                       /* Data Direction for Port B Bit 6 */
    byte PTBDD7      :1;                                       /* Data Direction for Port B Bit 7 */
  } Bits;
} PTBDDSTR;
extern volatile PTBDDSTR _PTBDD @0x00000003;
#define PTBDD                           _PTBDD.Byte
#define PTBDD_PTBDD0                    _PTBDD.Bits.PTBDD0
#define PTBDD_PTBDD1                    _PTBDD.Bits.PTBDD1
#define PTBDD_PTBDD2                    _PTBDD.Bits.PTBDD2
#define PTBDD_PTBDD3                    _PTBDD.Bits.PTBDD3
#define PTBDD_PTBDD4                    _PTBDD.Bits.PTBDD4
#define PTBDD_PTBDD5                    _PTBDD.Bits.PTBDD5
#define PTBDD_PTBDD6                    _PTBDD.Bits.PTBDD6
#define PTBDD_PTBDD7                    _PTBDD.Bits.PTBDD7

#define PTBDD_PTBDD0_MASK               1U
#define PTBDD_PTBDD1_MASK               2U
#define PTBDD_PTBDD2_MASK               4U
#define PTBDD_PTBDD3_MASK               8U
#define PTBDD_PTBDD4_MASK               16U
#define PTBDD_PTBDD5_MASK               32U
#define PTBDD_PTBDD6_MASK               64U
#define PTBDD_PTBDD7_MASK               128U


/*** PTCD - Port C Data Register; 0x00000004 ***/
typedef union {
  byte Byte;
  struct {
    byte PTCD0       :1;                                       /* Port C Data Register Bit 0 */
    byte PTCD1       :1;                                       /* Port C Data Register Bit 1 */
    byte PTCD2       :1;                                       /* Port C Data Register Bit 2 */
    byte PTCD3       :1;                                       /* Port C Data Register Bit 3 */
    byte PTCD4       :1;                                       /* Port C Data Register Bit 4 */
    byte PTCD5       :1;                                       /* Port C Data Register Bit 5 */
    byte PTCD6       :1;                                       /* Port C Data Register Bit 6 */
    byte PTCD7       :1;                                       /* Port C Data Register Bit 7 */
  } Bits;
} PTCDSTR;
extern volatile PTCDSTR _PTCD @0x00000004;
#define PTCD                            _PTCD.Byte
#define PTCD_PTCD0                      _PTCD.Bits.PTCD0
#define PTCD_PTCD1                      _PTCD.Bits.PTCD1
#define PTCD_PTCD2                      _PTCD.Bits.PTCD2
#define PTCD_PTCD3                      _PTCD.Bits.PTCD3
#define PTCD_PTCD4                      _PTCD.Bits.PTCD4
#define PTCD_PTCD5                      _PTCD.Bits.PTCD5
#define PTCD_PTCD6                      _PTCD.Bits.PTCD6
#define PTCD_PTCD7                      _PTCD.Bits.PTCD7

#define PTCD_PTCD0_MASK                 1U
#define PTCD_PTCD1_MASK                 2U
#define PTCD_PTCD2_MASK                 4U
#define PTCD_PTCD3_MASK                 8U
#define PTCD_PTCD4_MASK                 16U
#define PTCD_PTCD5_MASK                 32U
#define PTCD_PTCD6_MASK                 64U
#define PTCD_PTCD7_MASK                 128U


/*** PTCDD - Port C Data Direction Register; 0x00000005 ***/
typedef union {
  byte Byte;
  struct {
    byte PTCDD0      :1;                                       /* Data Direction for Port C Bit 0 */
    byte PTCDD1      :1;                                       /* Data Direction for Port C Bit 1 */
    byte PTCDD2      :1;                                       /* Data Direction for Port C Bit 2 */
    byte PTCDD3      :1;                                       /* Data Direction for Port C Bit 3 */
    byte PTCDD4      :1;                                       /* Data Direction for Port C Bit 4 */
    byte PTCDD5      :1;                                       /* Data Direction for Port C Bit 5 */
    byte PTCDD6      :1;                                       /* Data Direction for Port C Bit 6 */
    byte PTCDD7      :1;                                       /* Data Direction for Port C Bit 7 */
  } Bits;
} PTCDDSTR;
extern volatile PTCDDSTR _PTCDD @0x00000005;
#define PTCDD                           _PTCDD.Byte
#define PTCDD_PTCDD0                    _PTCDD.Bits.PTCDD0
#define PTCDD_PTCDD1                    _PTCDD.Bits.PTCDD1
#define PTCDD_PTCDD2                    _PTCDD.Bits.PTCDD2
#define PTCDD_PTCDD3                    _PTCDD.Bits.PTCDD3
#define PTCDD_PTCDD4                    _PTCDD.Bits.PTCDD4
#define PTCDD_PTCDD5                    _PTCDD.Bits.PTCDD5
#define PTCDD_PTCDD6                    _PTCDD.Bits.PTCDD6
#define PTCDD_PTCDD7                    _PTCDD.Bits.PTCDD7

#define PTCDD_PTCDD0_MASK               1U
#define PTCDD_PTCDD1_MASK               2U
#define PTCDD_PTCDD2_MASK               4U
#define PTCDD_PTCDD3_MASK               8U
#define PTCDD_PTCDD4_MASK               16U
#define PTCDD_PTCDD5_MASK               32U
#define PTCDD_PTCDD6_MASK               64U
#define PTCDD_PTCDD7_MASK               128U


/*** PTDD - Port D Data Register; 0x00000006 ***/
typedef union {
  byte Byte;
  struct {
    byte PTDD0       :1;                                       /* Port D Data Register Bit 0 */
    byte PTDD1       :1;                                       /* Port D Data Register Bit 1 */
    byte PTDD2       :1;                                       /* Port D Data Register Bit 2 */
    byte PTDD3       :1;                                       /* Port D Data Register Bit 3 */
    byte PTDD4       :1;                                       /* Port D Data Register Bit 4 */
    byte PTDD5       :1;                                       /* Port D Data Register Bit 5 */
    byte PTDD6       :1;                                       /* Port D Data Register Bit 6 */
    byte PTDD7       :1;                                       /* Port D Data Register Bit 7 */
  } Bits;
} PTDDSTR;
extern volatile PTDDSTR _PTDD @0x00000006;
#define PTDD                            _PTDD.Byte
#define PTDD_PTDD0                      _PTDD.Bits.PTDD0
#define PTDD_PTDD1                      _PTDD.Bits.PTDD1
#define PTDD_PTDD2                      _PTDD.Bits.PTDD2
#define PTDD_PTDD3                      _PTDD.Bits.PTDD3
#define PTDD_PTDD4                      _PTDD.Bits.PTDD4
#define PTDD_PTDD5                      _PTDD.Bits.PTDD5
#define PTDD_PTDD6                      _PTDD.Bits.PTDD6
#define PTDD_PTDD7                      _PTDD.Bits.PTDD7

#define PTDD_PTDD0_MASK                 1U
#define PTDD_PTDD1_MASK                 2U
#define PTDD_PTDD2_MASK                 4U
#define PTDD_PTDD3_MASK                 8U
#define PTDD_PTDD4_MASK                 16U
#define PTDD_PTDD5_MASK                 32U
#define PTDD_PTDD6_MASK                 64U
#define PTDD_PTDD7_MASK                 128U


/*** PTDDD - Port D Data Direction Register; 0x00000007 ***/
typedef union {
  byte Byte;
  struct {
    byte PTDDD0      :1;                                       /* Data Direction for Port D Bit 0 */
    byte PTDDD1      :1;                                       /* Data Direction for Port D Bit 1 */
    byte PTDDD2      :1;                                       /* Data Direction for Port D Bit 2 */
    byte PTDDD3      :1;                                       /* Data Direction for Port D Bit 3 */
    byte PTDDD4      :1;                                       /* Data Direction for Port D Bit 4 */
    byte PTDDD5      :1;                                       /* Data Direction for Port D Bit 5 */
    byte PTDDD6      :1;                                       /* Data Direction for Port D Bit 6 */
    byte PTDDD7      :1;                                       /* Data Direction for Port D Bit 7 */
  } Bits;
} PTDDDSTR;
extern volatile PTDDDSTR _PTDDD @0x00000007;
#define PTDDD                           _PTDDD.Byte
#define PTDDD_PTDDD0                    _PTDDD.Bits.PTDDD0
#define PTDDD_PTDDD1                    _PTDDD.Bits.PTDDD1
#define PTDDD_PTDDD2                    _PTDDD.Bits.PTDDD2
#define PTDDD_PTDDD3                    _PTDDD.Bits.PTDDD3
#define PTDDD_PTDDD4                    _PTDDD.Bits.PTDDD4
#define PTDDD_PTDDD5                    _PTDDD.Bits.PTDDD5
#define PTDDD_PTDDD6                    _PTDDD.Bits.PTDDD6
#define PTDDD_PTDDD7                    _PTDDD.Bits.PTDDD7

#define PTDDD_PTDDD0_MASK               1U
#define PTDDD_PTDDD1_MASK               2U
#define PTDDD_PTDDD2_MASK               4U
#define PTDDD_PTDDD3_MASK               8U
#define PTDDD_PTDDD4_MASK               16U
#define PTDDD_PTDDD5_MASK               32U
#define PTDDD_PTDDD6_MASK               64U
#define PTDDD_PTDDD7_MASK               128U


/*** PTED - Port E Data Register; 0x00000008 ***/
typedef union {
  byte Byte;
  struct {
    byte PTED0       :1;                                       /* Port E Data Register Bit 0 */
    byte PTED1       :1;                                       /* Port E Data Register Bit 1 */
    byte PTED2       :1;                                       /* Port E Data Register Bit 2 */
    byte PTED3       :1;                                       /* Port E Data Register Bit 3 */
    byte PTED4       :1;                                       /* Port E Data Register Bit 4 */
    byte PTED5       :1;                                       /* Port E Data Register Bit 5 */
    byte PTED6       :1;                                       /* Port E Data Register Bit 6 */
    byte PTED7       :1;                                       /* Port E Data Register Bit 7 */
  } Bits;
} PTEDSTR;
extern volatile PTEDSTR _PTED @0x00000008;
#define PTED                            _PTED.Byte
#define PTED_PTED0                      _PTED.Bits.PTED0
#define PTED_PTED1                      _PTED.Bits.PTED1
#define PTED_PTED2                      _PTED.Bits.PTED2
#define PTED_PTED3                      _PTED.Bits.PTED3
#define PTED_PTED4                      _PTED.Bits.PTED4
#define PTED_PTED5                      _PTED.Bits.PTED5
#define PTED_PTED6                      _PTED.Bits.PTED6
#define PTED_PTED7                      _PTED.Bits.PTED7

#define PTED_PTED0_MASK                 1U
#define PTED_PTED1_MASK                 2U
#define PTED_PTED2_MASK                 4U
#define PTED_PTED3_MASK                 8U
#define PTED_PTED4_MASK                 16U
#define PTED_PTED5_MASK                 32U
#define PTED_PTED6_MASK                 64U
#define PTED_PTED7_MASK                 128U


/*** PTEDD - Port E Data Direction Register; 0x00000009 ***/
typedef union {
  byte Byte;
  struct {
    byte PTEDD0      :1;                                       /* Data Direction for Port E Bit 0 */
    byte PTEDD1      :1;                                       /* Data Direction for Port E Bit 1 */
    byte PTEDD2      :1;                                       /* Data Direction for Port E Bit 2 */
    byte PTEDD3      :1;                                       /* Data Direction for Port E Bit 3 */
    byte PTEDD4      :1;                                       /* Data Direction for Port E Bit 4 */
    byte PTEDD5      :1;                                       /* Data Direction for Port E Bit 5 */
    byte PTEDD6      :1;                                       /* Data Direction for Port E Bit 6 */
    byte PTEDD7      :1;                                       /* Data Direction for Port E Bit 7 */
  } Bits;
} PTEDDSTR;
extern volatile PTEDDSTR _PTEDD @0x00000009;
#define PTEDD                           _PTEDD.Byte
#define PTEDD_PTEDD0                    _PTEDD.Bits.PTEDD0
#define PTEDD_PTEDD1                    _PTEDD.Bits.PTEDD1
#define PTEDD_PTEDD2                    _PTEDD.Bits.PTEDD2
#define PTEDD_PTEDD3                    _PTEDD.Bits.PTEDD3
#define PTEDD_PTEDD4                    _PTEDD.Bits.PTEDD4
#define PTEDD_PTEDD5                    _PTEDD.Bits.PTEDD5
#define PTEDD_PTEDD6                    _PTEDD.Bits.PTEDD6
#define PTEDD_PTEDD7                    _PTEDD.Bits.PTEDD7

#define PTEDD_PTEDD0_MASK               1U
#define PTEDD_PTEDD1_MASK               2U
#define PTEDD_PTEDD2_MASK               4U
#define PTEDD_PTEDD3_MASK               8U
#define PTEDD_PTEDD4_MASK               16U
#define PTEDD_PTEDD5_MASK               32U
#define PTEDD_PTEDD6_MASK               64U
#define PTEDD_PTEDD7_MASK               128U


/*** PTFD - Port F Data Register; 0x0000000A ***/
typedef union {
  byte Byte;
  struct {
    byte PTFD0       :1;                                       /* Port F Data Register Bit 0 */
    byte PTFD1       :1;                                       /* Port F Data Register Bit 1 */
    byte PTFD2       :1;                                       /* Port F Data Register Bit 2 */
    byte PTFD3       :1;                                       /* Port F Data Register Bit 3 */
    byte PTFD4       :1;                                       /* Port F Data Register Bit 4 */
    byte PTFD5       :1;                                       /* Port F Data Register Bit 5 */
    byte PTFD6       :1;                                       /* Port F Data Register Bit 6 */
    byte PTFD7       :1;                                       /* Port F Data Register Bit 7 */
  } Bits;
} PTFDSTR;
extern volatile PTFDSTR _PTFD @0x0000000A;
#define PTFD                            _PTFD.Byte
#define PTFD_PTFD0                      _PTFD.Bits.PTFD0
#define PTFD_PTFD1                      _PTFD.Bits.PTFD1
#define PTFD_PTFD2                      _PTFD.Bits.PTFD2
#define PTFD_PTFD3                      _PTFD.Bits.PTFD3
#define PTFD_PTFD4                      _PTFD.Bits.PTFD4
#define PTFD_PTFD5                      _PTFD.Bits.PTFD5
#define PTFD_PTFD6                      _PTFD.Bits.PTFD6
#define PTFD_PTFD7                      _PTFD.Bits.PTFD7

#define PTFD_PTFD0_MASK                 1U
#define PTFD_PTFD1_MASK                 2U
#define PTFD_PTFD2_MASK                 4U
#define PTFD_PTFD3_MASK                 8U
#define PTFD_PTFD4_MASK                 16U
#define PTFD_PTFD5_MASK                 32U
#define PTFD_PTFD6_MASK                 64U
#define PTFD_PTFD7_MASK                 128U


/*** PTFDD - Port F Data Direction Register; 0x0000000B ***/
typedef union {
  byte Byte;
  struct {
    byte PTFDD0      :1;                                       /* Data Direction for Port F Bit 0 */
    byte PTFDD1      :1;                                       /* Data Direction for Port F Bit 1 */
    byte PTFDD2      :1;                                       /* Data Direction for Port F Bit 2 */
    byte PTFDD3      :1;                                       /* Data Direction for Port F Bit 3 */
    byte PTFDD4      :1;                                       /* Data Direction for Port F Bit 4 */
    byte PTFDD5      :1;                                       /* Data Direction for Port F Bit 5 */
    byte PTFDD6      :1;                                       /* Data Direction for Port F Bit 6 */
    byte PTFDD7      :1;                                       /* Data Direction for Port F Bit 7 */
  } Bits;
} PTFDDSTR;
extern volatile PTFDDSTR _PTFDD @0x0000000B;
#define PTFDD                           _PTFDD.Byte
#define PTFDD_PTFDD0                    _PTFDD.Bits.PTFDD0
#define PTFDD_PTFDD1                    _PTFDD.Bits.PTFDD1
#define PTFDD_PTFDD2                    _PTFDD.Bits.PTFDD2
#define PTFDD_PTFDD3                    _PTFDD.Bits.PTFDD3
#define PTFDD_PTFDD4                    _PTFDD.Bits.PTFDD4
#define PTFDD_PTFDD5                    _PTFDD.Bits.PTFDD5
#define PTFDD_PTFDD6                    _PTFDD.Bits.PTFDD6
#define PTFDD_PTFDD7                    _PTFDD.Bits.PTFDD7

#define PTFDD_PTFDD0_MASK               1U
#define PTFDD_PTFDD1_MASK               2U
#define PTFDD_PTFDD2_MASK               4U
#define PTFDD_PTFDD3_MASK               8U
#define PTFDD_PTFDD4_MASK               16U
#define PTFDD_PTFDD5_MASK               32U
#define PTFDD_PTFDD6_MASK               64U
#define PTFDD_PTFDD7_MASK               128U


/*** KBI1SC - KBI1 Status and Control Register; 0x0000000C ***/
typedef union {
  byte Byte;
  struct {
    byte KBIMOD      :1;                                       /* Keyboard Detection Mode */
    byte KBIE        :1;                                       /* Keyboard Interrupt Enable */
    byte KBACK       :1;                                       /* Keyboard Interrupt Acknowledge */
    byte KBF         :1;                                       /* Keyboard Interrupt Flag */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} KBI1SCSTR;
extern volatile KBI1SCSTR _KBI1SC @0x0000000C;
#define KBI1SC                          _KBI1SC.Byte
#define KBI1SC_KBIMOD                   _KBI1SC.Bits.KBIMOD
#define KBI1SC_KBIE                     _KBI1SC.Bits.KBIE
#define KBI1SC_KBACK                    _KBI1SC.Bits.KBACK
#define KBI1SC_KBF                      _KBI1SC.Bits.KBF

#define KBI1SC_KBIMOD_MASK              1U
#define KBI1SC_KBIE_MASK                2U
#define KBI1SC_KBACK_MASK               4U
#define KBI1SC_KBF_MASK                 8U


/*** KBI1PE - KBI1 Pin Enable Register; 0x0000000D ***/
typedef union {
  byte Byte;
  struct {
    byte KBIPE0      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 0 */
    byte KBIPE1      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 1 */
    byte KBIPE2      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 2 */
    byte KBIPE3      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 3 */
    byte KBIPE4      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 4 */
    byte KBIPE5      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 5 */
    byte KBIPE6      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 6 */
    byte KBIPE7      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 7 */
  } Bits;
} KBI1PESTR;
extern volatile KBI1PESTR _KBI1PE @0x0000000D;
#define KBI1PE                          _KBI1PE.Byte
#define KBI1PE_KBIPE0                   _KBI1PE.Bits.KBIPE0
#define KBI1PE_KBIPE1                   _KBI1PE.Bits.KBIPE1
#define KBI1PE_KBIPE2                   _KBI1PE.Bits.KBIPE2
#define KBI1PE_KBIPE3                   _KBI1PE.Bits.KBIPE3
#define KBI1PE_KBIPE4                   _KBI1PE.Bits.KBIPE4
#define KBI1PE_KBIPE5                   _KBI1PE.Bits.KBIPE5
#define KBI1PE_KBIPE6                   _KBI1PE.Bits.KBIPE6
#define KBI1PE_KBIPE7                   _KBI1PE.Bits.KBIPE7

#define KBI1PE_KBIPE0_MASK              1U
#define KBI1PE_KBIPE1_MASK              2U
#define KBI1PE_KBIPE2_MASK              4U
#define KBI1PE_KBIPE3_MASK              8U
#define KBI1PE_KBIPE4_MASK              16U
#define KBI1PE_KBIPE5_MASK              32U
#define KBI1PE_KBIPE6_MASK              64U
#define KBI1PE_KBIPE7_MASK              128U


/*** KBI1ES - KBI1 Edge Select Register; 0x0000000E ***/
typedef union {
  byte Byte;
  struct {
    byte KBEDG0      :1;                                       /* Keyboard Edge Select Bit 0 */
    byte KBEDG1      :1;                                       /* Keyboard Edge Select Bit 1 */
    byte KBEDG2      :1;                                       /* Keyboard Edge Select Bit 2 */
    byte KBEDG3      :1;                                       /* Keyboard Edge Select Bit 3 */
    byte KBEDG4      :1;                                       /* Keyboard Edge Select Bit 4 */
    byte KBEDG5      :1;                                       /* Keyboard Edge Select Bit 5 */
    byte KBEDG6      :1;                                       /* Keyboard Edge Select Bit 6 */
    byte KBEDG7      :1;                                       /* Keyboard Edge Select Bit 7 */
  } Bits;
} KBI1ESSTR;
extern volatile KBI1ESSTR _KBI1ES @0x0000000E;
#define KBI1ES                          _KBI1ES.Byte
#define KBI1ES_KBEDG0                   _KBI1ES.Bits.KBEDG0
#define KBI1ES_KBEDG1                   _KBI1ES.Bits.KBEDG1
#define KBI1ES_KBEDG2                   _KBI1ES.Bits.KBEDG2
#define KBI1ES_KBEDG3                   _KBI1ES.Bits.KBEDG3
#define KBI1ES_KBEDG4                   _KBI1ES.Bits.KBEDG4
#define KBI1ES_KBEDG5                   _KBI1ES.Bits.KBEDG5
#define KBI1ES_KBEDG6                   _KBI1ES.Bits.KBEDG6
#define KBI1ES_KBEDG7                   _KBI1ES.Bits.KBEDG7

#define KBI1ES_KBEDG0_MASK              1U
#define KBI1ES_KBEDG1_MASK              2U
#define KBI1ES_KBEDG2_MASK              4U
#define KBI1ES_KBEDG3_MASK              8U
#define KBI1ES_KBEDG4_MASK              16U
#define KBI1ES_KBEDG5_MASK              32U
#define KBI1ES_KBEDG6_MASK              64U
#define KBI1ES_KBEDG7_MASK              128U


/*** IRQSC - Interrupt request status and control register; 0x0000000F ***/
typedef union {
  byte Byte;
  struct {
    byte IRQMOD      :1;                                       /* IRQ Detection Mode */
    byte IRQIE       :1;                                       /* IRQ Interrupt Enable */
    byte IRQACK      :1;                                       /* IRQ Acknowledge */
    byte IRQF        :1;                                       /* IRQ Flag */
    byte IRQPE       :1;                                       /* IRQ Pin Enable */
    byte IRQEDG      :1;                                       /* IRQ Edge Select */
    byte IRQPDD      :1;                                       /* IRQ Pull Device Disable */
    byte             :1; 
  } Bits;
} IRQSCSTR;
extern volatile IRQSCSTR _IRQSC @0x0000000F;
#define IRQSC                           _IRQSC.Byte
#define IRQSC_IRQMOD                    _IRQSC.Bits.IRQMOD
#define IRQSC_IRQIE                     _IRQSC.Bits.IRQIE
#define IRQSC_IRQACK                    _IRQSC.Bits.IRQACK
#define IRQSC_IRQF                      _IRQSC.Bits.IRQF
#define IRQSC_IRQPE                     _IRQSC.Bits.IRQPE
#define IRQSC_IRQEDG                    _IRQSC.Bits.IRQEDG
#define IRQSC_IRQPDD                    _IRQSC.Bits.IRQPDD

#define IRQSC_IRQMOD_MASK               1U
#define IRQSC_IRQIE_MASK                2U
#define IRQSC_IRQACK_MASK               4U
#define IRQSC_IRQF_MASK                 8U
#define IRQSC_IRQPE_MASK                16U
#define IRQSC_IRQEDG_MASK               32U
#define IRQSC_IRQPDD_MASK               64U


/*** ADCSC1 - Status and Control Register 1; 0x00000010 ***/
typedef union {
  byte Byte;
  struct {
    byte ADCH0       :1;                                       /* Input Channel Select Bit 0 */
    byte ADCH1       :1;                                       /* Input Channel Select Bit 1 */
    byte ADCH2       :1;                                       /* Input Channel Select Bit 2 */
    byte ADCH3       :1;                                       /* Input Channel Select Bit 3 */
    byte ADCH4       :1;                                       /* Input Channel Select Bit 4 */
    byte ADCO        :1;                                       /* Continuous Conversion Enable - ADCO is used to enable continuous conversions */
    byte AIEN        :1;                                       /* Interrupt Enable - AIEN is used to enable conversion complete interrupts. When COCO becomes set while AIEN is high, an interrupt is asserted */
    byte COCO        :1;                                       /* Conversion Complete Flag */
  } Bits;
  struct {
    byte grpADCH :5;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} ADCSC1STR;
extern volatile ADCSC1STR _ADCSC1 @0x00000010;
#define ADCSC1                          _ADCSC1.Byte
#define ADCSC1_ADCH0                    _ADCSC1.Bits.ADCH0
#define ADCSC1_ADCH1                    _ADCSC1.Bits.ADCH1
#define ADCSC1_ADCH2                    _ADCSC1.Bits.ADCH2
#define ADCSC1_ADCH3                    _ADCSC1.Bits.ADCH3
#define ADCSC1_ADCH4                    _ADCSC1.Bits.ADCH4
#define ADCSC1_ADCO                     _ADCSC1.Bits.ADCO
#define ADCSC1_AIEN                     _ADCSC1.Bits.AIEN
#define ADCSC1_COCO                     _ADCSC1.Bits.COCO
#define ADCSC1_ADCH                     _ADCSC1.MergedBits.grpADCH

#define ADCSC1_ADCH0_MASK               1U
#define ADCSC1_ADCH1_MASK               2U
#define ADCSC1_ADCH2_MASK               4U
#define ADCSC1_ADCH3_MASK               8U
#define ADCSC1_ADCH4_MASK               16U
#define ADCSC1_ADCO_MASK                32U
#define ADCSC1_AIEN_MASK                64U
#define ADCSC1_COCO_MASK                128U
#define ADCSC1_ADCH_MASK                31U
#define ADCSC1_ADCH_BITNUM              0U


/*** ADCSC2 - Status and Control Register 2; 0x00000011 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte ACFGT       :1;                                       /* Compare Function Greater Than Enable */
    byte ACFE        :1;                                       /* Compare Function Enable - ACFE is used to enable the compare function */
    byte ADTRG       :1;                                       /* Conversion Trigger Select-ADTRG is used to select the type of trigger to be used for initiating a conversion */
    byte ADACT       :1;                                       /* Conversion Active - ADACT indicates that a conversion is in progress. ADACT is set when a conversion is initiated and cleared when a conversion is completed or aborted */
  } Bits;
} ADCSC2STR;
extern volatile ADCSC2STR _ADCSC2 @0x00000011;
#define ADCSC2                          _ADCSC2.Byte
#define ADCSC2_ACFGT                    _ADCSC2.Bits.ACFGT
#define ADCSC2_ACFE                     _ADCSC2.Bits.ACFE
#define ADCSC2_ADTRG                    _ADCSC2.Bits.ADTRG
#define ADCSC2_ADACT                    _ADCSC2.Bits.ADACT

#define ADCSC2_ACFGT_MASK               16U
#define ADCSC2_ACFE_MASK                32U
#define ADCSC2_ADTRG_MASK               64U
#define ADCSC2_ADACT_MASK               128U


/*** ADCR - Data Result Register; 0x00000012 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** ADCRH - Data Result High Register; 0x00000012 ***/
    union {
      byte Byte;
      struct {
        byte ADR8        :1;                                       /* ADC Result Data Bit 8 */
        byte ADR9        :1;                                       /* ADC Result Data Bit 9 */
        byte ADR10       :1;                                       /* ADC Result Data Bit 10 */
        byte ADR11       :1;                                       /* ADC Result Data Bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpADR_8 :4;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } ADCRHSTR;
    #define ADCRH                       _ADCR.Overlap_STR.ADCRHSTR.Byte
    #define ADCRH_ADR8                  _ADCR.Overlap_STR.ADCRHSTR.Bits.ADR8
    #define ADCRH_ADR9                  _ADCR.Overlap_STR.ADCRHSTR.Bits.ADR9
    #define ADCRH_ADR10                 _ADCR.Overlap_STR.ADCRHSTR.Bits.ADR10
    #define ADCRH_ADR11                 _ADCR.Overlap_STR.ADCRHSTR.Bits.ADR11
    #define ADCRH_ADR_8                 _ADCR.Overlap_STR.ADCRHSTR.MergedBits.grpADR_8
    #define ADCRH_ADR                   ADCRH_ADR_8
    
    #define ADCRH_ADR8_MASK             1U
    #define ADCRH_ADR9_MASK             2U
    #define ADCRH_ADR10_MASK            4U
    #define ADCRH_ADR11_MASK            8U
    #define ADCRH_ADR_8_MASK            15U
    #define ADCRH_ADR_8_BITNUM          0U
    

    /*** ADCRL - Data Result Low Register; 0x00000013 ***/
    union {
      byte Byte;
      struct {
        byte ADR0        :1;                                       /* ADC Result Data Bit 0 */
        byte ADR1        :1;                                       /* ADC Result Data Bit 1 */
        byte ADR2        :1;                                       /* ADC Result Data Bit 2 */
        byte ADR3        :1;                                       /* ADC Result Data Bit 3 */
        byte ADR4        :1;                                       /* ADC Result Data Bit 4 */
        byte ADR5        :1;                                       /* ADC Result Data Bit 5 */
        byte ADR6        :1;                                       /* ADC Result Data Bit 6 */
        byte ADR7        :1;                                       /* ADC Result Data Bit 7 */
      } Bits;
    } ADCRLSTR;
    #define ADCRL                       _ADCR.Overlap_STR.ADCRLSTR.Byte
    #define ADCRL_ADR0                  _ADCR.Overlap_STR.ADCRLSTR.Bits.ADR0
    #define ADCRL_ADR1                  _ADCR.Overlap_STR.ADCRLSTR.Bits.ADR1
    #define ADCRL_ADR2                  _ADCR.Overlap_STR.ADCRLSTR.Bits.ADR2
    #define ADCRL_ADR3                  _ADCR.Overlap_STR.ADCRLSTR.Bits.ADR3
    #define ADCRL_ADR4                  _ADCR.Overlap_STR.ADCRLSTR.Bits.ADR4
    #define ADCRL_ADR5                  _ADCR.Overlap_STR.ADCRLSTR.Bits.ADR5
    #define ADCRL_ADR6                  _ADCR.Overlap_STR.ADCRLSTR.Bits.ADR6
    #define ADCRL_ADR7                  _ADCR.Overlap_STR.ADCRLSTR.Bits.ADR7
    
    #define ADCRL_ADR0_MASK             1U
    #define ADCRL_ADR1_MASK             2U
    #define ADCRL_ADR2_MASK             4U
    #define ADCRL_ADR3_MASK             8U
    #define ADCRL_ADR4_MASK             16U
    #define ADCRL_ADR5_MASK             32U
    #define ADCRL_ADR6_MASK             64U
    #define ADCRL_ADR7_MASK             128U
    
  } Overlap_STR;

} ADCRSTR;
extern volatile ADCRSTR _ADCR @0x00000012;
#define ADCR                            _ADCR.Word


/*** ADCCV - Compare Value Register; 0x00000014 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** ADCCVH - Compare Value High Register; 0x00000014 ***/
    union {
      byte Byte;
      struct {
        byte ADCV8       :1;                                       /* Compare Function Value 8 */
        byte ADCV9       :1;                                       /* Compare Function Value 9 */
        byte ADCV10      :1;                                       /* Compare Function Value 10 */
        byte ADCV11      :1;                                       /* Compare Function Value 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpADCV_8 :4;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } ADCCVHSTR;
    #define ADCCVH                      _ADCCV.Overlap_STR.ADCCVHSTR.Byte
    #define ADCCVH_ADCV8                _ADCCV.Overlap_STR.ADCCVHSTR.Bits.ADCV8
    #define ADCCVH_ADCV9                _ADCCV.Overlap_STR.ADCCVHSTR.Bits.ADCV9
    #define ADCCVH_ADCV10               _ADCCV.Overlap_STR.ADCCVHSTR.Bits.ADCV10
    #define ADCCVH_ADCV11               _ADCCV.Overlap_STR.ADCCVHSTR.Bits.ADCV11
    #define ADCCVH_ADCV_8               _ADCCV.Overlap_STR.ADCCVHSTR.MergedBits.grpADCV_8
    #define ADCCVH_ADCV                 ADCCVH_ADCV_8
    
    #define ADCCVH_ADCV8_MASK           1U
    #define ADCCVH_ADCV9_MASK           2U
    #define ADCCVH_ADCV10_MASK          4U
    #define ADCCVH_ADCV11_MASK          8U
    #define ADCCVH_ADCV_8_MASK          15U
    #define ADCCVH_ADCV_8_BITNUM        0U
    

    /*** ADCCVL - Compare Value Low Register; 0x00000015 ***/
    union {
      byte Byte;
      struct {
        byte ADCV0       :1;                                       /* Compare Function Value 0 */
        byte ADCV1       :1;                                       /* Compare Function Value 1 */
        byte ADCV2       :1;                                       /* Compare Function Value 2 */
        byte ADCV3       :1;                                       /* Compare Function Value 3 */
        byte ADCV4       :1;                                       /* Compare Function Value 4 */
        byte ADCV5       :1;                                       /* Compare Function Value 5 */
        byte ADCV6       :1;                                       /* Compare Function Value 6 */
        byte ADCV7       :1;                                       /* Compare Function Value 7 */
      } Bits;
    } ADCCVLSTR;
    #define ADCCVL                      _ADCCV.Overlap_STR.ADCCVLSTR.Byte
    #define ADCCVL_ADCV0                _ADCCV.Overlap_STR.ADCCVLSTR.Bits.ADCV0
    #define ADCCVL_ADCV1                _ADCCV.Overlap_STR.ADCCVLSTR.Bits.ADCV1
    #define ADCCVL_ADCV2                _ADCCV.Overlap_STR.ADCCVLSTR.Bits.ADCV2
    #define ADCCVL_ADCV3                _ADCCV.Overlap_STR.ADCCVLSTR.Bits.ADCV3
    #define ADCCVL_ADCV4                _ADCCV.Overlap_STR.ADCCVLSTR.Bits.ADCV4
    #define ADCCVL_ADCV5                _ADCCV.Overlap_STR.ADCCVLSTR.Bits.ADCV5
    #define ADCCVL_ADCV6                _ADCCV.Overlap_STR.ADCCVLSTR.Bits.ADCV6
    #define ADCCVL_ADCV7                _ADCCV.Overlap_STR.ADCCVLSTR.Bits.ADCV7
    
    #define ADCCVL_ADCV0_MASK           1U
    #define ADCCVL_ADCV1_MASK           2U
    #define ADCCVL_ADCV2_MASK           4U
    #define ADCCVL_ADCV3_MASK           8U
    #define ADCCVL_ADCV4_MASK           16U
    #define ADCCVL_ADCV5_MASK           32U
    #define ADCCVL_ADCV6_MASK           64U
    #define ADCCVL_ADCV7_MASK           128U
    
  } Overlap_STR;

} ADCCVSTR;
extern volatile ADCCVSTR _ADCCV @0x00000014;
#define ADCCV                           _ADCCV.Word


/*** ADCCFG - Configuration Register; 0x00000016 ***/
typedef union {
  byte Byte;
  struct {
    byte ADICLK0     :1;                                       /* Input Clock Select Bit 0 */
    byte ADICLK1     :1;                                       /* Input Clock Select Bit 1 */
    byte MODE0       :1;                                       /* Conversion Mode Selection Bit 0 */
    byte MODE1       :1;                                       /* Conversion Mode Selection Bit 1 */
    byte ADLSMP      :1;                                       /* Long Sample Time Configuration */
    byte ADIV0       :1;                                       /* Clock Divide Select Bit 0 */
    byte ADIV1       :1;                                       /* Clock Divide Select Bit 1 */
    byte ADLPC       :1;                                       /* Low Power Configuration */
  } Bits;
  struct {
    byte grpADICLK :2;
    byte grpMODE :2;
    byte         :1;
    byte grpADIV :2;
    byte         :1;
  } MergedBits;
} ADCCFGSTR;
extern volatile ADCCFGSTR _ADCCFG @0x00000016;
#define ADCCFG                          _ADCCFG.Byte
#define ADCCFG_ADICLK0                  _ADCCFG.Bits.ADICLK0
#define ADCCFG_ADICLK1                  _ADCCFG.Bits.ADICLK1
#define ADCCFG_MODE0                    _ADCCFG.Bits.MODE0
#define ADCCFG_MODE1                    _ADCCFG.Bits.MODE1
#define ADCCFG_ADLSMP                   _ADCCFG.Bits.ADLSMP
#define ADCCFG_ADIV0                    _ADCCFG.Bits.ADIV0
#define ADCCFG_ADIV1                    _ADCCFG.Bits.ADIV1
#define ADCCFG_ADLPC                    _ADCCFG.Bits.ADLPC
#define ADCCFG_ADICLK                   _ADCCFG.MergedBits.grpADICLK
#define ADCCFG_MODE                     _ADCCFG.MergedBits.grpMODE
#define ADCCFG_ADIV                     _ADCCFG.MergedBits.grpADIV

#define ADCCFG_ADICLK0_MASK             1U
#define ADCCFG_ADICLK1_MASK             2U
#define ADCCFG_MODE0_MASK               4U
#define ADCCFG_MODE1_MASK               8U
#define ADCCFG_ADLSMP_MASK              16U
#define ADCCFG_ADIV0_MASK               32U
#define ADCCFG_ADIV1_MASK               64U
#define ADCCFG_ADLPC_MASK               128U
#define ADCCFG_ADICLK_MASK              3U
#define ADCCFG_ADICLK_BITNUM            0U
#define ADCCFG_MODE_MASK                12U
#define ADCCFG_MODE_BITNUM              2U
#define ADCCFG_ADIV_MASK                96U
#define ADCCFG_ADIV_BITNUM              5U


/*** APCTL1 - Pin Control 1 Register; 0x00000017 ***/
typedef union {
  byte Byte;
  struct {
    byte ADPC0       :1;                                       /* ADC Pin Control 0 - ADPC0 is used to control the pin associated with channel AD0 */
    byte ADPC1       :1;                                       /* ADC Pin Control 1 - ADPC1 is used to control the pin associated with channel AD1 */
    byte ADPC2       :1;                                       /* ADC Pin Control 2 - ADPC2 is used to control the pin associated with channel AD2 */
    byte ADPC3       :1;                                       /* ADC Pin Control 3 - ADPC3 is used to control the pin associated with channel AD3 */
    byte ADPC4       :1;                                       /* ADC Pin Control 4 - ADPC4 is used to control the pin associated with channel AD4 */
    byte ADPC5       :1;                                       /* ADC Pin Control 5 - ADPC5 is used to control the pin associated with channel AD5 */
    byte ADPC6       :1;                                       /* ADC Pin Control 6 - ADPC6 is used to control the pin associated with channel AD6 */
    byte ADPC7       :1;                                       /* ADC Pin Control 7 - ADPC7 is used to control the pin associated with channel AD7 */
  } Bits;
} APCTL1STR;
extern volatile APCTL1STR _APCTL1 @0x00000017;
#define APCTL1                          _APCTL1.Byte
#define APCTL1_ADPC0                    _APCTL1.Bits.ADPC0
#define APCTL1_ADPC1                    _APCTL1.Bits.ADPC1
#define APCTL1_ADPC2                    _APCTL1.Bits.ADPC2
#define APCTL1_ADPC3                    _APCTL1.Bits.ADPC3
#define APCTL1_ADPC4                    _APCTL1.Bits.ADPC4
#define APCTL1_ADPC5                    _APCTL1.Bits.ADPC5
#define APCTL1_ADPC6                    _APCTL1.Bits.ADPC6
#define APCTL1_ADPC7                    _APCTL1.Bits.ADPC7

#define APCTL1_ADPC0_MASK               1U
#define APCTL1_ADPC1_MASK               2U
#define APCTL1_ADPC2_MASK               4U
#define APCTL1_ADPC3_MASK               8U
#define APCTL1_ADPC4_MASK               16U
#define APCTL1_ADPC5_MASK               32U
#define APCTL1_ADPC6_MASK               64U
#define APCTL1_ADPC7_MASK               128U


/*** APCTL2 - Pin Control 2 Register; 0x00000018 ***/
typedef union {
  byte Byte;
  struct {
    byte ADPC8       :1;                                       /* ADC Pin Control 8 - ADPC8 is used to control the pin associated with channel AD8 */
    byte ADPC9       :1;                                       /* ADC Pin Control 9 - ADPC9 is used to control the pin associated with channel AD9 */
    byte ADPC10      :1;                                       /* ADC Pin Control 10 - ADPC10 is used to control the pin associated with channel AD10 */
    byte ADPC11      :1;                                       /* ADC Pin Control 11 - ADPC11 is used to control the pin associated with channel AD11 */
    byte ADPC12      :1;                                       /* ADC Pin Control 12 - ADPC12 is used to control the pin associated with channel AD12 */
    byte ADPC13      :1;                                       /* ADC Pin Control 13 - ADPC13 is used to control the pin associated with channel AD13 */
    byte ADPC14      :1;                                       /* ADC Pin Control 14 - ADPC14 is used to control the pin associated with channel AD14 */
    byte ADPC15      :1;                                       /* ADC Pin Control 15 - ADPC15 is used to control the pin associated with channel AD15 */
  } Bits;
} APCTL2STR;
extern volatile APCTL2STR _APCTL2 @0x00000018;
#define APCTL2                          _APCTL2.Byte
#define APCTL2_ADPC8                    _APCTL2.Bits.ADPC8
#define APCTL2_ADPC9                    _APCTL2.Bits.ADPC9
#define APCTL2_ADPC10                   _APCTL2.Bits.ADPC10
#define APCTL2_ADPC11                   _APCTL2.Bits.ADPC11
#define APCTL2_ADPC12                   _APCTL2.Bits.ADPC12
#define APCTL2_ADPC13                   _APCTL2.Bits.ADPC13
#define APCTL2_ADPC14                   _APCTL2.Bits.ADPC14
#define APCTL2_ADPC15                   _APCTL2.Bits.ADPC15

#define APCTL2_ADPC8_MASK               1U
#define APCTL2_ADPC9_MASK               2U
#define APCTL2_ADPC10_MASK              4U
#define APCTL2_ADPC11_MASK              8U
#define APCTL2_ADPC12_MASK              16U
#define APCTL2_ADPC13_MASK              32U
#define APCTL2_ADPC14_MASK              64U
#define APCTL2_ADPC15_MASK              128U


/*** APCTL3 - Pin Control 3 Register; 0x00000019 ***/
typedef union {
  byte Byte;
  struct {
    byte ADPC16      :1;                                       /* ADC Pin Control 16 - ADPC16 is used to control the pin associated with channel AD16 */
    byte ADPC17      :1;                                       /* ADC Pin Control 17 - ADPC17 is used to control the pin associated with channel AD17 */
    byte ADPC18      :1;                                       /* ADC Pin Control 18 - ADPC18 is used to control the pin associated with channel AD18 */
    byte ADPC19      :1;                                       /* ADC Pin Control 19 - ADPC19 is used to control the pin associated with channel AD19 */
    byte ADPC20      :1;                                       /* ADC Pin Control 20 - ADPC20 is used to control the pin associated with channel AD20 */
    byte ADPC21      :1;                                       /* ADC Pin Control 21 - ADPC21 is used to control the pin associated with channel AD21 */
    byte ADPC22      :1;                                       /* ADC Pin Control 22 - ADPC22 is used to control the pin associated with channel AD22 */
    byte ADPC23      :1;                                       /* ADC Pin Control 23 - ADPC23 is used to control the pin associated with channel AD23 */
  } Bits;
} APCTL3STR;
extern volatile APCTL3STR _APCTL3 @0x00000019;
#define APCTL3                          _APCTL3.Byte
#define APCTL3_ADPC16                   _APCTL3.Bits.ADPC16
#define APCTL3_ADPC17                   _APCTL3.Bits.ADPC17
#define APCTL3_ADPC18                   _APCTL3.Bits.ADPC18
#define APCTL3_ADPC19                   _APCTL3.Bits.ADPC19
#define APCTL3_ADPC20                   _APCTL3.Bits.ADPC20
#define APCTL3_ADPC21                   _APCTL3.Bits.ADPC21
#define APCTL3_ADPC22                   _APCTL3.Bits.ADPC22
#define APCTL3_ADPC23                   _APCTL3.Bits.ADPC23

#define APCTL3_ADPC16_MASK              1U
#define APCTL3_ADPC17_MASK              2U
#define APCTL3_ADPC18_MASK              4U
#define APCTL3_ADPC19_MASK              8U
#define APCTL3_ADPC20_MASK              16U
#define APCTL3_ADPC21_MASK              32U
#define APCTL3_ADPC22_MASK              64U
#define APCTL3_ADPC23_MASK              128U


/*** ACMP1SC - ACMP1 Status and Control Register; 0x0000001A ***/
typedef union {
  byte Byte;
  struct {
    byte ACMOD0      :1;                                       /* Analog Comparator Mode Bit 0 */
    byte ACMOD1      :1;                                       /* Analog Comparator Mode Bit 1 */
    byte ACOPE       :1;                                       /* Analog Comparator Output Pin Enable */
    byte ACO         :1;                                       /* Analog Comparator Output */
    byte ACIE        :1;                                       /* Analog Comparator Interrupt Enable */
    byte ACF         :1;                                       /* Analog Comparator Flag */
    byte ACBGS       :1;                                       /* Analog Comparator Bandgap Select */
    byte ACME        :1;                                       /* Analog Comparator Module Enable */
  } Bits;
  struct {
    byte grpACMOD :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} ACMP1SCSTR;
extern volatile ACMP1SCSTR _ACMP1SC @0x0000001A;
#define ACMP1SC                         _ACMP1SC.Byte
#define ACMP1SC_ACMOD0                  _ACMP1SC.Bits.ACMOD0
#define ACMP1SC_ACMOD1                  _ACMP1SC.Bits.ACMOD1
#define ACMP1SC_ACOPE                   _ACMP1SC.Bits.ACOPE
#define ACMP1SC_ACO                     _ACMP1SC.Bits.ACO
#define ACMP1SC_ACIE                    _ACMP1SC.Bits.ACIE
#define ACMP1SC_ACF                     _ACMP1SC.Bits.ACF
#define ACMP1SC_ACBGS                   _ACMP1SC.Bits.ACBGS
#define ACMP1SC_ACME                    _ACMP1SC.Bits.ACME
#define ACMP1SC_ACMOD                   _ACMP1SC.MergedBits.grpACMOD

#define ACMP1SC_ACMOD0_MASK             1U
#define ACMP1SC_ACMOD1_MASK             2U
#define ACMP1SC_ACOPE_MASK              4U
#define ACMP1SC_ACO_MASK                8U
#define ACMP1SC_ACIE_MASK               16U
#define ACMP1SC_ACF_MASK                32U
#define ACMP1SC_ACBGS_MASK              64U
#define ACMP1SC_ACME_MASK               128U
#define ACMP1SC_ACMOD_MASK              3U
#define ACMP1SC_ACMOD_BITNUM            0U


/*** ACMP2SC - ACMP2 Status and Control Register; 0x0000001B ***/
typedef union {
  byte Byte;
  struct {
    byte ACMOD0      :1;                                       /* Analog Comparator Mode Bit 0 */
    byte ACMOD1      :1;                                       /* Analog Comparator Mode Bit 1 */
    byte ACOPE       :1;                                       /* Analog Comparator Output Pin Enable */
    byte ACO         :1;                                       /* Analog Comparator Output */
    byte ACIE        :1;                                       /* Analog Comparator Interrupt Enable */
    byte ACF         :1;                                       /* Analog Comparator Flag */
    byte ACBGS       :1;                                       /* Analog Comparator Bandgap Select */
    byte ACME        :1;                                       /* Analog Comparator Module Enable */
  } Bits;
  struct {
    byte grpACMOD :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} ACMP2SCSTR;
extern volatile ACMP2SCSTR _ACMP2SC @0x0000001B;
#define ACMP2SC                         _ACMP2SC.Byte
#define ACMP2SC_ACMOD0                  _ACMP2SC.Bits.ACMOD0
#define ACMP2SC_ACMOD1                  _ACMP2SC.Bits.ACMOD1
#define ACMP2SC_ACOPE                   _ACMP2SC.Bits.ACOPE
#define ACMP2SC_ACO                     _ACMP2SC.Bits.ACO
#define ACMP2SC_ACIE                    _ACMP2SC.Bits.ACIE
#define ACMP2SC_ACF                     _ACMP2SC.Bits.ACF
#define ACMP2SC_ACBGS                   _ACMP2SC.Bits.ACBGS
#define ACMP2SC_ACME                    _ACMP2SC.Bits.ACME
#define ACMP2SC_ACMOD                   _ACMP2SC.MergedBits.grpACMOD

#define ACMP2SC_ACMOD0_MASK             1U
#define ACMP2SC_ACMOD1_MASK             2U
#define ACMP2SC_ACOPE_MASK              4U
#define ACMP2SC_ACO_MASK                8U
#define ACMP2SC_ACIE_MASK               16U
#define ACMP2SC_ACF_MASK                32U
#define ACMP2SC_ACBGS_MASK              64U
#define ACMP2SC_ACME_MASK               128U
#define ACMP2SC_ACMOD_MASK              3U
#define ACMP2SC_ACMOD_BITNUM            0U


/*** PTGD - Port G Data Register; 0x0000001C ***/
typedef union {
  byte Byte;
  struct {
    byte PTGD0       :1;                                       /* Port G Data Register Bit 0 */
    byte PTGD1       :1;                                       /* Port G Data Register Bit 1 */
    byte PTGD2       :1;                                       /* Port G Data Register Bit 2 */
    byte PTGD3       :1;                                       /* Port G Data Register Bit 3 */
    byte PTGD4       :1;                                       /* Port G Data Register Bit 4 */
    byte PTGD5       :1;                                       /* Port G Data Register Bit 5 */
    byte PTGD6       :1;                                       /* Port G Data Register Bit 6 */
    byte PTGD7       :1;                                       /* Port G Data Register Bit 7 */
  } Bits;
} PTGDSTR;
extern volatile PTGDSTR _PTGD @0x0000001C;
#define PTGD                            _PTGD.Byte
#define PTGD_PTGD0                      _PTGD.Bits.PTGD0
#define PTGD_PTGD1                      _PTGD.Bits.PTGD1
#define PTGD_PTGD2                      _PTGD.Bits.PTGD2
#define PTGD_PTGD3                      _PTGD.Bits.PTGD3
#define PTGD_PTGD4                      _PTGD.Bits.PTGD4
#define PTGD_PTGD5                      _PTGD.Bits.PTGD5
#define PTGD_PTGD6                      _PTGD.Bits.PTGD6
#define PTGD_PTGD7                      _PTGD.Bits.PTGD7

#define PTGD_PTGD0_MASK                 1U
#define PTGD_PTGD1_MASK                 2U
#define PTGD_PTGD2_MASK                 4U
#define PTGD_PTGD3_MASK                 8U
#define PTGD_PTGD4_MASK                 16U
#define PTGD_PTGD5_MASK                 32U
#define PTGD_PTGD6_MASK                 64U
#define PTGD_PTGD7_MASK                 128U


/*** PTGDD - Port G Data Direction Register; 0x0000001D ***/
typedef union {
  byte Byte;
  struct {
    byte PTGDD0      :1;                                       /* Data Direction for Port G Bit 0 */
    byte PTGDD1      :1;                                       /* Data Direction for Port G Bit 1 */
    byte PTGDD2      :1;                                       /* Data Direction for Port G Bit 2 */
    byte PTGDD3      :1;                                       /* Data Direction for Port G Bit 3 */
    byte PTGDD4      :1;                                       /* Data Direction for Port G Bit 4 */
    byte PTGDD5      :1;                                       /* Data Direction for Port G Bit 5 */
    byte PTGDD6      :1;                                       /* Data Direction for Port G Bit 6 */
    byte PTGDD7      :1;                                       /* Data Direction for Port G Bit 7 */
  } Bits;
} PTGDDSTR;
extern volatile PTGDDSTR _PTGDD @0x0000001D;
#define PTGDD                           _PTGDD.Byte
#define PTGDD_PTGDD0                    _PTGDD.Bits.PTGDD0
#define PTGDD_PTGDD1                    _PTGDD.Bits.PTGDD1
#define PTGDD_PTGDD2                    _PTGDD.Bits.PTGDD2
#define PTGDD_PTGDD3                    _PTGDD.Bits.PTGDD3
#define PTGDD_PTGDD4                    _PTGDD.Bits.PTGDD4
#define PTGDD_PTGDD5                    _PTGDD.Bits.PTGDD5
#define PTGDD_PTGDD6                    _PTGDD.Bits.PTGDD6
#define PTGDD_PTGDD7                    _PTGDD.Bits.PTGDD7

#define PTGDD_PTGDD0_MASK               1U
#define PTGDD_PTGDD1_MASK               2U
#define PTGDD_PTGDD2_MASK               4U
#define PTGDD_PTGDD3_MASK               8U
#define PTGDD_PTGDD4_MASK               16U
#define PTGDD_PTGDD5_MASK               32U
#define PTGDD_PTGDD6_MASK               64U
#define PTGDD_PTGDD7_MASK               128U


/*** PTHD - Port H Data Register; 0x0000001E ***/
typedef union {
  byte Byte;
  struct {
    byte PTHD0       :1;                                       /* Port H Data Register Bit 0 */
    byte PTHD1       :1;                                       /* Port H Data Register Bit 1 */
    byte PTHD2       :1;                                       /* Port H Data Register Bit 2 */
    byte PTHD3       :1;                                       /* Port H Data Register Bit 3 */
    byte PTHD4       :1;                                       /* Port H Data Register Bit 4 */
    byte PTHD5       :1;                                       /* Port H Data Register Bit 5 */
    byte PTHD6       :1;                                       /* Port H Data Register Bit 6 */
    byte PTHD7       :1;                                       /* Port H Data Register Bit 7 */
  } Bits;
} PTHDSTR;
extern volatile PTHDSTR _PTHD @0x0000001E;
#define PTHD                            _PTHD.Byte
#define PTHD_PTHD0                      _PTHD.Bits.PTHD0
#define PTHD_PTHD1                      _PTHD.Bits.PTHD1
#define PTHD_PTHD2                      _PTHD.Bits.PTHD2
#define PTHD_PTHD3                      _PTHD.Bits.PTHD3
#define PTHD_PTHD4                      _PTHD.Bits.PTHD4
#define PTHD_PTHD5                      _PTHD.Bits.PTHD5
#define PTHD_PTHD6                      _PTHD.Bits.PTHD6
#define PTHD_PTHD7                      _PTHD.Bits.PTHD7

#define PTHD_PTHD0_MASK                 1U
#define PTHD_PTHD1_MASK                 2U
#define PTHD_PTHD2_MASK                 4U
#define PTHD_PTHD3_MASK                 8U
#define PTHD_PTHD4_MASK                 16U
#define PTHD_PTHD5_MASK                 32U
#define PTHD_PTHD6_MASK                 64U
#define PTHD_PTHD7_MASK                 128U


/*** PTHDD - Port H Data Direction Register; 0x0000001F ***/
typedef union {
  byte Byte;
  struct {
    byte PTHDD0      :1;                                       /* Data Direction for Port H Bit 0 */
    byte PTHDD1      :1;                                       /* Data Direction for Port H Bit 1 */
    byte PTHDD2      :1;                                       /* Data Direction for Port H Bit 2 */
    byte PTHDD3      :1;                                       /* Data Direction for Port H Bit 3 */
    byte PTHDD4      :1;                                       /* Data Direction for Port H Bit 4 */
    byte PTHDD5      :1;                                       /* Data Direction for Port H Bit 5 */
    byte PTHDD6      :1;                                       /* Data Direction for Port H Bit 6 */
    byte PTHDD7      :1;                                       /* Data Direction for Port H Bit 7 */
  } Bits;
} PTHDDSTR;
extern volatile PTHDDSTR _PTHDD @0x0000001F;
#define PTHDD                           _PTHDD.Byte
#define PTHDD_PTHDD0                    _PTHDD.Bits.PTHDD0
#define PTHDD_PTHDD1                    _PTHDD.Bits.PTHDD1
#define PTHDD_PTHDD2                    _PTHDD.Bits.PTHDD2
#define PTHDD_PTHDD3                    _PTHDD.Bits.PTHDD3
#define PTHDD_PTHDD4                    _PTHDD.Bits.PTHDD4
#define PTHDD_PTHDD5                    _PTHDD.Bits.PTHDD5
#define PTHDD_PTHDD6                    _PTHDD.Bits.PTHDD6
#define PTHDD_PTHDD7                    _PTHDD.Bits.PTHDD7

#define PTHDD_PTHDD0_MASK               1U
#define PTHDD_PTHDD1_MASK               2U
#define PTHDD_PTHDD2_MASK               4U
#define PTHDD_PTHDD3_MASK               8U
#define PTHDD_PTHDD4_MASK               16U
#define PTHDD_PTHDD5_MASK               32U
#define PTHDD_PTHDD6_MASK               64U
#define PTHDD_PTHDD7_MASK               128U


/*** SCI1BD - SCI1 Baud Rate Register; 0x00000020 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** SCI1BDH - SCI1 Baud Rate Register High; 0x00000020 ***/
    union {
      byte Byte;
      struct {
        byte SBR8        :1;                                       /* Baud Rate Modulo Divisor Bit 8 */
        byte SBR9        :1;                                       /* Baud Rate Modulo Divisor Bit 9 */
        byte SBR10       :1;                                       /* Baud Rate Modulo Divisor Bit 10 */
        byte SBR11       :1;                                       /* Baud Rate Modulo Divisor Bit 11 */
        byte SBR12       :1;                                       /* Baud Rate Modulo Divisor Bit 12 */
        byte             :1; 
        byte RXEDGIE     :1;                                       /* RxD Input Active Edge Interrupt Enable (for RXEDGIF) */
        byte LBKDIE      :1;                                       /* LIN Break Detect Interrupt Enable (for LBKDIF) */
      } Bits;
      struct {
        byte grpSBR_8 :5;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } SCI1BDHSTR;
    #define SCI1BDH                     _SCI1BD.Overlap_STR.SCI1BDHSTR.Byte
    #define SCI1BDH_SBR8                _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR8
    #define SCI1BDH_SBR9                _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR9
    #define SCI1BDH_SBR10               _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR10
    #define SCI1BDH_SBR11               _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR11
    #define SCI1BDH_SBR12               _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.SBR12
    #define SCI1BDH_RXEDGIE             _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.RXEDGIE
    #define SCI1BDH_LBKDIE              _SCI1BD.Overlap_STR.SCI1BDHSTR.Bits.LBKDIE
    #define SCI1BDH_SBR_8               _SCI1BD.Overlap_STR.SCI1BDHSTR.MergedBits.grpSBR_8
    #define SCI1BDH_SBR                 SCI1BDH_SBR_8
    
    #define SCI1BDH_SBR8_MASK           1U
    #define SCI1BDH_SBR9_MASK           2U
    #define SCI1BDH_SBR10_MASK          4U
    #define SCI1BDH_SBR11_MASK          8U
    #define SCI1BDH_SBR12_MASK          16U
    #define SCI1BDH_RXEDGIE_MASK        64U
    #define SCI1BDH_LBKDIE_MASK         128U
    #define SCI1BDH_SBR_8_MASK          31U
    #define SCI1BDH_SBR_8_BITNUM        0U
    

    /*** SCI1BDL - SCI1 Baud Rate Register Low; 0x00000021 ***/
    union {
      byte Byte;
      struct {
        byte SBR0        :1;                                       /* Baud Rate Modulo Divisor Bit 0 */
        byte SBR1        :1;                                       /* Baud Rate Modulo Divisor Bit 1 */
        byte SBR2        :1;                                       /* Baud Rate Modulo Divisor Bit 2 */
        byte SBR3        :1;                                       /* Baud Rate Modulo Divisor Bit 3 */
        byte SBR4        :1;                                       /* Baud Rate Modulo Divisor Bit 4 */
        byte SBR5        :1;                                       /* Baud Rate Modulo Divisor Bit 5 */
        byte SBR6        :1;                                       /* Baud Rate Modulo Divisor Bit 6 */
        byte SBR7        :1;                                       /* Baud Rate Modulo Divisor Bit 7 */
      } Bits;
    } SCI1BDLSTR;
    #define SCI1BDL                     _SCI1BD.Overlap_STR.SCI1BDLSTR.Byte
    #define SCI1BDL_SBR0                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR0
    #define SCI1BDL_SBR1                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR1
    #define SCI1BDL_SBR2                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR2
    #define SCI1BDL_SBR3                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR3
    #define SCI1BDL_SBR4                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR4
    #define SCI1BDL_SBR5                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR5
    #define SCI1BDL_SBR6                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR6
    #define SCI1BDL_SBR7                _SCI1BD.Overlap_STR.SCI1BDLSTR.Bits.SBR7
    
    #define SCI1BDL_SBR0_MASK           1U
    #define SCI1BDL_SBR1_MASK           2U
    #define SCI1BDL_SBR2_MASK           4U
    #define SCI1BDL_SBR3_MASK           8U
    #define SCI1BDL_SBR4_MASK           16U
    #define SCI1BDL_SBR5_MASK           32U
    #define SCI1BDL_SBR6_MASK           64U
    #define SCI1BDL_SBR7_MASK           128U
    
  } Overlap_STR;

} SCI1BDSTR;
extern volatile SCI1BDSTR _SCI1BD @0x00000020;
#define SCI1BD                          _SCI1BD.Word


/*** SCI1C1 - SCI1 Control Register 1; 0x00000022 ***/
typedef union {
  byte Byte;
  struct {
    byte PT          :1;                                       /* Parity Type */
    byte PE          :1;                                       /* Parity Enable */
    byte ILT         :1;                                       /* Idle Line Type Select */
    byte WAKE        :1;                                       /* Receiver Wakeup Method Select */
    byte M           :1;                                       /* 9-Bit or 8-Bit Mode Select */
    byte RSRC        :1;                                       /* Receiver Source Select */
    byte SCISWAI     :1;                                       /* SCI Stops in Wait Mode */
    byte LOOPS       :1;                                       /* Loop Mode Select */
  } Bits;
} SCI1C1STR;
extern volatile SCI1C1STR _SCI1C1 @0x00000022;
#define SCI1C1                          _SCI1C1.Byte
#define SCI1C1_PT                       _SCI1C1.Bits.PT
#define SCI1C1_PE                       _SCI1C1.Bits.PE
#define SCI1C1_ILT                      _SCI1C1.Bits.ILT
#define SCI1C1_WAKE                     _SCI1C1.Bits.WAKE
#define SCI1C1_M                        _SCI1C1.Bits.M
#define SCI1C1_RSRC                     _SCI1C1.Bits.RSRC
#define SCI1C1_SCISWAI                  _SCI1C1.Bits.SCISWAI
#define SCI1C1_LOOPS                    _SCI1C1.Bits.LOOPS

#define SCI1C1_PT_MASK                  1U
#define SCI1C1_PE_MASK                  2U
#define SCI1C1_ILT_MASK                 4U
#define SCI1C1_WAKE_MASK                8U
#define SCI1C1_M_MASK                   16U
#define SCI1C1_RSRC_MASK                32U
#define SCI1C1_SCISWAI_MASK             64U
#define SCI1C1_LOOPS_MASK               128U


/*** SCI1C2 - SCI1 Control Register 2; 0x00000023 ***/
typedef union {
  byte Byte;
  struct {
    byte SBK         :1;                                       /* Send Break */
    byte RWU         :1;                                       /* Receiver Wakeup Control */
    byte RE          :1;                                       /* Receiver Enable */
    byte TE          :1;                                       /* Transmitter Enable */
    byte ILIE        :1;                                       /* Idle Line Interrupt Enable (for IDLE) */
    byte RIE         :1;                                       /* Receiver Interrupt Enable (for RDRF) */
    byte TCIE        :1;                                       /* Transmission Complete Interrupt Enable (for TC) */
    byte TIE         :1;                                       /* Transmit Interrupt Enable (for TDRE) */
  } Bits;
} SCI1C2STR;
extern volatile SCI1C2STR _SCI1C2 @0x00000023;
#define SCI1C2                          _SCI1C2.Byte
#define SCI1C2_SBK                      _SCI1C2.Bits.SBK
#define SCI1C2_RWU                      _SCI1C2.Bits.RWU
#define SCI1C2_RE                       _SCI1C2.Bits.RE
#define SCI1C2_TE                       _SCI1C2.Bits.TE
#define SCI1C2_ILIE                     _SCI1C2.Bits.ILIE
#define SCI1C2_RIE                      _SCI1C2.Bits.RIE
#define SCI1C2_TCIE                     _SCI1C2.Bits.TCIE
#define SCI1C2_TIE                      _SCI1C2.Bits.TIE

#define SCI1C2_SBK_MASK                 1U
#define SCI1C2_RWU_MASK                 2U
#define SCI1C2_RE_MASK                  4U
#define SCI1C2_TE_MASK                  8U
#define SCI1C2_ILIE_MASK                16U
#define SCI1C2_RIE_MASK                 32U
#define SCI1C2_TCIE_MASK                64U
#define SCI1C2_TIE_MASK                 128U


/*** SCI1S1 - SCI1 Status Register 1; 0x00000024 ***/
typedef union {
  byte Byte;
  struct {
    byte PF          :1;                                       /* Parity Error Flag */
    byte FE          :1;                                       /* Framing Error Flag */
    byte NF          :1;                                       /* Noise Flag */
    byte OR          :1;                                       /* Receiver Overrun Flag */
    byte IDLE        :1;                                       /* Idle Line Flag */
    byte RDRF        :1;                                       /* Receive Data Register Full Flag */
    byte TC          :1;                                       /* Transmission Complete Flag */
    byte TDRE        :1;                                       /* Transmit Data Register Empty Flag */
  } Bits;
} SCI1S1STR;
extern volatile SCI1S1STR _SCI1S1 @0x00000024;
#define SCI1S1                          _SCI1S1.Byte
#define SCI1S1_PF                       _SCI1S1.Bits.PF
#define SCI1S1_FE                       _SCI1S1.Bits.FE
#define SCI1S1_NF                       _SCI1S1.Bits.NF
#define SCI1S1_OR                       _SCI1S1.Bits.OR
#define SCI1S1_IDLE                     _SCI1S1.Bits.IDLE
#define SCI1S1_RDRF                     _SCI1S1.Bits.RDRF
#define SCI1S1_TC                       _SCI1S1.Bits.TC
#define SCI1S1_TDRE                     _SCI1S1.Bits.TDRE

#define SCI1S1_PF_MASK                  1U
#define SCI1S1_FE_MASK                  2U
#define SCI1S1_NF_MASK                  4U
#define SCI1S1_OR_MASK                  8U
#define SCI1S1_IDLE_MASK                16U
#define SCI1S1_RDRF_MASK                32U
#define SCI1S1_TC_MASK                  64U
#define SCI1S1_TDRE_MASK                128U


/*** SCI1S2 - SCI1 Status Register 2; 0x00000025 ***/
typedef union {
  byte Byte;
  struct {
    byte RAF         :1;                                       /* Receiver Active Flag */
    byte LBKDE       :1;                                       /* LIN Break Detection Enable */
    byte BRK13       :1;                                       /* Break Character Generation Length */
    byte RWUID       :1;                                       /* Receive Wake Up Idle Detect */
    byte RXINV       :1;                                       /* Receive Data Inversion */
    byte             :1; 
    byte RXEDGIF     :1;                                       /* RxD Pin Active Edge Interrupt Flag */
    byte LBKDIF      :1;                                       /* LIN Break Detect Interrupt Flag */
  } Bits;
} SCI1S2STR;
extern volatile SCI1S2STR _SCI1S2 @0x00000025;
#define SCI1S2                          _SCI1S2.Byte
#define SCI1S2_RAF                      _SCI1S2.Bits.RAF
#define SCI1S2_LBKDE                    _SCI1S2.Bits.LBKDE
#define SCI1S2_BRK13                    _SCI1S2.Bits.BRK13
#define SCI1S2_RWUID                    _SCI1S2.Bits.RWUID
#define SCI1S2_RXINV                    _SCI1S2.Bits.RXINV
#define SCI1S2_RXEDGIF                  _SCI1S2.Bits.RXEDGIF
#define SCI1S2_LBKDIF                   _SCI1S2.Bits.LBKDIF

#define SCI1S2_RAF_MASK                 1U
#define SCI1S2_LBKDE_MASK               2U
#define SCI1S2_BRK13_MASK               4U
#define SCI1S2_RWUID_MASK               8U
#define SCI1S2_RXINV_MASK               16U
#define SCI1S2_RXEDGIF_MASK             64U
#define SCI1S2_LBKDIF_MASK              128U


/*** SCI1C3 - SCI1 Control Register 3; 0x00000026 ***/
typedef union {
  byte Byte;
  struct {
    byte PEIE        :1;                                       /* Parity Error Interrupt Enable */
    byte FEIE        :1;                                       /* Framing Error Interrupt Enable */
    byte NEIE        :1;                                       /* Noise Error Interrupt Enable */
    byte ORIE        :1;                                       /* Overrun Interrupt Enable */
    byte TXINV       :1;                                       /* Transmit Data Inversion */
    byte TXDIR       :1;                                       /* TxD Pin Direction in Single-Wire Mode */
    byte T8          :1;                                       /* Ninth Data Bit for Transmitter */
    byte R8          :1;                                       /* Ninth Data Bit for Receiver */
  } Bits;
} SCI1C3STR;
extern volatile SCI1C3STR _SCI1C3 @0x00000026;
#define SCI1C3                          _SCI1C3.Byte
#define SCI1C3_PEIE                     _SCI1C3.Bits.PEIE
#define SCI1C3_FEIE                     _SCI1C3.Bits.FEIE
#define SCI1C3_NEIE                     _SCI1C3.Bits.NEIE
#define SCI1C3_ORIE                     _SCI1C3.Bits.ORIE
#define SCI1C3_TXINV                    _SCI1C3.Bits.TXINV
#define SCI1C3_TXDIR                    _SCI1C3.Bits.TXDIR
#define SCI1C3_T8                       _SCI1C3.Bits.T8
#define SCI1C3_R8                       _SCI1C3.Bits.R8

#define SCI1C3_PEIE_MASK                1U
#define SCI1C3_FEIE_MASK                2U
#define SCI1C3_NEIE_MASK                4U
#define SCI1C3_ORIE_MASK                8U
#define SCI1C3_TXINV_MASK               16U
#define SCI1C3_TXDIR_MASK               32U
#define SCI1C3_T8_MASK                  64U
#define SCI1C3_R8_MASK                  128U


/*** SCI1D - SCI1 Data Register; 0x00000027 ***/
typedef union {
  byte Byte;
  struct {
    byte R0_T0       :1;                                       /* Receive/Transmit Data Bit 0 */
    byte R1_T1       :1;                                       /* Receive/Transmit Data Bit 1 */
    byte R2_T2       :1;                                       /* Receive/Transmit Data Bit 2 */
    byte R3_T3       :1;                                       /* Receive/Transmit Data Bit 3 */
    byte R4_T4       :1;                                       /* Receive/Transmit Data Bit 4 */
    byte R5_T5       :1;                                       /* Receive/Transmit Data Bit 5 */
    byte R6_T6       :1;                                       /* Receive/Transmit Data Bit 6 */
    byte R7_T7       :1;                                       /* Receive/Transmit Data Bit 7 */
  } Bits;
} SCI1DSTR;
extern volatile SCI1DSTR _SCI1D @0x00000027;
#define SCI1D                           _SCI1D.Byte
#define SCI1D_R0_T0                     _SCI1D.Bits.R0_T0
#define SCI1D_R1_T1                     _SCI1D.Bits.R1_T1
#define SCI1D_R2_T2                     _SCI1D.Bits.R2_T2
#define SCI1D_R3_T3                     _SCI1D.Bits.R3_T3
#define SCI1D_R4_T4                     _SCI1D.Bits.R4_T4
#define SCI1D_R5_T5                     _SCI1D.Bits.R5_T5
#define SCI1D_R6_T6                     _SCI1D.Bits.R6_T6
#define SCI1D_R7_T7                     _SCI1D.Bits.R7_T7

#define SCI1D_R0_T0_MASK                1U
#define SCI1D_R1_T1_MASK                2U
#define SCI1D_R2_T2_MASK                4U
#define SCI1D_R3_T3_MASK                8U
#define SCI1D_R4_T4_MASK                16U
#define SCI1D_R5_T5_MASK                32U
#define SCI1D_R6_T6_MASK                64U
#define SCI1D_R7_T7_MASK                128U


/*** SPI1C1 - SPI1 Control Register 1; 0x00000028 ***/
typedef union {
  byte Byte;
  struct {
    byte LSBFE       :1;                                       /* LSB First (Shifter Direction) */
    byte SSOE        :1;                                       /* Slave Select Output Enable */
    byte CPHA        :1;                                       /* Clock Phase */
    byte CPOL        :1;                                       /* Clock Polarity */
    byte MSTR        :1;                                       /* Master/Slave Mode Select */
    byte SPTIE       :1;                                       /* SPI Transmit Interrupt Enable */
    byte SPE         :1;                                       /* SPI System Enable */
    byte SPIE        :1;                                       /* SPI Interrupt Enable (for SPRF and MODF) */
  } Bits;
} SPI1C1STR;
extern volatile SPI1C1STR _SPI1C1 @0x00000028;
#define SPI1C1                          _SPI1C1.Byte
#define SPI1C1_LSBFE                    _SPI1C1.Bits.LSBFE
#define SPI1C1_SSOE                     _SPI1C1.Bits.SSOE
#define SPI1C1_CPHA                     _SPI1C1.Bits.CPHA
#define SPI1C1_CPOL                     _SPI1C1.Bits.CPOL
#define SPI1C1_MSTR                     _SPI1C1.Bits.MSTR
#define SPI1C1_SPTIE                    _SPI1C1.Bits.SPTIE
#define SPI1C1_SPE                      _SPI1C1.Bits.SPE
#define SPI1C1_SPIE                     _SPI1C1.Bits.SPIE

#define SPI1C1_LSBFE_MASK               1U
#define SPI1C1_SSOE_MASK                2U
#define SPI1C1_CPHA_MASK                4U
#define SPI1C1_CPOL_MASK                8U
#define SPI1C1_MSTR_MASK                16U
#define SPI1C1_SPTIE_MASK               32U
#define SPI1C1_SPE_MASK                 64U
#define SPI1C1_SPIE_MASK                128U


/*** SPI1C2 - SPI1 Control Register 2; 0x00000029 ***/
typedef union {
  byte Byte;
  struct {
    byte SPC0        :1;                                       /* SPI Pin Control 0 */
    byte SPISWAI     :1;                                       /* SPI Stop in Wait Mode */
    byte             :1; 
    byte BIDIROE     :1;                                       /* Bidirectional Mode Output Enable */
    byte MODFEN      :1;                                       /* Master Mode-Fault Function Enable */
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} SPI1C2STR;
extern volatile SPI1C2STR _SPI1C2 @0x00000029;
#define SPI1C2                          _SPI1C2.Byte
#define SPI1C2_SPC0                     _SPI1C2.Bits.SPC0
#define SPI1C2_SPISWAI                  _SPI1C2.Bits.SPISWAI
#define SPI1C2_BIDIROE                  _SPI1C2.Bits.BIDIROE
#define SPI1C2_MODFEN                   _SPI1C2.Bits.MODFEN

#define SPI1C2_SPC0_MASK                1U
#define SPI1C2_SPISWAI_MASK             2U
#define SPI1C2_BIDIROE_MASK             8U
#define SPI1C2_MODFEN_MASK              16U


/*** SPI1BR - SPI1 Baud Rate Register; 0x0000002A ***/
typedef union {
  byte Byte;
  struct {
    byte SPR0        :1;                                       /* SPI Baud Rate Divisor Bit 0 */
    byte SPR1        :1;                                       /* SPI Baud Rate Divisor Bit 1 */
    byte SPR2        :1;                                       /* SPI Baud Rate Divisor Bit 2 */
    byte             :1; 
    byte SPPR0       :1;                                       /* SPI Baud Rate Prescale Divisor Bit 0 */
    byte SPPR1       :1;                                       /* SPI Baud Rate Prescale Divisor Bit 1 */
    byte SPPR2       :1;                                       /* SPI Baud Rate Prescale Divisor Bit 2 */
    byte             :1; 
  } Bits;
  struct {
    byte grpSPR  :3;
    byte         :1;
    byte grpSPPR :3;
    byte         :1;
  } MergedBits;
} SPI1BRSTR;
extern volatile SPI1BRSTR _SPI1BR @0x0000002A;
#define SPI1BR                          _SPI1BR.Byte
#define SPI1BR_SPR0                     _SPI1BR.Bits.SPR0
#define SPI1BR_SPR1                     _SPI1BR.Bits.SPR1
#define SPI1BR_SPR2                     _SPI1BR.Bits.SPR2
#define SPI1BR_SPPR0                    _SPI1BR.Bits.SPPR0
#define SPI1BR_SPPR1                    _SPI1BR.Bits.SPPR1
#define SPI1BR_SPPR2                    _SPI1BR.Bits.SPPR2
#define SPI1BR_SPR                      _SPI1BR.MergedBits.grpSPR
#define SPI1BR_SPPR                     _SPI1BR.MergedBits.grpSPPR

#define SPI1BR_SPR0_MASK                1U
#define SPI1BR_SPR1_MASK                2U
#define SPI1BR_SPR2_MASK                4U
#define SPI1BR_SPPR0_MASK               16U
#define SPI1BR_SPPR1_MASK               32U
#define SPI1BR_SPPR2_MASK               64U
#define SPI1BR_SPR_MASK                 7U
#define SPI1BR_SPR_BITNUM               0U
#define SPI1BR_SPPR_MASK                112U
#define SPI1BR_SPPR_BITNUM              4U


/*** SPI1S - SPI1 Status Register; 0x0000002B ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte MODF        :1;                                       /* Master Mode Fault Flag */
    byte SPTEF       :1;                                       /* SPI Transmit Buffer Empty Flag */
    byte             :1; 
    byte SPRF        :1;                                       /* SPI Read Buffer Full Flag */
  } Bits;
} SPI1SSTR;
extern volatile SPI1SSTR _SPI1S @0x0000002B;
#define SPI1S                           _SPI1S.Byte
#define SPI1S_MODF                      _SPI1S.Bits.MODF
#define SPI1S_SPTEF                     _SPI1S.Bits.SPTEF
#define SPI1S_SPRF                      _SPI1S.Bits.SPRF

#define SPI1S_MODF_MASK                 16U
#define SPI1S_SPTEF_MASK                32U
#define SPI1S_SPRF_MASK                 128U


/*** SPI1D - SPI1 Data Register; 0x0000002D ***/
typedef union {
  byte Byte;
} SPI1DSTR;
extern volatile SPI1DSTR _SPI1D @0x0000002D;
#define SPI1D                           _SPI1D.Byte


/*** PTJD - Port J Data Register; 0x0000002E ***/
typedef union {
  byte Byte;
  struct {
    byte PTJD0       :1;                                       /* Port J Data Register Bit 0 */
    byte PTJD1       :1;                                       /* Port J Data Register Bit 1 */
    byte PTJD2       :1;                                       /* Port J Data Register Bit 2 */
    byte PTJD3       :1;                                       /* Port J Data Register Bit 3 */
    byte PTJD4       :1;                                       /* Port J Data Register Bit 4 */
    byte PTJD5       :1;                                       /* Port J Data Register Bit 5 */
    byte PTJD6       :1;                                       /* Port J Data Register Bit 6 */
    byte PTJD7       :1;                                       /* Port J Data Register Bit 7 */
  } Bits;
} PTJDSTR;
extern volatile PTJDSTR _PTJD @0x0000002E;
#define PTJD                            _PTJD.Byte
#define PTJD_PTJD0                      _PTJD.Bits.PTJD0
#define PTJD_PTJD1                      _PTJD.Bits.PTJD1
#define PTJD_PTJD2                      _PTJD.Bits.PTJD2
#define PTJD_PTJD3                      _PTJD.Bits.PTJD3
#define PTJD_PTJD4                      _PTJD.Bits.PTJD4
#define PTJD_PTJD5                      _PTJD.Bits.PTJD5
#define PTJD_PTJD6                      _PTJD.Bits.PTJD6
#define PTJD_PTJD7                      _PTJD.Bits.PTJD7

#define PTJD_PTJD0_MASK                 1U
#define PTJD_PTJD1_MASK                 2U
#define PTJD_PTJD2_MASK                 4U
#define PTJD_PTJD3_MASK                 8U
#define PTJD_PTJD4_MASK                 16U
#define PTJD_PTJD5_MASK                 32U
#define PTJD_PTJD6_MASK                 64U
#define PTJD_PTJD7_MASK                 128U


/*** PTJDD - Port J Data Direction Register; 0x0000002F ***/
typedef union {
  byte Byte;
  struct {
    byte PTJDD0      :1;                                       /* Data Direction for Port J Bit 0 */
    byte PTJDD1      :1;                                       /* Data Direction for Port J Bit 1 */
    byte PTJDD2      :1;                                       /* Data Direction for Port J Bit 2 */
    byte PTJDD3      :1;                                       /* Data Direction for Port J Bit 3 */
    byte PTJDD4      :1;                                       /* Data Direction for Port J Bit 4 */
    byte PTJDD5      :1;                                       /* Data Direction for Port J Bit 5 */
    byte PTJDD6      :1;                                       /* Data Direction for Port J Bit 6 */
    byte PTJDD7      :1;                                       /* Data Direction for Port J Bit 7 */
  } Bits;
} PTJDDSTR;
extern volatile PTJDDSTR _PTJDD @0x0000002F;
#define PTJDD                           _PTJDD.Byte
#define PTJDD_PTJDD0                    _PTJDD.Bits.PTJDD0
#define PTJDD_PTJDD1                    _PTJDD.Bits.PTJDD1
#define PTJDD_PTJDD2                    _PTJDD.Bits.PTJDD2
#define PTJDD_PTJDD3                    _PTJDD.Bits.PTJDD3
#define PTJDD_PTJDD4                    _PTJDD.Bits.PTJDD4
#define PTJDD_PTJDD5                    _PTJDD.Bits.PTJDD5
#define PTJDD_PTJDD6                    _PTJDD.Bits.PTJDD6
#define PTJDD_PTJDD7                    _PTJDD.Bits.PTJDD7

#define PTJDD_PTJDD0_MASK               1U
#define PTJDD_PTJDD1_MASK               2U
#define PTJDD_PTJDD2_MASK               4U
#define PTJDD_PTJDD3_MASK               8U
#define PTJDD_PTJDD4_MASK               16U
#define PTJDD_PTJDD5_MASK               32U
#define PTJDD_PTJDD6_MASK               64U
#define PTJDD_PTJDD7_MASK               128U


/*** IIC1A - IIC Address Register; 0x00000030 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte AD1         :1;                                       /* Slave Address Bit 1 */
    byte AD2         :1;                                       /* Slave Address Bit 2 */
    byte AD3         :1;                                       /* Slave Address Bit 3 */
    byte AD4         :1;                                       /* Slave Address Bit 4 */
    byte AD5         :1;                                       /* Slave Address Bit 5 */
    byte AD6         :1;                                       /* Slave Address Bit 6 */
    byte AD7         :1;                                       /* Slave Address Bit 7 */
  } Bits;
  struct {
    byte         :1;
    byte grpAD_1 :7;
  } MergedBits;
} IIC1ASTR;
extern volatile IIC1ASTR _IIC1A @0x00000030;
#define IIC1A                           _IIC1A.Byte
#define IIC1A_AD1                       _IIC1A.Bits.AD1
#define IIC1A_AD2                       _IIC1A.Bits.AD2
#define IIC1A_AD3                       _IIC1A.Bits.AD3
#define IIC1A_AD4                       _IIC1A.Bits.AD4
#define IIC1A_AD5                       _IIC1A.Bits.AD5
#define IIC1A_AD6                       _IIC1A.Bits.AD6
#define IIC1A_AD7                       _IIC1A.Bits.AD7
#define IIC1A_AD_1                      _IIC1A.MergedBits.grpAD_1
#define IIC1A_AD                        IIC1A_AD_1

#define IIC1A_AD1_MASK                  2U
#define IIC1A_AD2_MASK                  4U
#define IIC1A_AD3_MASK                  8U
#define IIC1A_AD4_MASK                  16U
#define IIC1A_AD5_MASK                  32U
#define IIC1A_AD6_MASK                  64U
#define IIC1A_AD7_MASK                  128U
#define IIC1A_AD_1_MASK                 254U
#define IIC1A_AD_1_BITNUM               1U


/*** IIC1F - IIC Frequency Divider Register; 0x00000031 ***/
typedef union {
  byte Byte;
  struct {
    byte ICR0        :1;                                       /* IIC Clock Rate Bit 0 */
    byte ICR1        :1;                                       /* IIC Clock Rate Bit 1 */
    byte ICR2        :1;                                       /* IIC Clock Rate Bit 2 */
    byte ICR3        :1;                                       /* IIC Clock Rate Bit 3 */
    byte ICR4        :1;                                       /* IIC Clock Rate Bit 4 */
    byte ICR5        :1;                                       /* IIC Clock Rate Bit 5 */
    byte MULT0       :1;                                       /* Multiplier Factor Bit 0 */
    byte MULT1       :1;                                       /* Multiplier Factor Bit 1 */
  } Bits;
  struct {
    byte grpICR  :6;
    byte grpMULT :2;
  } MergedBits;
} IIC1FSTR;
extern volatile IIC1FSTR _IIC1F @0x00000031;
#define IIC1F                           _IIC1F.Byte
#define IIC1F_ICR0                      _IIC1F.Bits.ICR0
#define IIC1F_ICR1                      _IIC1F.Bits.ICR1
#define IIC1F_ICR2                      _IIC1F.Bits.ICR2
#define IIC1F_ICR3                      _IIC1F.Bits.ICR3
#define IIC1F_ICR4                      _IIC1F.Bits.ICR4
#define IIC1F_ICR5                      _IIC1F.Bits.ICR5
#define IIC1F_MULT0                     _IIC1F.Bits.MULT0
#define IIC1F_MULT1                     _IIC1F.Bits.MULT1
#define IIC1F_ICR                       _IIC1F.MergedBits.grpICR
#define IIC1F_MULT                      _IIC1F.MergedBits.grpMULT

#define IIC1F_ICR0_MASK                 1U
#define IIC1F_ICR1_MASK                 2U
#define IIC1F_ICR2_MASK                 4U
#define IIC1F_ICR3_MASK                 8U
#define IIC1F_ICR4_MASK                 16U
#define IIC1F_ICR5_MASK                 32U
#define IIC1F_MULT0_MASK                64U
#define IIC1F_MULT1_MASK                128U
#define IIC1F_ICR_MASK                  63U
#define IIC1F_ICR_BITNUM                0U
#define IIC1F_MULT_MASK                 192U
#define IIC1F_MULT_BITNUM               6U


/*** IIC1C1 - IIC Control Register 1; 0x00000032 ***/
typedef union {
  byte Byte;
  union { /* Several registers at the same address */
    /*** IIC1C1 - IIC Control Register 1; Several registers at the same address ***/
    union {
      struct {
        byte             :1; 
        byte             :1; 
        byte RSTA        :1;                                       /* Repeat START */
        byte TXAK        :1;                                       /* Transmit Acknowledge Enable */
        byte TX          :1;                                       /* Transmit Mode Select */
        byte MST         :1;                                       /* Master Mode Select */
        byte IICIE       :1;                                       /* IIC Interrupt Enable */
        byte IICEN       :1;                                       /* IIC Enable */
      } Bits;
    } IIC1C1STR;
    #define IIC1C1                      _IIC1C1.Byte
    #define IIC1C1_RSTA                 _IIC1C1.SameAddr_STR.IIC1C1STR.Bits.RSTA
    #define IIC1C1_TXAK                 _IIC1C1.SameAddr_STR.IIC1C1STR.Bits.TXAK
    #define IIC1C1_TX                   _IIC1C1.SameAddr_STR.IIC1C1STR.Bits.TX
    #define IIC1C1_MST                  _IIC1C1.SameAddr_STR.IIC1C1STR.Bits.MST
    #define IIC1C1_IICIE                _IIC1C1.SameAddr_STR.IIC1C1STR.Bits.IICIE
    #define IIC1C1_IICEN                _IIC1C1.SameAddr_STR.IIC1C1STR.Bits.IICEN
    
    #define IIC1C1_RSTA_MASK            4U
    #define IIC1C1_TXAK_MASK            8U
    #define IIC1C1_TX_MASK              16U
    #define IIC1C1_MST_MASK             32U
    #define IIC1C1_IICIE_MASK           64U
    #define IIC1C1_IICEN_MASK           128U
    
    /*** IIC1C - IIC Control Register; Several registers at the same address ***/
    union {
      struct {
        byte             :1; 
        byte             :1; 
        byte RSTA        :1;                                       /* Repeat START */
        byte TXAK        :1;                                       /* Transmit Acknowledge Enable */
        byte TX          :1;                                       /* Transmit Mode Select */
        byte MST         :1;                                       /* Master Mode Select */
        byte IICIE       :1;                                       /* IIC Interrupt Enable */
        byte IICEN       :1;                                       /* IIC Enable */
      } Bits;
    } IIC1CSTR;
    #define IIC1C                       _IIC1C1.Byte
    #define IIC1C_RSTA                  _IIC1C1.SameAddr_STR.IIC1CSTR.Bits.RSTA
    #define IIC1C_TXAK                  _IIC1C1.SameAddr_STR.IIC1CSTR.Bits.TXAK
    #define IIC1C_TX                    _IIC1C1.SameAddr_STR.IIC1CSTR.Bits.TX
    #define IIC1C_MST                   _IIC1C1.SameAddr_STR.IIC1CSTR.Bits.MST
    #define IIC1C_IICIE                 _IIC1C1.SameAddr_STR.IIC1CSTR.Bits.IICIE
    #define IIC1C_IICEN                 _IIC1C1.SameAddr_STR.IIC1CSTR.Bits.IICEN
    
    #define IIC1C_RSTA_MASK             4U
    #define IIC1C_TXAK_MASK             8U
    #define IIC1C_TX_MASK               16U
    #define IIC1C_MST_MASK              32U
    #define IIC1C_IICIE_MASK            64U
    #define IIC1C_IICEN_MASK            128U
    
  } SameAddr_STR; /*Several registers at the same address */

} IIC1C1STR;
extern volatile IIC1C1STR _IIC1C1 @0x00000032;


/*** IIC1S - IIC Status Register; 0x00000033 ***/
typedef union {
  byte Byte;
  struct {
    byte RXAK        :1;                                       /* Receive Acknowledge */
    byte IICIF       :1;                                       /* IIC Interrupt Flag */
    byte SRW         :1;                                       /* Slave Read/Write */
    byte             :1; 
    byte ARBL        :1;                                       /* Arbitration Lost */
    byte BUSY        :1;                                       /* Bus Busy */
    byte IAAS        :1;                                       /* Addressed as a Slave */
    byte TCF         :1;                                       /* Transfer Complete Flag */
  } Bits;
} IIC1SSTR;
extern volatile IIC1SSTR _IIC1S @0x00000033;
#define IIC1S                           _IIC1S.Byte
#define IIC1S_RXAK                      _IIC1S.Bits.RXAK
#define IIC1S_IICIF                     _IIC1S.Bits.IICIF
#define IIC1S_SRW                       _IIC1S.Bits.SRW
#define IIC1S_ARBL                      _IIC1S.Bits.ARBL
#define IIC1S_BUSY                      _IIC1S.Bits.BUSY
#define IIC1S_IAAS                      _IIC1S.Bits.IAAS
#define IIC1S_TCF                       _IIC1S.Bits.TCF

#define IIC1S_RXAK_MASK                 1U
#define IIC1S_IICIF_MASK                2U
#define IIC1S_SRW_MASK                  4U
#define IIC1S_ARBL_MASK                 16U
#define IIC1S_BUSY_MASK                 32U
#define IIC1S_IAAS_MASK                 64U
#define IIC1S_TCF_MASK                  128U


/*** IIC1D - IIC Data I/O Register; 0x00000034 ***/
typedef union {
  byte Byte;
  struct {
    byte DATA0       :1;                                       /* IIC Data Bit 0 */
    byte DATA1       :1;                                       /* IIC Data Bit 1 */
    byte DATA2       :1;                                       /* IIC Data Bit 2 */
    byte DATA3       :1;                                       /* IIC Data Bit 3 */
    byte DATA4       :1;                                       /* IIC Data Bit 4 */
    byte DATA5       :1;                                       /* IIC Data Bit 5 */
    byte DATA6       :1;                                       /* IIC Data Bit 6 */
    byte DATA7       :1;                                       /* IIC Data Bit 7 */
  } Bits;
} IIC1DSTR;
extern volatile IIC1DSTR _IIC1D @0x00000034;
#define IIC1D                           _IIC1D.Byte
#define IIC1D_DATA0                     _IIC1D.Bits.DATA0
#define IIC1D_DATA1                     _IIC1D.Bits.DATA1
#define IIC1D_DATA2                     _IIC1D.Bits.DATA2
#define IIC1D_DATA3                     _IIC1D.Bits.DATA3
#define IIC1D_DATA4                     _IIC1D.Bits.DATA4
#define IIC1D_DATA5                     _IIC1D.Bits.DATA5
#define IIC1D_DATA6                     _IIC1D.Bits.DATA6
#define IIC1D_DATA7                     _IIC1D.Bits.DATA7

#define IIC1D_DATA0_MASK                1U
#define IIC1D_DATA1_MASK                2U
#define IIC1D_DATA2_MASK                4U
#define IIC1D_DATA3_MASK                8U
#define IIC1D_DATA4_MASK                16U
#define IIC1D_DATA5_MASK                32U
#define IIC1D_DATA6_MASK                64U
#define IIC1D_DATA7_MASK                128U


/*** IIC1C2 - IIC Control Register 2; 0x00000035 ***/
typedef union {
  byte Byte;
  struct {
    byte AD8         :1;                                       /* Slave Address Bit 8 */
    byte AD9         :1;                                       /* Slave Address Bit 9 */
    byte AD10        :1;                                       /* Slave Address Bit 10 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte ADEXT       :1;                                       /* Address Extension */
    byte GCAEN       :1;                                       /* General Call Address Enable */
  } Bits;
  struct {
    byte grpAD_8 :3;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} IIC1C2STR;
extern volatile IIC1C2STR _IIC1C2 @0x00000035;
#define IIC1C2                          _IIC1C2.Byte
#define IIC1C2_AD8                      _IIC1C2.Bits.AD8
#define IIC1C2_AD9                      _IIC1C2.Bits.AD9
#define IIC1C2_AD10                     _IIC1C2.Bits.AD10
#define IIC1C2_ADEXT                    _IIC1C2.Bits.ADEXT
#define IIC1C2_GCAEN                    _IIC1C2.Bits.GCAEN
#define IIC1C2_AD_8                     _IIC1C2.MergedBits.grpAD_8
#define IIC1C2_AD                       IIC1C2_AD_8

#define IIC1C2_AD8_MASK                 1U
#define IIC1C2_AD9_MASK                 2U
#define IIC1C2_AD10_MASK                4U
#define IIC1C2_ADEXT_MASK               64U
#define IIC1C2_GCAEN_MASK               128U
#define IIC1C2_AD_8_MASK                7U
#define IIC1C2_AD_8_BITNUM              0U


/*** ICSC1 - ICS Control Register 1; 0x00000038 ***/
typedef union {
  byte Byte;
  struct {
    byte IREFSTEN    :1;                                       /* Internal Reference Stop Enable */
    byte IRCLKEN     :1;                                       /* Internal Reference Clock Enable */
    byte IREFS       :1;                                       /* Internal Reference Select */
    byte RDIV0       :1;                                       /* Reference Divider, bit 0 */
    byte RDIV1       :1;                                       /* Reference Divider, bit 1 */
    byte RDIV2       :1;                                       /* Reference Divider, bit 2 */
    byte CLKS0       :1;                                       /* Clock Source Select, bit 0 */
    byte CLKS1       :1;                                       /* Clock Source Select, bit 1 */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpRDIV :3;
    byte grpCLKS :2;
  } MergedBits;
} ICSC1STR;
extern volatile ICSC1STR _ICSC1 @0x00000038;
#define ICSC1                           _ICSC1.Byte
#define ICSC1_IREFSTEN                  _ICSC1.Bits.IREFSTEN
#define ICSC1_IRCLKEN                   _ICSC1.Bits.IRCLKEN
#define ICSC1_IREFS                     _ICSC1.Bits.IREFS
#define ICSC1_RDIV0                     _ICSC1.Bits.RDIV0
#define ICSC1_RDIV1                     _ICSC1.Bits.RDIV1
#define ICSC1_RDIV2                     _ICSC1.Bits.RDIV2
#define ICSC1_CLKS0                     _ICSC1.Bits.CLKS0
#define ICSC1_CLKS1                     _ICSC1.Bits.CLKS1
#define ICSC1_RDIV                      _ICSC1.MergedBits.grpRDIV
#define ICSC1_CLKS                      _ICSC1.MergedBits.grpCLKS

#define ICSC1_IREFSTEN_MASK             1U
#define ICSC1_IRCLKEN_MASK              2U
#define ICSC1_IREFS_MASK                4U
#define ICSC1_RDIV0_MASK                8U
#define ICSC1_RDIV1_MASK                16U
#define ICSC1_RDIV2_MASK                32U
#define ICSC1_CLKS0_MASK                64U
#define ICSC1_CLKS1_MASK                128U
#define ICSC1_RDIV_MASK                 56U
#define ICSC1_RDIV_BITNUM               3U
#define ICSC1_CLKS_MASK                 192U
#define ICSC1_CLKS_BITNUM               6U


/*** ICSC2 - ICS Control Register 2; 0x00000039 ***/
typedef union {
  byte Byte;
  struct {
    byte EREFSTEN    :1;                                       /* External Reference Stop Enable */
    byte ERCLKEN     :1;                                       /* External Reference Enable */
    byte EREFS       :1;                                       /* External Reference Select */
    byte LP          :1;                                       /* Low Power Select */
    byte HGO         :1;                                       /* High Gain Oscillator Select */
    byte RANGE       :1;                                       /* Frequency Range Select */
    byte BDIV0       :1;                                       /* Bus Frequency Divider, bit 0 */
    byte BDIV1       :1;                                       /* Bus Frequency Divider, bit 1 */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpBDIV :2;
  } MergedBits;
} ICSC2STR;
extern volatile ICSC2STR _ICSC2 @0x00000039;
#define ICSC2                           _ICSC2.Byte
#define ICSC2_EREFSTEN                  _ICSC2.Bits.EREFSTEN
#define ICSC2_ERCLKEN                   _ICSC2.Bits.ERCLKEN
#define ICSC2_EREFS                     _ICSC2.Bits.EREFS
#define ICSC2_LP                        _ICSC2.Bits.LP
#define ICSC2_HGO                       _ICSC2.Bits.HGO
#define ICSC2_RANGE                     _ICSC2.Bits.RANGE
#define ICSC2_BDIV0                     _ICSC2.Bits.BDIV0
#define ICSC2_BDIV1                     _ICSC2.Bits.BDIV1
#define ICSC2_BDIV                      _ICSC2.MergedBits.grpBDIV

#define ICSC2_EREFSTEN_MASK             1U
#define ICSC2_ERCLKEN_MASK              2U
#define ICSC2_EREFS_MASK                4U
#define ICSC2_LP_MASK                   8U
#define ICSC2_HGO_MASK                  16U
#define ICSC2_RANGE_MASK                32U
#define ICSC2_BDIV0_MASK                64U
#define ICSC2_BDIV1_MASK                128U
#define ICSC2_BDIV_MASK                 192U
#define ICSC2_BDIV_BITNUM               6U


/*** ICSTRM - ICS Trim Register; 0x0000003A ***/
typedef union {
  byte Byte;
  struct {
    byte TRIM0       :1;                                       /* ICS Trim Setting, bit 0 */
    byte TRIM1       :1;                                       /* ICS Trim Setting, bit 1 */
    byte TRIM2       :1;                                       /* ICS Trim Setting, bit 2 */
    byte TRIM3       :1;                                       /* ICS Trim Setting, bit 3 */
    byte TRIM4       :1;                                       /* ICS Trim Setting, bit 4 */
    byte TRIM5       :1;                                       /* ICS Trim Setting, bit 5 */
    byte TRIM6       :1;                                       /* ICS Trim Setting, bit 6 */
    byte TRIM7       :1;                                       /* ICS Trim Setting, bit 7 */
  } Bits;
} ICSTRMSTR;
extern volatile ICSTRMSTR _ICSTRM @0x0000003A;
#define ICSTRM                          _ICSTRM.Byte
#define ICSTRM_TRIM0                    _ICSTRM.Bits.TRIM0
#define ICSTRM_TRIM1                    _ICSTRM.Bits.TRIM1
#define ICSTRM_TRIM2                    _ICSTRM.Bits.TRIM2
#define ICSTRM_TRIM3                    _ICSTRM.Bits.TRIM3
#define ICSTRM_TRIM4                    _ICSTRM.Bits.TRIM4
#define ICSTRM_TRIM5                    _ICSTRM.Bits.TRIM5
#define ICSTRM_TRIM6                    _ICSTRM.Bits.TRIM6
#define ICSTRM_TRIM7                    _ICSTRM.Bits.TRIM7

#define ICSTRM_TRIM0_MASK               1U
#define ICSTRM_TRIM1_MASK               2U
#define ICSTRM_TRIM2_MASK               4U
#define ICSTRM_TRIM3_MASK               8U
#define ICSTRM_TRIM4_MASK               16U
#define ICSTRM_TRIM5_MASK               32U
#define ICSTRM_TRIM6_MASK               64U
#define ICSTRM_TRIM7_MASK               128U


/*** ICSSC - ICS Status and Control Register; 0x0000003B ***/
typedef union {
  byte Byte;
  struct {
    byte FTRIM       :1;                                       /* ICS Fine Trim */
    byte OSCINIT     :1;                                       /* OSC Initialization */
    byte CLKST0      :1;                                       /* Clock Mode Status, bit 0 */
    byte CLKST1      :1;                                       /* Clock Mode Status, bit 1 */
    byte IREFST      :1;                                       /* Internal Reference Status */
    byte DMX32       :1;                                       /* DCO Maximum frequency with 32.768 kHz reference */
    byte DRST_DRS0   :1;                                       /* DCO Range Status/Range Select, bit 0 */
    byte DRST_DRS1   :1;                                       /* DCO Range Status/Range Select, bit 1 */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpCLKST :2;
    byte         :1;
    byte grpDMX_32 :1;
    byte grpDRST_DRS :2;
  } MergedBits;
} ICSSCSTR;
extern volatile ICSSCSTR _ICSSC @0x0000003B;
#define ICSSC                           _ICSSC.Byte
#define ICSSC_FTRIM                     _ICSSC.Bits.FTRIM
#define ICSSC_OSCINIT                   _ICSSC.Bits.OSCINIT
#define ICSSC_CLKST0                    _ICSSC.Bits.CLKST0
#define ICSSC_CLKST1                    _ICSSC.Bits.CLKST1
#define ICSSC_IREFST                    _ICSSC.Bits.IREFST
#define ICSSC_DMX32                     _ICSSC.Bits.DMX32
#define ICSSC_DRST_DRS0                 _ICSSC.Bits.DRST_DRS0
#define ICSSC_DRST_DRS1                 _ICSSC.Bits.DRST_DRS1
#define ICSSC_CLKST                     _ICSSC.MergedBits.grpCLKST
#define ICSSC_DRST_DRS                  _ICSSC.MergedBits.grpDRST_DRS

#define ICSSC_FTRIM_MASK                1U
#define ICSSC_OSCINIT_MASK              2U
#define ICSSC_CLKST0_MASK               4U
#define ICSSC_CLKST1_MASK               8U
#define ICSSC_IREFST_MASK               16U
#define ICSSC_DMX32_MASK                32U
#define ICSSC_DRST_DRS0_MASK            64U
#define ICSSC_DRST_DRS1_MASK            128U
#define ICSSC_CLKST_MASK                12U
#define ICSSC_CLKST_BITNUM              2U
#define ICSSC_DRST_DRS_MASK             192U
#define ICSSC_DRST_DRS_BITNUM           6U


/*** KBI2SC - KBI2 Status and Control Register; 0x0000003C ***/
typedef union {
  byte Byte;
  struct {
    byte KBIMOD      :1;                                       /* Keyboard Detection Mode */
    byte KBIE        :1;                                       /* Keyboard Interrupt Enable */
    byte KBACK       :1;                                       /* Keyboard Interrupt Acknowledge */
    byte KBF         :1;                                       /* Keyboard Interrupt Flag */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} KBI2SCSTR;
extern volatile KBI2SCSTR _KBI2SC @0x0000003C;
#define KBI2SC                          _KBI2SC.Byte
#define KBI2SC_KBIMOD                   _KBI2SC.Bits.KBIMOD
#define KBI2SC_KBIE                     _KBI2SC.Bits.KBIE
#define KBI2SC_KBACK                    _KBI2SC.Bits.KBACK
#define KBI2SC_KBF                      _KBI2SC.Bits.KBF

#define KBI2SC_KBIMOD_MASK              1U
#define KBI2SC_KBIE_MASK                2U
#define KBI2SC_KBACK_MASK               4U
#define KBI2SC_KBF_MASK                 8U


/*** KBI2PE - KBI2 Pin Enable Register; 0x0000003D ***/
typedef union {
  byte Byte;
  struct {
    byte KBIPE0      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 0 */
    byte KBIPE1      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 1 */
    byte KBIPE2      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 2 */
    byte KBIPE3      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 3 */
    byte KBIPE4      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 4 */
    byte KBIPE5      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 5 */
    byte KBIPE6      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 6 */
    byte KBIPE7      :1;                                       /* Keyboard Pin Enable for KBI Port Bit 7 */
  } Bits;
} KBI2PESTR;
extern volatile KBI2PESTR _KBI2PE @0x0000003D;
#define KBI2PE                          _KBI2PE.Byte
#define KBI2PE_KBIPE0                   _KBI2PE.Bits.KBIPE0
#define KBI2PE_KBIPE1                   _KBI2PE.Bits.KBIPE1
#define KBI2PE_KBIPE2                   _KBI2PE.Bits.KBIPE2
#define KBI2PE_KBIPE3                   _KBI2PE.Bits.KBIPE3
#define KBI2PE_KBIPE4                   _KBI2PE.Bits.KBIPE4
#define KBI2PE_KBIPE5                   _KBI2PE.Bits.KBIPE5
#define KBI2PE_KBIPE6                   _KBI2PE.Bits.KBIPE6
#define KBI2PE_KBIPE7                   _KBI2PE.Bits.KBIPE7

#define KBI2PE_KBIPE0_MASK              1U
#define KBI2PE_KBIPE1_MASK              2U
#define KBI2PE_KBIPE2_MASK              4U
#define KBI2PE_KBIPE3_MASK              8U
#define KBI2PE_KBIPE4_MASK              16U
#define KBI2PE_KBIPE5_MASK              32U
#define KBI2PE_KBIPE6_MASK              64U
#define KBI2PE_KBIPE7_MASK              128U


/*** KBI2ES - KBI2 Edge Select Register; 0x0000003E ***/
typedef union {
  byte Byte;
  struct {
    byte KBEDG0      :1;                                       /* Keyboard Edge Select Bit 0 */
    byte KBEDG1      :1;                                       /* Keyboard Edge Select Bit 1 */
    byte KBEDG2      :1;                                       /* Keyboard Edge Select Bit 2 */
    byte KBEDG3      :1;                                       /* Keyboard Edge Select Bit 3 */
    byte KBEDG4      :1;                                       /* Keyboard Edge Select Bit 4 */
    byte KBEDG5      :1;                                       /* Keyboard Edge Select Bit 5 */
    byte KBEDG6      :1;                                       /* Keyboard Edge Select Bit 6 */
    byte KBEDG7      :1;                                       /* Keyboard Edge Select Bit 7 */
  } Bits;
} KBI2ESSTR;
extern volatile KBI2ESSTR _KBI2ES @0x0000003E;
#define KBI2ES                          _KBI2ES.Byte
#define KBI2ES_KBEDG0                   _KBI2ES.Bits.KBEDG0
#define KBI2ES_KBEDG1                   _KBI2ES.Bits.KBEDG1
#define KBI2ES_KBEDG2                   _KBI2ES.Bits.KBEDG2
#define KBI2ES_KBEDG3                   _KBI2ES.Bits.KBEDG3
#define KBI2ES_KBEDG4                   _KBI2ES.Bits.KBEDG4
#define KBI2ES_KBEDG5                   _KBI2ES.Bits.KBEDG5
#define KBI2ES_KBEDG6                   _KBI2ES.Bits.KBEDG6
#define KBI2ES_KBEDG7                   _KBI2ES.Bits.KBEDG7

#define KBI2ES_KBEDG0_MASK              1U
#define KBI2ES_KBEDG1_MASK              2U
#define KBI2ES_KBEDG2_MASK              4U
#define KBI2ES_KBEDG3_MASK              8U
#define KBI2ES_KBEDG4_MASK              16U
#define KBI2ES_KBEDG5_MASK              32U
#define KBI2ES_KBEDG6_MASK              64U
#define KBI2ES_KBEDG7_MASK              128U


/*** TPM1SC - TPM1 Status and Control Register; 0x00000040 ***/
typedef union {
  byte Byte;
  struct {
    byte PS0         :1;                                       /* Prescale Divisor Select Bit 0 */
    byte PS1         :1;                                       /* Prescale Divisor Select Bit 1 */
    byte PS2         :1;                                       /* Prescale Divisor Select Bit 2 */
    byte CLKSA       :1;                                       /* Clock Source Select A */
    byte CLKSB       :1;                                       /* Clock Source Select B */
    byte CPWMS       :1;                                       /* Center-Aligned PWM Select */
    byte TOIE        :1;                                       /* Timer Overflow Interrupt Enable */
    byte TOF         :1;                                       /* Timer Overflow Flag */
  } Bits;
  struct {
    byte grpPS   :3;
    byte grpCLKSx :2;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1SCSTR;
extern volatile TPM1SCSTR _TPM1SC @0x00000040;
#define TPM1SC                          _TPM1SC.Byte
#define TPM1SC_PS0                      _TPM1SC.Bits.PS0
#define TPM1SC_PS1                      _TPM1SC.Bits.PS1
#define TPM1SC_PS2                      _TPM1SC.Bits.PS2
#define TPM1SC_CLKSA                    _TPM1SC.Bits.CLKSA
#define TPM1SC_CLKSB                    _TPM1SC.Bits.CLKSB
#define TPM1SC_CPWMS                    _TPM1SC.Bits.CPWMS
#define TPM1SC_TOIE                     _TPM1SC.Bits.TOIE
#define TPM1SC_TOF                      _TPM1SC.Bits.TOF
#define TPM1SC_PS                       _TPM1SC.MergedBits.grpPS
#define TPM1SC_CLKSx                    _TPM1SC.MergedBits.grpCLKSx

#define TPM1SC_PS0_MASK                 1U
#define TPM1SC_PS1_MASK                 2U
#define TPM1SC_PS2_MASK                 4U
#define TPM1SC_CLKSA_MASK               8U
#define TPM1SC_CLKSB_MASK               16U
#define TPM1SC_CPWMS_MASK               32U
#define TPM1SC_TOIE_MASK                64U
#define TPM1SC_TOF_MASK                 128U
#define TPM1SC_PS_MASK                  7U
#define TPM1SC_PS_BITNUM                0U
#define TPM1SC_CLKSx_MASK               24U
#define TPM1SC_CLKSx_BITNUM             3U


/*** TPM1CNT - TPM1 Timer Counter Register; 0x00000041 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1CNTH - TPM1 Timer Counter Register High; 0x00000041 ***/
    union {
      byte Byte;
    } TPM1CNTHSTR;
    #define TPM1CNTH                    _TPM1CNT.Overlap_STR.TPM1CNTHSTR.Byte
    

    /*** TPM1CNTL - TPM1 Timer Counter Register Low; 0x00000042 ***/
    union {
      byte Byte;
    } TPM1CNTLSTR;
    #define TPM1CNTL                    _TPM1CNT.Overlap_STR.TPM1CNTLSTR.Byte
    
  } Overlap_STR;

} TPM1CNTSTR;
extern volatile TPM1CNTSTR _TPM1CNT @0x00000041;
#define TPM1CNT                         _TPM1CNT.Word


/*** TPM1MOD - TPM1 Timer Counter Modulo Register; 0x00000043 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1MODH - TPM1 Timer Counter Modulo Register High; 0x00000043 ***/
    union {
      byte Byte;
    } TPM1MODHSTR;
    #define TPM1MODH                    _TPM1MOD.Overlap_STR.TPM1MODHSTR.Byte
    

    /*** TPM1MODL - TPM1 Timer Counter Modulo Register Low; 0x00000044 ***/
    union {
      byte Byte;
    } TPM1MODLSTR;
    #define TPM1MODL                    _TPM1MOD.Overlap_STR.TPM1MODLSTR.Byte
    
  } Overlap_STR;

} TPM1MODSTR;
extern volatile TPM1MODSTR _TPM1MOD @0x00000043;
#define TPM1MOD                         _TPM1MOD.Word


/*** TPM1C0SC - TPM1 Timer Channel 0 Status and Control Register; 0x00000045 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS0A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS0B       :1;                                       /* Edge/Level Select Bit B */
    byte MS0A        :1;                                       /* Mode Select A for TPM Channel 0 */
    byte MS0B        :1;                                       /* Mode Select B for TPM Channel 0 */
    byte CH0IE       :1;                                       /* Channel 0 Interrupt Enable */
    byte CH0F        :1;                                       /* Channel 0 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS0x :2;
    byte grpMS0x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1C0SCSTR;
extern volatile TPM1C0SCSTR _TPM1C0SC @0x00000045;
#define TPM1C0SC                        _TPM1C0SC.Byte
#define TPM1C0SC_ELS0A                  _TPM1C0SC.Bits.ELS0A
#define TPM1C0SC_ELS0B                  _TPM1C0SC.Bits.ELS0B
#define TPM1C0SC_MS0A                   _TPM1C0SC.Bits.MS0A
#define TPM1C0SC_MS0B                   _TPM1C0SC.Bits.MS0B
#define TPM1C0SC_CH0IE                  _TPM1C0SC.Bits.CH0IE
#define TPM1C0SC_CH0F                   _TPM1C0SC.Bits.CH0F
#define TPM1C0SC_ELS0x                  _TPM1C0SC.MergedBits.grpELS0x
#define TPM1C0SC_MS0x                   _TPM1C0SC.MergedBits.grpMS0x

#define TPM1C0SC_ELS0A_MASK             4U
#define TPM1C0SC_ELS0B_MASK             8U
#define TPM1C0SC_MS0A_MASK              16U
#define TPM1C0SC_MS0B_MASK              32U
#define TPM1C0SC_CH0IE_MASK             64U
#define TPM1C0SC_CH0F_MASK              128U
#define TPM1C0SC_ELS0x_MASK             12U
#define TPM1C0SC_ELS0x_BITNUM           2U
#define TPM1C0SC_MS0x_MASK              48U
#define TPM1C0SC_MS0x_BITNUM            4U


/*** TPM1C0V - TPM1 Timer Channel 0 Value Register; 0x00000046 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1C0VH - TPM1 Timer Channel 0 Value Register High; 0x00000046 ***/
    union {
      byte Byte;
    } TPM1C0VHSTR;
    #define TPM1C0VH                    _TPM1C0V.Overlap_STR.TPM1C0VHSTR.Byte
    

    /*** TPM1C0VL - TPM1 Timer Channel 0 Value Register Low; 0x00000047 ***/
    union {
      byte Byte;
    } TPM1C0VLSTR;
    #define TPM1C0VL                    _TPM1C0V.Overlap_STR.TPM1C0VLSTR.Byte
    
  } Overlap_STR;

} TPM1C0VSTR;
extern volatile TPM1C0VSTR _TPM1C0V @0x00000046;
#define TPM1C0V                         _TPM1C0V.Word


/*** TPM1C1SC - TPM1 Timer Channel 1 Status and Control Register; 0x00000048 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS1A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS1B       :1;                                       /* Edge/Level Select Bit B */
    byte MS1A        :1;                                       /* Mode Select A for TPM Channel 1 */
    byte MS1B        :1;                                       /* Mode Select B for TPM Channel 1 */
    byte CH1IE       :1;                                       /* Channel 1 Interrupt Enable */
    byte CH1F        :1;                                       /* Channel 1 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS1x :2;
    byte grpMS1x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1C1SCSTR;
extern volatile TPM1C1SCSTR _TPM1C1SC @0x00000048;
#define TPM1C1SC                        _TPM1C1SC.Byte
#define TPM1C1SC_ELS1A                  _TPM1C1SC.Bits.ELS1A
#define TPM1C1SC_ELS1B                  _TPM1C1SC.Bits.ELS1B
#define TPM1C1SC_MS1A                   _TPM1C1SC.Bits.MS1A
#define TPM1C1SC_MS1B                   _TPM1C1SC.Bits.MS1B
#define TPM1C1SC_CH1IE                  _TPM1C1SC.Bits.CH1IE
#define TPM1C1SC_CH1F                   _TPM1C1SC.Bits.CH1F
#define TPM1C1SC_ELS1x                  _TPM1C1SC.MergedBits.grpELS1x
#define TPM1C1SC_MS1x                   _TPM1C1SC.MergedBits.grpMS1x

#define TPM1C1SC_ELS1A_MASK             4U
#define TPM1C1SC_ELS1B_MASK             8U
#define TPM1C1SC_MS1A_MASK              16U
#define TPM1C1SC_MS1B_MASK              32U
#define TPM1C1SC_CH1IE_MASK             64U
#define TPM1C1SC_CH1F_MASK              128U
#define TPM1C1SC_ELS1x_MASK             12U
#define TPM1C1SC_ELS1x_BITNUM           2U
#define TPM1C1SC_MS1x_MASK              48U
#define TPM1C1SC_MS1x_BITNUM            4U


/*** TPM1C1V - TPM1 Timer Channel 1 Value Register; 0x00000049 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1C1VH - TPM1 Timer Channel 1 Value Register High; 0x00000049 ***/
    union {
      byte Byte;
    } TPM1C1VHSTR;
    #define TPM1C1VH                    _TPM1C1V.Overlap_STR.TPM1C1VHSTR.Byte
    

    /*** TPM1C1VL - TPM1 Timer Channel 1 Value Register Low; 0x0000004A ***/
    union {
      byte Byte;
    } TPM1C1VLSTR;
    #define TPM1C1VL                    _TPM1C1V.Overlap_STR.TPM1C1VLSTR.Byte
    
  } Overlap_STR;

} TPM1C1VSTR;
extern volatile TPM1C1VSTR _TPM1C1V @0x00000049;
#define TPM1C1V                         _TPM1C1V.Word


/*** TPM1C2SC - TPM1 Timer Channel 2 Status and Control Register; 0x0000004B ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS2A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS2B       :1;                                       /* Edge/Level Select Bit B */
    byte MS2A        :1;                                       /* Mode Select A for TPM Channel 2 */
    byte MS2B        :1;                                       /* Mode Select B for TPM Channel 2 */
    byte CH2IE       :1;                                       /* Channel 2 Interrupt Enable */
    byte CH2F        :1;                                       /* Channel 2 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS2x :2;
    byte grpMS2x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM1C2SCSTR;
extern volatile TPM1C2SCSTR _TPM1C2SC @0x0000004B;
#define TPM1C2SC                        _TPM1C2SC.Byte
#define TPM1C2SC_ELS2A                  _TPM1C2SC.Bits.ELS2A
#define TPM1C2SC_ELS2B                  _TPM1C2SC.Bits.ELS2B
#define TPM1C2SC_MS2A                   _TPM1C2SC.Bits.MS2A
#define TPM1C2SC_MS2B                   _TPM1C2SC.Bits.MS2B
#define TPM1C2SC_CH2IE                  _TPM1C2SC.Bits.CH2IE
#define TPM1C2SC_CH2F                   _TPM1C2SC.Bits.CH2F
#define TPM1C2SC_ELS2x                  _TPM1C2SC.MergedBits.grpELS2x
#define TPM1C2SC_MS2x                   _TPM1C2SC.MergedBits.grpMS2x

#define TPM1C2SC_ELS2A_MASK             4U
#define TPM1C2SC_ELS2B_MASK             8U
#define TPM1C2SC_MS2A_MASK              16U
#define TPM1C2SC_MS2B_MASK              32U
#define TPM1C2SC_CH2IE_MASK             64U
#define TPM1C2SC_CH2F_MASK              128U
#define TPM1C2SC_ELS2x_MASK             12U
#define TPM1C2SC_ELS2x_BITNUM           2U
#define TPM1C2SC_MS2x_MASK              48U
#define TPM1C2SC_MS2x_BITNUM            4U


/*** TPM1C2V - TPM1 Timer Channel 2 Value Register; 0x0000004C ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM1C2VH - TPM1 Timer Channel 2 Value Register High; 0x0000004C ***/
    union {
      byte Byte;
    } TPM1C2VHSTR;
    #define TPM1C2VH                    _TPM1C2V.Overlap_STR.TPM1C2VHSTR.Byte
    

    /*** TPM1C2VL - TPM1 Timer Channel 2 Value Register Low; 0x0000004D ***/
    union {
      byte Byte;
    } TPM1C2VLSTR;
    #define TPM1C2VL                    _TPM1C2V.Overlap_STR.TPM1C2VLSTR.Byte
    
  } Overlap_STR;

} TPM1C2VSTR;
extern volatile TPM1C2VSTR _TPM1C2V @0x0000004C;
#define TPM1C2V                         _TPM1C2V.Word


/*** TPM2SC - TPM2 Status and Control Register; 0x00000050 ***/
typedef union {
  byte Byte;
  struct {
    byte PS0         :1;                                       /* Prescale Divisor Select Bit 0 */
    byte PS1         :1;                                       /* Prescale Divisor Select Bit 1 */
    byte PS2         :1;                                       /* Prescale Divisor Select Bit 2 */
    byte CLKSA       :1;                                       /* Clock Source Select A */
    byte CLKSB       :1;                                       /* Clock Source Select B */
    byte CPWMS       :1;                                       /* Center-Aligned PWM Select */
    byte TOIE        :1;                                       /* Timer Overflow Interrupt Enable */
    byte TOF         :1;                                       /* Timer Overflow Flag */
  } Bits;
  struct {
    byte grpPS   :3;
    byte grpCLKSx :2;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2SCSTR;
extern volatile TPM2SCSTR _TPM2SC @0x00000050;
#define TPM2SC                          _TPM2SC.Byte
#define TPM2SC_PS0                      _TPM2SC.Bits.PS0
#define TPM2SC_PS1                      _TPM2SC.Bits.PS1
#define TPM2SC_PS2                      _TPM2SC.Bits.PS2
#define TPM2SC_CLKSA                    _TPM2SC.Bits.CLKSA
#define TPM2SC_CLKSB                    _TPM2SC.Bits.CLKSB
#define TPM2SC_CPWMS                    _TPM2SC.Bits.CPWMS
#define TPM2SC_TOIE                     _TPM2SC.Bits.TOIE
#define TPM2SC_TOF                      _TPM2SC.Bits.TOF
#define TPM2SC_PS                       _TPM2SC.MergedBits.grpPS
#define TPM2SC_CLKSx                    _TPM2SC.MergedBits.grpCLKSx

#define TPM2SC_PS0_MASK                 1U
#define TPM2SC_PS1_MASK                 2U
#define TPM2SC_PS2_MASK                 4U
#define TPM2SC_CLKSA_MASK               8U
#define TPM2SC_CLKSB_MASK               16U
#define TPM2SC_CPWMS_MASK               32U
#define TPM2SC_TOIE_MASK                64U
#define TPM2SC_TOF_MASK                 128U
#define TPM2SC_PS_MASK                  7U
#define TPM2SC_PS_BITNUM                0U
#define TPM2SC_CLKSx_MASK               24U
#define TPM2SC_CLKSx_BITNUM             3U


/*** TPM2CNT - TPM2 Timer Counter Register; 0x00000051 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2CNTH - TPM2 Timer Counter Register High; 0x00000051 ***/
    union {
      byte Byte;
    } TPM2CNTHSTR;
    #define TPM2CNTH                    _TPM2CNT.Overlap_STR.TPM2CNTHSTR.Byte
    

    /*** TPM2CNTL - TPM2 Timer Counter Register Low; 0x00000052 ***/
    union {
      byte Byte;
    } TPM2CNTLSTR;
    #define TPM2CNTL                    _TPM2CNT.Overlap_STR.TPM2CNTLSTR.Byte
    
  } Overlap_STR;

} TPM2CNTSTR;
extern volatile TPM2CNTSTR _TPM2CNT @0x00000051;
#define TPM2CNT                         _TPM2CNT.Word


/*** TPM2MOD - TPM2 Timer Counter Modulo Register; 0x00000053 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2MODH - TPM2 Timer Counter Modulo Register High; 0x00000053 ***/
    union {
      byte Byte;
    } TPM2MODHSTR;
    #define TPM2MODH                    _TPM2MOD.Overlap_STR.TPM2MODHSTR.Byte
    

    /*** TPM2MODL - TPM2 Timer Counter Modulo Register Low; 0x00000054 ***/
    union {
      byte Byte;
    } TPM2MODLSTR;
    #define TPM2MODL                    _TPM2MOD.Overlap_STR.TPM2MODLSTR.Byte
    
  } Overlap_STR;

} TPM2MODSTR;
extern volatile TPM2MODSTR _TPM2MOD @0x00000053;
#define TPM2MOD                         _TPM2MOD.Word


/*** TPM2C0SC - TPM2 Timer Channel 0 Status and Control Register; 0x00000055 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS0A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS0B       :1;                                       /* Edge/Level Select Bit B */
    byte MS0A        :1;                                       /* Mode Select A for TPM Channel 0 */
    byte MS0B        :1;                                       /* Mode Select B for TPM Channel 0 */
    byte CH0IE       :1;                                       /* Channel 0 Interrupt Enable */
    byte CH0F        :1;                                       /* Channel 0 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS0x :2;
    byte grpMS0x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2C0SCSTR;
extern volatile TPM2C0SCSTR _TPM2C0SC @0x00000055;
#define TPM2C0SC                        _TPM2C0SC.Byte
#define TPM2C0SC_ELS0A                  _TPM2C0SC.Bits.ELS0A
#define TPM2C0SC_ELS0B                  _TPM2C0SC.Bits.ELS0B
#define TPM2C0SC_MS0A                   _TPM2C0SC.Bits.MS0A
#define TPM2C0SC_MS0B                   _TPM2C0SC.Bits.MS0B
#define TPM2C0SC_CH0IE                  _TPM2C0SC.Bits.CH0IE
#define TPM2C0SC_CH0F                   _TPM2C0SC.Bits.CH0F
#define TPM2C0SC_ELS0x                  _TPM2C0SC.MergedBits.grpELS0x
#define TPM2C0SC_MS0x                   _TPM2C0SC.MergedBits.grpMS0x

#define TPM2C0SC_ELS0A_MASK             4U
#define TPM2C0SC_ELS0B_MASK             8U
#define TPM2C0SC_MS0A_MASK              16U
#define TPM2C0SC_MS0B_MASK              32U
#define TPM2C0SC_CH0IE_MASK             64U
#define TPM2C0SC_CH0F_MASK              128U
#define TPM2C0SC_ELS0x_MASK             12U
#define TPM2C0SC_ELS0x_BITNUM           2U
#define TPM2C0SC_MS0x_MASK              48U
#define TPM2C0SC_MS0x_BITNUM            4U


/*** TPM2C0V - TPM2 Timer Channel 0 Value Register; 0x00000056 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2C0VH - TPM2 Timer Channel 0 Value Register High; 0x00000056 ***/
    union {
      byte Byte;
    } TPM2C0VHSTR;
    #define TPM2C0VH                    _TPM2C0V.Overlap_STR.TPM2C0VHSTR.Byte
    

    /*** TPM2C0VL - TPM2 Timer Channel 0 Value Register Low; 0x00000057 ***/
    union {
      byte Byte;
    } TPM2C0VLSTR;
    #define TPM2C0VL                    _TPM2C0V.Overlap_STR.TPM2C0VLSTR.Byte
    
  } Overlap_STR;

} TPM2C0VSTR;
extern volatile TPM2C0VSTR _TPM2C0V @0x00000056;
#define TPM2C0V                         _TPM2C0V.Word


/*** TPM2C1SC - TPM2 Timer Channel 1 Status and Control Register; 0x00000058 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS1A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS1B       :1;                                       /* Edge/Level Select Bit B */
    byte MS1A        :1;                                       /* Mode Select A for TPM Channel 1 */
    byte MS1B        :1;                                       /* Mode Select B for TPM Channel 1 */
    byte CH1IE       :1;                                       /* Channel 1 Interrupt Enable */
    byte CH1F        :1;                                       /* Channel 1 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS1x :2;
    byte grpMS1x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2C1SCSTR;
extern volatile TPM2C1SCSTR _TPM2C1SC @0x00000058;
#define TPM2C1SC                        _TPM2C1SC.Byte
#define TPM2C1SC_ELS1A                  _TPM2C1SC.Bits.ELS1A
#define TPM2C1SC_ELS1B                  _TPM2C1SC.Bits.ELS1B
#define TPM2C1SC_MS1A                   _TPM2C1SC.Bits.MS1A
#define TPM2C1SC_MS1B                   _TPM2C1SC.Bits.MS1B
#define TPM2C1SC_CH1IE                  _TPM2C1SC.Bits.CH1IE
#define TPM2C1SC_CH1F                   _TPM2C1SC.Bits.CH1F
#define TPM2C1SC_ELS1x                  _TPM2C1SC.MergedBits.grpELS1x
#define TPM2C1SC_MS1x                   _TPM2C1SC.MergedBits.grpMS1x

#define TPM2C1SC_ELS1A_MASK             4U
#define TPM2C1SC_ELS1B_MASK             8U
#define TPM2C1SC_MS1A_MASK              16U
#define TPM2C1SC_MS1B_MASK              32U
#define TPM2C1SC_CH1IE_MASK             64U
#define TPM2C1SC_CH1F_MASK              128U
#define TPM2C1SC_ELS1x_MASK             12U
#define TPM2C1SC_ELS1x_BITNUM           2U
#define TPM2C1SC_MS1x_MASK              48U
#define TPM2C1SC_MS1x_BITNUM            4U


/*** TPM2C1V - TPM2 Timer Channel 1 Value Register; 0x00000059 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2C1VH - TPM2 Timer Channel 1 Value Register High; 0x00000059 ***/
    union {
      byte Byte;
    } TPM2C1VHSTR;
    #define TPM2C1VH                    _TPM2C1V.Overlap_STR.TPM2C1VHSTR.Byte
    

    /*** TPM2C1VL - TPM2 Timer Channel 1 Value Register Low; 0x0000005A ***/
    union {
      byte Byte;
    } TPM2C1VLSTR;
    #define TPM2C1VL                    _TPM2C1V.Overlap_STR.TPM2C1VLSTR.Byte
    
  } Overlap_STR;

} TPM2C1VSTR;
extern volatile TPM2C1VSTR _TPM2C1V @0x00000059;
#define TPM2C1V                         _TPM2C1V.Word


/*** TPM2C2SC - TPM2 Timer Channel 2 Status and Control Register; 0x0000005B ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS2A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS2B       :1;                                       /* Edge/Level Select Bit B */
    byte MS2A        :1;                                       /* Mode Select A for TPM Channel 2 */
    byte MS2B        :1;                                       /* Mode Select B for TPM Channel 2 */
    byte CH2IE       :1;                                       /* Channel 2 Interrupt Enable */
    byte CH2F        :1;                                       /* Channel 2 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS2x :2;
    byte grpMS2x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM2C2SCSTR;
extern volatile TPM2C2SCSTR _TPM2C2SC @0x0000005B;
#define TPM2C2SC                        _TPM2C2SC.Byte
#define TPM2C2SC_ELS2A                  _TPM2C2SC.Bits.ELS2A
#define TPM2C2SC_ELS2B                  _TPM2C2SC.Bits.ELS2B
#define TPM2C2SC_MS2A                   _TPM2C2SC.Bits.MS2A
#define TPM2C2SC_MS2B                   _TPM2C2SC.Bits.MS2B
#define TPM2C2SC_CH2IE                  _TPM2C2SC.Bits.CH2IE
#define TPM2C2SC_CH2F                   _TPM2C2SC.Bits.CH2F
#define TPM2C2SC_ELS2x                  _TPM2C2SC.MergedBits.grpELS2x
#define TPM2C2SC_MS2x                   _TPM2C2SC.MergedBits.grpMS2x

#define TPM2C2SC_ELS2A_MASK             4U
#define TPM2C2SC_ELS2B_MASK             8U
#define TPM2C2SC_MS2A_MASK              16U
#define TPM2C2SC_MS2B_MASK              32U
#define TPM2C2SC_CH2IE_MASK             64U
#define TPM2C2SC_CH2F_MASK              128U
#define TPM2C2SC_ELS2x_MASK             12U
#define TPM2C2SC_ELS2x_BITNUM           2U
#define TPM2C2SC_MS2x_MASK              48U
#define TPM2C2SC_MS2x_BITNUM            4U


/*** TPM2C2V - TPM2 Timer Channel 2 Value Register; 0x0000005C ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM2C2VH - TPM2 Timer Channel 2 Value Register High; 0x0000005C ***/
    union {
      byte Byte;
    } TPM2C2VHSTR;
    #define TPM2C2VH                    _TPM2C2V.Overlap_STR.TPM2C2VHSTR.Byte
    

    /*** TPM2C2VL - TPM2 Timer Channel 2 Value Register Low; 0x0000005D ***/
    union {
      byte Byte;
    } TPM2C2VLSTR;
    #define TPM2C2VL                    _TPM2C2V.Overlap_STR.TPM2C2VLSTR.Byte
    
  } Overlap_STR;

} TPM2C2VSTR;
extern volatile TPM2C2VSTR _TPM2C2V @0x0000005C;
#define TPM2C2V                         _TPM2C2V.Word


/*** TPM3SC - TPM3 Status and Control Register; 0x00000060 ***/
typedef union {
  byte Byte;
  struct {
    byte PS0         :1;                                       /* Prescale Divisor Select Bit 0 */
    byte PS1         :1;                                       /* Prescale Divisor Select Bit 1 */
    byte PS2         :1;                                       /* Prescale Divisor Select Bit 2 */
    byte CLKSA       :1;                                       /* Clock Source Select A */
    byte CLKSB       :1;                                       /* Clock Source Select B */
    byte CPWMS       :1;                                       /* Center-Aligned PWM Select */
    byte TOIE        :1;                                       /* Timer Overflow Interrupt Enable */
    byte TOF         :1;                                       /* Timer Overflow Flag */
  } Bits;
  struct {
    byte grpPS   :3;
    byte grpCLKSx :2;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM3SCSTR;
extern volatile TPM3SCSTR _TPM3SC @0x00000060;
#define TPM3SC                          _TPM3SC.Byte
#define TPM3SC_PS0                      _TPM3SC.Bits.PS0
#define TPM3SC_PS1                      _TPM3SC.Bits.PS1
#define TPM3SC_PS2                      _TPM3SC.Bits.PS2
#define TPM3SC_CLKSA                    _TPM3SC.Bits.CLKSA
#define TPM3SC_CLKSB                    _TPM3SC.Bits.CLKSB
#define TPM3SC_CPWMS                    _TPM3SC.Bits.CPWMS
#define TPM3SC_TOIE                     _TPM3SC.Bits.TOIE
#define TPM3SC_TOF                      _TPM3SC.Bits.TOF
#define TPM3SC_PS                       _TPM3SC.MergedBits.grpPS
#define TPM3SC_CLKSx                    _TPM3SC.MergedBits.grpCLKSx

#define TPM3SC_PS0_MASK                 1U
#define TPM3SC_PS1_MASK                 2U
#define TPM3SC_PS2_MASK                 4U
#define TPM3SC_CLKSA_MASK               8U
#define TPM3SC_CLKSB_MASK               16U
#define TPM3SC_CPWMS_MASK               32U
#define TPM3SC_TOIE_MASK                64U
#define TPM3SC_TOF_MASK                 128U
#define TPM3SC_PS_MASK                  7U
#define TPM3SC_PS_BITNUM                0U
#define TPM3SC_CLKSx_MASK               24U
#define TPM3SC_CLKSx_BITNUM             3U


/*** TPM3CNT - TPM3 Timer Counter Register; 0x00000061 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM3CNTH - TPM3 Timer Counter Register High; 0x00000061 ***/
    union {
      byte Byte;
    } TPM3CNTHSTR;
    #define TPM3CNTH                    _TPM3CNT.Overlap_STR.TPM3CNTHSTR.Byte
    

    /*** TPM3CNTL - TPM3 Timer Counter Register Low; 0x00000062 ***/
    union {
      byte Byte;
    } TPM3CNTLSTR;
    #define TPM3CNTL                    _TPM3CNT.Overlap_STR.TPM3CNTLSTR.Byte
    
  } Overlap_STR;

} TPM3CNTSTR;
extern volatile TPM3CNTSTR _TPM3CNT @0x00000061;
#define TPM3CNT                         _TPM3CNT.Word


/*** TPM3MOD - TPM3 Timer Counter Modulo Register; 0x00000063 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM3MODH - TPM3 Timer Counter Modulo Register High; 0x00000063 ***/
    union {
      byte Byte;
    } TPM3MODHSTR;
    #define TPM3MODH                    _TPM3MOD.Overlap_STR.TPM3MODHSTR.Byte
    

    /*** TPM3MODL - TPM3 Timer Counter Modulo Register Low; 0x00000064 ***/
    union {
      byte Byte;
    } TPM3MODLSTR;
    #define TPM3MODL                    _TPM3MOD.Overlap_STR.TPM3MODLSTR.Byte
    
  } Overlap_STR;

} TPM3MODSTR;
extern volatile TPM3MODSTR _TPM3MOD @0x00000063;
#define TPM3MOD                         _TPM3MOD.Word


/*** TPM3C0SC - TPM3 Timer Channel 0 Status and Control Register; 0x00000065 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS0A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS0B       :1;                                       /* Edge/Level Select Bit B */
    byte MS0A        :1;                                       /* Mode Select A for TPM Channel 0 */
    byte MS0B        :1;                                       /* Mode Select B for TPM Channel 0 */
    byte CH0IE       :1;                                       /* Channel 0 Interrupt Enable */
    byte CH0F        :1;                                       /* Channel 0 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS0x :2;
    byte grpMS0x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM3C0SCSTR;
extern volatile TPM3C0SCSTR _TPM3C0SC @0x00000065;
#define TPM3C0SC                        _TPM3C0SC.Byte
#define TPM3C0SC_ELS0A                  _TPM3C0SC.Bits.ELS0A
#define TPM3C0SC_ELS0B                  _TPM3C0SC.Bits.ELS0B
#define TPM3C0SC_MS0A                   _TPM3C0SC.Bits.MS0A
#define TPM3C0SC_MS0B                   _TPM3C0SC.Bits.MS0B
#define TPM3C0SC_CH0IE                  _TPM3C0SC.Bits.CH0IE
#define TPM3C0SC_CH0F                   _TPM3C0SC.Bits.CH0F
#define TPM3C0SC_ELS0x                  _TPM3C0SC.MergedBits.grpELS0x
#define TPM3C0SC_MS0x                   _TPM3C0SC.MergedBits.grpMS0x

#define TPM3C0SC_ELS0A_MASK             4U
#define TPM3C0SC_ELS0B_MASK             8U
#define TPM3C0SC_MS0A_MASK              16U
#define TPM3C0SC_MS0B_MASK              32U
#define TPM3C0SC_CH0IE_MASK             64U
#define TPM3C0SC_CH0F_MASK              128U
#define TPM3C0SC_ELS0x_MASK             12U
#define TPM3C0SC_ELS0x_BITNUM           2U
#define TPM3C0SC_MS0x_MASK              48U
#define TPM3C0SC_MS0x_BITNUM            4U


/*** TPM3C0V - TPM3 Timer Channel 0 Value Register; 0x00000066 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM3C0VH - TPM3 Timer Channel 0 Value Register High; 0x00000066 ***/
    union {
      byte Byte;
    } TPM3C0VHSTR;
    #define TPM3C0VH                    _TPM3C0V.Overlap_STR.TPM3C0VHSTR.Byte
    

    /*** TPM3C0VL - TPM3 Timer Channel 0 Value Register Low; 0x00000067 ***/
    union {
      byte Byte;
    } TPM3C0VLSTR;
    #define TPM3C0VL                    _TPM3C0V.Overlap_STR.TPM3C0VLSTR.Byte
    
  } Overlap_STR;

} TPM3C0VSTR;
extern volatile TPM3C0VSTR _TPM3C0V @0x00000066;
#define TPM3C0V                         _TPM3C0V.Word


/*** TPM3C1SC - TPM3 Timer Channel 1 Status and Control Register; 0x00000068 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS1A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS1B       :1;                                       /* Edge/Level Select Bit B */
    byte MS1A        :1;                                       /* Mode Select A for TPM Channel 1 */
    byte MS1B        :1;                                       /* Mode Select B for TPM Channel 1 */
    byte CH1IE       :1;                                       /* Channel 1 Interrupt Enable */
    byte CH1F        :1;                                       /* Channel 1 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS1x :2;
    byte grpMS1x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM3C1SCSTR;
extern volatile TPM3C1SCSTR _TPM3C1SC @0x00000068;
#define TPM3C1SC                        _TPM3C1SC.Byte
#define TPM3C1SC_ELS1A                  _TPM3C1SC.Bits.ELS1A
#define TPM3C1SC_ELS1B                  _TPM3C1SC.Bits.ELS1B
#define TPM3C1SC_MS1A                   _TPM3C1SC.Bits.MS1A
#define TPM3C1SC_MS1B                   _TPM3C1SC.Bits.MS1B
#define TPM3C1SC_CH1IE                  _TPM3C1SC.Bits.CH1IE
#define TPM3C1SC_CH1F                   _TPM3C1SC.Bits.CH1F
#define TPM3C1SC_ELS1x                  _TPM3C1SC.MergedBits.grpELS1x
#define TPM3C1SC_MS1x                   _TPM3C1SC.MergedBits.grpMS1x

#define TPM3C1SC_ELS1A_MASK             4U
#define TPM3C1SC_ELS1B_MASK             8U
#define TPM3C1SC_MS1A_MASK              16U
#define TPM3C1SC_MS1B_MASK              32U
#define TPM3C1SC_CH1IE_MASK             64U
#define TPM3C1SC_CH1F_MASK              128U
#define TPM3C1SC_ELS1x_MASK             12U
#define TPM3C1SC_ELS1x_BITNUM           2U
#define TPM3C1SC_MS1x_MASK              48U
#define TPM3C1SC_MS1x_BITNUM            4U


/*** TPM3C1V - TPM3 Timer Channel 1 Value Register; 0x00000069 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM3C1VH - TPM3 Timer Channel 1 Value Register High; 0x00000069 ***/
    union {
      byte Byte;
    } TPM3C1VHSTR;
    #define TPM3C1VH                    _TPM3C1V.Overlap_STR.TPM3C1VHSTR.Byte
    

    /*** TPM3C1VL - TPM3 Timer Channel 1 Value Register Low; 0x0000006A ***/
    union {
      byte Byte;
    } TPM3C1VLSTR;
    #define TPM3C1VL                    _TPM3C1V.Overlap_STR.TPM3C1VLSTR.Byte
    
  } Overlap_STR;

} TPM3C1VSTR;
extern volatile TPM3C1VSTR _TPM3C1V @0x00000069;
#define TPM3C1V                         _TPM3C1V.Word


/*** TPM3C2SC - TPM3 Timer Channel 2 Status and Control Register; 0x0000006B ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS2A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS2B       :1;                                       /* Edge/Level Select Bit B */
    byte MS2A        :1;                                       /* Mode Select A for TPM Channel 2 */
    byte MS2B        :1;                                       /* Mode Select B for TPM Channel 2 */
    byte CH2IE       :1;                                       /* Channel 2 Interrupt Enable */
    byte CH2F        :1;                                       /* Channel 2 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS2x :2;
    byte grpMS2x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM3C2SCSTR;
extern volatile TPM3C2SCSTR _TPM3C2SC @0x0000006B;
#define TPM3C2SC                        _TPM3C2SC.Byte
#define TPM3C2SC_ELS2A                  _TPM3C2SC.Bits.ELS2A
#define TPM3C2SC_ELS2B                  _TPM3C2SC.Bits.ELS2B
#define TPM3C2SC_MS2A                   _TPM3C2SC.Bits.MS2A
#define TPM3C2SC_MS2B                   _TPM3C2SC.Bits.MS2B
#define TPM3C2SC_CH2IE                  _TPM3C2SC.Bits.CH2IE
#define TPM3C2SC_CH2F                   _TPM3C2SC.Bits.CH2F
#define TPM3C2SC_ELS2x                  _TPM3C2SC.MergedBits.grpELS2x
#define TPM3C2SC_MS2x                   _TPM3C2SC.MergedBits.grpMS2x

#define TPM3C2SC_ELS2A_MASK             4U
#define TPM3C2SC_ELS2B_MASK             8U
#define TPM3C2SC_MS2A_MASK              16U
#define TPM3C2SC_MS2B_MASK              32U
#define TPM3C2SC_CH2IE_MASK             64U
#define TPM3C2SC_CH2F_MASK              128U
#define TPM3C2SC_ELS2x_MASK             12U
#define TPM3C2SC_ELS2x_BITNUM           2U
#define TPM3C2SC_MS2x_MASK              48U
#define TPM3C2SC_MS2x_BITNUM            4U


/*** TPM3C2V - TPM3 Timer Channel 2 Value Register; 0x0000006C ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM3C2VH - TPM3 Timer Channel 2 Value Register High; 0x0000006C ***/
    union {
      byte Byte;
    } TPM3C2VHSTR;
    #define TPM3C2VH                    _TPM3C2V.Overlap_STR.TPM3C2VHSTR.Byte
    

    /*** TPM3C2VL - TPM3 Timer Channel 2 Value Register Low; 0x0000006D ***/
    union {
      byte Byte;
    } TPM3C2VLSTR;
    #define TPM3C2VL                    _TPM3C2V.Overlap_STR.TPM3C2VLSTR.Byte
    
  } Overlap_STR;

} TPM3C2VSTR;
extern volatile TPM3C2VSTR _TPM3C2V @0x0000006C;
#define TPM3C2V                         _TPM3C2V.Word


/*** TPM3C3SC - TPM3 Timer Channel 3 Status and Control Register; 0x0000006E ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS3A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS3B       :1;                                       /* Edge/Level Select Bit B */
    byte MS3A        :1;                                       /* Mode Select A for TPM Channel 3 */
    byte MS3B        :1;                                       /* Mode Select B for TPM Channel 3 */
    byte CH3IE       :1;                                       /* Channel 3 Interrupt Enable */
    byte CH3F        :1;                                       /* Channel 3 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS3x :2;
    byte grpMS3x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM3C3SCSTR;
extern volatile TPM3C3SCSTR _TPM3C3SC @0x0000006E;
#define TPM3C3SC                        _TPM3C3SC.Byte
#define TPM3C3SC_ELS3A                  _TPM3C3SC.Bits.ELS3A
#define TPM3C3SC_ELS3B                  _TPM3C3SC.Bits.ELS3B
#define TPM3C3SC_MS3A                   _TPM3C3SC.Bits.MS3A
#define TPM3C3SC_MS3B                   _TPM3C3SC.Bits.MS3B
#define TPM3C3SC_CH3IE                  _TPM3C3SC.Bits.CH3IE
#define TPM3C3SC_CH3F                   _TPM3C3SC.Bits.CH3F
#define TPM3C3SC_ELS3x                  _TPM3C3SC.MergedBits.grpELS3x
#define TPM3C3SC_MS3x                   _TPM3C3SC.MergedBits.grpMS3x

#define TPM3C3SC_ELS3A_MASK             4U
#define TPM3C3SC_ELS3B_MASK             8U
#define TPM3C3SC_MS3A_MASK              16U
#define TPM3C3SC_MS3B_MASK              32U
#define TPM3C3SC_CH3IE_MASK             64U
#define TPM3C3SC_CH3F_MASK              128U
#define TPM3C3SC_ELS3x_MASK             12U
#define TPM3C3SC_ELS3x_BITNUM           2U
#define TPM3C3SC_MS3x_MASK              48U
#define TPM3C3SC_MS3x_BITNUM            4U


/*** TPM3C3V - TPM3 Timer Channel 3 Value Register; 0x0000006F ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM3C3VH - TPM3 Timer Channel 3 Value Register High; 0x0000006F ***/
    union {
      byte Byte;
    } TPM3C3VHSTR;
    #define TPM3C3VH                    _TPM3C3V.Overlap_STR.TPM3C3VHSTR.Byte
    

    /*** TPM3C3VL - TPM3 Timer Channel 3 Value Register Low; 0x00000070 ***/
    union {
      byte Byte;
    } TPM3C3VLSTR;
    #define TPM3C3VL                    _TPM3C3V.Overlap_STR.TPM3C3VLSTR.Byte
    
  } Overlap_STR;

} TPM3C3VSTR;
extern volatile TPM3C3VSTR _TPM3C3V @0x0000006F;
#define TPM3C3V                         _TPM3C3V.Word


/*** TPM3C4SC - TPM3 Timer Channel 4 Status and Control Register; 0x00000071 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS4A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS4B       :1;                                       /* Edge/Level Select Bit B */
    byte MS4A        :1;                                       /* Mode Select A for TPM Channel 4 */
    byte MS4B        :1;                                       /* Mode Select B for TPM Channel 4 */
    byte CH4IE       :1;                                       /* Channel 4 Interrupt Enable */
    byte CH4F        :1;                                       /* Channel 4 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS4x :2;
    byte grpMS4x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM3C4SCSTR;
extern volatile TPM3C4SCSTR _TPM3C4SC @0x00000071;
#define TPM3C4SC                        _TPM3C4SC.Byte
#define TPM3C4SC_ELS4A                  _TPM3C4SC.Bits.ELS4A
#define TPM3C4SC_ELS4B                  _TPM3C4SC.Bits.ELS4B
#define TPM3C4SC_MS4A                   _TPM3C4SC.Bits.MS4A
#define TPM3C4SC_MS4B                   _TPM3C4SC.Bits.MS4B
#define TPM3C4SC_CH4IE                  _TPM3C4SC.Bits.CH4IE
#define TPM3C4SC_CH4F                   _TPM3C4SC.Bits.CH4F
#define TPM3C4SC_ELS4x                  _TPM3C4SC.MergedBits.grpELS4x
#define TPM3C4SC_MS4x                   _TPM3C4SC.MergedBits.grpMS4x

#define TPM3C4SC_ELS4A_MASK             4U
#define TPM3C4SC_ELS4B_MASK             8U
#define TPM3C4SC_MS4A_MASK              16U
#define TPM3C4SC_MS4B_MASK              32U
#define TPM3C4SC_CH4IE_MASK             64U
#define TPM3C4SC_CH4F_MASK              128U
#define TPM3C4SC_ELS4x_MASK             12U
#define TPM3C4SC_ELS4x_BITNUM           2U
#define TPM3C4SC_MS4x_MASK              48U
#define TPM3C4SC_MS4x_BITNUM            4U


/*** TPM3C4V - TPM3 Timer Channel 4 Value Register; 0x00000072 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM3C4VH - TPM3 Timer Channel 4 Value Register High; 0x00000072 ***/
    union {
      byte Byte;
    } TPM3C4VHSTR;
    #define TPM3C4VH                    _TPM3C4V.Overlap_STR.TPM3C4VHSTR.Byte
    

    /*** TPM3C4VL - TPM3 Timer Channel 4 Value Register Low; 0x00000073 ***/
    union {
      byte Byte;
    } TPM3C4VLSTR;
    #define TPM3C4VL                    _TPM3C4V.Overlap_STR.TPM3C4VLSTR.Byte
    
  } Overlap_STR;

} TPM3C4VSTR;
extern volatile TPM3C4VSTR _TPM3C4V @0x00000072;
#define TPM3C4V                         _TPM3C4V.Word


/*** TPM3C5SC - TPM3 Timer Channel 5 Status and Control Register; 0x00000074 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte ELS5A       :1;                                       /* Edge/Level Select Bit A */
    byte ELS5B       :1;                                       /* Edge/Level Select Bit B */
    byte MS5A        :1;                                       /* Mode Select A for TPM Channel 5 */
    byte MS5B        :1;                                       /* Mode Select B for TPM Channel 5 */
    byte CH5IE       :1;                                       /* Channel 5 Interrupt Enable */
    byte CH5F        :1;                                       /* Channel 5 Flag */
  } Bits;
  struct {
    byte         :1;
    byte         :1;
    byte grpELS5x :2;
    byte grpMS5x :2;
    byte         :1;
    byte         :1;
  } MergedBits;
} TPM3C5SCSTR;
extern volatile TPM3C5SCSTR _TPM3C5SC @0x00000074;
#define TPM3C5SC                        _TPM3C5SC.Byte
#define TPM3C5SC_ELS5A                  _TPM3C5SC.Bits.ELS5A
#define TPM3C5SC_ELS5B                  _TPM3C5SC.Bits.ELS5B
#define TPM3C5SC_MS5A                   _TPM3C5SC.Bits.MS5A
#define TPM3C5SC_MS5B                   _TPM3C5SC.Bits.MS5B
#define TPM3C5SC_CH5IE                  _TPM3C5SC.Bits.CH5IE
#define TPM3C5SC_CH5F                   _TPM3C5SC.Bits.CH5F
#define TPM3C5SC_ELS5x                  _TPM3C5SC.MergedBits.grpELS5x
#define TPM3C5SC_MS5x                   _TPM3C5SC.MergedBits.grpMS5x

#define TPM3C5SC_ELS5A_MASK             4U
#define TPM3C5SC_ELS5B_MASK             8U
#define TPM3C5SC_MS5A_MASK              16U
#define TPM3C5SC_MS5B_MASK              32U
#define TPM3C5SC_CH5IE_MASK             64U
#define TPM3C5SC_CH5F_MASK              128U
#define TPM3C5SC_ELS5x_MASK             12U
#define TPM3C5SC_ELS5x_BITNUM           2U
#define TPM3C5SC_MS5x_MASK              48U
#define TPM3C5SC_MS5x_BITNUM            4U


/*** TPM3C5V - TPM3 Timer Channel 5 Value Register; 0x00000075 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** TPM3C5VH - TPM3 Timer Channel 5 Value Register High; 0x00000075 ***/
    union {
      byte Byte;
    } TPM3C5VHSTR;
    #define TPM3C5VH                    _TPM3C5V.Overlap_STR.TPM3C5VHSTR.Byte
    

    /*** TPM3C5VL - TPM3 Timer Channel 5 Value Register Low; 0x00000076 ***/
    union {
      byte Byte;
    } TPM3C5VLSTR;
    #define TPM3C5VL                    _TPM3C5V.Overlap_STR.TPM3C5VLSTR.Byte
    
  } Overlap_STR;

} TPM3C5VSTR;
extern volatile TPM3C5VSTR _TPM3C5V @0x00000075;
#define TPM3C5V                         _TPM3C5V.Word


/*** PPAGE - Program Page Register; 0x00000078 ***/
typedef union {
  byte Byte;
  struct {
    byte XA14        :1;                                       /* Extended address, bit 14 */
    byte XA15        :1;                                       /* Extended address, bit 15 */
    byte XA16        :1;                                       /* Extended address, bit 16 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpXA_14 :3;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} PPAGESTR;
extern volatile PPAGESTR _PPAGE @0x00000078;
#define PPAGE                           _PPAGE.Byte
#define PPAGE_XA14                      _PPAGE.Bits.XA14
#define PPAGE_XA15                      _PPAGE.Bits.XA15
#define PPAGE_XA16                      _PPAGE.Bits.XA16
#define PPAGE_XA_14                     _PPAGE.MergedBits.grpXA_14
#define PPAGE_XA                        PPAGE_XA_14

#define PPAGE_XA14_MASK                 1U
#define PPAGE_XA15_MASK                 2U
#define PPAGE_XA16_MASK                 4U
#define PPAGE_XA_14_MASK                7U
#define PPAGE_XA_14_BITNUM              0U


/*** LAP2 - Linear Address Pointer Register 2; 0x00000079 ***/
typedef union {
  byte Byte;
  struct {
    byte LA16        :1;                                       /* Linear address pointer, bit 16 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} LAP2STR;
extern volatile LAP2STR _LAP2 @0x00000079;
#define LAP2                            _LAP2.Byte
#define LAP2_LA16                       _LAP2.Bits.LA16

#define LAP2_LA16_MASK                  1U


/*** LAP1 - Linear Address Pointer Register 1; 0x0000007A ***/
typedef union {
  byte Byte;
  struct {
    byte LA8         :1;                                       /* Linear address pointer, bit 8 */
    byte LA9         :1;                                       /* Linear address pointer, bit 9 */
    byte LA10        :1;                                       /* Linear address pointer, bit 10 */
    byte LA11        :1;                                       /* Linear address pointer, bit 11 */
    byte LA12        :1;                                       /* Linear address pointer, bit 12 */
    byte LA13        :1;                                       /* Linear address pointer, bit 13 */
    byte LA14        :1;                                       /* Linear address pointer, bit 14 */
    byte LA15        :1;                                       /* Linear address pointer, bit 15 */
  } Bits;
} LAP1STR;
extern volatile LAP1STR _LAP1 @0x0000007A;
#define LAP1                            _LAP1.Byte
#define LAP1_LA8                        _LAP1.Bits.LA8
#define LAP1_LA9                        _LAP1.Bits.LA9
#define LAP1_LA10                       _LAP1.Bits.LA10
#define LAP1_LA11                       _LAP1.Bits.LA11
#define LAP1_LA12                       _LAP1.Bits.LA12
#define LAP1_LA13                       _LAP1.Bits.LA13
#define LAP1_LA14                       _LAP1.Bits.LA14
#define LAP1_LA15                       _LAP1.Bits.LA15

#define LAP1_LA8_MASK                   1U
#define LAP1_LA9_MASK                   2U
#define LAP1_LA10_MASK                  4U
#define LAP1_LA11_MASK                  8U
#define LAP1_LA12_MASK                  16U
#define LAP1_LA13_MASK                  32U
#define LAP1_LA14_MASK                  64U
#define LAP1_LA15_MASK                  128U


/*** LAP0 - Linear Address Pointer Register 0; 0x0000007B ***/
typedef union {
  byte Byte;
  struct {
    byte LA0         :1;                                       /* Linear address pointer, bit 0 */
    byte LA1         :1;                                       /* Linear address pointer, bit 1 */
    byte LA2         :1;                                       /* Linear address pointer, bit 2 */
    byte LA3         :1;                                       /* Linear address pointer, bit 3 */
    byte LA4         :1;                                       /* Linear address pointer, bit 4 */
    byte LA5         :1;                                       /* Linear address pointer, bit 5 */
    byte LA6         :1;                                       /* Linear address pointer, bit 6 */
    byte LA7         :1;                                       /* Linear address pointer, bit 7 */
  } Bits;
} LAP0STR;
extern volatile LAP0STR _LAP0 @0x0000007B;
#define LAP0                            _LAP0.Byte
#define LAP0_LA0                        _LAP0.Bits.LA0
#define LAP0_LA1                        _LAP0.Bits.LA1
#define LAP0_LA2                        _LAP0.Bits.LA2
#define LAP0_LA3                        _LAP0.Bits.LA3
#define LAP0_LA4                        _LAP0.Bits.LA4
#define LAP0_LA5                        _LAP0.Bits.LA5
#define LAP0_LA6                        _LAP0.Bits.LA6
#define LAP0_LA7                        _LAP0.Bits.LA7

#define LAP0_LA0_MASK                   1U
#define LAP0_LA1_MASK                   2U
#define LAP0_LA2_MASK                   4U
#define LAP0_LA3_MASK                   8U
#define LAP0_LA4_MASK                   16U
#define LAP0_LA5_MASK                   32U
#define LAP0_LA6_MASK                   64U
#define LAP0_LA7_MASK                   128U


/*** LWP - Linear Word Post Increment Register; 0x0000007C ***/
typedef union {
  byte Byte;
  struct {
    byte D0          :1;                                       /* Data value bit 0 */
    byte D1          :1;                                       /* Data value bit 1 */
    byte D2          :1;                                       /* Data value bit 2 */
    byte D3          :1;                                       /* Data value bit 3 */
    byte D4          :1;                                       /* Data value bit 4 */
    byte D5          :1;                                       /* Data value bit 5 */
    byte D6          :1;                                       /* Data value bit 6 */
    byte D7          :1;                                       /* Data value bit 7 */
  } Bits;
} LWPSTR;
extern volatile LWPSTR _LWP @0x0000007C;
#define LWP                             _LWP.Byte
#define LWP_D0                          _LWP.Bits.D0
#define LWP_D1                          _LWP.Bits.D1
#define LWP_D2                          _LWP.Bits.D2
#define LWP_D3                          _LWP.Bits.D3
#define LWP_D4                          _LWP.Bits.D4
#define LWP_D5                          _LWP.Bits.D5
#define LWP_D6                          _LWP.Bits.D6
#define LWP_D7                          _LWP.Bits.D7

#define LWP_D0_MASK                     1U
#define LWP_D1_MASK                     2U
#define LWP_D2_MASK                     4U
#define LWP_D3_MASK                     8U
#define LWP_D4_MASK                     16U
#define LWP_D5_MASK                     32U
#define LWP_D6_MASK                     64U
#define LWP_D7_MASK                     128U


/*** LBP - Linear Byte Post Increment Register; 0x0000007D ***/
typedef union {
  byte Byte;
  struct {
    byte D0          :1;                                       /* Data value bit 0 */
    byte D1          :1;                                       /* Data value bit 1 */
    byte D2          :1;                                       /* Data value bit 2 */
    byte D3          :1;                                       /* Data value bit 3 */
    byte D4          :1;                                       /* Data value bit 4 */
    byte D5          :1;                                       /* Data value bit 5 */
    byte D6          :1;                                       /* Data value bit 6 */
    byte D7          :1;                                       /* Data value bit 7 */
  } Bits;
} LBPSTR;
extern volatile LBPSTR _LBP @0x0000007D;
#define LBP                             _LBP.Byte
#define LBP_D0                          _LBP.Bits.D0
#define LBP_D1                          _LBP.Bits.D1
#define LBP_D2                          _LBP.Bits.D2
#define LBP_D3                          _LBP.Bits.D3
#define LBP_D4                          _LBP.Bits.D4
#define LBP_D5                          _LBP.Bits.D5
#define LBP_D6                          _LBP.Bits.D6
#define LBP_D7                          _LBP.Bits.D7

#define LBP_D0_MASK                     1U
#define LBP_D1_MASK                     2U
#define LBP_D2_MASK                     4U
#define LBP_D3_MASK                     8U
#define LBP_D4_MASK                     16U
#define LBP_D5_MASK                     32U
#define LBP_D6_MASK                     64U
#define LBP_D7_MASK                     128U


/*** LB - Linear Byte Register; 0x0000007E ***/
typedef union {
  byte Byte;
  struct {
    byte D0          :1;                                       /* Data value bit 0 */
    byte D1          :1;                                       /* Data value bit 1 */
    byte D2          :1;                                       /* Data value bit 2 */
    byte D3          :1;                                       /* Data value bit 3 */
    byte D4          :1;                                       /* Data value bit 4 */
    byte D5          :1;                                       /* Data value bit 5 */
    byte D6          :1;                                       /* Data value bit 6 */
    byte D7          :1;                                       /* Data value bit 7 */
  } Bits;
} LBSTR;
extern volatile LBSTR _LB @0x0000007E;
#define LB                              _LB.Byte
#define LB_D0                           _LB.Bits.D0
#define LB_D1                           _LB.Bits.D1
#define LB_D2                           _LB.Bits.D2
#define LB_D3                           _LB.Bits.D3
#define LB_D4                           _LB.Bits.D4
#define LB_D5                           _LB.Bits.D5
#define LB_D6                           _LB.Bits.D6
#define LB_D7                           _LB.Bits.D7

#define LB_D0_MASK                      1U
#define LB_D1_MASK                      2U
#define LB_D2_MASK                      4U
#define LB_D3_MASK                      8U
#define LB_D4_MASK                      16U
#define LB_D5_MASK                      32U
#define LB_D6_MASK                      64U
#define LB_D7_MASK                      128U


/*** LAPAB - Linear Address Pointer Add Byte Register; 0x0000007F ***/
typedef union {
  byte Byte;
  struct {
    byte D0          :1;                                       /* Data value bit 0 */
    byte D1          :1;                                       /* Data value bit 1 */
    byte D2          :1;                                       /* Data value bit 2 */
    byte D3          :1;                                       /* Data value bit 3 */
    byte D4          :1;                                       /* Data value bit 4 */
    byte D5          :1;                                       /* Data value bit 5 */
    byte D6          :1;                                       /* Data value bit 6 */
    byte D7          :1;                                       /* Data value bit 7 */
  } Bits;
} LAPABSTR;
extern volatile LAPABSTR _LAPAB @0x0000007F;
#define LAPAB                           _LAPAB.Byte
#define LAPAB_D0                        _LAPAB.Bits.D0
#define LAPAB_D1                        _LAPAB.Bits.D1
#define LAPAB_D2                        _LAPAB.Bits.D2
#define LAPAB_D3                        _LAPAB.Bits.D3
#define LAPAB_D4                        _LAPAB.Bits.D4
#define LAPAB_D5                        _LAPAB.Bits.D5
#define LAPAB_D6                        _LAPAB.Bits.D6
#define LAPAB_D7                        _LAPAB.Bits.D7

#define LAPAB_D0_MASK                   1U
#define LAPAB_D1_MASK                   2U
#define LAPAB_D2_MASK                   4U
#define LAPAB_D3_MASK                   8U
#define LAPAB_D4_MASK                   16U
#define LAPAB_D5_MASK                   32U
#define LAPAB_D6_MASK                   64U
#define LAPAB_D7_MASK                   128U


/*** SRS - System Reset Status Register; 0x00001800 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte LVD         :1;                                       /* Low Voltage Detect */
    byte             :1; 
    byte             :1; 
    byte ILOP        :1;                                       /* Illegal Opcode */
    byte COP         :1;                                       /* Computer Operating Properly (COP) Watchdog */
    byte PIN         :1;                                       /* External Reset Pin */
    byte POR         :1;                                       /* Power-On Reset */
  } Bits;
} SRSSTR;
extern volatile SRSSTR _SRS @0x00001800;
#define SRS                             _SRS.Byte
#define SRS_LVD                         _SRS.Bits.LVD
#define SRS_ILOP                        _SRS.Bits.ILOP
#define SRS_COP                         _SRS.Bits.COP
#define SRS_PIN                         _SRS.Bits.PIN
#define SRS_POR                         _SRS.Bits.POR

#define SRS_LVD_MASK                    2U
#define SRS_ILOP_MASK                   16U
#define SRS_COP_MASK                    32U
#define SRS_PIN_MASK                    64U
#define SRS_POR_MASK                    128U


/*** SBDFR - System Background Debug Force Reset Register; 0x00001801 ***/
typedef union {
  byte Byte;
  struct {
    byte BDFR        :1;                                       /* Background Debug Force Reset */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} SBDFRSTR;
extern volatile SBDFRSTR _SBDFR @0x00001801;
#define SBDFR                           _SBDFR.Byte
#define SBDFR_BDFR                      _SBDFR.Bits.BDFR

#define SBDFR_BDFR_MASK                 1U


/*** SOPT1 - System Options Register 1; 0x00001802 ***/
typedef union {
  byte Byte;
  struct {
    byte RSTPE       :1;                                       /* RESET Pin Enable */
    byte BKGDPE      :1;                                       /* Background Debug Mode Pin Enable */
    byte RSTOPE      :1;                                       /* RSTO Pin Enable */
    byte             :1; 
    byte             :1; 
    byte STOPE       :1;                                       /* Stop Mode Enable */
    byte COPT        :1;                                       /* COP Watchdog Timeout */
    byte COPE        :1;                                       /* COP Watchdog Enable */
  } Bits;
} SOPT1STR;
extern volatile SOPT1STR _SOPT1 @0x00001802;
#define SOPT1                           _SOPT1.Byte
#define SOPT1_RSTPE                     _SOPT1.Bits.RSTPE
#define SOPT1_BKGDPE                    _SOPT1.Bits.BKGDPE
#define SOPT1_RSTOPE                    _SOPT1.Bits.RSTOPE
#define SOPT1_STOPE                     _SOPT1.Bits.STOPE
#define SOPT1_COPT                      _SOPT1.Bits.COPT
#define SOPT1_COPE                      _SOPT1.Bits.COPE

#define SOPT1_RSTPE_MASK                1U
#define SOPT1_BKGDPE_MASK               2U
#define SOPT1_RSTOPE_MASK               4U
#define SOPT1_STOPE_MASK                32U
#define SOPT1_COPT_MASK                 64U
#define SOPT1_COPE_MASK                 128U


/*** SOPT2 - System Options Register 2; 0x00001803 ***/
typedef union {
  byte Byte;
  struct {
    byte ACIC1       :1;                                       /* Analog Comparator 1 to Input Capture Enable */
    byte IIC1PS      :1;                                       /* IIC1 Pin Select */
    byte ACIC2       :1;                                       /* Analog Comparator 2 to Input Capture Enable */
    byte SPI1PS      :1;                                       /* SPI1 Pin Select */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte COPCLKS     :1;                                       /* COP Watchdog Clock Select */
  } Bits;
} SOPT2STR;
extern volatile SOPT2STR _SOPT2 @0x00001803;
#define SOPT2                           _SOPT2.Byte
#define SOPT2_ACIC1                     _SOPT2.Bits.ACIC1
#define SOPT2_IIC1PS                    _SOPT2.Bits.IIC1PS
#define SOPT2_ACIC2                     _SOPT2.Bits.ACIC2
#define SOPT2_SPI1PS                    _SOPT2.Bits.SPI1PS
#define SOPT2_COPCLKS                   _SOPT2.Bits.COPCLKS

#define SOPT2_ACIC1_MASK                1U
#define SOPT2_IIC1PS_MASK               2U
#define SOPT2_ACIC2_MASK                4U
#define SOPT2_SPI1PS_MASK               8U
#define SOPT2_COPCLKS_MASK              128U


/*** SDID - System Device Identification Register; 0x00001806 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** SDIDH - System Device Identification Register High; 0x00001806 ***/
    union {
      byte Byte;
      struct {
        byte ID8         :1;                                       /* Part Identification Number, bit 8 */
        byte ID9         :1;                                       /* Part Identification Number, bit 9 */
        byte ID10        :1;                                       /* Part Identification Number, bit 10 */
        byte ID11        :1;                                       /* Part Identification Number, bit 11 */
        byte             :1; 
        byte             :1; 
        byte             :1; 
        byte             :1; 
      } Bits;
      struct {
        byte grpID_8 :4;
        byte     :1;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } SDIDHSTR;
    #define SDIDH                       _SDID.Overlap_STR.SDIDHSTR.Byte
    #define SDIDH_ID8                   _SDID.Overlap_STR.SDIDHSTR.Bits.ID8
    #define SDIDH_ID9                   _SDID.Overlap_STR.SDIDHSTR.Bits.ID9
    #define SDIDH_ID10                  _SDID.Overlap_STR.SDIDHSTR.Bits.ID10
    #define SDIDH_ID11                  _SDID.Overlap_STR.SDIDHSTR.Bits.ID11
    #define SDIDH_ID_8                  _SDID.Overlap_STR.SDIDHSTR.MergedBits.grpID_8
    #define SDIDH_ID                    SDIDH_ID_8
    
    #define SDIDH_ID8_MASK              1U
    #define SDIDH_ID9_MASK              2U
    #define SDIDH_ID10_MASK             4U
    #define SDIDH_ID11_MASK             8U
    #define SDIDH_ID_8_MASK             15U
    #define SDIDH_ID_8_BITNUM           0U
    

    /*** SDIDL - System Device Identification Register Low; 0x00001807 ***/
    union {
      byte Byte;
      struct {
        byte ID0         :1;                                       /* Part Identification Number, bit 0 */
        byte ID1         :1;                                       /* Part Identification Number, bit 1 */
        byte ID2         :1;                                       /* Part Identification Number, bit 2 */
        byte ID3         :1;                                       /* Part Identification Number, bit 3 */
        byte ID4         :1;                                       /* Part Identification Number, bit 4 */
        byte ID5         :1;                                       /* Part Identification Number, bit 5 */
        byte ID6         :1;                                       /* Part Identification Number, bit 6 */
        byte ID7         :1;                                       /* Part Identification Number, bit 7 */
      } Bits;
    } SDIDLSTR;
    #define SDIDL                       _SDID.Overlap_STR.SDIDLSTR.Byte
    #define SDIDL_ID0                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID0
    #define SDIDL_ID1                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID1
    #define SDIDL_ID2                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID2
    #define SDIDL_ID3                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID3
    #define SDIDL_ID4                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID4
    #define SDIDL_ID5                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID5
    #define SDIDL_ID6                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID6
    #define SDIDL_ID7                   _SDID.Overlap_STR.SDIDLSTR.Bits.ID7
    
    #define SDIDL_ID0_MASK              1U
    #define SDIDL_ID1_MASK              2U
    #define SDIDL_ID2_MASK              4U
    #define SDIDL_ID3_MASK              8U
    #define SDIDL_ID4_MASK              16U
    #define SDIDL_ID5_MASK              32U
    #define SDIDL_ID6_MASK              64U
    #define SDIDL_ID7_MASK              128U
    
  } Overlap_STR;

} SDIDSTR;
extern volatile SDIDSTR _SDID @0x00001806;
#define SDID                            _SDID.Word


/*** SPMSC1 - System Power Management Status and Control 1 Register; 0x00001808 ***/
typedef union {
  byte Byte;
  struct {
    byte BGBE        :1;                                       /* Bandgap Buffer Enable */
    byte             :1; 
    byte LVDE        :1;                                       /* Low-Voltage Detect Enable */
    byte LVDSE       :1;                                       /* Low-Voltage Detect Stop Enable */
    byte LVDRE       :1;                                       /* Low-Voltage Detect Reset Enable */
    byte LVDIE       :1;                                       /* Low-Voltage Detect Interrupt Enable */
    byte LVDACK      :1;                                       /* Low-Voltage Detect Acknowledge */
    byte LVDF        :1;                                       /* Low-Voltage Detect Flag */
  } Bits;
} SPMSC1STR;
extern volatile SPMSC1STR _SPMSC1 @0x00001808;
#define SPMSC1                          _SPMSC1.Byte
#define SPMSC1_BGBE                     _SPMSC1.Bits.BGBE
#define SPMSC1_LVDE                     _SPMSC1.Bits.LVDE
#define SPMSC1_LVDSE                    _SPMSC1.Bits.LVDSE
#define SPMSC1_LVDRE                    _SPMSC1.Bits.LVDRE
#define SPMSC1_LVDIE                    _SPMSC1.Bits.LVDIE
#define SPMSC1_LVDACK                   _SPMSC1.Bits.LVDACK
#define SPMSC1_LVDF                     _SPMSC1.Bits.LVDF

#define SPMSC1_BGBE_MASK                1U
#define SPMSC1_LVDE_MASK                4U
#define SPMSC1_LVDSE_MASK               8U
#define SPMSC1_LVDRE_MASK               16U
#define SPMSC1_LVDIE_MASK               32U
#define SPMSC1_LVDACK_MASK              64U
#define SPMSC1_LVDF_MASK                128U


/*** SPMSC2 - System Power Management Status and Control 2 Register; 0x00001809 ***/
typedef union {
  byte Byte;
  struct {
    byte PPDC        :1;                                       /* Partial Power Down Control */
    byte PPDE        :1;                                       /* Partial Power-Down Enable */
    byte PPDACK      :1;                                       /* Partial Power Down Acknowledge */
    byte PPDF        :1;                                       /* Partial Power Down Flag */
    byte             :1; 
    byte LPWUI       :1;                                       /* Low Power Wake Up on Interrupt */
    byte LPRS        :1;                                       /* Low Power Regulator Status */
    byte LPR         :1;                                       /* Low Power Regulator Control */
  } Bits;
} SPMSC2STR;
extern volatile SPMSC2STR _SPMSC2 @0x00001809;
#define SPMSC2                          _SPMSC2.Byte
#define SPMSC2_PPDC                     _SPMSC2.Bits.PPDC
#define SPMSC2_PPDE                     _SPMSC2.Bits.PPDE
#define SPMSC2_PPDACK                   _SPMSC2.Bits.PPDACK
#define SPMSC2_PPDF                     _SPMSC2.Bits.PPDF
#define SPMSC2_LPWUI                    _SPMSC2.Bits.LPWUI
#define SPMSC2_LPRS                     _SPMSC2.Bits.LPRS
#define SPMSC2_LPR                      _SPMSC2.Bits.LPR

#define SPMSC2_PPDC_MASK                1U
#define SPMSC2_PPDE_MASK                2U
#define SPMSC2_PPDACK_MASK              4U
#define SPMSC2_PPDF_MASK                8U
#define SPMSC2_LPWUI_MASK               32U
#define SPMSC2_LPRS_MASK                64U
#define SPMSC2_LPR_MASK                 128U


/*** SPMSC3 - System Power Management Status and Control 3 Register; 0x0000180B ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte LVWIE       :1;                                       /* Low-Voltage Warning Interrupt Enable */
    byte LVWV        :1;                                       /* Low-Voltage Warning Voltage Select */
    byte LVDV        :1;                                       /* Low-Voltage Detect Voltage Select */
    byte LVWACK      :1;                                       /* Low-Voltage Warning Acknowledge */
    byte LVWF        :1;                                       /* Low-Voltage Warning Flag */
  } Bits;
} SPMSC3STR;
extern volatile SPMSC3STR _SPMSC3 @0x0000180B;
#define SPMSC3                          _SPMSC3.Byte
#define SPMSC3_LVWIE                    _SPMSC3.Bits.LVWIE
#define SPMSC3_LVWV                     _SPMSC3.Bits.LVWV
#define SPMSC3_LVDV                     _SPMSC3.Bits.LVDV
#define SPMSC3_LVWACK                   _SPMSC3.Bits.LVWACK
#define SPMSC3_LVWF                     _SPMSC3.Bits.LVWF

#define SPMSC3_LVWIE_MASK               8U
#define SPMSC3_LVWV_MASK                16U
#define SPMSC3_LVDV_MASK                32U
#define SPMSC3_LVWACK_MASK              64U
#define SPMSC3_LVWF_MASK                128U


/*** SCGC1 - System Clock Gating Control 1 Register; 0x0000180E ***/
typedef union {
  byte Byte;
  struct {
    byte SCI1        :1;                                       /* SCI1 Clock Gate Control */
    byte SCI2        :1;                                       /* SCI2 Clock Gate Control */
    byte IIC1        :1;                                       /* IIC1 Clock Gate Control */
    byte IIC2        :1;                                       /* IIC2 Clock Gate Control */
    byte ADC         :1;                                       /* ADC Clock Gate Control */
    byte TPM1        :1;                                       /* TPM1 Clock Gate Control */
    byte TPM2        :1;                                       /* TPM2 Clock Gate Control */
    byte TPM3        :1;                                       /* TPM3 Clock Gate Control */
  } Bits;
  struct {
    byte grpSCI_1 :2;
    byte grpIIC_1 :2;
    byte         :1;
    byte grpTPM_1 :3;
  } MergedBits;
} SCGC1STR;
extern volatile SCGC1STR _SCGC1 @0x0000180E;
#define SCGC1                           _SCGC1.Byte
#define SCGC1_SCI1                      _SCGC1.Bits.SCI1
#define SCGC1_SCI2                      _SCGC1.Bits.SCI2
#define SCGC1_IIC1                      _SCGC1.Bits.IIC1
#define SCGC1_IIC2                      _SCGC1.Bits.IIC2
#define SCGC1_ADC                       _SCGC1.Bits.ADC
#define SCGC1_TPM1                      _SCGC1.Bits.TPM1
#define SCGC1_TPM2                      _SCGC1.Bits.TPM2
#define SCGC1_TPM3                      _SCGC1.Bits.TPM3
#define SCGC1_SCI_1                     _SCGC1.MergedBits.grpSCI_1
#define SCGC1_IIC_1                     _SCGC1.MergedBits.grpIIC_1
#define SCGC1_TPM_1                     _SCGC1.MergedBits.grpTPM_1
#define SCGC1_SCI                       SCGC1_SCI_1
#define SCGC1_IIC                       SCGC1_IIC_1
#define SCGC1_TPM                       SCGC1_TPM_1

#define SCGC1_SCI1_MASK                 1U
#define SCGC1_SCI2_MASK                 2U
#define SCGC1_IIC1_MASK                 4U
#define SCGC1_IIC2_MASK                 8U
#define SCGC1_ADC_MASK                  16U
#define SCGC1_TPM1_MASK                 32U
#define SCGC1_TPM2_MASK                 64U
#define SCGC1_TPM3_MASK                 128U
#define SCGC1_SCI_1_MASK                3U
#define SCGC1_SCI_1_BITNUM              0U
#define SCGC1_IIC_1_MASK                12U
#define SCGC1_IIC_1_BITNUM              2U
#define SCGC1_TPM_1_MASK                224U
#define SCGC1_TPM_1_BITNUM              5U


/*** SCGC2 - System Clock Gating Control 2 Register; 0x0000180F ***/
typedef union {
  byte Byte;
  struct {
    byte SPI1        :1;                                       /* SPI1 Clock Gate Control */
    byte SPI2        :1;                                       /* SPI2 Clock Gate Control */
    byte RTC         :1;                                       /* RTC Clock Gate Control */
    byte ACMP        :1;                                       /* ACMP Clock Gate Control */
    byte KBI         :1;                                       /* KBI Clock Gate Control */
    byte IRQ         :1;                                       /* IRQ Clock Gate Control */
    byte FLS         :1;                                       /* FLASH Register Clock Gate Control */
    byte DBG         :1;                                       /* DBG Clock Gate Control */
  } Bits;
  struct {
    byte grpSPI_1 :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} SCGC2STR;
extern volatile SCGC2STR _SCGC2 @0x0000180F;
#define SCGC2                           _SCGC2.Byte
#define SCGC2_SPI1                      _SCGC2.Bits.SPI1
#define SCGC2_SPI2                      _SCGC2.Bits.SPI2
#define SCGC2_RTC                       _SCGC2.Bits.RTC
#define SCGC2_ACMP                      _SCGC2.Bits.ACMP
#define SCGC2_KBI                       _SCGC2.Bits.KBI
#define SCGC2_IRQ                       _SCGC2.Bits.IRQ
#define SCGC2_FLS                       _SCGC2.Bits.FLS
#define SCGC2_DBG                       _SCGC2.Bits.DBG
#define SCGC2_SPI_1                     _SCGC2.MergedBits.grpSPI_1
#define SCGC2_SPI                       SCGC2_SPI_1

#define SCGC2_SPI1_MASK                 1U
#define SCGC2_SPI2_MASK                 2U
#define SCGC2_RTC_MASK                  4U
#define SCGC2_ACMP_MASK                 8U
#define SCGC2_KBI_MASK                  16U
#define SCGC2_IRQ_MASK                  32U
#define SCGC2_FLS_MASK                  64U
#define SCGC2_DBG_MASK                  128U
#define SCGC2_SPI_1_MASK                3U
#define SCGC2_SPI_1_BITNUM              0U


/*** DBGCA - Debug Comparator A Register; 0x00001810 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DBGCAH - Debug Comparator A High Register; 0x00001810 ***/
    union {
      byte Byte;
      struct {
        byte Bit8        :1;                                       /* Comparator A High Compare Bit 8 */
        byte Bit9        :1;                                       /* Comparator A High Compare Bit 9 */
        byte Bit10       :1;                                       /* Comparator A High Compare Bit 10 */
        byte Bit11       :1;                                       /* Comparator A High Compare Bit 11 */
        byte Bit12       :1;                                       /* Comparator A High Compare Bit 12 */
        byte Bit13       :1;                                       /* Comparator A High Compare Bit 13 */
        byte Bit14       :1;                                       /* Comparator A High Compare Bit 14 */
        byte Bit15       :1;                                       /* Comparator A High Compare Bit 15 */
      } Bits;
    } DBGCAHSTR;
    #define DBGCAH                      _DBGCA.Overlap_STR.DBGCAHSTR.Byte
    #define DBGCAH_Bit8                 _DBGCA.Overlap_STR.DBGCAHSTR.Bits.Bit8
    #define DBGCAH_Bit9                 _DBGCA.Overlap_STR.DBGCAHSTR.Bits.Bit9
    #define DBGCAH_Bit10                _DBGCA.Overlap_STR.DBGCAHSTR.Bits.Bit10
    #define DBGCAH_Bit11                _DBGCA.Overlap_STR.DBGCAHSTR.Bits.Bit11
    #define DBGCAH_Bit12                _DBGCA.Overlap_STR.DBGCAHSTR.Bits.Bit12
    #define DBGCAH_Bit13                _DBGCA.Overlap_STR.DBGCAHSTR.Bits.Bit13
    #define DBGCAH_Bit14                _DBGCA.Overlap_STR.DBGCAHSTR.Bits.Bit14
    #define DBGCAH_Bit15                _DBGCA.Overlap_STR.DBGCAHSTR.Bits.Bit15
    
    #define DBGCAH_Bit8_MASK            1U
    #define DBGCAH_Bit9_MASK            2U
    #define DBGCAH_Bit10_MASK           4U
    #define DBGCAH_Bit11_MASK           8U
    #define DBGCAH_Bit12_MASK           16U
    #define DBGCAH_Bit13_MASK           32U
    #define DBGCAH_Bit14_MASK           64U
    #define DBGCAH_Bit15_MASK           128U
    

    /*** DBGCAL - Debug Comparator A Low Register; 0x00001811 ***/
    union {
      byte Byte;
      struct {
        byte Bit0        :1;                                       /* Comparator A Low Compare Bit 0 */
        byte Bit1        :1;                                       /* Comparator A Low Compare Bit 1 */
        byte Bit2        :1;                                       /* Comparator A Low Compare Bit 2 */
        byte Bit3        :1;                                       /* Comparator A Low Compare Bit 3 */
        byte Bit4        :1;                                       /* Comparator A Low Compare Bit 4 */
        byte Bit5        :1;                                       /* Comparator A Low Compare Bit 5 */
        byte Bit6        :1;                                       /* Comparator A Low Compare Bit 6 */
        byte Bit7        :1;                                       /* Comparator A Low Compare Bit 7 */
      } Bits;
    } DBGCALSTR;
    #define DBGCAL                      _DBGCA.Overlap_STR.DBGCALSTR.Byte
    #define DBGCAL_Bit0                 _DBGCA.Overlap_STR.DBGCALSTR.Bits.Bit0
    #define DBGCAL_Bit1                 _DBGCA.Overlap_STR.DBGCALSTR.Bits.Bit1
    #define DBGCAL_Bit2                 _DBGCA.Overlap_STR.DBGCALSTR.Bits.Bit2
    #define DBGCAL_Bit3                 _DBGCA.Overlap_STR.DBGCALSTR.Bits.Bit3
    #define DBGCAL_Bit4                 _DBGCA.Overlap_STR.DBGCALSTR.Bits.Bit4
    #define DBGCAL_Bit5                 _DBGCA.Overlap_STR.DBGCALSTR.Bits.Bit5
    #define DBGCAL_Bit6                 _DBGCA.Overlap_STR.DBGCALSTR.Bits.Bit6
    #define DBGCAL_Bit7                 _DBGCA.Overlap_STR.DBGCALSTR.Bits.Bit7
    
    #define DBGCAL_Bit0_MASK            1U
    #define DBGCAL_Bit1_MASK            2U
    #define DBGCAL_Bit2_MASK            4U
    #define DBGCAL_Bit3_MASK            8U
    #define DBGCAL_Bit4_MASK            16U
    #define DBGCAL_Bit5_MASK            32U
    #define DBGCAL_Bit6_MASK            64U
    #define DBGCAL_Bit7_MASK            128U
    
  } Overlap_STR;

} DBGCASTR;
extern volatile DBGCASTR _DBGCA @0x00001810;
#define DBGCA                           _DBGCA.Word


/*** DBGCB - Debug Comparator B Register; 0x00001812 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DBGCBH - Debug Comparator B High Register; 0x00001812 ***/
    union {
      byte Byte;
      struct {
        byte Bit8        :1;                                       /* Comparator B High Compare Bit 8 */
        byte Bit9        :1;                                       /* Comparator B High Compare Bit 9 */
        byte Bit10       :1;                                       /* Comparator B High Compare Bit 10 */
        byte Bit11       :1;                                       /* Comparator B High Compare Bit 11 */
        byte Bit12       :1;                                       /* Comparator B High Compare Bit 12 */
        byte Bit13       :1;                                       /* Comparator B High Compare Bit 13 */
        byte Bit14       :1;                                       /* Comparator B High Compare Bit 14 */
        byte Bit15       :1;                                       /* Comparator B High Compare Bit 15 */
      } Bits;
    } DBGCBHSTR;
    #define DBGCBH                      _DBGCB.Overlap_STR.DBGCBHSTR.Byte
    #define DBGCBH_Bit8                 _DBGCB.Overlap_STR.DBGCBHSTR.Bits.Bit8
    #define DBGCBH_Bit9                 _DBGCB.Overlap_STR.DBGCBHSTR.Bits.Bit9
    #define DBGCBH_Bit10                _DBGCB.Overlap_STR.DBGCBHSTR.Bits.Bit10
    #define DBGCBH_Bit11                _DBGCB.Overlap_STR.DBGCBHSTR.Bits.Bit11
    #define DBGCBH_Bit12                _DBGCB.Overlap_STR.DBGCBHSTR.Bits.Bit12
    #define DBGCBH_Bit13                _DBGCB.Overlap_STR.DBGCBHSTR.Bits.Bit13
    #define DBGCBH_Bit14                _DBGCB.Overlap_STR.DBGCBHSTR.Bits.Bit14
    #define DBGCBH_Bit15                _DBGCB.Overlap_STR.DBGCBHSTR.Bits.Bit15
    
    #define DBGCBH_Bit8_MASK            1U
    #define DBGCBH_Bit9_MASK            2U
    #define DBGCBH_Bit10_MASK           4U
    #define DBGCBH_Bit11_MASK           8U
    #define DBGCBH_Bit12_MASK           16U
    #define DBGCBH_Bit13_MASK           32U
    #define DBGCBH_Bit14_MASK           64U
    #define DBGCBH_Bit15_MASK           128U
    

    /*** DBGCBL - Debug Comparator B Low Register; 0x00001813 ***/
    union {
      byte Byte;
      struct {
        byte Bit0        :1;                                       /* Comparator B Low Compare Bit 0 */
        byte Bit1        :1;                                       /* Comparator B Low Compare Bit 1 */
        byte Bit2        :1;                                       /* Comparator B Low Compare Bit 2 */
        byte Bit3        :1;                                       /* Comparator B Low Compare Bit 3 */
        byte Bit4        :1;                                       /* Comparator B Low Compare Bit 4 */
        byte Bit5        :1;                                       /* Comparator B Low Compare Bit 5 */
        byte Bit6        :1;                                       /* Comparator B Low Compare Bit 6 */
        byte Bit7        :1;                                       /* Comparator B Low Compare Bit 7 */
      } Bits;
    } DBGCBLSTR;
    #define DBGCBL                      _DBGCB.Overlap_STR.DBGCBLSTR.Byte
    #define DBGCBL_Bit0                 _DBGCB.Overlap_STR.DBGCBLSTR.Bits.Bit0
    #define DBGCBL_Bit1                 _DBGCB.Overlap_STR.DBGCBLSTR.Bits.Bit1
    #define DBGCBL_Bit2                 _DBGCB.Overlap_STR.DBGCBLSTR.Bits.Bit2
    #define DBGCBL_Bit3                 _DBGCB.Overlap_STR.DBGCBLSTR.Bits.Bit3
    #define DBGCBL_Bit4                 _DBGCB.Overlap_STR.DBGCBLSTR.Bits.Bit4
    #define DBGCBL_Bit5                 _DBGCB.Overlap_STR.DBGCBLSTR.Bits.Bit5
    #define DBGCBL_Bit6                 _DBGCB.Overlap_STR.DBGCBLSTR.Bits.Bit6
    #define DBGCBL_Bit7                 _DBGCB.Overlap_STR.DBGCBLSTR.Bits.Bit7
    
    #define DBGCBL_Bit0_MASK            1U
    #define DBGCBL_Bit1_MASK            2U
    #define DBGCBL_Bit2_MASK            4U
    #define DBGCBL_Bit3_MASK            8U
    #define DBGCBL_Bit4_MASK            16U
    #define DBGCBL_Bit5_MASK            32U
    #define DBGCBL_Bit6_MASK            64U
    #define DBGCBL_Bit7_MASK            128U
    
  } Overlap_STR;

} DBGCBSTR;
extern volatile DBGCBSTR _DBGCB @0x00001812;
#define DBGCB                           _DBGCB.Word


/*** DBGCC - Debug Comparator C Register; 0x00001814 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DBGCCH - Debug Comparator C High Register; 0x00001814 ***/
    union {
      byte Byte;
      struct {
        byte Bit8        :1;                                       /* Comparator C High Compare Bit 8 */
        byte Bit9        :1;                                       /* Comparator C High Compare Bit 9 */
        byte Bit10       :1;                                       /* Comparator C High Compare Bit 10 */
        byte Bit11       :1;                                       /* Comparator C High Compare Bit 11 */
        byte Bit12       :1;                                       /* Comparator C High Compare Bit 12 */
        byte Bit13       :1;                                       /* Comparator C High Compare Bit 13 */
        byte Bit14       :1;                                       /* Comparator C High Compare Bit 14 */
        byte Bit15       :1;                                       /* Comparator C High Compare Bit 15 */
      } Bits;
    } DBGCCHSTR;
    #define DBGCCH                      _DBGCC.Overlap_STR.DBGCCHSTR.Byte
    #define DBGCCH_Bit8                 _DBGCC.Overlap_STR.DBGCCHSTR.Bits.Bit8
    #define DBGCCH_Bit9                 _DBGCC.Overlap_STR.DBGCCHSTR.Bits.Bit9
    #define DBGCCH_Bit10                _DBGCC.Overlap_STR.DBGCCHSTR.Bits.Bit10
    #define DBGCCH_Bit11                _DBGCC.Overlap_STR.DBGCCHSTR.Bits.Bit11
    #define DBGCCH_Bit12                _DBGCC.Overlap_STR.DBGCCHSTR.Bits.Bit12
    #define DBGCCH_Bit13                _DBGCC.Overlap_STR.DBGCCHSTR.Bits.Bit13
    #define DBGCCH_Bit14                _DBGCC.Overlap_STR.DBGCCHSTR.Bits.Bit14
    #define DBGCCH_Bit15                _DBGCC.Overlap_STR.DBGCCHSTR.Bits.Bit15
    
    #define DBGCCH_Bit8_MASK            1U
    #define DBGCCH_Bit9_MASK            2U
    #define DBGCCH_Bit10_MASK           4U
    #define DBGCCH_Bit11_MASK           8U
    #define DBGCCH_Bit12_MASK           16U
    #define DBGCCH_Bit13_MASK           32U
    #define DBGCCH_Bit14_MASK           64U
    #define DBGCCH_Bit15_MASK           128U
    

    /*** DBGCCL - Debug Comparator C Low Register; 0x00001815 ***/
    union {
      byte Byte;
      struct {
        byte Bit0        :1;                                       /* Comparator C Low Compare Bit 0 */
        byte Bit1        :1;                                       /* Comparator C Low Compare Bit 1 */
        byte Bit2        :1;                                       /* Comparator C Low Compare Bit 2 */
        byte Bit3        :1;                                       /* Comparator C Low Compare Bit 3 */
        byte Bit4        :1;                                       /* Comparator C Low Compare Bit 4 */
        byte Bit5        :1;                                       /* Comparator C Low Compare Bit 5 */
        byte Bit6        :1;                                       /* Comparator C Low Compare Bit 6 */
        byte Bit7        :1;                                       /* Comparator C Low Compare Bit 7 */
      } Bits;
    } DBGCCLSTR;
    #define DBGCCL                      _DBGCC.Overlap_STR.DBGCCLSTR.Byte
    #define DBGCCL_Bit0                 _DBGCC.Overlap_STR.DBGCCLSTR.Bits.Bit0
    #define DBGCCL_Bit1                 _DBGCC.Overlap_STR.DBGCCLSTR.Bits.Bit1
    #define DBGCCL_Bit2                 _DBGCC.Overlap_STR.DBGCCLSTR.Bits.Bit2
    #define DBGCCL_Bit3                 _DBGCC.Overlap_STR.DBGCCLSTR.Bits.Bit3
    #define DBGCCL_Bit4                 _DBGCC.Overlap_STR.DBGCCLSTR.Bits.Bit4
    #define DBGCCL_Bit5                 _DBGCC.Overlap_STR.DBGCCLSTR.Bits.Bit5
    #define DBGCCL_Bit6                 _DBGCC.Overlap_STR.DBGCCLSTR.Bits.Bit6
    #define DBGCCL_Bit7                 _DBGCC.Overlap_STR.DBGCCLSTR.Bits.Bit7
    
    #define DBGCCL_Bit0_MASK            1U
    #define DBGCCL_Bit1_MASK            2U
    #define DBGCCL_Bit2_MASK            4U
    #define DBGCCL_Bit3_MASK            8U
    #define DBGCCL_Bit4_MASK            16U
    #define DBGCCL_Bit5_MASK            32U
    #define DBGCCL_Bit6_MASK            64U
    #define DBGCCL_Bit7_MASK            128U
    
  } Overlap_STR;

} DBGCCSTR;
extern volatile DBGCCSTR _DBGCC @0x00001814;
#define DBGCC                           _DBGCC.Word


/*** DBGF - Debug FIFO Register; 0x00001816 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** DBGFH - Debug FIFO High Register; 0x00001816 ***/
    union {
      byte Byte;
      struct {
        byte Bit8        :1;                                       /* FIFO High Data Bit 8 */
        byte Bit9        :1;                                       /* FIFO High Data Bit 9 */
        byte Bit10       :1;                                       /* FIFO High Data Bit 10 */
        byte Bit11       :1;                                       /* FIFO High Data Bit 11 */
        byte Bit12       :1;                                       /* FIFO High Data Bit 12 */
        byte Bit13       :1;                                       /* FIFO High Data Bit 13 */
        byte Bit14       :1;                                       /* FIFO High Data Bit 14 */
        byte Bit15       :1;                                       /* FIFO High Data Bit 15 */
      } Bits;
    } DBGFHSTR;
    #define DBGFH                       _DBGF.Overlap_STR.DBGFHSTR.Byte
    #define DBGFH_Bit8                  _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit8
    #define DBGFH_Bit9                  _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit9
    #define DBGFH_Bit10                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit10
    #define DBGFH_Bit11                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit11
    #define DBGFH_Bit12                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit12
    #define DBGFH_Bit13                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit13
    #define DBGFH_Bit14                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit14
    #define DBGFH_Bit15                 _DBGF.Overlap_STR.DBGFHSTR.Bits.Bit15
    
    #define DBGFH_Bit8_MASK             1U
    #define DBGFH_Bit9_MASK             2U
    #define DBGFH_Bit10_MASK            4U
    #define DBGFH_Bit11_MASK            8U
    #define DBGFH_Bit12_MASK            16U
    #define DBGFH_Bit13_MASK            32U
    #define DBGFH_Bit14_MASK            64U
    #define DBGFH_Bit15_MASK            128U
    

    /*** DBGFL - Debug FIFO Low Register; 0x00001817 ***/
    union {
      byte Byte;
      struct {
        byte Bit0        :1;                                       /* FIFO Low Data Bit 0 */
        byte Bit1        :1;                                       /* FIFO Low Data Bit 1 */
        byte Bit2        :1;                                       /* FIFO Low Data Bit 2 */
        byte Bit3        :1;                                       /* FIFO Low Data Bit 3 */
        byte Bit4        :1;                                       /* FIFO Low Data Bit 4 */
        byte Bit5        :1;                                       /* FIFO Low Data Bit 5 */
        byte Bit6        :1;                                       /* FIFO Low Data Bit 6 */
        byte Bit7        :1;                                       /* FIFO Low Data Bit 7 */
      } Bits;
    } DBGFLSTR;
    #define DBGFL                       _DBGF.Overlap_STR.DBGFLSTR.Byte
    #define DBGFL_Bit0                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit0
    #define DBGFL_Bit1                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit1
    #define DBGFL_Bit2                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit2
    #define DBGFL_Bit3                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit3
    #define DBGFL_Bit4                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit4
    #define DBGFL_Bit5                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit5
    #define DBGFL_Bit6                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit6
    #define DBGFL_Bit7                  _DBGF.Overlap_STR.DBGFLSTR.Bits.Bit7
    
    #define DBGFL_Bit0_MASK             1U
    #define DBGFL_Bit1_MASK             2U
    #define DBGFL_Bit2_MASK             4U
    #define DBGFL_Bit3_MASK             8U
    #define DBGFL_Bit4_MASK             16U
    #define DBGFL_Bit5_MASK             32U
    #define DBGFL_Bit6_MASK             64U
    #define DBGFL_Bit7_MASK             128U
    
  } Overlap_STR;

} DBGFSTR;
extern volatile DBGFSTR _DBGF @0x00001816;
#define DBGF                            _DBGF.Word


/*** DBGCAX - Debug Comparator A Extension Register; 0x00001818 ***/
typedef union {
  byte Byte;
  struct {
    byte Bit16       :1;                                       /* omparator A Extended Address Bit 16 Compare Bit */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte PAGSEL      :1;                                       /* Comparator A Page Select Bit */
    byte RWA         :1;                                       /* Read/Write Comparator A Value Bit */
    byte RWAEN       :1;                                       /* Read/Write Comparator A Enable Bit */
  } Bits;
} DBGCAXSTR;
extern volatile DBGCAXSTR _DBGCAX @0x00001818;
#define DBGCAX                          _DBGCAX.Byte
#define DBGCAX_Bit16                    _DBGCAX.Bits.Bit16
#define DBGCAX_PAGSEL                   _DBGCAX.Bits.PAGSEL
#define DBGCAX_RWA                      _DBGCAX.Bits.RWA
#define DBGCAX_RWAEN                    _DBGCAX.Bits.RWAEN

#define DBGCAX_Bit16_MASK               1U
#define DBGCAX_PAGSEL_MASK              32U
#define DBGCAX_RWA_MASK                 64U
#define DBGCAX_RWAEN_MASK               128U


/*** DBGCBX - Debug Comparator B Extension Register; 0x00001819 ***/
typedef union {
  byte Byte;
  struct {
    byte Bit16       :1;                                       /* omparator B Extended Address Bit 16 Compare Bit */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte PAGSEL      :1;                                       /* Comparator B Page Select Bit */
    byte RWB         :1;                                       /* Read/Write Comparator B Value Bit */
    byte RWBEN       :1;                                       /* Read/Write Comparator B Enable Bit */
  } Bits;
} DBGCBXSTR;
extern volatile DBGCBXSTR _DBGCBX @0x00001819;
#define DBGCBX                          _DBGCBX.Byte
#define DBGCBX_Bit16                    _DBGCBX.Bits.Bit16
#define DBGCBX_PAGSEL                   _DBGCBX.Bits.PAGSEL
#define DBGCBX_RWB                      _DBGCBX.Bits.RWB
#define DBGCBX_RWBEN                    _DBGCBX.Bits.RWBEN

#define DBGCBX_Bit16_MASK               1U
#define DBGCBX_PAGSEL_MASK              32U
#define DBGCBX_RWB_MASK                 64U
#define DBGCBX_RWBEN_MASK               128U


/*** DBGCCX - Debug Comparator C Extension Register; 0x0000181A ***/
typedef union {
  byte Byte;
  struct {
    byte Bit16       :1;                                       /* omparator C Extended Address Bit 16 Compare Bit */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte PAGSEL      :1;                                       /* Comparator C Page Select Bit */
    byte RWC         :1;                                       /* Read/Write Comparator C Value Bit */
    byte RWCEN       :1;                                       /* Read/Write Comparator C Enable Bit */
  } Bits;
} DBGCCXSTR;
extern volatile DBGCCXSTR _DBGCCX @0x0000181A;
#define DBGCCX                          _DBGCCX.Byte
#define DBGCCX_Bit16                    _DBGCCX.Bits.Bit16
#define DBGCCX_PAGSEL                   _DBGCCX.Bits.PAGSEL
#define DBGCCX_RWC                      _DBGCCX.Bits.RWC
#define DBGCCX_RWCEN                    _DBGCCX.Bits.RWCEN

#define DBGCCX_Bit16_MASK               1U
#define DBGCCX_PAGSEL_MASK              32U
#define DBGCCX_RWC_MASK                 64U
#define DBGCCX_RWCEN_MASK               128U


/*** DBGFX - Debug FIFO Extended Information Register; 0x0000181B ***/
typedef union {
  byte Byte;
  struct {
    byte Bit16       :1;                                       /* Extended Address Bit 16 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte PPACC       :1;                                       /* PPAGE Access Indicator Bit */
  } Bits;
} DBGFXSTR;
extern volatile DBGFXSTR _DBGFX @0x0000181B;
#define DBGFX                           _DBGFX.Byte
#define DBGFX_Bit16                     _DBGFX.Bits.Bit16
#define DBGFX_PPACC                     _DBGFX.Bits.PPACC

#define DBGFX_Bit16_MASK                1U
#define DBGFX_PPACC_MASK                128U


/*** DBGC - Debug Control Register; 0x0000181C ***/
typedef union {
  byte Byte;
  struct {
    byte LOOP1       :1;                                       /* Select LOOP1 Capture Mode */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte BRKEN       :1;                                       /* Break Enable Bit */
    byte TAG         :1;                                       /* Tag or Force Bit */
    byte ARM         :1;                                       /* Arm Bit */
    byte DBGEN       :1;                                       /* DBG Module Enable Bit */
  } Bits;
} DBGCSTR;
extern volatile DBGCSTR _DBGC @0x0000181C;
#define DBGC                            _DBGC.Byte
#define DBGC_LOOP1                      _DBGC.Bits.LOOP1
#define DBGC_BRKEN                      _DBGC.Bits.BRKEN
#define DBGC_TAG                        _DBGC.Bits.TAG
#define DBGC_ARM                        _DBGC.Bits.ARM
#define DBGC_DBGEN                      _DBGC.Bits.DBGEN

#define DBGC_LOOP1_MASK                 1U
#define DBGC_BRKEN_MASK                 16U
#define DBGC_TAG_MASK                   32U
#define DBGC_ARM_MASK                   64U
#define DBGC_DBGEN_MASK                 128U


/*** DBGT - Debug Trigger Register; 0x0000181D ***/
typedef union {
  byte Byte;
  struct {
    byte TRG0        :1;                                       /* Trigger Mode Bit 0 */
    byte TRG1        :1;                                       /* Trigger Mode Bit 1 */
    byte TRG2        :1;                                       /* Trigger Mode Bit 2 */
    byte TRG3        :1;                                       /* Trigger Mode Bit 3 */
    byte             :1; 
    byte             :1; 
    byte BEGIN       :1;                                       /* Begin/End Trigger Bit */
    byte TRGSEL      :1;                                       /* Trigger Selection Bit */
  } Bits;
  struct {
    byte grpTRG  :4;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} DBGTSTR;
extern volatile DBGTSTR _DBGT @0x0000181D;
#define DBGT                            _DBGT.Byte
#define DBGT_TRG0                       _DBGT.Bits.TRG0
#define DBGT_TRG1                       _DBGT.Bits.TRG1
#define DBGT_TRG2                       _DBGT.Bits.TRG2
#define DBGT_TRG3                       _DBGT.Bits.TRG3
#define DBGT_BEGIN                      _DBGT.Bits.BEGIN
#define DBGT_TRGSEL                     _DBGT.Bits.TRGSEL
#define DBGT_TRG                        _DBGT.MergedBits.grpTRG

#define DBGT_TRG0_MASK                  1U
#define DBGT_TRG1_MASK                  2U
#define DBGT_TRG2_MASK                  4U
#define DBGT_TRG3_MASK                  8U
#define DBGT_BEGIN_MASK                 64U
#define DBGT_TRGSEL_MASK                128U
#define DBGT_TRG_MASK                   15U
#define DBGT_TRG_BITNUM                 0U


/*** DBGS - Debug Status Register; 0x0000181E ***/
typedef union {
  byte Byte;
  struct {
    byte ARMF        :1;                                       /* Arm Flag Bit */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte CF          :1;                                       /* Trigger C Match Bit */
    byte BF          :1;                                       /* Trigger B Match Bit */
    byte AF          :1;                                       /* Trigger A Match Bit */
  } Bits;
} DBGSSTR;
extern volatile DBGSSTR _DBGS @0x0000181E;
#define DBGS                            _DBGS.Byte
#define DBGS_ARMF                       _DBGS.Bits.ARMF
#define DBGS_CF                         _DBGS.Bits.CF
#define DBGS_BF                         _DBGS.Bits.BF
#define DBGS_AF                         _DBGS.Bits.AF

#define DBGS_ARMF_MASK                  1U
#define DBGS_CF_MASK                    32U
#define DBGS_BF_MASK                    64U
#define DBGS_AF_MASK                    128U


/*** DBGCNT - Debug Count Status Register; 0x0000181F ***/
typedef union {
  byte Byte;
  struct {
    byte CNT0        :1;                                       /* FIFO Valid Count Bits, bit 0 */
    byte CNT1        :1;                                       /* FIFO Valid Count Bits, bit 1 */
    byte CNT2        :1;                                       /* FIFO Valid Count Bits, bit 2 */
    byte CNT3        :1;                                       /* FIFO Valid Count Bits, bit 3 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
  struct {
    byte grpCNT  :4;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} DBGCNTSTR;
extern volatile DBGCNTSTR _DBGCNT @0x0000181F;
#define DBGCNT                          _DBGCNT.Byte
#define DBGCNT_CNT0                     _DBGCNT.Bits.CNT0
#define DBGCNT_CNT1                     _DBGCNT.Bits.CNT1
#define DBGCNT_CNT2                     _DBGCNT.Bits.CNT2
#define DBGCNT_CNT3                     _DBGCNT.Bits.CNT3
#define DBGCNT_CNT                      _DBGCNT.MergedBits.grpCNT

#define DBGCNT_CNT0_MASK                1U
#define DBGCNT_CNT1_MASK                2U
#define DBGCNT_CNT2_MASK                4U
#define DBGCNT_CNT3_MASK                8U
#define DBGCNT_CNT_MASK                 15U
#define DBGCNT_CNT_BITNUM               0U


/*** FCDIV - FLASH Clock Divider Register; 0x00001820 ***/
typedef union {
  byte Byte;
  struct {
    byte FDIV0       :1;                                       /* Divisor for FLASH Clock Divider, bit 0 */
    byte FDIV1       :1;                                       /* Divisor for FLASH Clock Divider, bit 1 */
    byte FDIV2       :1;                                       /* Divisor for FLASH Clock Divider, bit 2 */
    byte FDIV3       :1;                                       /* Divisor for FLASH Clock Divider, bit 3 */
    byte FDIV4       :1;                                       /* Divisor for FLASH Clock Divider, bit 4 */
    byte FDIV5       :1;                                       /* Divisor for FLASH Clock Divider, bit 5 */
    byte PRDIV8      :1;                                       /* Prescale (Divide) FLASH Clock by 8 */
    byte FDIVLD      :1;                                       /* Divisor Loaded Status Flag */
  } Bits;
  struct {
    byte grpFDIV :6;
    byte grpPRDIV_8 :1;
    byte         :1;
  } MergedBits;
} FCDIVSTR;
extern volatile FCDIVSTR _FCDIV @0x00001820;
#define FCDIV                           _FCDIV.Byte
#define FCDIV_FDIV0                     _FCDIV.Bits.FDIV0
#define FCDIV_FDIV1                     _FCDIV.Bits.FDIV1
#define FCDIV_FDIV2                     _FCDIV.Bits.FDIV2
#define FCDIV_FDIV3                     _FCDIV.Bits.FDIV3
#define FCDIV_FDIV4                     _FCDIV.Bits.FDIV4
#define FCDIV_FDIV5                     _FCDIV.Bits.FDIV5
#define FCDIV_PRDIV8                    _FCDIV.Bits.PRDIV8
#define FCDIV_FDIVLD                    _FCDIV.Bits.FDIVLD
#define FCDIV_FDIV                      _FCDIV.MergedBits.grpFDIV

#define FCDIV_FDIV0_MASK                1U
#define FCDIV_FDIV1_MASK                2U
#define FCDIV_FDIV2_MASK                4U
#define FCDIV_FDIV3_MASK                8U
#define FCDIV_FDIV4_MASK                16U
#define FCDIV_FDIV5_MASK                32U
#define FCDIV_PRDIV8_MASK               64U
#define FCDIV_FDIVLD_MASK               128U
#define FCDIV_FDIV_MASK                 63U
#define FCDIV_FDIV_BITNUM               0U


/*** FOPT - Flash Options Register; 0x00001821 ***/
typedef union {
  byte Byte;
  struct {
    byte SEC0        :1;                                       /* Flash Security Bit 0 */
    byte SEC1        :1;                                       /* Flash Security Bit 1 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte KEYEN0      :1;                                       /* Backdoor Key Security Enable Bit 0 */
    byte KEYEN1      :1;                                       /* Backdoor Key Security Enable Bit 1 */
  } Bits;
  struct {
    byte grpSEC  :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpKEYEN :2;
  } MergedBits;
} FOPTSTR;
extern volatile FOPTSTR _FOPT @0x00001821;
#define FOPT                            _FOPT.Byte
#define FOPT_SEC0                       _FOPT.Bits.SEC0
#define FOPT_SEC1                       _FOPT.Bits.SEC1
#define FOPT_KEYEN0                     _FOPT.Bits.KEYEN0
#define FOPT_KEYEN1                     _FOPT.Bits.KEYEN1
#define FOPT_SEC                        _FOPT.MergedBits.grpSEC
#define FOPT_KEYEN                      _FOPT.MergedBits.grpKEYEN

#define FOPT_SEC0_MASK                  1U
#define FOPT_SEC1_MASK                  2U
#define FOPT_KEYEN0_MASK                64U
#define FOPT_KEYEN1_MASK                128U
#define FOPT_SEC_MASK                   3U
#define FOPT_SEC_BITNUM                 0U
#define FOPT_KEYEN_MASK                 192U
#define FOPT_KEYEN_BITNUM               6U


/*** FCNFG - Flash Configuration Register; 0x00001823 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte KEYACC      :1;                                       /* Enable Security Key Writing */
    byte             :1; 
    byte             :1; 
  } Bits;
} FCNFGSTR;
extern volatile FCNFGSTR _FCNFG @0x00001823;
#define FCNFG                           _FCNFG.Byte
#define FCNFG_KEYACC                    _FCNFG.Bits.KEYACC

#define FCNFG_KEYACC_MASK               32U


/*** FPROT - Flash Protection Register; 0x00001824 ***/
typedef union {
  byte Byte;
  struct {
    byte FPOPEN      :1;                                       /* Flash Protection Open */
    byte FPS0        :1;                                       /* Flash Protection Size, bit 0 */
    byte FPS1        :1;                                       /* Flash Protection Size, bit 1 */
    byte FPS2        :1;                                       /* Flash Protection Size, bit 2 */
    byte FPS3        :1;                                       /* Flash Protection Size, bit 3 */
    byte FPS4        :1;                                       /* Flash Protection Size, bit 4 */
    byte FPS5        :1;                                       /* Flash Protection Size, bit 5 */
    byte FPS6        :1;                                       /* Flash Protection Size, bit 6 */
  } Bits;
  struct {
    byte         :1;
    byte grpFPS  :7;
  } MergedBits;
} FPROTSTR;
extern volatile FPROTSTR _FPROT @0x00001824;
#define FPROT                           _FPROT.Byte
#define FPROT_FPOPEN                    _FPROT.Bits.FPOPEN
#define FPROT_FPS0                      _FPROT.Bits.FPS0
#define FPROT_FPS1                      _FPROT.Bits.FPS1
#define FPROT_FPS2                      _FPROT.Bits.FPS2
#define FPROT_FPS3                      _FPROT.Bits.FPS3
#define FPROT_FPS4                      _FPROT.Bits.FPS4
#define FPROT_FPS5                      _FPROT.Bits.FPS5
#define FPROT_FPS6                      _FPROT.Bits.FPS6
#define FPROT_FPS                       _FPROT.MergedBits.grpFPS

#define FPROT_FPOPEN_MASK               1U
#define FPROT_FPS0_MASK                 2U
#define FPROT_FPS1_MASK                 4U
#define FPROT_FPS2_MASK                 8U
#define FPROT_FPS3_MASK                 16U
#define FPROT_FPS4_MASK                 32U
#define FPROT_FPS5_MASK                 64U
#define FPROT_FPS6_MASK                 128U
#define FPROT_FPS_MASK                  254U
#define FPROT_FPS_BITNUM                1U


/*** FSTAT - Flash Status Register; 0x00001825 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte FBLANK      :1;                                       /* FLASH Flag Indicating the Erase Verify Operation Status */
    byte             :1; 
    byte FACCERR     :1;                                       /* FLASH Access Error Flag */
    byte FPVIOL      :1;                                       /* FLASH Protection Violation Flag */
    byte FCCF        :1;                                       /* FLASH Command Complete Interrupt Flag */
    byte FCBEF       :1;                                       /* FLASH Command Buffer Empty Flag */
  } Bits;
} FSTATSTR;
extern volatile FSTATSTR _FSTAT @0x00001825;
#define FSTAT                           _FSTAT.Byte
#define FSTAT_FBLANK                    _FSTAT.Bits.FBLANK
#define FSTAT_FACCERR                   _FSTAT.Bits.FACCERR
#define FSTAT_FPVIOL                    _FSTAT.Bits.FPVIOL
#define FSTAT_FCCF                      _FSTAT.Bits.FCCF
#define FSTAT_FCBEF                     _FSTAT.Bits.FCBEF

#define FSTAT_FBLANK_MASK               4U
#define FSTAT_FACCERR_MASK              16U
#define FSTAT_FPVIOL_MASK               32U
#define FSTAT_FCCF_MASK                 64U
#define FSTAT_FCBEF_MASK                128U


/*** FCMD - Flash Command Register; 0x00001826 ***/
typedef union {
  byte Byte;
  struct {
    byte FCMD0       :1;                                       /* Flash Command, bit 0 */
    byte FCMD1       :1;                                       /* Flash Command, bit 1 */
    byte FCMD2       :1;                                       /* Flash Command, bit 2 */
    byte FCMD3       :1;                                       /* Flash Command, bit 3 */
    byte FCMD4       :1;                                       /* Flash Command, bit 4 */
    byte FCMD5       :1;                                       /* Flash Command, bit 5 */
    byte FCMD6       :1;                                       /* Flash Command, bit 6 */
    byte             :1; 
  } Bits;
  struct {
    byte grpFCMD :7;
    byte         :1;
  } MergedBits;
} FCMDSTR;
extern volatile FCMDSTR _FCMD @0x00001826;
#define FCMD                            _FCMD.Byte
#define FCMD_FCMD0                      _FCMD.Bits.FCMD0
#define FCMD_FCMD1                      _FCMD.Bits.FCMD1
#define FCMD_FCMD2                      _FCMD.Bits.FCMD2
#define FCMD_FCMD3                      _FCMD.Bits.FCMD3
#define FCMD_FCMD4                      _FCMD.Bits.FCMD4
#define FCMD_FCMD5                      _FCMD.Bits.FCMD5
#define FCMD_FCMD6                      _FCMD.Bits.FCMD6
#define FCMD_FCMD                       _FCMD.MergedBits.grpFCMD

#define FCMD_FCMD0_MASK                 1U
#define FCMD_FCMD1_MASK                 2U
#define FCMD_FCMD2_MASK                 4U
#define FCMD_FCMD3_MASK                 8U
#define FCMD_FCMD4_MASK                 16U
#define FCMD_FCMD5_MASK                 32U
#define FCMD_FCMD6_MASK                 64U
#define FCMD_FCMD_MASK                  127U
#define FCMD_FCMD_BITNUM                0U


/*** RTCSC - RTC Status and Control Register; 0x00001830 ***/
typedef union {
  byte Byte;
  struct {
    byte RTCPS0      :1;                                       /* Real-Time Clock Prescaler Select, bit 0 */
    byte RTCPS1      :1;                                       /* Real-Time Clock Prescaler Select, bit 1 */
    byte RTCPS2      :1;                                       /* Real-Time Clock Prescaler Select, bit 2 */
    byte RTCPS3      :1;                                       /* Real-Time Clock Prescaler Select, bit 3 */
    byte RTIE        :1;                                       /* Real-Time Interrupt Enable */
    byte RTCLKS0     :1;                                       /* Real-Time Clock Source Select, bit 0 */
    byte RTCLKS1     :1;                                       /* Real-Time Clock Source Select, bit 1 */
    byte RTIF        :1;                                       /* Real-Time Interrupt Flag */
  } Bits;
  struct {
    byte grpRTCPS :4;
    byte         :1;
    byte grpRTCLKS :2;
    byte         :1;
  } MergedBits;
} RTCSCSTR;
extern volatile RTCSCSTR _RTCSC @0x00001830;
#define RTCSC                           _RTCSC.Byte
#define RTCSC_RTCPS0                    _RTCSC.Bits.RTCPS0
#define RTCSC_RTCPS1                    _RTCSC.Bits.RTCPS1
#define RTCSC_RTCPS2                    _RTCSC.Bits.RTCPS2
#define RTCSC_RTCPS3                    _RTCSC.Bits.RTCPS3
#define RTCSC_RTIE                      _RTCSC.Bits.RTIE
#define RTCSC_RTCLKS0                   _RTCSC.Bits.RTCLKS0
#define RTCSC_RTCLKS1                   _RTCSC.Bits.RTCLKS1
#define RTCSC_RTIF                      _RTCSC.Bits.RTIF
#define RTCSC_RTCPS                     _RTCSC.MergedBits.grpRTCPS
#define RTCSC_RTCLKS                    _RTCSC.MergedBits.grpRTCLKS

#define RTCSC_RTCPS0_MASK               1U
#define RTCSC_RTCPS1_MASK               2U
#define RTCSC_RTCPS2_MASK               4U
#define RTCSC_RTCPS3_MASK               8U
#define RTCSC_RTIE_MASK                 16U
#define RTCSC_RTCLKS0_MASK              32U
#define RTCSC_RTCLKS1_MASK              64U
#define RTCSC_RTIF_MASK                 128U
#define RTCSC_RTCPS_MASK                15U
#define RTCSC_RTCPS_BITNUM              0U
#define RTCSC_RTCLKS_MASK               96U
#define RTCSC_RTCLKS_BITNUM             5U


/*** RTCCNT - RTC Counter Register; 0x00001831 ***/
typedef union {
  byte Byte;
} RTCCNTSTR;
extern volatile RTCCNTSTR _RTCCNT @0x00001831;
#define RTCCNT                          _RTCCNT.Byte


/*** RTCMOD - RTC Modulo Register; 0x00001832 ***/
typedef union {
  byte Byte;
} RTCMODSTR;
extern volatile RTCMODSTR _RTCMOD @0x00001832;
#define RTCMOD                          _RTCMOD.Byte


/*** SPI2C1 - SPI2 Control Register 1; 0x00001838 ***/
typedef union {
  byte Byte;
  struct {
    byte LSBFE       :1;                                       /* LSB First (Shifter Direction) */
    byte SSOE        :1;                                       /* Slave Select Output Enable */
    byte CPHA        :1;                                       /* Clock Phase */
    byte CPOL        :1;                                       /* Clock Polarity */
    byte MSTR        :1;                                       /* Master/Slave Mode Select */
    byte SPTIE       :1;                                       /* SPI Transmit Interrupt Enable */
    byte SPE         :1;                                       /* SPI System Enable */
    byte SPIE        :1;                                       /* SPI Interrupt Enable (for SPRF and MODF) */
  } Bits;
} SPI2C1STR;
extern volatile SPI2C1STR _SPI2C1 @0x00001838;
#define SPI2C1                          _SPI2C1.Byte
#define SPI2C1_LSBFE                    _SPI2C1.Bits.LSBFE
#define SPI2C1_SSOE                     _SPI2C1.Bits.SSOE
#define SPI2C1_CPHA                     _SPI2C1.Bits.CPHA
#define SPI2C1_CPOL                     _SPI2C1.Bits.CPOL
#define SPI2C1_MSTR                     _SPI2C1.Bits.MSTR
#define SPI2C1_SPTIE                    _SPI2C1.Bits.SPTIE
#define SPI2C1_SPE                      _SPI2C1.Bits.SPE
#define SPI2C1_SPIE                     _SPI2C1.Bits.SPIE

#define SPI2C1_LSBFE_MASK               1U
#define SPI2C1_SSOE_MASK                2U
#define SPI2C1_CPHA_MASK                4U
#define SPI2C1_CPOL_MASK                8U
#define SPI2C1_MSTR_MASK                16U
#define SPI2C1_SPTIE_MASK               32U
#define SPI2C1_SPE_MASK                 64U
#define SPI2C1_SPIE_MASK                128U


/*** SPI2C2 - SPI2 Control Register 2; 0x00001839 ***/
typedef union {
  byte Byte;
  struct {
    byte SPC0        :1;                                       /* SPI Pin Control 0 */
    byte SPISWAI     :1;                                       /* SPI Stop in Wait Mode */
    byte             :1; 
    byte BIDIROE     :1;                                       /* Bidirectional Mode Output Enable */
    byte MODFEN      :1;                                       /* Master Mode-Fault Function Enable */
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} SPI2C2STR;
extern volatile SPI2C2STR _SPI2C2 @0x00001839;
#define SPI2C2                          _SPI2C2.Byte
#define SPI2C2_SPC0                     _SPI2C2.Bits.SPC0
#define SPI2C2_SPISWAI                  _SPI2C2.Bits.SPISWAI
#define SPI2C2_BIDIROE                  _SPI2C2.Bits.BIDIROE
#define SPI2C2_MODFEN                   _SPI2C2.Bits.MODFEN

#define SPI2C2_SPC0_MASK                1U
#define SPI2C2_SPISWAI_MASK             2U
#define SPI2C2_BIDIROE_MASK             8U
#define SPI2C2_MODFEN_MASK              16U


/*** SPI2BR - SPI2 Baud Rate Register; 0x0000183A ***/
typedef union {
  byte Byte;
  struct {
    byte SPR0        :1;                                       /* SPI Baud Rate Divisor Bit 0 */
    byte SPR1        :1;                                       /* SPI Baud Rate Divisor Bit 1 */
    byte SPR2        :1;                                       /* SPI Baud Rate Divisor Bit 2 */
    byte             :1; 
    byte SPPR0       :1;                                       /* SPI Baud Rate Prescale Divisor Bit 0 */
    byte SPPR1       :1;                                       /* SPI Baud Rate Prescale Divisor Bit 1 */
    byte SPPR2       :1;                                       /* SPI Baud Rate Prescale Divisor Bit 2 */
    byte             :1; 
  } Bits;
  struct {
    byte grpSPR  :3;
    byte         :1;
    byte grpSPPR :3;
    byte         :1;
  } MergedBits;
} SPI2BRSTR;
extern volatile SPI2BRSTR _SPI2BR @0x0000183A;
#define SPI2BR                          _SPI2BR.Byte
#define SPI2BR_SPR0                     _SPI2BR.Bits.SPR0
#define SPI2BR_SPR1                     _SPI2BR.Bits.SPR1
#define SPI2BR_SPR2                     _SPI2BR.Bits.SPR2
#define SPI2BR_SPPR0                    _SPI2BR.Bits.SPPR0
#define SPI2BR_SPPR1                    _SPI2BR.Bits.SPPR1
#define SPI2BR_SPPR2                    _SPI2BR.Bits.SPPR2
#define SPI2BR_SPR                      _SPI2BR.MergedBits.grpSPR
#define SPI2BR_SPPR                     _SPI2BR.MergedBits.grpSPPR

#define SPI2BR_SPR0_MASK                1U
#define SPI2BR_SPR1_MASK                2U
#define SPI2BR_SPR2_MASK                4U
#define SPI2BR_SPPR0_MASK               16U
#define SPI2BR_SPPR1_MASK               32U
#define SPI2BR_SPPR2_MASK               64U
#define SPI2BR_SPR_MASK                 7U
#define SPI2BR_SPR_BITNUM               0U
#define SPI2BR_SPPR_MASK                112U
#define SPI2BR_SPPR_BITNUM              4U


/*** SPI2S - SPI2 Status Register; 0x0000183B ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte MODF        :1;                                       /* Master Mode Fault Flag */
    byte SPTEF       :1;                                       /* SPI Transmit Buffer Empty Flag */
    byte             :1; 
    byte SPRF        :1;                                       /* SPI Read Buffer Full Flag */
  } Bits;
} SPI2SSTR;
extern volatile SPI2SSTR _SPI2S @0x0000183B;
#define SPI2S                           _SPI2S.Byte
#define SPI2S_MODF                      _SPI2S.Bits.MODF
#define SPI2S_SPTEF                     _SPI2S.Bits.SPTEF
#define SPI2S_SPRF                      _SPI2S.Bits.SPRF

#define SPI2S_MODF_MASK                 16U
#define SPI2S_SPTEF_MASK                32U
#define SPI2S_SPRF_MASK                 128U


/*** SPI2D - SPI2 Data Register; 0x0000183D ***/
typedef union {
  byte Byte;
} SPI2DSTR;
extern volatile SPI2DSTR _SPI2D @0x0000183D;
#define SPI2D                           _SPI2D.Byte


/*** PTAPE - Port A Pull Enable Register; 0x00001840 ***/
typedef union {
  byte Byte;
  struct {
    byte PTAPE0      :1;                                       /* Internal Pull Enable for Port A Bit 0 */
    byte PTAPE1      :1;                                       /* Internal Pull Enable for Port A Bit 1 */
    byte PTAPE2      :1;                                       /* Internal Pull Enable for Port A Bit 2 */
    byte PTAPE3      :1;                                       /* Internal Pull Enable for Port A Bit 3 */
    byte PTAPE4      :1;                                       /* Internal Pull Enable for Port A Bit 4 */
    byte PTAPE5      :1;                                       /* Internal Pull Enable for Port A Bit 5 */
    byte PTAPE6      :1;                                       /* Internal Pull Enable for Port A Bit 6 */
    byte PTAPE7      :1;                                       /* Internal Pull Enable for Port A Bit 7 */
  } Bits;
} PTAPESTR;
extern volatile PTAPESTR _PTAPE @0x00001840;
#define PTAPE                           _PTAPE.Byte
#define PTAPE_PTAPE0                    _PTAPE.Bits.PTAPE0
#define PTAPE_PTAPE1                    _PTAPE.Bits.PTAPE1
#define PTAPE_PTAPE2                    _PTAPE.Bits.PTAPE2
#define PTAPE_PTAPE3                    _PTAPE.Bits.PTAPE3
#define PTAPE_PTAPE4                    _PTAPE.Bits.PTAPE4
#define PTAPE_PTAPE5                    _PTAPE.Bits.PTAPE5
#define PTAPE_PTAPE6                    _PTAPE.Bits.PTAPE6
#define PTAPE_PTAPE7                    _PTAPE.Bits.PTAPE7

#define PTAPE_PTAPE0_MASK               1U
#define PTAPE_PTAPE1_MASK               2U
#define PTAPE_PTAPE2_MASK               4U
#define PTAPE_PTAPE3_MASK               8U
#define PTAPE_PTAPE4_MASK               16U
#define PTAPE_PTAPE5_MASK               32U
#define PTAPE_PTAPE6_MASK               64U
#define PTAPE_PTAPE7_MASK               128U


/*** PTASE - Port A Slew Rate Enable Register; 0x00001841 ***/
typedef union {
  byte Byte;
  struct {
    byte PTASE0      :1;                                       /* Output Slew Rate Enable for Port A Bit 0 */
    byte PTASE1      :1;                                       /* Output Slew Rate Enable for Port A Bit 1 */
    byte PTASE2      :1;                                       /* Output Slew Rate Enable for Port A Bit 2 */
    byte PTASE3      :1;                                       /* Output Slew Rate Enable for Port A Bit 3 */
    byte PTASE4      :1;                                       /* Output Slew Rate Enable for Port A Bit 4 */
    byte PTASE5      :1;                                       /* Output Slew Rate Enable for Port A Bit 5 */
    byte PTASE6      :1;                                       /* Output Slew Rate Enable for Port A Bit 6 */
    byte PTASE7      :1;                                       /* Output Slew Rate Enable for Port A Bit 7 */
  } Bits;
} PTASESTR;
extern volatile PTASESTR _PTASE @0x00001841;
#define PTASE                           _PTASE.Byte
#define PTASE_PTASE0                    _PTASE.Bits.PTASE0
#define PTASE_PTASE1                    _PTASE.Bits.PTASE1
#define PTASE_PTASE2                    _PTASE.Bits.PTASE2
#define PTASE_PTASE3                    _PTASE.Bits.PTASE3
#define PTASE_PTASE4                    _PTASE.Bits.PTASE4
#define PTASE_PTASE5                    _PTASE.Bits.PTASE5
#define PTASE_PTASE6                    _PTASE.Bits.PTASE6
#define PTASE_PTASE7                    _PTASE.Bits.PTASE7

#define PTASE_PTASE0_MASK               1U
#define PTASE_PTASE1_MASK               2U
#define PTASE_PTASE2_MASK               4U
#define PTASE_PTASE3_MASK               8U
#define PTASE_PTASE4_MASK               16U
#define PTASE_PTASE5_MASK               32U
#define PTASE_PTASE6_MASK               64U
#define PTASE_PTASE7_MASK               128U


/*** PTADS - Port A Drive Strength Selection Register; 0x00001842 ***/
typedef union {
  byte Byte;
  struct {
    byte PTADS0      :1;                                       /* Output Drive Strength Selection for Port A Bit 0 */
    byte PTADS1      :1;                                       /* Output Drive Strength Selection for Port A Bit 1 */
    byte PTADS2      :1;                                       /* Output Drive Strength Selection for Port A Bit 2 */
    byte PTADS3      :1;                                       /* Output Drive Strength Selection for Port A Bit 3 */
    byte PTADS4      :1;                                       /* Output Drive Strength Selection for Port A Bit 4 */
    byte PTADS5      :1;                                       /* Output Drive Strength Selection for Port A Bit 5 */
    byte PTADS6      :1;                                       /* Output Drive Strength Selection for Port A Bit 6 */
    byte PTADS7      :1;                                       /* Output Drive Strength Selection for Port A Bit 7 */
  } Bits;
} PTADSSTR;
extern volatile PTADSSTR _PTADS @0x00001842;
#define PTADS                           _PTADS.Byte
#define PTADS_PTADS0                    _PTADS.Bits.PTADS0
#define PTADS_PTADS1                    _PTADS.Bits.PTADS1
#define PTADS_PTADS2                    _PTADS.Bits.PTADS2
#define PTADS_PTADS3                    _PTADS.Bits.PTADS3
#define PTADS_PTADS4                    _PTADS.Bits.PTADS4
#define PTADS_PTADS5                    _PTADS.Bits.PTADS5
#define PTADS_PTADS6                    _PTADS.Bits.PTADS6
#define PTADS_PTADS7                    _PTADS.Bits.PTADS7

#define PTADS_PTADS0_MASK               1U
#define PTADS_PTADS1_MASK               2U
#define PTADS_PTADS2_MASK               4U
#define PTADS_PTADS3_MASK               8U
#define PTADS_PTADS4_MASK               16U
#define PTADS_PTADS5_MASK               32U
#define PTADS_PTADS6_MASK               64U
#define PTADS_PTADS7_MASK               128U


/*** PTBPE - Port B Pull Enable Register; 0x00001844 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBPE0      :1;                                       /* Internal Pull Enable for Port B Bit 0 */
    byte PTBPE1      :1;                                       /* Internal Pull Enable for Port B Bit 1 */
    byte PTBPE2      :1;                                       /* Internal Pull Enable for Port B Bit 2 */
    byte PTBPE3      :1;                                       /* Internal Pull Enable for Port B Bit 3 */
    byte PTBPE4      :1;                                       /* Internal Pull Enable for Port B Bit 4 */
    byte PTBPE5      :1;                                       /* Internal Pull Enable for Port B Bit 5 */
    byte PTBPE6      :1;                                       /* Internal Pull Enable for Port B Bit 6 */
    byte PTBPE7      :1;                                       /* Internal Pull Enable for Port B Bit 7 */
  } Bits;
} PTBPESTR;
extern volatile PTBPESTR _PTBPE @0x00001844;
#define PTBPE                           _PTBPE.Byte
#define PTBPE_PTBPE0                    _PTBPE.Bits.PTBPE0
#define PTBPE_PTBPE1                    _PTBPE.Bits.PTBPE1
#define PTBPE_PTBPE2                    _PTBPE.Bits.PTBPE2
#define PTBPE_PTBPE3                    _PTBPE.Bits.PTBPE3
#define PTBPE_PTBPE4                    _PTBPE.Bits.PTBPE4
#define PTBPE_PTBPE5                    _PTBPE.Bits.PTBPE5
#define PTBPE_PTBPE6                    _PTBPE.Bits.PTBPE6
#define PTBPE_PTBPE7                    _PTBPE.Bits.PTBPE7

#define PTBPE_PTBPE0_MASK               1U
#define PTBPE_PTBPE1_MASK               2U
#define PTBPE_PTBPE2_MASK               4U
#define PTBPE_PTBPE3_MASK               8U
#define PTBPE_PTBPE4_MASK               16U
#define PTBPE_PTBPE5_MASK               32U
#define PTBPE_PTBPE6_MASK               64U
#define PTBPE_PTBPE7_MASK               128U


/*** PTBSE - Port B Slew Rate Enable Register; 0x00001845 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBSE0      :1;                                       /* Output Slew Rate Enable for Port B Bit 0 */
    byte PTBSE1      :1;                                       /* Output Slew Rate Enable for Port B Bit 1 */
    byte PTBSE2      :1;                                       /* Output Slew Rate Enable for Port B Bit 2 */
    byte PTBSE3      :1;                                       /* Output Slew Rate Enable for Port B Bit 3 */
    byte PTBSE4      :1;                                       /* Output Slew Rate Enable for Port B Bit 4 */
    byte PTBSE5      :1;                                       /* Output Slew Rate Enable for Port B Bit 5 */
    byte PTBSE6      :1;                                       /* Output Slew Rate Enable for Port B Bit 6 */
    byte PTBSE7      :1;                                       /* Output Slew Rate Enable for Port B Bit 7 */
  } Bits;
} PTBSESTR;
extern volatile PTBSESTR _PTBSE @0x00001845;
#define PTBSE                           _PTBSE.Byte
#define PTBSE_PTBSE0                    _PTBSE.Bits.PTBSE0
#define PTBSE_PTBSE1                    _PTBSE.Bits.PTBSE1
#define PTBSE_PTBSE2                    _PTBSE.Bits.PTBSE2
#define PTBSE_PTBSE3                    _PTBSE.Bits.PTBSE3
#define PTBSE_PTBSE4                    _PTBSE.Bits.PTBSE4
#define PTBSE_PTBSE5                    _PTBSE.Bits.PTBSE5
#define PTBSE_PTBSE6                    _PTBSE.Bits.PTBSE6
#define PTBSE_PTBSE7                    _PTBSE.Bits.PTBSE7

#define PTBSE_PTBSE0_MASK               1U
#define PTBSE_PTBSE1_MASK               2U
#define PTBSE_PTBSE2_MASK               4U
#define PTBSE_PTBSE3_MASK               8U
#define PTBSE_PTBSE4_MASK               16U
#define PTBSE_PTBSE5_MASK               32U
#define PTBSE_PTBSE6_MASK               64U
#define PTBSE_PTBSE7_MASK               128U


/*** PTBDS - Port B Drive Strength Selection Register; 0x00001846 ***/
typedef union {
  byte Byte;
  struct {
    byte PTBDS0      :1;                                       /* Output Drive Strength Selection for Port B Bit 0 */
    byte PTBDS1      :1;                                       /* Output Drive Strength Selection for Port B Bit 1 */
    byte PTBDS2      :1;                                       /* Output Drive Strength Selection for Port B Bit 2 */
    byte PTBDS3      :1;                                       /* Output Drive Strength Selection for Port B Bit 3 */
    byte PTBDS4      :1;                                       /* Output Drive Strength Selection for Port B Bit 4 */
    byte PTBDS5      :1;                                       /* Output Drive Strength Selection for Port B Bit 5 */
    byte PTBDS6      :1;                                       /* Output Drive Strength Selection for Port B Bit 6 */
    byte PTBDS7      :1;                                       /* Output Drive Strength Selection for Port B Bit 7 */
  } Bits;
} PTBDSSTR;
extern volatile PTBDSSTR _PTBDS @0x00001846;
#define PTBDS                           _PTBDS.Byte
#define PTBDS_PTBDS0                    _PTBDS.Bits.PTBDS0
#define PTBDS_PTBDS1                    _PTBDS.Bits.PTBDS1
#define PTBDS_PTBDS2                    _PTBDS.Bits.PTBDS2
#define PTBDS_PTBDS3                    _PTBDS.Bits.PTBDS3
#define PTBDS_PTBDS4                    _PTBDS.Bits.PTBDS4
#define PTBDS_PTBDS5                    _PTBDS.Bits.PTBDS5
#define PTBDS_PTBDS6                    _PTBDS.Bits.PTBDS6
#define PTBDS_PTBDS7                    _PTBDS.Bits.PTBDS7

#define PTBDS_PTBDS0_MASK               1U
#define PTBDS_PTBDS1_MASK               2U
#define PTBDS_PTBDS2_MASK               4U
#define PTBDS_PTBDS3_MASK               8U
#define PTBDS_PTBDS4_MASK               16U
#define PTBDS_PTBDS5_MASK               32U
#define PTBDS_PTBDS6_MASK               64U
#define PTBDS_PTBDS7_MASK               128U


/*** PTCPE - Port C Pull Enable Register; 0x00001848 ***/
typedef union {
  byte Byte;
  struct {
    byte PTCPE0      :1;                                       /* Internal Pull Enable for Port C Bit 0 */
    byte PTCPE1      :1;                                       /* Internal Pull Enable for Port C Bit 1 */
    byte PTCPE2      :1;                                       /* Internal Pull Enable for Port C Bit 2 */
    byte PTCPE3      :1;                                       /* Internal Pull Enable for Port C Bit 3 */
    byte PTCPE4      :1;                                       /* Internal Pull Enable for Port C Bit 4 */
    byte PTCPE5      :1;                                       /* Internal Pull Enable for Port C Bit 5 */
    byte PTCPE6      :1;                                       /* Internal Pull Enable for Port C Bit 6 */
    byte PTCPE7      :1;                                       /* Internal Pull Enable for Port C Bit 7 */
  } Bits;
} PTCPESTR;
extern volatile PTCPESTR _PTCPE @0x00001848;
#define PTCPE                           _PTCPE.Byte
#define PTCPE_PTCPE0                    _PTCPE.Bits.PTCPE0
#define PTCPE_PTCPE1                    _PTCPE.Bits.PTCPE1
#define PTCPE_PTCPE2                    _PTCPE.Bits.PTCPE2
#define PTCPE_PTCPE3                    _PTCPE.Bits.PTCPE3
#define PTCPE_PTCPE4                    _PTCPE.Bits.PTCPE4
#define PTCPE_PTCPE5                    _PTCPE.Bits.PTCPE5
#define PTCPE_PTCPE6                    _PTCPE.Bits.PTCPE6
#define PTCPE_PTCPE7                    _PTCPE.Bits.PTCPE7

#define PTCPE_PTCPE0_MASK               1U
#define PTCPE_PTCPE1_MASK               2U
#define PTCPE_PTCPE2_MASK               4U
#define PTCPE_PTCPE3_MASK               8U
#define PTCPE_PTCPE4_MASK               16U
#define PTCPE_PTCPE5_MASK               32U
#define PTCPE_PTCPE6_MASK               64U
#define PTCPE_PTCPE7_MASK               128U


/*** PTCSE - Port C Slew Rate Enable Register; 0x00001849 ***/
typedef union {
  byte Byte;
  struct {
    byte PTCSE0      :1;                                       /* Output Slew Rate Enable for Port C Bit 0 */
    byte PTCSE1      :1;                                       /* Output Slew Rate Enable for Port C Bit 1 */
    byte PTCSE2      :1;                                       /* Output Slew Rate Enable for Port C Bit 2 */
    byte PTCSE3      :1;                                       /* Output Slew Rate Enable for Port C Bit 3 */
    byte PTCSE4      :1;                                       /* Output Slew Rate Enable for Port C Bit 4 */
    byte PTCSE5      :1;                                       /* Output Slew Rate Enable for Port C Bit 5 */
    byte PTCSE6      :1;                                       /* Output Slew Rate Enable for Port C Bit 6 */
    byte PTCSE7      :1;                                       /* Output Slew Rate Enable for Port C Bit 7 */
  } Bits;
} PTCSESTR;
extern volatile PTCSESTR _PTCSE @0x00001849;
#define PTCSE                           _PTCSE.Byte
#define PTCSE_PTCSE0                    _PTCSE.Bits.PTCSE0
#define PTCSE_PTCSE1                    _PTCSE.Bits.PTCSE1
#define PTCSE_PTCSE2                    _PTCSE.Bits.PTCSE2
#define PTCSE_PTCSE3                    _PTCSE.Bits.PTCSE3
#define PTCSE_PTCSE4                    _PTCSE.Bits.PTCSE4
#define PTCSE_PTCSE5                    _PTCSE.Bits.PTCSE5
#define PTCSE_PTCSE6                    _PTCSE.Bits.PTCSE6
#define PTCSE_PTCSE7                    _PTCSE.Bits.PTCSE7

#define PTCSE_PTCSE0_MASK               1U
#define PTCSE_PTCSE1_MASK               2U
#define PTCSE_PTCSE2_MASK               4U
#define PTCSE_PTCSE3_MASK               8U
#define PTCSE_PTCSE4_MASK               16U
#define PTCSE_PTCSE5_MASK               32U
#define PTCSE_PTCSE6_MASK               64U
#define PTCSE_PTCSE7_MASK               128U


/*** PTCDS - Port C Drive Strength Selection Register; 0x0000184A ***/
typedef union {
  byte Byte;
  struct {
    byte PTCDS0      :1;                                       /* Output Drive Strength Selection for Port C Bit 0 */
    byte PTCDS1      :1;                                       /* Output Drive Strength Selection for Port C Bit 1 */
    byte PTCDS2      :1;                                       /* Output Drive Strength Selection for Port C Bit 2 */
    byte PTCDS3      :1;                                       /* Output Drive Strength Selection for Port C Bit 3 */
    byte PTCDS4      :1;                                       /* Output Drive Strength Selection for Port C Bit 4 */
    byte PTCDS5      :1;                                       /* Output Drive Strength Selection for Port C Bit 5 */
    byte PTCDS6      :1;                                       /* Output Drive Strength Selection for Port C Bit 6 */
    byte PTCDS7      :1;                                       /* Output Drive Strength Selection for Port C Bit 7 */
  } Bits;
} PTCDSSTR;
extern volatile PTCDSSTR _PTCDS @0x0000184A;
#define PTCDS                           _PTCDS.Byte
#define PTCDS_PTCDS0                    _PTCDS.Bits.PTCDS0
#define PTCDS_PTCDS1                    _PTCDS.Bits.PTCDS1
#define PTCDS_PTCDS2                    _PTCDS.Bits.PTCDS2
#define PTCDS_PTCDS3                    _PTCDS.Bits.PTCDS3
#define PTCDS_PTCDS4                    _PTCDS.Bits.PTCDS4
#define PTCDS_PTCDS5                    _PTCDS.Bits.PTCDS5
#define PTCDS_PTCDS6                    _PTCDS.Bits.PTCDS6
#define PTCDS_PTCDS7                    _PTCDS.Bits.PTCDS7

#define PTCDS_PTCDS0_MASK               1U
#define PTCDS_PTCDS1_MASK               2U
#define PTCDS_PTCDS2_MASK               4U
#define PTCDS_PTCDS3_MASK               8U
#define PTCDS_PTCDS4_MASK               16U
#define PTCDS_PTCDS5_MASK               32U
#define PTCDS_PTCDS6_MASK               64U
#define PTCDS_PTCDS7_MASK               128U


/*** PTDPE - Port D Pull Enable Register; 0x0000184C ***/
typedef union {
  byte Byte;
  struct {
    byte PTDPE0      :1;                                       /* Internal Pull Enable for Port D Bit 0 */
    byte PTDPE1      :1;                                       /* Internal Pull Enable for Port D Bit 1 */
    byte PTDPE2      :1;                                       /* Internal Pull Enable for Port D Bit 2 */
    byte PTDPE3      :1;                                       /* Internal Pull Enable for Port D Bit 3 */
    byte PTDPE4      :1;                                       /* Internal Pull Enable for Port D Bit 4 */
    byte PTDPE5      :1;                                       /* Internal Pull Enable for Port D Bit 5 */
    byte PTDPE6      :1;                                       /* Internal Pull Enable for Port D Bit 6 */
    byte PTDPE7      :1;                                       /* Internal Pull Enable for Port D Bit 7 */
  } Bits;
} PTDPESTR;
extern volatile PTDPESTR _PTDPE @0x0000184C;
#define PTDPE                           _PTDPE.Byte
#define PTDPE_PTDPE0                    _PTDPE.Bits.PTDPE0
#define PTDPE_PTDPE1                    _PTDPE.Bits.PTDPE1
#define PTDPE_PTDPE2                    _PTDPE.Bits.PTDPE2
#define PTDPE_PTDPE3                    _PTDPE.Bits.PTDPE3
#define PTDPE_PTDPE4                    _PTDPE.Bits.PTDPE4
#define PTDPE_PTDPE5                    _PTDPE.Bits.PTDPE5
#define PTDPE_PTDPE6                    _PTDPE.Bits.PTDPE6
#define PTDPE_PTDPE7                    _PTDPE.Bits.PTDPE7

#define PTDPE_PTDPE0_MASK               1U
#define PTDPE_PTDPE1_MASK               2U
#define PTDPE_PTDPE2_MASK               4U
#define PTDPE_PTDPE3_MASK               8U
#define PTDPE_PTDPE4_MASK               16U
#define PTDPE_PTDPE5_MASK               32U
#define PTDPE_PTDPE6_MASK               64U
#define PTDPE_PTDPE7_MASK               128U


/*** PTDSE - Port D Slew Rate Enable Register; 0x0000184D ***/
typedef union {
  byte Byte;
  struct {
    byte PTDSE0      :1;                                       /* Output Slew Rate Enable for Port D Bit 0 */
    byte PTDSE1      :1;                                       /* Output Slew Rate Enable for Port D Bit 1 */
    byte PTDSE2      :1;                                       /* Output Slew Rate Enable for Port D Bit 2 */
    byte PTDSE3      :1;                                       /* Output Slew Rate Enable for Port D Bit 3 */
    byte PTDSE4      :1;                                       /* Output Slew Rate Enable for Port D Bit 4 */
    byte PTDSE5      :1;                                       /* Output Slew Rate Enable for Port D Bit 5 */
    byte PTDSE6      :1;                                       /* Output Slew Rate Enable for Port D Bit 6 */
    byte PTDSE7      :1;                                       /* Output Slew Rate Enable for Port D Bit 7 */
  } Bits;
} PTDSESTR;
extern volatile PTDSESTR _PTDSE @0x0000184D;
#define PTDSE                           _PTDSE.Byte
#define PTDSE_PTDSE0                    _PTDSE.Bits.PTDSE0
#define PTDSE_PTDSE1                    _PTDSE.Bits.PTDSE1
#define PTDSE_PTDSE2                    _PTDSE.Bits.PTDSE2
#define PTDSE_PTDSE3                    _PTDSE.Bits.PTDSE3
#define PTDSE_PTDSE4                    _PTDSE.Bits.PTDSE4
#define PTDSE_PTDSE5                    _PTDSE.Bits.PTDSE5
#define PTDSE_PTDSE6                    _PTDSE.Bits.PTDSE6
#define PTDSE_PTDSE7                    _PTDSE.Bits.PTDSE7

#define PTDSE_PTDSE0_MASK               1U
#define PTDSE_PTDSE1_MASK               2U
#define PTDSE_PTDSE2_MASK               4U
#define PTDSE_PTDSE3_MASK               8U
#define PTDSE_PTDSE4_MASK               16U
#define PTDSE_PTDSE5_MASK               32U
#define PTDSE_PTDSE6_MASK               64U
#define PTDSE_PTDSE7_MASK               128U


/*** PTDDS - Port D Drive Strength Selection Register; 0x0000184E ***/
typedef union {
  byte Byte;
  struct {
    byte PTDDS0      :1;                                       /* Output Drive Strength Selection for Port D Bit 0 */
    byte PTDDS1      :1;                                       /* Output Drive Strength Selection for Port D Bit 1 */
    byte PTDDS2      :1;                                       /* Output Drive Strength Selection for Port D Bit 2 */
    byte PTDDS3      :1;                                       /* Output Drive Strength Selection for Port D Bit 3 */
    byte PTDDS4      :1;                                       /* Output Drive Strength Selection for Port D Bit 4 */
    byte PTDDS5      :1;                                       /* Output Drive Strength Selection for Port D Bit 5 */
    byte PTDDS6      :1;                                       /* Output Drive Strength Selection for Port D Bit 6 */
    byte PTDDS7      :1;                                       /* Output Drive Strength Selection for Port D Bit 7 */
  } Bits;
} PTDDSSTR;
extern volatile PTDDSSTR _PTDDS @0x0000184E;
#define PTDDS                           _PTDDS.Byte
#define PTDDS_PTDDS0                    _PTDDS.Bits.PTDDS0
#define PTDDS_PTDDS1                    _PTDDS.Bits.PTDDS1
#define PTDDS_PTDDS2                    _PTDDS.Bits.PTDDS2
#define PTDDS_PTDDS3                    _PTDDS.Bits.PTDDS3
#define PTDDS_PTDDS4                    _PTDDS.Bits.PTDDS4
#define PTDDS_PTDDS5                    _PTDDS.Bits.PTDDS5
#define PTDDS_PTDDS6                    _PTDDS.Bits.PTDDS6
#define PTDDS_PTDDS7                    _PTDDS.Bits.PTDDS7

#define PTDDS_PTDDS0_MASK               1U
#define PTDDS_PTDDS1_MASK               2U
#define PTDDS_PTDDS2_MASK               4U
#define PTDDS_PTDDS3_MASK               8U
#define PTDDS_PTDDS4_MASK               16U
#define PTDDS_PTDDS5_MASK               32U
#define PTDDS_PTDDS6_MASK               64U
#define PTDDS_PTDDS7_MASK               128U


/*** PTEPE - Port E Pull Enable Register; 0x00001850 ***/
typedef union {
  byte Byte;
  struct {
    byte PTEPE0      :1;                                       /* Internal Pull Enable for Port E Bit 0 */
    byte PTEPE1      :1;                                       /* Internal Pull Enable for Port E Bit 1 */
    byte PTEPE2      :1;                                       /* Internal Pull Enable for Port E Bit 2 */
    byte PTEPE3      :1;                                       /* Internal Pull Enable for Port E Bit 3 */
    byte PTEPE4      :1;                                       /* Internal Pull Enable for Port E Bit 4 */
    byte PTEPE5      :1;                                       /* Internal Pull Enable for Port E Bit 5 */
    byte PTEPE6      :1;                                       /* Internal Pull Enable for Port E Bit 6 */
    byte PTEPE7      :1;                                       /* Internal Pull Enable for Port E Bit 7 */
  } Bits;
} PTEPESTR;
extern volatile PTEPESTR _PTEPE @0x00001850;
#define PTEPE                           _PTEPE.Byte
#define PTEPE_PTEPE0                    _PTEPE.Bits.PTEPE0
#define PTEPE_PTEPE1                    _PTEPE.Bits.PTEPE1
#define PTEPE_PTEPE2                    _PTEPE.Bits.PTEPE2
#define PTEPE_PTEPE3                    _PTEPE.Bits.PTEPE3
#define PTEPE_PTEPE4                    _PTEPE.Bits.PTEPE4
#define PTEPE_PTEPE5                    _PTEPE.Bits.PTEPE5
#define PTEPE_PTEPE6                    _PTEPE.Bits.PTEPE6
#define PTEPE_PTEPE7                    _PTEPE.Bits.PTEPE7

#define PTEPE_PTEPE0_MASK               1U
#define PTEPE_PTEPE1_MASK               2U
#define PTEPE_PTEPE2_MASK               4U
#define PTEPE_PTEPE3_MASK               8U
#define PTEPE_PTEPE4_MASK               16U
#define PTEPE_PTEPE5_MASK               32U
#define PTEPE_PTEPE6_MASK               64U
#define PTEPE_PTEPE7_MASK               128U


/*** PTESE - Port E Slew Rate Enable Register; 0x00001851 ***/
typedef union {
  byte Byte;
  struct {
    byte PTESE0      :1;                                       /* Output Slew Rate Enable for Port E Bit 0 */
    byte PTESE1      :1;                                       /* Output Slew Rate Enable for Port E Bit 1 */
    byte PTESE2      :1;                                       /* Output Slew Rate Enable for Port E Bit 2 */
    byte PTESE3      :1;                                       /* Output Slew Rate Enable for Port E Bit 3 */
    byte PTESE4      :1;                                       /* Output Slew Rate Enable for Port E Bit 4 */
    byte PTESE5      :1;                                       /* Output Slew Rate Enable for Port E Bit 5 */
    byte PTESE6      :1;                                       /* Output Slew Rate Enable for Port E Bit 6 */
    byte PTESE7      :1;                                       /* Output Slew Rate Enable for Port E Bit 7 */
  } Bits;
} PTESESTR;
extern volatile PTESESTR _PTESE @0x00001851;
#define PTESE                           _PTESE.Byte
#define PTESE_PTESE0                    _PTESE.Bits.PTESE0
#define PTESE_PTESE1                    _PTESE.Bits.PTESE1
#define PTESE_PTESE2                    _PTESE.Bits.PTESE2
#define PTESE_PTESE3                    _PTESE.Bits.PTESE3
#define PTESE_PTESE4                    _PTESE.Bits.PTESE4
#define PTESE_PTESE5                    _PTESE.Bits.PTESE5
#define PTESE_PTESE6                    _PTESE.Bits.PTESE6
#define PTESE_PTESE7                    _PTESE.Bits.PTESE7

#define PTESE_PTESE0_MASK               1U
#define PTESE_PTESE1_MASK               2U
#define PTESE_PTESE2_MASK               4U
#define PTESE_PTESE3_MASK               8U
#define PTESE_PTESE4_MASK               16U
#define PTESE_PTESE5_MASK               32U
#define PTESE_PTESE6_MASK               64U
#define PTESE_PTESE7_MASK               128U


/*** PTEDS - Port E Drive Strength Selection Register; 0x00001852 ***/
typedef union {
  byte Byte;
  struct {
    byte PTEDS0      :1;                                       /* Output Drive Strength Selection for Port E Bit 0 */
    byte PTEDS1      :1;                                       /* Output Drive Strength Selection for Port E Bit 1 */
    byte PTEDS2      :1;                                       /* Output Drive Strength Selection for Port E Bit 2 */
    byte PTEDS3      :1;                                       /* Output Drive Strength Selection for Port E Bit 3 */
    byte PTEDS4      :1;                                       /* Output Drive Strength Selection for Port E Bit 4 */
    byte PTEDS5      :1;                                       /* Output Drive Strength Selection for Port E Bit 5 */
    byte PTEDS6      :1;                                       /* Output Drive Strength Selection for Port E Bit 6 */
    byte PTEDS7      :1;                                       /* Output Drive Strength Selection for Port E Bit 7 */
  } Bits;
} PTEDSSTR;
extern volatile PTEDSSTR _PTEDS @0x00001852;
#define PTEDS                           _PTEDS.Byte
#define PTEDS_PTEDS0                    _PTEDS.Bits.PTEDS0
#define PTEDS_PTEDS1                    _PTEDS.Bits.PTEDS1
#define PTEDS_PTEDS2                    _PTEDS.Bits.PTEDS2
#define PTEDS_PTEDS3                    _PTEDS.Bits.PTEDS3
#define PTEDS_PTEDS4                    _PTEDS.Bits.PTEDS4
#define PTEDS_PTEDS5                    _PTEDS.Bits.PTEDS5
#define PTEDS_PTEDS6                    _PTEDS.Bits.PTEDS6
#define PTEDS_PTEDS7                    _PTEDS.Bits.PTEDS7

#define PTEDS_PTEDS0_MASK               1U
#define PTEDS_PTEDS1_MASK               2U
#define PTEDS_PTEDS2_MASK               4U
#define PTEDS_PTEDS3_MASK               8U
#define PTEDS_PTEDS4_MASK               16U
#define PTEDS_PTEDS5_MASK               32U
#define PTEDS_PTEDS6_MASK               64U
#define PTEDS_PTEDS7_MASK               128U


/*** PTFPE - Port F Pull Enable Register; 0x00001854 ***/
typedef union {
  byte Byte;
  struct {
    byte PTFPE0      :1;                                       /* Internal Pull Enable for Port F Bit 0 */
    byte PTFPE1      :1;                                       /* Internal Pull Enable for Port F Bit 1 */
    byte PTFPE2      :1;                                       /* Internal Pull Enable for Port F Bit 2 */
    byte PTFPE3      :1;                                       /* Internal Pull Enable for Port F Bit 3 */
    byte PTFPE4      :1;                                       /* Internal Pull Enable for Port F Bit 4 */
    byte PTFPE5      :1;                                       /* Internal Pull Enable for Port F Bit 5 */
    byte PTFPE6      :1;                                       /* Internal Pull Enable for Port F Bit 6 */
    byte PTFPE7      :1;                                       /* Internal Pull Enable for Port F Bit 7 */
  } Bits;
} PTFPESTR;
extern volatile PTFPESTR _PTFPE @0x00001854;
#define PTFPE                           _PTFPE.Byte
#define PTFPE_PTFPE0                    _PTFPE.Bits.PTFPE0
#define PTFPE_PTFPE1                    _PTFPE.Bits.PTFPE1
#define PTFPE_PTFPE2                    _PTFPE.Bits.PTFPE2
#define PTFPE_PTFPE3                    _PTFPE.Bits.PTFPE3
#define PTFPE_PTFPE4                    _PTFPE.Bits.PTFPE4
#define PTFPE_PTFPE5                    _PTFPE.Bits.PTFPE5
#define PTFPE_PTFPE6                    _PTFPE.Bits.PTFPE6
#define PTFPE_PTFPE7                    _PTFPE.Bits.PTFPE7

#define PTFPE_PTFPE0_MASK               1U
#define PTFPE_PTFPE1_MASK               2U
#define PTFPE_PTFPE2_MASK               4U
#define PTFPE_PTFPE3_MASK               8U
#define PTFPE_PTFPE4_MASK               16U
#define PTFPE_PTFPE5_MASK               32U
#define PTFPE_PTFPE6_MASK               64U
#define PTFPE_PTFPE7_MASK               128U


/*** PTFSE - Port F Slew Rate Enable Register; 0x00001855 ***/
typedef union {
  byte Byte;
  struct {
    byte PTFSE0      :1;                                       /* Output Slew Rate Enable for Port F Bit 0 */
    byte PTFSE1      :1;                                       /* Output Slew Rate Enable for Port F Bit 1 */
    byte PTFSE2      :1;                                       /* Output Slew Rate Enable for Port F Bit 2 */
    byte PTFSE3      :1;                                       /* Output Slew Rate Enable for Port F Bit 3 */
    byte PTFSE4      :1;                                       /* Output Slew Rate Enable for Port F Bit 4 */
    byte PTFSE5      :1;                                       /* Output Slew Rate Enable for Port F Bit 5 */
    byte PTFSE6      :1;                                       /* Output Slew Rate Enable for Port F Bit 6 */
    byte PTFSE7      :1;                                       /* Output Slew Rate Enable for Port F Bit 7 */
  } Bits;
} PTFSESTR;
extern volatile PTFSESTR _PTFSE @0x00001855;
#define PTFSE                           _PTFSE.Byte
#define PTFSE_PTFSE0                    _PTFSE.Bits.PTFSE0
#define PTFSE_PTFSE1                    _PTFSE.Bits.PTFSE1
#define PTFSE_PTFSE2                    _PTFSE.Bits.PTFSE2
#define PTFSE_PTFSE3                    _PTFSE.Bits.PTFSE3
#define PTFSE_PTFSE4                    _PTFSE.Bits.PTFSE4
#define PTFSE_PTFSE5                    _PTFSE.Bits.PTFSE5
#define PTFSE_PTFSE6                    _PTFSE.Bits.PTFSE6
#define PTFSE_PTFSE7                    _PTFSE.Bits.PTFSE7

#define PTFSE_PTFSE0_MASK               1U
#define PTFSE_PTFSE1_MASK               2U
#define PTFSE_PTFSE2_MASK               4U
#define PTFSE_PTFSE3_MASK               8U
#define PTFSE_PTFSE4_MASK               16U
#define PTFSE_PTFSE5_MASK               32U
#define PTFSE_PTFSE6_MASK               64U
#define PTFSE_PTFSE7_MASK               128U


/*** PTFDS - Port F Drive Strength Selection Register; 0x00001856 ***/
typedef union {
  byte Byte;
  struct {
    byte PTFDS0      :1;                                       /* Output Drive Strength Selection for Port F Bit 0 */
    byte PTFDS1      :1;                                       /* Output Drive Strength Selection for Port F Bit 1 */
    byte PTFDS2      :1;                                       /* Output Drive Strength Selection for Port F Bit 2 */
    byte PTFDS3      :1;                                       /* Output Drive Strength Selection for Port F Bit 3 */
    byte PTFDS4      :1;                                       /* Output Drive Strength Selection for Port F Bit 4 */
    byte PTFDS5      :1;                                       /* Output Drive Strength Selection for Port F Bit 5 */
    byte PTFDS6      :1;                                       /* Output Drive Strength Selection for Port F Bit 6 */
    byte PTFDS7      :1;                                       /* Output Drive Strength Selection for Port F Bit 7 */
  } Bits;
} PTFDSSTR;
extern volatile PTFDSSTR _PTFDS @0x00001856;
#define PTFDS                           _PTFDS.Byte
#define PTFDS_PTFDS0                    _PTFDS.Bits.PTFDS0
#define PTFDS_PTFDS1                    _PTFDS.Bits.PTFDS1
#define PTFDS_PTFDS2                    _PTFDS.Bits.PTFDS2
#define PTFDS_PTFDS3                    _PTFDS.Bits.PTFDS3
#define PTFDS_PTFDS4                    _PTFDS.Bits.PTFDS4
#define PTFDS_PTFDS5                    _PTFDS.Bits.PTFDS5
#define PTFDS_PTFDS6                    _PTFDS.Bits.PTFDS6
#define PTFDS_PTFDS7                    _PTFDS.Bits.PTFDS7

#define PTFDS_PTFDS0_MASK               1U
#define PTFDS_PTFDS1_MASK               2U
#define PTFDS_PTFDS2_MASK               4U
#define PTFDS_PTFDS3_MASK               8U
#define PTFDS_PTFDS4_MASK               16U
#define PTFDS_PTFDS5_MASK               32U
#define PTFDS_PTFDS6_MASK               64U
#define PTFDS_PTFDS7_MASK               128U


/*** PTGPE - Port G Pull Enable Register; 0x00001858 ***/
typedef union {
  byte Byte;
  struct {
    byte PTGPE0      :1;                                       /* Internal Pull Enable for Port G Bit 0 */
    byte PTGPE1      :1;                                       /* Internal Pull Enable for Port G Bit 1 */
    byte PTGPE2      :1;                                       /* Internal Pull Enable for Port G Bit 2 */
    byte PTGPE3      :1;                                       /* Internal Pull Enable for Port G Bit 3 */
    byte PTGPE4      :1;                                       /* Internal Pull Enable for Port G Bit 4 */
    byte PTGPE5      :1;                                       /* Internal Pull Enable for Port G Bit 5 */
    byte PTGPE6      :1;                                       /* Internal Pull Enable for Port G Bit 6 */
    byte PTGPE7      :1;                                       /* Internal Pull Enable for Port G Bit 7 */
  } Bits;
} PTGPESTR;
extern volatile PTGPESTR _PTGPE @0x00001858;
#define PTGPE                           _PTGPE.Byte
#define PTGPE_PTGPE0                    _PTGPE.Bits.PTGPE0
#define PTGPE_PTGPE1                    _PTGPE.Bits.PTGPE1
#define PTGPE_PTGPE2                    _PTGPE.Bits.PTGPE2
#define PTGPE_PTGPE3                    _PTGPE.Bits.PTGPE3
#define PTGPE_PTGPE4                    _PTGPE.Bits.PTGPE4
#define PTGPE_PTGPE5                    _PTGPE.Bits.PTGPE5
#define PTGPE_PTGPE6                    _PTGPE.Bits.PTGPE6
#define PTGPE_PTGPE7                    _PTGPE.Bits.PTGPE7

#define PTGPE_PTGPE0_MASK               1U
#define PTGPE_PTGPE1_MASK               2U
#define PTGPE_PTGPE2_MASK               4U
#define PTGPE_PTGPE3_MASK               8U
#define PTGPE_PTGPE4_MASK               16U
#define PTGPE_PTGPE5_MASK               32U
#define PTGPE_PTGPE6_MASK               64U
#define PTGPE_PTGPE7_MASK               128U


/*** PTGSE - Port G Slew Rate Enable Register; 0x00001859 ***/
typedef union {
  byte Byte;
  struct {
    byte PTGSE0      :1;                                       /* Output Slew Rate Enable for Port G Bit 0 */
    byte PTGSE1      :1;                                       /* Output Slew Rate Enable for Port G Bit 1 */
    byte PTGSE2      :1;                                       /* Output Slew Rate Enable for Port G Bit 2 */
    byte PTGSE3      :1;                                       /* Output Slew Rate Enable for Port G Bit 3 */
    byte PTGSE4      :1;                                       /* Output Slew Rate Enable for Port G Bit 4 */
    byte PTGSE5      :1;                                       /* Output Slew Rate Enable for Port G Bit 5 */
    byte PTGSE6      :1;                                       /* Output Slew Rate Enable for Port G Bit 6 */
    byte PTGSE7      :1;                                       /* Output Slew Rate Enable for Port G Bit 7 */
  } Bits;
} PTGSESTR;
extern volatile PTGSESTR _PTGSE @0x00001859;
#define PTGSE                           _PTGSE.Byte
#define PTGSE_PTGSE0                    _PTGSE.Bits.PTGSE0
#define PTGSE_PTGSE1                    _PTGSE.Bits.PTGSE1
#define PTGSE_PTGSE2                    _PTGSE.Bits.PTGSE2
#define PTGSE_PTGSE3                    _PTGSE.Bits.PTGSE3
#define PTGSE_PTGSE4                    _PTGSE.Bits.PTGSE4
#define PTGSE_PTGSE5                    _PTGSE.Bits.PTGSE5
#define PTGSE_PTGSE6                    _PTGSE.Bits.PTGSE6
#define PTGSE_PTGSE7                    _PTGSE.Bits.PTGSE7

#define PTGSE_PTGSE0_MASK               1U
#define PTGSE_PTGSE1_MASK               2U
#define PTGSE_PTGSE2_MASK               4U
#define PTGSE_PTGSE3_MASK               8U
#define PTGSE_PTGSE4_MASK               16U
#define PTGSE_PTGSE5_MASK               32U
#define PTGSE_PTGSE6_MASK               64U
#define PTGSE_PTGSE7_MASK               128U


/*** PTGDS - Port G Drive Strength Selection Register; 0x0000185A ***/
typedef union {
  byte Byte;
  struct {
    byte PTGDS0      :1;                                       /* Output Drive Strength Selection for Port G Bit 0 */
    byte PTGDS1      :1;                                       /* Output Drive Strength Selection for Port G Bit 1 */
    byte PTGDS2      :1;                                       /* Output Drive Strength Selection for Port G Bit 2 */
    byte PTGDS3      :1;                                       /* Output Drive Strength Selection for Port G Bit 3 */
    byte PTGDS4      :1;                                       /* Output Drive Strength Selection for Port G Bit 4 */
    byte PTGDS5      :1;                                       /* Output Drive Strength Selection for Port G Bit 5 */
    byte PTGDS6      :1;                                       /* Output Drive Strength Selection for Port G Bit 6 */
    byte PTGDS7      :1;                                       /* Output Drive Strength Selection for Port G Bit 7 */
  } Bits;
} PTGDSSTR;
extern volatile PTGDSSTR _PTGDS @0x0000185A;
#define PTGDS                           _PTGDS.Byte
#define PTGDS_PTGDS0                    _PTGDS.Bits.PTGDS0
#define PTGDS_PTGDS1                    _PTGDS.Bits.PTGDS1
#define PTGDS_PTGDS2                    _PTGDS.Bits.PTGDS2
#define PTGDS_PTGDS3                    _PTGDS.Bits.PTGDS3
#define PTGDS_PTGDS4                    _PTGDS.Bits.PTGDS4
#define PTGDS_PTGDS5                    _PTGDS.Bits.PTGDS5
#define PTGDS_PTGDS6                    _PTGDS.Bits.PTGDS6
#define PTGDS_PTGDS7                    _PTGDS.Bits.PTGDS7

#define PTGDS_PTGDS0_MASK               1U
#define PTGDS_PTGDS1_MASK               2U
#define PTGDS_PTGDS2_MASK               4U
#define PTGDS_PTGDS3_MASK               8U
#define PTGDS_PTGDS4_MASK               16U
#define PTGDS_PTGDS5_MASK               32U
#define PTGDS_PTGDS6_MASK               64U
#define PTGDS_PTGDS7_MASK               128U


/*** PTHPE - Port H Pull Enable Register; 0x0000185C ***/
typedef union {
  byte Byte;
  struct {
    byte PTHPE0      :1;                                       /* Internal Pull Enable for Port H Bit 0 */
    byte PTHPE1      :1;                                       /* Internal Pull Enable for Port H Bit 1 */
    byte PTHPE2      :1;                                       /* Internal Pull Enable for Port H Bit 2 */
    byte PTHPE3      :1;                                       /* Internal Pull Enable for Port H Bit 3 */
    byte PTHPE4      :1;                                       /* Internal Pull Enable for Port H Bit 4 */
    byte PTHPE5      :1;                                       /* Internal Pull Enable for Port H Bit 5 */
    byte PTHPE6      :1;                                       /* Internal Pull Enable for Port H Bit 6 */
    byte PTHPE7      :1;                                       /* Internal Pull Enable for Port H Bit 7 */
  } Bits;
} PTHPESTR;
extern volatile PTHPESTR _PTHPE @0x0000185C;
#define PTHPE                           _PTHPE.Byte
#define PTHPE_PTHPE0                    _PTHPE.Bits.PTHPE0
#define PTHPE_PTHPE1                    _PTHPE.Bits.PTHPE1
#define PTHPE_PTHPE2                    _PTHPE.Bits.PTHPE2
#define PTHPE_PTHPE3                    _PTHPE.Bits.PTHPE3
#define PTHPE_PTHPE4                    _PTHPE.Bits.PTHPE4
#define PTHPE_PTHPE5                    _PTHPE.Bits.PTHPE5
#define PTHPE_PTHPE6                    _PTHPE.Bits.PTHPE6
#define PTHPE_PTHPE7                    _PTHPE.Bits.PTHPE7

#define PTHPE_PTHPE0_MASK               1U
#define PTHPE_PTHPE1_MASK               2U
#define PTHPE_PTHPE2_MASK               4U
#define PTHPE_PTHPE3_MASK               8U
#define PTHPE_PTHPE4_MASK               16U
#define PTHPE_PTHPE5_MASK               32U
#define PTHPE_PTHPE6_MASK               64U
#define PTHPE_PTHPE7_MASK               128U


/*** PTHSE - Port H Slew Rate Enable Register; 0x0000185D ***/
typedef union {
  byte Byte;
  struct {
    byte PTHSE0      :1;                                       /* Output Slew Rate Enable for Port H Bit 0 */
    byte PTHSE1      :1;                                       /* Output Slew Rate Enable for Port H Bit 1 */
    byte PTHSE2      :1;                                       /* Output Slew Rate Enable for Port H Bit 2 */
    byte PTHSE3      :1;                                       /* Output Slew Rate Enable for Port H Bit 3 */
    byte PTHSE4      :1;                                       /* Output Slew Rate Enable for Port H Bit 4 */
    byte PTHSE5      :1;                                       /* Output Slew Rate Enable for Port H Bit 5 */
    byte PTHSE6      :1;                                       /* Output Slew Rate Enable for Port H Bit 6 */
    byte PTHSE7      :1;                                       /* Output Slew Rate Enable for Port H Bit 7 */
  } Bits;
} PTHSESTR;
extern volatile PTHSESTR _PTHSE @0x0000185D;
#define PTHSE                           _PTHSE.Byte
#define PTHSE_PTHSE0                    _PTHSE.Bits.PTHSE0
#define PTHSE_PTHSE1                    _PTHSE.Bits.PTHSE1
#define PTHSE_PTHSE2                    _PTHSE.Bits.PTHSE2
#define PTHSE_PTHSE3                    _PTHSE.Bits.PTHSE3
#define PTHSE_PTHSE4                    _PTHSE.Bits.PTHSE4
#define PTHSE_PTHSE5                    _PTHSE.Bits.PTHSE5
#define PTHSE_PTHSE6                    _PTHSE.Bits.PTHSE6
#define PTHSE_PTHSE7                    _PTHSE.Bits.PTHSE7

#define PTHSE_PTHSE0_MASK               1U
#define PTHSE_PTHSE1_MASK               2U
#define PTHSE_PTHSE2_MASK               4U
#define PTHSE_PTHSE3_MASK               8U
#define PTHSE_PTHSE4_MASK               16U
#define PTHSE_PTHSE5_MASK               32U
#define PTHSE_PTHSE6_MASK               64U
#define PTHSE_PTHSE7_MASK               128U


/*** PTHDS - Port H Drive Strength Selection Register; 0x0000185E ***/
typedef union {
  byte Byte;
  struct {
    byte PTHDS0      :1;                                       /* Output Drive Strength Selection for Port H Bit 0 */
    byte PTHDS1      :1;                                       /* Output Drive Strength Selection for Port H Bit 1 */
    byte PTHDS2      :1;                                       /* Output Drive Strength Selection for Port H Bit 2 */
    byte PTHDS3      :1;                                       /* Output Drive Strength Selection for Port H Bit 3 */
    byte PTHDS4      :1;                                       /* Output Drive Strength Selection for Port H Bit 4 */
    byte PTHDS5      :1;                                       /* Output Drive Strength Selection for Port H Bit 5 */
    byte PTHDS6      :1;                                       /* Output Drive Strength Selection for Port H Bit 6 */
    byte PTHDS7      :1;                                       /* Output Drive Strength Selection for Port H Bit 7 */
  } Bits;
} PTHDSSTR;
extern volatile PTHDSSTR _PTHDS @0x0000185E;
#define PTHDS                           _PTHDS.Byte
#define PTHDS_PTHDS0                    _PTHDS.Bits.PTHDS0
#define PTHDS_PTHDS1                    _PTHDS.Bits.PTHDS1
#define PTHDS_PTHDS2                    _PTHDS.Bits.PTHDS2
#define PTHDS_PTHDS3                    _PTHDS.Bits.PTHDS3
#define PTHDS_PTHDS4                    _PTHDS.Bits.PTHDS4
#define PTHDS_PTHDS5                    _PTHDS.Bits.PTHDS5
#define PTHDS_PTHDS6                    _PTHDS.Bits.PTHDS6
#define PTHDS_PTHDS7                    _PTHDS.Bits.PTHDS7

#define PTHDS_PTHDS0_MASK               1U
#define PTHDS_PTHDS1_MASK               2U
#define PTHDS_PTHDS2_MASK               4U
#define PTHDS_PTHDS3_MASK               8U
#define PTHDS_PTHDS4_MASK               16U
#define PTHDS_PTHDS5_MASK               32U
#define PTHDS_PTHDS6_MASK               64U
#define PTHDS_PTHDS7_MASK               128U


/*** PTJPE - Port J Pull Enable Register; 0x00001860 ***/
typedef union {
  byte Byte;
  struct {
    byte PTJPE0      :1;                                       /* Internal Pull Enable for Port J Bit 0 */
    byte PTJPE1      :1;                                       /* Internal Pull Enable for Port J Bit 1 */
    byte PTJPE2      :1;                                       /* Internal Pull Enable for Port J Bit 2 */
    byte PTJPE3      :1;                                       /* Internal Pull Enable for Port J Bit 3 */
    byte PTJPE4      :1;                                       /* Internal Pull Enable for Port J Bit 4 */
    byte PTJPE5      :1;                                       /* Internal Pull Enable for Port J Bit 5 */
    byte PTJPE6      :1;                                       /* Internal Pull Enable for Port J Bit 6 */
    byte PTJPE7      :1;                                       /* Internal Pull Enable for Port J Bit 7 */
  } Bits;
} PTJPESTR;
extern volatile PTJPESTR _PTJPE @0x00001860;
#define PTJPE                           _PTJPE.Byte
#define PTJPE_PTJPE0                    _PTJPE.Bits.PTJPE0
#define PTJPE_PTJPE1                    _PTJPE.Bits.PTJPE1
#define PTJPE_PTJPE2                    _PTJPE.Bits.PTJPE2
#define PTJPE_PTJPE3                    _PTJPE.Bits.PTJPE3
#define PTJPE_PTJPE4                    _PTJPE.Bits.PTJPE4
#define PTJPE_PTJPE5                    _PTJPE.Bits.PTJPE5
#define PTJPE_PTJPE6                    _PTJPE.Bits.PTJPE6
#define PTJPE_PTJPE7                    _PTJPE.Bits.PTJPE7

#define PTJPE_PTJPE0_MASK               1U
#define PTJPE_PTJPE1_MASK               2U
#define PTJPE_PTJPE2_MASK               4U
#define PTJPE_PTJPE3_MASK               8U
#define PTJPE_PTJPE4_MASK               16U
#define PTJPE_PTJPE5_MASK               32U
#define PTJPE_PTJPE6_MASK               64U
#define PTJPE_PTJPE7_MASK               128U


/*** PTJSE - Port J Slew Rate Enable Register; 0x00001861 ***/
typedef union {
  byte Byte;
  struct {
    byte PTJSE0      :1;                                       /* Output Slew Rate Enable for Port J Bit 0 */
    byte PTJSE1      :1;                                       /* Output Slew Rate Enable for Port J Bit 1 */
    byte PTJSE2      :1;                                       /* Output Slew Rate Enable for Port J Bit 2 */
    byte PTJSE3      :1;                                       /* Output Slew Rate Enable for Port J Bit 3 */
    byte PTJSE4      :1;                                       /* Output Slew Rate Enable for Port J Bit 4 */
    byte PTJSE5      :1;                                       /* Output Slew Rate Enable for Port J Bit 5 */
    byte PTJSE6      :1;                                       /* Output Slew Rate Enable for Port J Bit 6 */
    byte PTJSE7      :1;                                       /* Output Slew Rate Enable for Port J Bit 7 */
  } Bits;
} PTJSESTR;
extern volatile PTJSESTR _PTJSE @0x00001861;
#define PTJSE                           _PTJSE.Byte
#define PTJSE_PTJSE0                    _PTJSE.Bits.PTJSE0
#define PTJSE_PTJSE1                    _PTJSE.Bits.PTJSE1
#define PTJSE_PTJSE2                    _PTJSE.Bits.PTJSE2
#define PTJSE_PTJSE3                    _PTJSE.Bits.PTJSE3
#define PTJSE_PTJSE4                    _PTJSE.Bits.PTJSE4
#define PTJSE_PTJSE5                    _PTJSE.Bits.PTJSE5
#define PTJSE_PTJSE6                    _PTJSE.Bits.PTJSE6
#define PTJSE_PTJSE7                    _PTJSE.Bits.PTJSE7

#define PTJSE_PTJSE0_MASK               1U
#define PTJSE_PTJSE1_MASK               2U
#define PTJSE_PTJSE2_MASK               4U
#define PTJSE_PTJSE3_MASK               8U
#define PTJSE_PTJSE4_MASK               16U
#define PTJSE_PTJSE5_MASK               32U
#define PTJSE_PTJSE6_MASK               64U
#define PTJSE_PTJSE7_MASK               128U


/*** PTJDS - Port J Drive Strength Selection Register; 0x00001862 ***/
typedef union {
  byte Byte;
  struct {
    byte PTJDS0      :1;                                       /* Output Drive Strength Selection for Port J Bit 0 */
    byte PTJDS1      :1;                                       /* Output Drive Strength Selection for Port J Bit 1 */
    byte PTJDS2      :1;                                       /* Output Drive Strength Selection for Port J Bit 2 */
    byte PTJDS3      :1;                                       /* Output Drive Strength Selection for Port J Bit 3 */
    byte PTJDS4      :1;                                       /* Output Drive Strength Selection for Port J Bit 4 */
    byte PTJDS5      :1;                                       /* Output Drive Strength Selection for Port J Bit 5 */
    byte PTJDS6      :1;                                       /* Output Drive Strength Selection for Port J Bit 6 */
    byte PTJDS7      :1;                                       /* Output Drive Strength Selection for Port J Bit 7 */
  } Bits;
} PTJDSSTR;
extern volatile PTJDSSTR _PTJDS @0x00001862;
#define PTJDS                           _PTJDS.Byte
#define PTJDS_PTJDS0                    _PTJDS.Bits.PTJDS0
#define PTJDS_PTJDS1                    _PTJDS.Bits.PTJDS1
#define PTJDS_PTJDS2                    _PTJDS.Bits.PTJDS2
#define PTJDS_PTJDS3                    _PTJDS.Bits.PTJDS3
#define PTJDS_PTJDS4                    _PTJDS.Bits.PTJDS4
#define PTJDS_PTJDS5                    _PTJDS.Bits.PTJDS5
#define PTJDS_PTJDS6                    _PTJDS.Bits.PTJDS6
#define PTJDS_PTJDS7                    _PTJDS.Bits.PTJDS7

#define PTJDS_PTJDS0_MASK               1U
#define PTJDS_PTJDS1_MASK               2U
#define PTJDS_PTJDS2_MASK               4U
#define PTJDS_PTJDS3_MASK               8U
#define PTJDS_PTJDS4_MASK               16U
#define PTJDS_PTJDS5_MASK               32U
#define PTJDS_PTJDS6_MASK               64U
#define PTJDS_PTJDS7_MASK               128U


/*** IIC2A - IIC Address Register; 0x00001868 ***/
typedef union {
  byte Byte;
  struct {
    byte             :1; 
    byte AD1         :1;                                       /* Slave Address Bit 1 */
    byte AD2         :1;                                       /* Slave Address Bit 2 */
    byte AD3         :1;                                       /* Slave Address Bit 3 */
    byte AD4         :1;                                       /* Slave Address Bit 4 */
    byte AD5         :1;                                       /* Slave Address Bit 5 */
    byte AD6         :1;                                       /* Slave Address Bit 6 */
    byte AD7         :1;                                       /* Slave Address Bit 7 */
  } Bits;
  struct {
    byte         :1;
    byte grpAD_1 :7;
  } MergedBits;
} IIC2ASTR;
extern volatile IIC2ASTR _IIC2A @0x00001868;
#define IIC2A                           _IIC2A.Byte
#define IIC2A_AD1                       _IIC2A.Bits.AD1
#define IIC2A_AD2                       _IIC2A.Bits.AD2
#define IIC2A_AD3                       _IIC2A.Bits.AD3
#define IIC2A_AD4                       _IIC2A.Bits.AD4
#define IIC2A_AD5                       _IIC2A.Bits.AD5
#define IIC2A_AD6                       _IIC2A.Bits.AD6
#define IIC2A_AD7                       _IIC2A.Bits.AD7
#define IIC2A_AD_1                      _IIC2A.MergedBits.grpAD_1
#define IIC2A_AD                        IIC2A_AD_1

#define IIC2A_AD1_MASK                  2U
#define IIC2A_AD2_MASK                  4U
#define IIC2A_AD3_MASK                  8U
#define IIC2A_AD4_MASK                  16U
#define IIC2A_AD5_MASK                  32U
#define IIC2A_AD6_MASK                  64U
#define IIC2A_AD7_MASK                  128U
#define IIC2A_AD_1_MASK                 254U
#define IIC2A_AD_1_BITNUM               1U


/*** IIC2F - IIC Frequency Divider Register; 0x00001869 ***/
typedef union {
  byte Byte;
  struct {
    byte ICR0        :1;                                       /* IIC Clock Rate Bit 0 */
    byte ICR1        :1;                                       /* IIC Clock Rate Bit 1 */
    byte ICR2        :1;                                       /* IIC Clock Rate Bit 2 */
    byte ICR3        :1;                                       /* IIC Clock Rate Bit 3 */
    byte ICR4        :1;                                       /* IIC Clock Rate Bit 4 */
    byte ICR5        :1;                                       /* IIC Clock Rate Bit 5 */
    byte MULT0       :1;                                       /* Multiplier Factor Bit 0 */
    byte MULT1       :1;                                       /* Multiplier Factor Bit 1 */
  } Bits;
  struct {
    byte grpICR  :6;
    byte grpMULT :2;
  } MergedBits;
} IIC2FSTR;
extern volatile IIC2FSTR _IIC2F @0x00001869;
#define IIC2F                           _IIC2F.Byte
#define IIC2F_ICR0                      _IIC2F.Bits.ICR0
#define IIC2F_ICR1                      _IIC2F.Bits.ICR1
#define IIC2F_ICR2                      _IIC2F.Bits.ICR2
#define IIC2F_ICR3                      _IIC2F.Bits.ICR3
#define IIC2F_ICR4                      _IIC2F.Bits.ICR4
#define IIC2F_ICR5                      _IIC2F.Bits.ICR5
#define IIC2F_MULT0                     _IIC2F.Bits.MULT0
#define IIC2F_MULT1                     _IIC2F.Bits.MULT1
#define IIC2F_ICR                       _IIC2F.MergedBits.grpICR
#define IIC2F_MULT                      _IIC2F.MergedBits.grpMULT

#define IIC2F_ICR0_MASK                 1U
#define IIC2F_ICR1_MASK                 2U
#define IIC2F_ICR2_MASK                 4U
#define IIC2F_ICR3_MASK                 8U
#define IIC2F_ICR4_MASK                 16U
#define IIC2F_ICR5_MASK                 32U
#define IIC2F_MULT0_MASK                64U
#define IIC2F_MULT1_MASK                128U
#define IIC2F_ICR_MASK                  63U
#define IIC2F_ICR_BITNUM                0U
#define IIC2F_MULT_MASK                 192U
#define IIC2F_MULT_BITNUM               6U


/*** IIC2C1 - IIC Control Register 1; 0x0000186A ***/
typedef union {
  byte Byte;
  union { /* Several registers at the same address */
    /*** IIC2C1 - IIC Control Register 1; Several registers at the same address ***/
    union {
      struct {
        byte             :1; 
        byte             :1; 
        byte RSTA        :1;                                       /* Repeat START */
        byte TXAK        :1;                                       /* Transmit Acknowledge Enable */
        byte TX          :1;                                       /* Transmit Mode Select */
        byte MST         :1;                                       /* Master Mode Select */
        byte IICIE       :1;                                       /* IIC Interrupt Enable */
        byte IICEN       :1;                                       /* IIC Enable */
      } Bits;
    } IIC2C1STR;
    #define IIC2C1                      _IIC2C1.Byte
    #define IIC2C1_RSTA                 _IIC2C1.SameAddr_STR.IIC2C1STR.Bits.RSTA
    #define IIC2C1_TXAK                 _IIC2C1.SameAddr_STR.IIC2C1STR.Bits.TXAK
    #define IIC2C1_TX                   _IIC2C1.SameAddr_STR.IIC2C1STR.Bits.TX
    #define IIC2C1_MST                  _IIC2C1.SameAddr_STR.IIC2C1STR.Bits.MST
    #define IIC2C1_IICIE                _IIC2C1.SameAddr_STR.IIC2C1STR.Bits.IICIE
    #define IIC2C1_IICEN                _IIC2C1.SameAddr_STR.IIC2C1STR.Bits.IICEN
    
    #define IIC2C1_RSTA_MASK            4U
    #define IIC2C1_TXAK_MASK            8U
    #define IIC2C1_TX_MASK              16U
    #define IIC2C1_MST_MASK             32U
    #define IIC2C1_IICIE_MASK           64U
    #define IIC2C1_IICEN_MASK           128U
    
    /*** IIC2C - IIC Control Register; Several registers at the same address ***/
    union {
      struct {
        byte             :1; 
        byte             :1; 
        byte RSTA        :1;                                       /* Repeat START */
        byte TXAK        :1;                                       /* Transmit Acknowledge Enable */
        byte TX          :1;                                       /* Transmit Mode Select */
        byte MST         :1;                                       /* Master Mode Select */
        byte IICIE       :1;                                       /* IIC Interrupt Enable */
        byte IICEN       :1;                                       /* IIC Enable */
      } Bits;
    } IIC2CSTR;
    #define IIC2C                       _IIC2C1.Byte
    #define IIC2C_RSTA                  _IIC2C1.SameAddr_STR.IIC2CSTR.Bits.RSTA
    #define IIC2C_TXAK                  _IIC2C1.SameAddr_STR.IIC2CSTR.Bits.TXAK
    #define IIC2C_TX                    _IIC2C1.SameAddr_STR.IIC2CSTR.Bits.TX
    #define IIC2C_MST                   _IIC2C1.SameAddr_STR.IIC2CSTR.Bits.MST
    #define IIC2C_IICIE                 _IIC2C1.SameAddr_STR.IIC2CSTR.Bits.IICIE
    #define IIC2C_IICEN                 _IIC2C1.SameAddr_STR.IIC2CSTR.Bits.IICEN
    
    #define IIC2C_RSTA_MASK             4U
    #define IIC2C_TXAK_MASK             8U
    #define IIC2C_TX_MASK               16U
    #define IIC2C_MST_MASK              32U
    #define IIC2C_IICIE_MASK            64U
    #define IIC2C_IICEN_MASK            128U
    
  } SameAddr_STR; /*Several registers at the same address */

} IIC2C1STR;
extern volatile IIC2C1STR _IIC2C1 @0x0000186A;


/*** IIC2S - IIC Status Register; 0x0000186B ***/
typedef union {
  byte Byte;
  struct {
    byte RXAK        :1;                                       /* Receive Acknowledge */
    byte IICIF       :1;                                       /* IIC Interrupt Flag */
    byte SRW         :1;                                       /* Slave Read/Write */
    byte             :1; 
    byte ARBL        :1;                                       /* Arbitration Lost */
    byte BUSY        :1;                                       /* Bus Busy */
    byte IAAS        :1;                                       /* Addressed as a Slave */
    byte TCF         :1;                                       /* Transfer Complete Flag */
  } Bits;
} IIC2SSTR;
extern volatile IIC2SSTR _IIC2S @0x0000186B;
#define IIC2S                           _IIC2S.Byte
#define IIC2S_RXAK                      _IIC2S.Bits.RXAK
#define IIC2S_IICIF                     _IIC2S.Bits.IICIF
#define IIC2S_SRW                       _IIC2S.Bits.SRW
#define IIC2S_ARBL                      _IIC2S.Bits.ARBL
#define IIC2S_BUSY                      _IIC2S.Bits.BUSY
#define IIC2S_IAAS                      _IIC2S.Bits.IAAS
#define IIC2S_TCF                       _IIC2S.Bits.TCF

#define IIC2S_RXAK_MASK                 1U
#define IIC2S_IICIF_MASK                2U
#define IIC2S_SRW_MASK                  4U
#define IIC2S_ARBL_MASK                 16U
#define IIC2S_BUSY_MASK                 32U
#define IIC2S_IAAS_MASK                 64U
#define IIC2S_TCF_MASK                  128U


/*** IIC2D - IIC Data I/O Register; 0x0000186C ***/
typedef union {
  byte Byte;
  struct {
    byte DATA0       :1;                                       /* IIC Data Bit 0 */
    byte DATA1       :1;                                       /* IIC Data Bit 1 */
    byte DATA2       :1;                                       /* IIC Data Bit 2 */
    byte DATA3       :1;                                       /* IIC Data Bit 3 */
    byte DATA4       :1;                                       /* IIC Data Bit 4 */
    byte DATA5       :1;                                       /* IIC Data Bit 5 */
    byte DATA6       :1;                                       /* IIC Data Bit 6 */
    byte DATA7       :1;                                       /* IIC Data Bit 7 */
  } Bits;
} IIC2DSTR;
extern volatile IIC2DSTR _IIC2D @0x0000186C;
#define IIC2D                           _IIC2D.Byte
#define IIC2D_DATA0                     _IIC2D.Bits.DATA0
#define IIC2D_DATA1                     _IIC2D.Bits.DATA1
#define IIC2D_DATA2                     _IIC2D.Bits.DATA2
#define IIC2D_DATA3                     _IIC2D.Bits.DATA3
#define IIC2D_DATA4                     _IIC2D.Bits.DATA4
#define IIC2D_DATA5                     _IIC2D.Bits.DATA5
#define IIC2D_DATA6                     _IIC2D.Bits.DATA6
#define IIC2D_DATA7                     _IIC2D.Bits.DATA7

#define IIC2D_DATA0_MASK                1U
#define IIC2D_DATA1_MASK                2U
#define IIC2D_DATA2_MASK                4U
#define IIC2D_DATA3_MASK                8U
#define IIC2D_DATA4_MASK                16U
#define IIC2D_DATA5_MASK                32U
#define IIC2D_DATA6_MASK                64U
#define IIC2D_DATA7_MASK                128U


/*** IIC2C2 - IIC Control Register 2; 0x0000186D ***/
typedef union {
  byte Byte;
  struct {
    byte AD8         :1;                                       /* Slave Address Bit 8 */
    byte AD9         :1;                                       /* Slave Address Bit 9 */
    byte AD10        :1;                                       /* Slave Address Bit 10 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte ADEXT       :1;                                       /* Address Extension */
    byte GCAEN       :1;                                       /* General Call Address Enable */
  } Bits;
  struct {
    byte grpAD_8 :3;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
  } MergedBits;
} IIC2C2STR;
extern volatile IIC2C2STR _IIC2C2 @0x0000186D;
#define IIC2C2                          _IIC2C2.Byte
#define IIC2C2_AD8                      _IIC2C2.Bits.AD8
#define IIC2C2_AD9                      _IIC2C2.Bits.AD9
#define IIC2C2_AD10                     _IIC2C2.Bits.AD10
#define IIC2C2_ADEXT                    _IIC2C2.Bits.ADEXT
#define IIC2C2_GCAEN                    _IIC2C2.Bits.GCAEN
#define IIC2C2_AD_8                     _IIC2C2.MergedBits.grpAD_8
#define IIC2C2_AD                       IIC2C2_AD_8

#define IIC2C2_AD8_MASK                 1U
#define IIC2C2_AD9_MASK                 2U
#define IIC2C2_AD10_MASK                4U
#define IIC2C2_ADEXT_MASK               64U
#define IIC2C2_GCAEN_MASK               128U
#define IIC2C2_AD_8_MASK                7U
#define IIC2C2_AD_8_BITNUM              0U


/*** SCI2BD - SCI2 Baud Rate Register; 0x00001870 ***/
typedef union {
  word Word;
   /* Overlapped registers: */
  struct {
    /*** SCI2BDH - SCI2 Baud Rate Register High; 0x00001870 ***/
    union {
      byte Byte;
      struct {
        byte SBR8        :1;                                       /* Baud Rate Modulo Divisor Bit 8 */
        byte SBR9        :1;                                       /* Baud Rate Modulo Divisor Bit 9 */
        byte SBR10       :1;                                       /* Baud Rate Modulo Divisor Bit 10 */
        byte SBR11       :1;                                       /* Baud Rate Modulo Divisor Bit 11 */
        byte SBR12       :1;                                       /* Baud Rate Modulo Divisor Bit 12 */
        byte             :1; 
        byte RXEDGIE     :1;                                       /* RxD Input Active Edge Interrupt Enable (for RXEDGIF) */
        byte LBKDIE      :1;                                       /* LIN Break Detect Interrupt Enable (for LBKDIF) */
      } Bits;
      struct {
        byte grpSBR_8 :5;
        byte     :1;
        byte     :1;
        byte     :1;
      } MergedBits;
    } SCI2BDHSTR;
    #define SCI2BDH                     _SCI2BD.Overlap_STR.SCI2BDHSTR.Byte
    #define SCI2BDH_SBR8                _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR8
    #define SCI2BDH_SBR9                _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR9
    #define SCI2BDH_SBR10               _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR10
    #define SCI2BDH_SBR11               _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR11
    #define SCI2BDH_SBR12               _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.SBR12
    #define SCI2BDH_RXEDGIE             _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.RXEDGIE
    #define SCI2BDH_LBKDIE              _SCI2BD.Overlap_STR.SCI2BDHSTR.Bits.LBKDIE
    #define SCI2BDH_SBR_8               _SCI2BD.Overlap_STR.SCI2BDHSTR.MergedBits.grpSBR_8
    #define SCI2BDH_SBR                 SCI2BDH_SBR_8
    
    #define SCI2BDH_SBR8_MASK           1U
    #define SCI2BDH_SBR9_MASK           2U
    #define SCI2BDH_SBR10_MASK          4U
    #define SCI2BDH_SBR11_MASK          8U
    #define SCI2BDH_SBR12_MASK          16U
    #define SCI2BDH_RXEDGIE_MASK        64U
    #define SCI2BDH_LBKDIE_MASK         128U
    #define SCI2BDH_SBR_8_MASK          31U
    #define SCI2BDH_SBR_8_BITNUM        0U
    

    /*** SCI2BDL - SCI2 Baud Rate Register Low; 0x00001871 ***/
    union {
      byte Byte;
      struct {
        byte SBR0        :1;                                       /* Baud Rate Modulo Divisor Bit 0 */
        byte SBR1        :1;                                       /* Baud Rate Modulo Divisor Bit 1 */
        byte SBR2        :1;                                       /* Baud Rate Modulo Divisor Bit 2 */
        byte SBR3        :1;                                       /* Baud Rate Modulo Divisor Bit 3 */
        byte SBR4        :1;                                       /* Baud Rate Modulo Divisor Bit 4 */
        byte SBR5        :1;                                       /* Baud Rate Modulo Divisor Bit 5 */
        byte SBR6        :1;                                       /* Baud Rate Modulo Divisor Bit 6 */
        byte SBR7        :1;                                       /* Baud Rate Modulo Divisor Bit 7 */
      } Bits;
    } SCI2BDLSTR;
    #define SCI2BDL                     _SCI2BD.Overlap_STR.SCI2BDLSTR.Byte
    #define SCI2BDL_SBR0                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR0
    #define SCI2BDL_SBR1                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR1
    #define SCI2BDL_SBR2                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR2
    #define SCI2BDL_SBR3                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR3
    #define SCI2BDL_SBR4                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR4
    #define SCI2BDL_SBR5                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR5
    #define SCI2BDL_SBR6                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR6
    #define SCI2BDL_SBR7                _SCI2BD.Overlap_STR.SCI2BDLSTR.Bits.SBR7
    
    #define SCI2BDL_SBR0_MASK           1U
    #define SCI2BDL_SBR1_MASK           2U
    #define SCI2BDL_SBR2_MASK           4U
    #define SCI2BDL_SBR3_MASK           8U
    #define SCI2BDL_SBR4_MASK           16U
    #define SCI2BDL_SBR5_MASK           32U
    #define SCI2BDL_SBR6_MASK           64U
    #define SCI2BDL_SBR7_MASK           128U
    
  } Overlap_STR;

} SCI2BDSTR;
extern volatile SCI2BDSTR _SCI2BD @0x00001870;
#define SCI2BD                          _SCI2BD.Word


/*** SCI2C1 - SCI2 Control Register 1; 0x00001872 ***/
typedef union {
  byte Byte;
  struct {
    byte PT          :1;                                       /* Parity Type */
    byte PE          :1;                                       /* Parity Enable */
    byte ILT         :1;                                       /* Idle Line Type Select */
    byte WAKE        :1;                                       /* Receiver Wakeup Method Select */
    byte M           :1;                                       /* 9-Bit or 8-Bit Mode Select */
    byte RSRC        :1;                                       /* Receiver Source Select */
    byte SCISWAI     :1;                                       /* SCI Stops in Wait Mode */
    byte LOOPS       :1;                                       /* Loop Mode Select */
  } Bits;
} SCI2C1STR;
extern volatile SCI2C1STR _SCI2C1 @0x00001872;
#define SCI2C1                          _SCI2C1.Byte
#define SCI2C1_PT                       _SCI2C1.Bits.PT
#define SCI2C1_PE                       _SCI2C1.Bits.PE
#define SCI2C1_ILT                      _SCI2C1.Bits.ILT
#define SCI2C1_WAKE                     _SCI2C1.Bits.WAKE
#define SCI2C1_M                        _SCI2C1.Bits.M
#define SCI2C1_RSRC                     _SCI2C1.Bits.RSRC
#define SCI2C1_SCISWAI                  _SCI2C1.Bits.SCISWAI
#define SCI2C1_LOOPS                    _SCI2C1.Bits.LOOPS

#define SCI2C1_PT_MASK                  1U
#define SCI2C1_PE_MASK                  2U
#define SCI2C1_ILT_MASK                 4U
#define SCI2C1_WAKE_MASK                8U
#define SCI2C1_M_MASK                   16U
#define SCI2C1_RSRC_MASK                32U
#define SCI2C1_SCISWAI_MASK             64U
#define SCI2C1_LOOPS_MASK               128U


/*** SCI2C2 - SCI2 Control Register 2; 0x00001873 ***/
typedef union {
  byte Byte;
  struct {
    byte SBK         :1;                                       /* Send Break */
    byte RWU         :1;                                       /* Receiver Wakeup Control */
    byte RE          :1;                                       /* Receiver Enable */
    byte TE          :1;                                       /* Transmitter Enable */
    byte ILIE        :1;                                       /* Idle Line Interrupt Enable (for IDLE) */
    byte RIE         :1;                                       /* Receiver Interrupt Enable (for RDRF) */
    byte TCIE        :1;                                       /* Transmission Complete Interrupt Enable (for TC) */
    byte TIE         :1;                                       /* Transmit Interrupt Enable (for TDRE) */
  } Bits;
} SCI2C2STR;
extern volatile SCI2C2STR _SCI2C2 @0x00001873;
#define SCI2C2                          _SCI2C2.Byte
#define SCI2C2_SBK                      _SCI2C2.Bits.SBK
#define SCI2C2_RWU                      _SCI2C2.Bits.RWU
#define SCI2C2_RE                       _SCI2C2.Bits.RE
#define SCI2C2_TE                       _SCI2C2.Bits.TE
#define SCI2C2_ILIE                     _SCI2C2.Bits.ILIE
#define SCI2C2_RIE                      _SCI2C2.Bits.RIE
#define SCI2C2_TCIE                     _SCI2C2.Bits.TCIE
#define SCI2C2_TIE                      _SCI2C2.Bits.TIE

#define SCI2C2_SBK_MASK                 1U
#define SCI2C2_RWU_MASK                 2U
#define SCI2C2_RE_MASK                  4U
#define SCI2C2_TE_MASK                  8U
#define SCI2C2_ILIE_MASK                16U
#define SCI2C2_RIE_MASK                 32U
#define SCI2C2_TCIE_MASK                64U
#define SCI2C2_TIE_MASK                 128U


/*** SCI2S1 - SCI2 Status Register 1; 0x00001874 ***/
typedef union {
  byte Byte;
  struct {
    byte PF          :1;                                       /* Parity Error Flag */
    byte FE          :1;                                       /* Framing Error Flag */
    byte NF          :1;                                       /* Noise Flag */
    byte OR          :1;                                       /* Receiver Overrun Flag */
    byte IDLE        :1;                                       /* Idle Line Flag */
    byte RDRF        :1;                                       /* Receive Data Register Full Flag */
    byte TC          :1;                                       /* Transmission Complete Flag */
    byte TDRE        :1;                                       /* Transmit Data Register Empty Flag */
  } Bits;
} SCI2S1STR;
extern volatile SCI2S1STR _SCI2S1 @0x00001874;
#define SCI2S1                          _SCI2S1.Byte
#define SCI2S1_PF                       _SCI2S1.Bits.PF
#define SCI2S1_FE                       _SCI2S1.Bits.FE
#define SCI2S1_NF                       _SCI2S1.Bits.NF
#define SCI2S1_OR                       _SCI2S1.Bits.OR
#define SCI2S1_IDLE                     _SCI2S1.Bits.IDLE
#define SCI2S1_RDRF                     _SCI2S1.Bits.RDRF
#define SCI2S1_TC                       _SCI2S1.Bits.TC
#define SCI2S1_TDRE                     _SCI2S1.Bits.TDRE

#define SCI2S1_PF_MASK                  1U
#define SCI2S1_FE_MASK                  2U
#define SCI2S1_NF_MASK                  4U
#define SCI2S1_OR_MASK                  8U
#define SCI2S1_IDLE_MASK                16U
#define SCI2S1_RDRF_MASK                32U
#define SCI2S1_TC_MASK                  64U
#define SCI2S1_TDRE_MASK                128U


/*** SCI2S2 - SCI2 Status Register 2; 0x00001875 ***/
typedef union {
  byte Byte;
  struct {
    byte RAF         :1;                                       /* Receiver Active Flag */
    byte LBKDE       :1;                                       /* LIN Break Detection Enable */
    byte BRK13       :1;                                       /* Break Character Generation Length */
    byte RWUID       :1;                                       /* Receive Wake Up Idle Detect */
    byte RXINV       :1;                                       /* Receive Data Inversion */
    byte             :1; 
    byte RXEDGIF     :1;                                       /* RxD Pin Active Edge Interrupt Flag */
    byte LBKDIF      :1;                                       /* LIN Break Detect Interrupt Flag */
  } Bits;
} SCI2S2STR;
extern volatile SCI2S2STR _SCI2S2 @0x00001875;
#define SCI2S2                          _SCI2S2.Byte
#define SCI2S2_RAF                      _SCI2S2.Bits.RAF
#define SCI2S2_LBKDE                    _SCI2S2.Bits.LBKDE
#define SCI2S2_BRK13                    _SCI2S2.Bits.BRK13
#define SCI2S2_RWUID                    _SCI2S2.Bits.RWUID
#define SCI2S2_RXINV                    _SCI2S2.Bits.RXINV
#define SCI2S2_RXEDGIF                  _SCI2S2.Bits.RXEDGIF
#define SCI2S2_LBKDIF                   _SCI2S2.Bits.LBKDIF

#define SCI2S2_RAF_MASK                 1U
#define SCI2S2_LBKDE_MASK               2U
#define SCI2S2_BRK13_MASK               4U
#define SCI2S2_RWUID_MASK               8U
#define SCI2S2_RXINV_MASK               16U
#define SCI2S2_RXEDGIF_MASK             64U
#define SCI2S2_LBKDIF_MASK              128U


/*** SCI2C3 - SCI2 Control Register 3; 0x00001876 ***/
typedef union {
  byte Byte;
  struct {
    byte PEIE        :1;                                       /* Parity Error Interrupt Enable */
    byte FEIE        :1;                                       /* Framing Error Interrupt Enable */
    byte NEIE        :1;                                       /* Noise Error Interrupt Enable */
    byte ORIE        :1;                                       /* Overrun Interrupt Enable */
    byte TXINV       :1;                                       /* Transmit Data Inversion */
    byte TXDIR       :1;                                       /* TxD Pin Direction in Single-Wire Mode */
    byte T8          :1;                                       /* Ninth Data Bit for Transmitter */
    byte R8          :1;                                       /* Ninth Data Bit for Receiver */
  } Bits;
} SCI2C3STR;
extern volatile SCI2C3STR _SCI2C3 @0x00001876;
#define SCI2C3                          _SCI2C3.Byte
#define SCI2C3_PEIE                     _SCI2C3.Bits.PEIE
#define SCI2C3_FEIE                     _SCI2C3.Bits.FEIE
#define SCI2C3_NEIE                     _SCI2C3.Bits.NEIE
#define SCI2C3_ORIE                     _SCI2C3.Bits.ORIE
#define SCI2C3_TXINV                    _SCI2C3.Bits.TXINV
#define SCI2C3_TXDIR                    _SCI2C3.Bits.TXDIR
#define SCI2C3_T8                       _SCI2C3.Bits.T8
#define SCI2C3_R8                       _SCI2C3.Bits.R8

#define SCI2C3_PEIE_MASK                1U
#define SCI2C3_FEIE_MASK                2U
#define SCI2C3_NEIE_MASK                4U
#define SCI2C3_ORIE_MASK                8U
#define SCI2C3_TXINV_MASK               16U
#define SCI2C3_TXDIR_MASK               32U
#define SCI2C3_T8_MASK                  64U
#define SCI2C3_R8_MASK                  128U


/*** SCI2D - SCI2 Data Register; 0x00001877 ***/
typedef union {
  byte Byte;
  struct {
    byte R0_T0       :1;                                       /* Receive/Transmit Data Bit 0 */
    byte R1_T1       :1;                                       /* Receive/Transmit Data Bit 1 */
    byte R2_T2       :1;                                       /* Receive/Transmit Data Bit 2 */
    byte R3_T3       :1;                                       /* Receive/Transmit Data Bit 3 */
    byte R4_T4       :1;                                       /* Receive/Transmit Data Bit 4 */
    byte R5_T5       :1;                                       /* Receive/Transmit Data Bit 5 */
    byte R6_T6       :1;                                       /* Receive/Transmit Data Bit 6 */
    byte R7_T7       :1;                                       /* Receive/Transmit Data Bit 7 */
  } Bits;
} SCI2DSTR;
extern volatile SCI2DSTR _SCI2D @0x00001877;
#define SCI2D                           _SCI2D.Byte
#define SCI2D_R0_T0                     _SCI2D.Bits.R0_T0
#define SCI2D_R1_T1                     _SCI2D.Bits.R1_T1
#define SCI2D_R2_T2                     _SCI2D.Bits.R2_T2
#define SCI2D_R3_T3                     _SCI2D.Bits.R3_T3
#define SCI2D_R4_T4                     _SCI2D.Bits.R4_T4
#define SCI2D_R5_T5                     _SCI2D.Bits.R5_T5
#define SCI2D_R6_T6                     _SCI2D.Bits.R6_T6
#define SCI2D_R7_T7                     _SCI2D.Bits.R7_T7

#define SCI2D_R0_T0_MASK                1U
#define SCI2D_R1_T1_MASK                2U
#define SCI2D_R2_T2_MASK                4U
#define SCI2D_R3_T3_MASK                8U
#define SCI2D_R4_T4_MASK                16U
#define SCI2D_R5_T5_MASK                32U
#define SCI2D_R6_T6_MASK                64U
#define SCI2D_R7_T7_MASK                128U


/*** PTCSET - Port C Data Set Register; 0x00001878 ***/
typedef union {
  byte Byte;
  struct {
    byte PTCSET0     :1;                                       /* Data Set for Port C Bit 0 */
    byte PTCSET1     :1;                                       /* Data Set for Port C Bit 1 */
    byte PTCSET2     :1;                                       /* Data Set for Port C Bit 2 */
    byte PTCSET3     :1;                                       /* Data Set for Port C Bit 3 */
    byte PTCSET4     :1;                                       /* Data Set for Port C Bit 4 */
    byte PTCSET5     :1;                                       /* Data Set for Port C Bit 5 */
    byte PTCSET6     :1;                                       /* Data Set for Port C Bit 6 */
    byte PTCSET7     :1;                                       /* Data Set for Port C Bit 7 */
  } Bits;
} PTCSETSTR;
extern volatile PTCSETSTR _PTCSET @0x00001878;
#define PTCSET                          _PTCSET.Byte
#define PTCSET_PTCSET0                  _PTCSET.Bits.PTCSET0
#define PTCSET_PTCSET1                  _PTCSET.Bits.PTCSET1
#define PTCSET_PTCSET2                  _PTCSET.Bits.PTCSET2
#define PTCSET_PTCSET3                  _PTCSET.Bits.PTCSET3
#define PTCSET_PTCSET4                  _PTCSET.Bits.PTCSET4
#define PTCSET_PTCSET5                  _PTCSET.Bits.PTCSET5
#define PTCSET_PTCSET6                  _PTCSET.Bits.PTCSET6
#define PTCSET_PTCSET7                  _PTCSET.Bits.PTCSET7

#define PTCSET_PTCSET0_MASK             1U
#define PTCSET_PTCSET1_MASK             2U
#define PTCSET_PTCSET2_MASK             4U
#define PTCSET_PTCSET3_MASK             8U
#define PTCSET_PTCSET4_MASK             16U
#define PTCSET_PTCSET5_MASK             32U
#define PTCSET_PTCSET6_MASK             64U
#define PTCSET_PTCSET7_MASK             128U


/*** PTESET - Port E Data Set Register; 0x00001879 ***/
typedef union {
  byte Byte;
  struct {
    byte PTESET0     :1;                                       /* Data Set for Port E Bit 0 */
    byte PTESET1     :1;                                       /* Data Set for Port E Bit 1 */
    byte PTESET2     :1;                                       /* Data Set for Port E Bit 2 */
    byte PTESET3     :1;                                       /* Data Set for Port E Bit 3 */
    byte PTESET4     :1;                                       /* Data Set for Port E Bit 4 */
    byte PTESET5     :1;                                       /* Data Set for Port E Bit 5 */
    byte PTESET6     :1;                                       /* Data Set for Port E Bit 6 */
    byte PTESET7     :1;                                       /* Data Set for Port E Bit 7 */
  } Bits;
} PTESETSTR;
extern volatile PTESETSTR _PTESET @0x00001879;
#define PTESET                          _PTESET.Byte
#define PTESET_PTESET0                  _PTESET.Bits.PTESET0
#define PTESET_PTESET1                  _PTESET.Bits.PTESET1
#define PTESET_PTESET2                  _PTESET.Bits.PTESET2
#define PTESET_PTESET3                  _PTESET.Bits.PTESET3
#define PTESET_PTESET4                  _PTESET.Bits.PTESET4
#define PTESET_PTESET5                  _PTESET.Bits.PTESET5
#define PTESET_PTESET6                  _PTESET.Bits.PTESET6
#define PTESET_PTESET7                  _PTESET.Bits.PTESET7

#define PTESET_PTESET0_MASK             1U
#define PTESET_PTESET1_MASK             2U
#define PTESET_PTESET2_MASK             4U
#define PTESET_PTESET3_MASK             8U
#define PTESET_PTESET4_MASK             16U
#define PTESET_PTESET5_MASK             32U
#define PTESET_PTESET6_MASK             64U
#define PTESET_PTESET7_MASK             128U


/*** PTCCLR - Port C Data Clear Register; 0x0000187A ***/
typedef union {
  byte Byte;
  struct {
    byte PTCCLR0     :1;                                       /* Data Clear for Port C Bit 0 */
    byte PTCCLR1     :1;                                       /* Data Clear for Port C Bit 1 */
    byte PTCCLR2     :1;                                       /* Data Clear for Port C Bit 2 */
    byte PTCCLR3     :1;                                       /* Data Clear for Port C Bit 3 */
    byte PTCCLR4     :1;                                       /* Data Clear for Port C Bit 4 */
    byte PTCCLR5     :1;                                       /* Data Clear for Port C Bit 5 */
    byte PTCCLR6     :1;                                       /* Data Clear for Port C Bit 6 */
    byte PTCCLR7     :1;                                       /* Data Clear for Port C Bit 7 */
  } Bits;
} PTCCLRSTR;
extern volatile PTCCLRSTR _PTCCLR @0x0000187A;
#define PTCCLR                          _PTCCLR.Byte
#define PTCCLR_PTCCLR0                  _PTCCLR.Bits.PTCCLR0
#define PTCCLR_PTCCLR1                  _PTCCLR.Bits.PTCCLR1
#define PTCCLR_PTCCLR2                  _PTCCLR.Bits.PTCCLR2
#define PTCCLR_PTCCLR3                  _PTCCLR.Bits.PTCCLR3
#define PTCCLR_PTCCLR4                  _PTCCLR.Bits.PTCCLR4
#define PTCCLR_PTCCLR5                  _PTCCLR.Bits.PTCCLR5
#define PTCCLR_PTCCLR6                  _PTCCLR.Bits.PTCCLR6
#define PTCCLR_PTCCLR7                  _PTCCLR.Bits.PTCCLR7

#define PTCCLR_PTCCLR0_MASK             1U
#define PTCCLR_PTCCLR1_MASK             2U
#define PTCCLR_PTCCLR2_MASK             4U
#define PTCCLR_PTCCLR3_MASK             8U
#define PTCCLR_PTCCLR4_MASK             16U
#define PTCCLR_PTCCLR5_MASK             32U
#define PTCCLR_PTCCLR6_MASK             64U
#define PTCCLR_PTCCLR7_MASK             128U


/*** PTECLR - Port E Data Clear Register; 0x0000187B ***/
typedef union {
  byte Byte;
  struct {
    byte PTECLR0     :1;                                       /* Data Clear for Port E Bit 0 */
    byte PTECLR1     :1;                                       /* Data Clear for Port E Bit 1 */
    byte PTECLR2     :1;                                       /* Data Clear for Port E Bit 2 */
    byte PTECLR3     :1;                                       /* Data Clear for Port E Bit 3 */
    byte PTECLR4     :1;                                       /* Data Clear for Port E Bit 4 */
    byte PTECLR5     :1;                                       /* Data Clear for Port E Bit 5 */
    byte PTECLR6     :1;                                       /* Data Clear for Port E Bit 6 */
    byte PTECLR7     :1;                                       /* Data Clear for Port E Bit 7 */
  } Bits;
} PTECLRSTR;
extern volatile PTECLRSTR _PTECLR @0x0000187B;
#define PTECLR                          _PTECLR.Byte
#define PTECLR_PTECLR0                  _PTECLR.Bits.PTECLR0
#define PTECLR_PTECLR1                  _PTECLR.Bits.PTECLR1
#define PTECLR_PTECLR2                  _PTECLR.Bits.PTECLR2
#define PTECLR_PTECLR3                  _PTECLR.Bits.PTECLR3
#define PTECLR_PTECLR4                  _PTECLR.Bits.PTECLR4
#define PTECLR_PTECLR5                  _PTECLR.Bits.PTECLR5
#define PTECLR_PTECLR6                  _PTECLR.Bits.PTECLR6
#define PTECLR_PTECLR7                  _PTECLR.Bits.PTECLR7

#define PTECLR_PTECLR0_MASK             1U
#define PTECLR_PTECLR1_MASK             2U
#define PTECLR_PTECLR2_MASK             4U
#define PTECLR_PTECLR3_MASK             8U
#define PTECLR_PTECLR4_MASK             16U
#define PTECLR_PTECLR5_MASK             32U
#define PTECLR_PTECLR6_MASK             64U
#define PTECLR_PTECLR7_MASK             128U


/*** PTCTOG - Port C Toggle Register; 0x0000187C ***/
typedef union {
  byte Byte;
  struct {
    byte PTCTOG0     :1;                                       /* Toggle Enable for Port C Bit 0 */
    byte PTCTOG1     :1;                                       /* Toggle Enable for Port C Bit 1 */
    byte PTCTOG2     :1;                                       /* Toggle Enable for Port C Bit 2 */
    byte PTCTOG3     :1;                                       /* Toggle Enable for Port C Bit 3 */
    byte PTCTOG4     :1;                                       /* Toggle Enable for Port C Bit 4 */
    byte PTCTOG5     :1;                                       /* Toggle Enable for Port C Bit 5 */
    byte PTCTOG6     :1;                                       /* Toggle Enable for Port C Bit 6 */
    byte PTCTOG7     :1;                                       /* Toggle Enable for Port C Bit 7 */
  } Bits;
} PTCTOGSTR;
extern volatile PTCTOGSTR _PTCTOG @0x0000187C;
#define PTCTOG                          _PTCTOG.Byte
#define PTCTOG_PTCTOG0                  _PTCTOG.Bits.PTCTOG0
#define PTCTOG_PTCTOG1                  _PTCTOG.Bits.PTCTOG1
#define PTCTOG_PTCTOG2                  _PTCTOG.Bits.PTCTOG2
#define PTCTOG_PTCTOG3                  _PTCTOG.Bits.PTCTOG3
#define PTCTOG_PTCTOG4                  _PTCTOG.Bits.PTCTOG4
#define PTCTOG_PTCTOG5                  _PTCTOG.Bits.PTCTOG5
#define PTCTOG_PTCTOG6                  _PTCTOG.Bits.PTCTOG6
#define PTCTOG_PTCTOG7                  _PTCTOG.Bits.PTCTOG7

#define PTCTOG_PTCTOG0_MASK             1U
#define PTCTOG_PTCTOG1_MASK             2U
#define PTCTOG_PTCTOG2_MASK             4U
#define PTCTOG_PTCTOG3_MASK             8U
#define PTCTOG_PTCTOG4_MASK             16U
#define PTCTOG_PTCTOG5_MASK             32U
#define PTCTOG_PTCTOG6_MASK             64U
#define PTCTOG_PTCTOG7_MASK             128U


/*** PTETOG - Port E Toggle Register; 0x0000187D ***/
typedef union {
  byte Byte;
  struct {
    byte PTETOG0     :1;                                       /* Toggle Enable for Port E Bit 0 */
    byte PTETOG1     :1;                                       /* Toggle Enable for Port E Bit 1 */
    byte PTETOG2     :1;                                       /* Toggle Enable for Port E Bit 2 */
    byte PTETOG3     :1;                                       /* Toggle Enable for Port E Bit 3 */
    byte PTETOG4     :1;                                       /* Toggle Enable for Port E Bit 4 */
    byte PTETOG5     :1;                                       /* Toggle Enable for Port E Bit 5 */
    byte PTETOG6     :1;                                       /* Toggle Enable for Port E Bit 6 */
    byte PTETOG7     :1;                                       /* Toggle Enable for Port E Bit 7 */
  } Bits;
} PTETOGSTR;
extern volatile PTETOGSTR _PTETOG @0x0000187D;
#define PTETOG                          _PTETOG.Byte
#define PTETOG_PTETOG0                  _PTETOG.Bits.PTETOG0
#define PTETOG_PTETOG1                  _PTETOG.Bits.PTETOG1
#define PTETOG_PTETOG2                  _PTETOG.Bits.PTETOG2
#define PTETOG_PTETOG3                  _PTETOG.Bits.PTETOG3
#define PTETOG_PTETOG4                  _PTETOG.Bits.PTETOG4
#define PTETOG_PTETOG5                  _PTETOG.Bits.PTETOG5
#define PTETOG_PTETOG6                  _PTETOG.Bits.PTETOG6
#define PTETOG_PTETOG7                  _PTETOG.Bits.PTETOG7

#define PTETOG_PTETOG0_MASK             1U
#define PTETOG_PTETOG1_MASK             2U
#define PTETOG_PTETOG2_MASK             4U
#define PTETOG_PTETOG3_MASK             8U
#define PTETOG_PTETOG4_MASK             16U
#define PTETOG_PTETOG5_MASK             32U
#define PTETOG_PTETOG6_MASK             64U
#define PTETOG_PTETOG7_MASK             128U


/*** NVFTRIM - Nonvolatile ICS Fine Trim; 0x0000FFAE ***/
typedef union {
  byte Byte;
  struct {
    byte FTRIM       :1;                                       /* ICS Fine Trim */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
  } Bits;
} NVFTRIMSTR;
/* Tip for register initialization in the user code:  const byte NVFTRIM_INIT @0x0000FFAE = <NVFTRIM_INITVAL>; */
#define _NVFTRIM (*(const NVFTRIMSTR * __far)0x0000FFAE)
#define NVFTRIM                         _NVFTRIM.Byte
#define NVFTRIM_FTRIM                   _NVFTRIM.Bits.FTRIM

#define NVFTRIM_FTRIM_MASK              1U


/*** NVICSTRM - Nonvolatile ICS Trim Register; 0x0000FFAF ***/
typedef union {
  byte Byte;
  struct {
    byte TRIM0       :1;                                       /* ICS Trim Setting, bit 0 */
    byte TRIM1       :1;                                       /* ICS Trim Setting, bit 1 */
    byte TRIM2       :1;                                       /* ICS Trim Setting, bit 2 */
    byte TRIM3       :1;                                       /* ICS Trim Setting, bit 3 */
    byte TRIM4       :1;                                       /* ICS Trim Setting, bit 4 */
    byte TRIM5       :1;                                       /* ICS Trim Setting, bit 5 */
    byte TRIM6       :1;                                       /* ICS Trim Setting, bit 6 */
    byte TRIM7       :1;                                       /* ICS Trim Setting, bit 7 */
  } Bits;
} NVICSTRMSTR;
/* Tip for register initialization in the user code:  const byte NVICSTRM_INIT @0x0000FFAF = <NVICSTRM_INITVAL>; */
#define _NVICSTRM (*(const NVICSTRMSTR * __far)0x0000FFAF)
#define NVICSTRM                        _NVICSTRM.Byte
#define NVICSTRM_TRIM0                  _NVICSTRM.Bits.TRIM0
#define NVICSTRM_TRIM1                  _NVICSTRM.Bits.TRIM1
#define NVICSTRM_TRIM2                  _NVICSTRM.Bits.TRIM2
#define NVICSTRM_TRIM3                  _NVICSTRM.Bits.TRIM3
#define NVICSTRM_TRIM4                  _NVICSTRM.Bits.TRIM4
#define NVICSTRM_TRIM5                  _NVICSTRM.Bits.TRIM5
#define NVICSTRM_TRIM6                  _NVICSTRM.Bits.TRIM6
#define NVICSTRM_TRIM7                  _NVICSTRM.Bits.TRIM7

#define NVICSTRM_TRIM0_MASK             1U
#define NVICSTRM_TRIM1_MASK             2U
#define NVICSTRM_TRIM2_MASK             4U
#define NVICSTRM_TRIM3_MASK             8U
#define NVICSTRM_TRIM4_MASK             16U
#define NVICSTRM_TRIM5_MASK             32U
#define NVICSTRM_TRIM6_MASK             64U
#define NVICSTRM_TRIM7_MASK             128U


/*** NVBACKKEY0 - Backdoor Comparison Key 0; 0x0000FFB0 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 0 Bits, bit 7 */
  } Bits;
} NVBACKKEY0STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY0_INIT @0x0000FFB0 = <NVBACKKEY0_INITVAL>; */
#define _NVBACKKEY0 (*(const NVBACKKEY0STR * __far)0x0000FFB0)
#define NVBACKKEY0                      _NVBACKKEY0.Byte
#define NVBACKKEY0_KEY0                 _NVBACKKEY0.Bits.KEY0
#define NVBACKKEY0_KEY1                 _NVBACKKEY0.Bits.KEY1
#define NVBACKKEY0_KEY2                 _NVBACKKEY0.Bits.KEY2
#define NVBACKKEY0_KEY3                 _NVBACKKEY0.Bits.KEY3
#define NVBACKKEY0_KEY4                 _NVBACKKEY0.Bits.KEY4
#define NVBACKKEY0_KEY5                 _NVBACKKEY0.Bits.KEY5
#define NVBACKKEY0_KEY6                 _NVBACKKEY0.Bits.KEY6
#define NVBACKKEY0_KEY7                 _NVBACKKEY0.Bits.KEY7
/* NVBACKKEY_ARR: Access 8 NVBACKKEYx registers in an array */
#define NVBACKKEY_ARR                   ((volatile byte * __far) &NVBACKKEY0)

#define NVBACKKEY0_KEY0_MASK            1U
#define NVBACKKEY0_KEY1_MASK            2U
#define NVBACKKEY0_KEY2_MASK            4U
#define NVBACKKEY0_KEY3_MASK            8U
#define NVBACKKEY0_KEY4_MASK            16U
#define NVBACKKEY0_KEY5_MASK            32U
#define NVBACKKEY0_KEY6_MASK            64U
#define NVBACKKEY0_KEY7_MASK            128U


/*** NVBACKKEY1 - Backdoor Comparison Key 1; 0x0000FFB1 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 1 Bits, bit 7 */
  } Bits;
} NVBACKKEY1STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY1_INIT @0x0000FFB1 = <NVBACKKEY1_INITVAL>; */
#define _NVBACKKEY1 (*(const NVBACKKEY1STR * __far)0x0000FFB1)
#define NVBACKKEY1                      _NVBACKKEY1.Byte
#define NVBACKKEY1_KEY0                 _NVBACKKEY1.Bits.KEY0
#define NVBACKKEY1_KEY1                 _NVBACKKEY1.Bits.KEY1
#define NVBACKKEY1_KEY2                 _NVBACKKEY1.Bits.KEY2
#define NVBACKKEY1_KEY3                 _NVBACKKEY1.Bits.KEY3
#define NVBACKKEY1_KEY4                 _NVBACKKEY1.Bits.KEY4
#define NVBACKKEY1_KEY5                 _NVBACKKEY1.Bits.KEY5
#define NVBACKKEY1_KEY6                 _NVBACKKEY1.Bits.KEY6
#define NVBACKKEY1_KEY7                 _NVBACKKEY1.Bits.KEY7

#define NVBACKKEY1_KEY0_MASK            1U
#define NVBACKKEY1_KEY1_MASK            2U
#define NVBACKKEY1_KEY2_MASK            4U
#define NVBACKKEY1_KEY3_MASK            8U
#define NVBACKKEY1_KEY4_MASK            16U
#define NVBACKKEY1_KEY5_MASK            32U
#define NVBACKKEY1_KEY6_MASK            64U
#define NVBACKKEY1_KEY7_MASK            128U


/*** NVBACKKEY2 - Backdoor Comparison Key 2; 0x0000FFB2 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 2 Bits, bit 7 */
  } Bits;
} NVBACKKEY2STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY2_INIT @0x0000FFB2 = <NVBACKKEY2_INITVAL>; */
#define _NVBACKKEY2 (*(const NVBACKKEY2STR * __far)0x0000FFB2)
#define NVBACKKEY2                      _NVBACKKEY2.Byte
#define NVBACKKEY2_KEY0                 _NVBACKKEY2.Bits.KEY0
#define NVBACKKEY2_KEY1                 _NVBACKKEY2.Bits.KEY1
#define NVBACKKEY2_KEY2                 _NVBACKKEY2.Bits.KEY2
#define NVBACKKEY2_KEY3                 _NVBACKKEY2.Bits.KEY3
#define NVBACKKEY2_KEY4                 _NVBACKKEY2.Bits.KEY4
#define NVBACKKEY2_KEY5                 _NVBACKKEY2.Bits.KEY5
#define NVBACKKEY2_KEY6                 _NVBACKKEY2.Bits.KEY6
#define NVBACKKEY2_KEY7                 _NVBACKKEY2.Bits.KEY7

#define NVBACKKEY2_KEY0_MASK            1U
#define NVBACKKEY2_KEY1_MASK            2U
#define NVBACKKEY2_KEY2_MASK            4U
#define NVBACKKEY2_KEY3_MASK            8U
#define NVBACKKEY2_KEY4_MASK            16U
#define NVBACKKEY2_KEY5_MASK            32U
#define NVBACKKEY2_KEY6_MASK            64U
#define NVBACKKEY2_KEY7_MASK            128U


/*** NVBACKKEY3 - Backdoor Comparison Key 3; 0x0000FFB3 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 3 Bits, bit 7 */
  } Bits;
} NVBACKKEY3STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY3_INIT @0x0000FFB3 = <NVBACKKEY3_INITVAL>; */
#define _NVBACKKEY3 (*(const NVBACKKEY3STR * __far)0x0000FFB3)
#define NVBACKKEY3                      _NVBACKKEY3.Byte
#define NVBACKKEY3_KEY0                 _NVBACKKEY3.Bits.KEY0
#define NVBACKKEY3_KEY1                 _NVBACKKEY3.Bits.KEY1
#define NVBACKKEY3_KEY2                 _NVBACKKEY3.Bits.KEY2
#define NVBACKKEY3_KEY3                 _NVBACKKEY3.Bits.KEY3
#define NVBACKKEY3_KEY4                 _NVBACKKEY3.Bits.KEY4
#define NVBACKKEY3_KEY5                 _NVBACKKEY3.Bits.KEY5
#define NVBACKKEY3_KEY6                 _NVBACKKEY3.Bits.KEY6
#define NVBACKKEY3_KEY7                 _NVBACKKEY3.Bits.KEY7

#define NVBACKKEY3_KEY0_MASK            1U
#define NVBACKKEY3_KEY1_MASK            2U
#define NVBACKKEY3_KEY2_MASK            4U
#define NVBACKKEY3_KEY3_MASK            8U
#define NVBACKKEY3_KEY4_MASK            16U
#define NVBACKKEY3_KEY5_MASK            32U
#define NVBACKKEY3_KEY6_MASK            64U
#define NVBACKKEY3_KEY7_MASK            128U


/*** NVBACKKEY4 - Backdoor Comparison Key 4; 0x0000FFB4 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 4 Bits, bit 7 */
  } Bits;
} NVBACKKEY4STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY4_INIT @0x0000FFB4 = <NVBACKKEY4_INITVAL>; */
#define _NVBACKKEY4 (*(const NVBACKKEY4STR * __far)0x0000FFB4)
#define NVBACKKEY4                      _NVBACKKEY4.Byte
#define NVBACKKEY4_KEY0                 _NVBACKKEY4.Bits.KEY0
#define NVBACKKEY4_KEY1                 _NVBACKKEY4.Bits.KEY1
#define NVBACKKEY4_KEY2                 _NVBACKKEY4.Bits.KEY2
#define NVBACKKEY4_KEY3                 _NVBACKKEY4.Bits.KEY3
#define NVBACKKEY4_KEY4                 _NVBACKKEY4.Bits.KEY4
#define NVBACKKEY4_KEY5                 _NVBACKKEY4.Bits.KEY5
#define NVBACKKEY4_KEY6                 _NVBACKKEY4.Bits.KEY6
#define NVBACKKEY4_KEY7                 _NVBACKKEY4.Bits.KEY7

#define NVBACKKEY4_KEY0_MASK            1U
#define NVBACKKEY4_KEY1_MASK            2U
#define NVBACKKEY4_KEY2_MASK            4U
#define NVBACKKEY4_KEY3_MASK            8U
#define NVBACKKEY4_KEY4_MASK            16U
#define NVBACKKEY4_KEY5_MASK            32U
#define NVBACKKEY4_KEY6_MASK            64U
#define NVBACKKEY4_KEY7_MASK            128U


/*** NVBACKKEY5 - Backdoor Comparison Key 5; 0x0000FFB5 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 5 Bits, bit 7 */
  } Bits;
} NVBACKKEY5STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY5_INIT @0x0000FFB5 = <NVBACKKEY5_INITVAL>; */
#define _NVBACKKEY5 (*(const NVBACKKEY5STR * __far)0x0000FFB5)
#define NVBACKKEY5                      _NVBACKKEY5.Byte
#define NVBACKKEY5_KEY0                 _NVBACKKEY5.Bits.KEY0
#define NVBACKKEY5_KEY1                 _NVBACKKEY5.Bits.KEY1
#define NVBACKKEY5_KEY2                 _NVBACKKEY5.Bits.KEY2
#define NVBACKKEY5_KEY3                 _NVBACKKEY5.Bits.KEY3
#define NVBACKKEY5_KEY4                 _NVBACKKEY5.Bits.KEY4
#define NVBACKKEY5_KEY5                 _NVBACKKEY5.Bits.KEY5
#define NVBACKKEY5_KEY6                 _NVBACKKEY5.Bits.KEY6
#define NVBACKKEY5_KEY7                 _NVBACKKEY5.Bits.KEY7

#define NVBACKKEY5_KEY0_MASK            1U
#define NVBACKKEY5_KEY1_MASK            2U
#define NVBACKKEY5_KEY2_MASK            4U
#define NVBACKKEY5_KEY3_MASK            8U
#define NVBACKKEY5_KEY4_MASK            16U
#define NVBACKKEY5_KEY5_MASK            32U
#define NVBACKKEY5_KEY6_MASK            64U
#define NVBACKKEY5_KEY7_MASK            128U


/*** NVBACKKEY6 - Backdoor Comparison Key 6; 0x0000FFB6 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 6 Bits, bit 7 */
  } Bits;
} NVBACKKEY6STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY6_INIT @0x0000FFB6 = <NVBACKKEY6_INITVAL>; */
#define _NVBACKKEY6 (*(const NVBACKKEY6STR * __far)0x0000FFB6)
#define NVBACKKEY6                      _NVBACKKEY6.Byte
#define NVBACKKEY6_KEY0                 _NVBACKKEY6.Bits.KEY0
#define NVBACKKEY6_KEY1                 _NVBACKKEY6.Bits.KEY1
#define NVBACKKEY6_KEY2                 _NVBACKKEY6.Bits.KEY2
#define NVBACKKEY6_KEY3                 _NVBACKKEY6.Bits.KEY3
#define NVBACKKEY6_KEY4                 _NVBACKKEY6.Bits.KEY4
#define NVBACKKEY6_KEY5                 _NVBACKKEY6.Bits.KEY5
#define NVBACKKEY6_KEY6                 _NVBACKKEY6.Bits.KEY6
#define NVBACKKEY6_KEY7                 _NVBACKKEY6.Bits.KEY7

#define NVBACKKEY6_KEY0_MASK            1U
#define NVBACKKEY6_KEY1_MASK            2U
#define NVBACKKEY6_KEY2_MASK            4U
#define NVBACKKEY6_KEY3_MASK            8U
#define NVBACKKEY6_KEY4_MASK            16U
#define NVBACKKEY6_KEY5_MASK            32U
#define NVBACKKEY6_KEY6_MASK            64U
#define NVBACKKEY6_KEY7_MASK            128U


/*** NVBACKKEY7 - Backdoor Comparison Key 7; 0x0000FFB7 ***/
typedef union {
  byte Byte;
  struct {
    byte KEY0        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 0 */
    byte KEY1        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 1 */
    byte KEY2        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 2 */
    byte KEY3        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 3 */
    byte KEY4        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 4 */
    byte KEY5        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 5 */
    byte KEY6        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 6 */
    byte KEY7        :1;                                       /* Backdoor Comparison Key 7 Bits, bit 7 */
  } Bits;
} NVBACKKEY7STR;
/* Tip for register initialization in the user code:  const byte NVBACKKEY7_INIT @0x0000FFB7 = <NVBACKKEY7_INITVAL>; */
#define _NVBACKKEY7 (*(const NVBACKKEY7STR * __far)0x0000FFB7)
#define NVBACKKEY7                      _NVBACKKEY7.Byte
#define NVBACKKEY7_KEY0                 _NVBACKKEY7.Bits.KEY0
#define NVBACKKEY7_KEY1                 _NVBACKKEY7.Bits.KEY1
#define NVBACKKEY7_KEY2                 _NVBACKKEY7.Bits.KEY2
#define NVBACKKEY7_KEY3                 _NVBACKKEY7.Bits.KEY3
#define NVBACKKEY7_KEY4                 _NVBACKKEY7.Bits.KEY4
#define NVBACKKEY7_KEY5                 _NVBACKKEY7.Bits.KEY5
#define NVBACKKEY7_KEY6                 _NVBACKKEY7.Bits.KEY6
#define NVBACKKEY7_KEY7                 _NVBACKKEY7.Bits.KEY7

#define NVBACKKEY7_KEY0_MASK            1U
#define NVBACKKEY7_KEY1_MASK            2U
#define NVBACKKEY7_KEY2_MASK            4U
#define NVBACKKEY7_KEY3_MASK            8U
#define NVBACKKEY7_KEY4_MASK            16U
#define NVBACKKEY7_KEY5_MASK            32U
#define NVBACKKEY7_KEY6_MASK            64U
#define NVBACKKEY7_KEY7_MASK            128U


/*** NVPROT - Nonvolatile Flash Protection Register; 0x0000FFBD ***/
typedef union {
  byte Byte;
  struct {
    byte FPOPEN      :1;                                       /* Flash Protection Open */
    byte FPS0        :1;                                       /* Flash Protection Size, bit 0 */
    byte FPS1        :1;                                       /* Flash Protection Size, bit 1 */
    byte FPS2        :1;                                       /* Flash Protection Size, bit 2 */
    byte FPS3        :1;                                       /* Flash Protection Size, bit 3 */
    byte FPS4        :1;                                       /* Flash Protection Size, bit 4 */
    byte FPS5        :1;                                       /* Flash Protection Size, bit 5 */
    byte FPS6        :1;                                       /* Flash Protection Size, bit 6 */
  } Bits;
  struct {
    byte         :1;
    byte grpFPS  :7;
  } MergedBits;
} NVPROTSTR;
/* Tip for register initialization in the user code:  const byte NVPROT_INIT @0x0000FFBD = <NVPROT_INITVAL>; */
#define _NVPROT (*(const NVPROTSTR * __far)0x0000FFBD)
#define NVPROT                          _NVPROT.Byte
#define NVPROT_FPOPEN                   _NVPROT.Bits.FPOPEN
#define NVPROT_FPS0                     _NVPROT.Bits.FPS0
#define NVPROT_FPS1                     _NVPROT.Bits.FPS1
#define NVPROT_FPS2                     _NVPROT.Bits.FPS2
#define NVPROT_FPS3                     _NVPROT.Bits.FPS3
#define NVPROT_FPS4                     _NVPROT.Bits.FPS4
#define NVPROT_FPS5                     _NVPROT.Bits.FPS5
#define NVPROT_FPS6                     _NVPROT.Bits.FPS6
#define NVPROT_FPS                      _NVPROT.MergedBits.grpFPS

#define NVPROT_FPOPEN_MASK              1U
#define NVPROT_FPS0_MASK                2U
#define NVPROT_FPS1_MASK                4U
#define NVPROT_FPS2_MASK                8U
#define NVPROT_FPS3_MASK                16U
#define NVPROT_FPS4_MASK                32U
#define NVPROT_FPS5_MASK                64U
#define NVPROT_FPS6_MASK                128U
#define NVPROT_FPS_MASK                 254U
#define NVPROT_FPS_BITNUM               1U


/*** NVOPT - Nonvolatile Flash Options Register; 0x0000FFBF ***/
typedef union {
  byte Byte;
  struct {
    byte SEC0        :1;                                       /* Flash Security Bit 0 */
    byte SEC1        :1;                                       /* Flash Security Bit 1 */
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte             :1; 
    byte KEYEN0      :1;                                       /* Backdoor Key Security Enable Bit 0 */
    byte KEYEN1      :1;                                       /* Backdoor Key Security Enable Bit 1 */
  } Bits;
  struct {
    byte grpSEC  :2;
    byte         :1;
    byte         :1;
    byte         :1;
    byte         :1;
    byte grpKEYEN :2;
  } MergedBits;
} NVOPTSTR;
/* Tip for register initialization in the user code:  const byte NVOPT_INIT @0x0000FFBF = <NVOPT_INITVAL>; */
#define _NVOPT (*(const NVOPTSTR * __far)0x0000FFBF)
#define NVOPT                           _NVOPT.Byte
#define NVOPT_SEC0                      _NVOPT.Bits.SEC0
#define NVOPT_SEC1                      _NVOPT.Bits.SEC1
#define NVOPT_KEYEN0                    _NVOPT.Bits.KEYEN0
#define NVOPT_KEYEN1                    _NVOPT.Bits.KEYEN1
#define NVOPT_SEC                       _NVOPT.MergedBits.grpSEC
#define NVOPT_KEYEN                     _NVOPT.MergedBits.grpKEYEN

#define NVOPT_SEC0_MASK                 1U
#define NVOPT_SEC1_MASK                 2U
#define NVOPT_KEYEN0_MASK               64U
#define NVOPT_KEYEN1_MASK               128U
#define NVOPT_SEC_MASK                  3U
#define NVOPT_SEC_BITNUM                0U
#define NVOPT_KEYEN_MASK                192U
#define NVOPT_KEYEN_BITNUM              6U



/* Flash commands */
#define mBlank                          0x05
#define mBurstProg                      0x25
#define mByteProg                       0x20
#define mMassErase                      0x41
#define mPageErase                      0x40


/***********************************************/
/**   D E P R E C I A T E D   S Y M B O L S   **/
/***********************************************/
#endif
/*lint -restore  +esym(961,18.4) +esym(961,19.7) Enable MISRA rule (1.1,18.4,6.4,19.7) checking. */
