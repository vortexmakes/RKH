; Based on CPU DB MC9S08QE128_80, version 3.00.000 (RegistersPrg V2.15)

; ###################################################################
;     Filename  : mc9s08qe128.inc
;     Processor : MC9S08QE128CLK
;     FileFormat: V2.15
;     DataSheet : MC9S08QE128RM Rev. 1.0 Draft F
;     Compiler  : CodeWarrior compiler
;     Date/Time : 16.04.2007, 16:31
;     Abstract  :
;         This header implements the mapping of I/O devices.
;
;     (c) Copyright UNIS, spol. s r.o. 1997-2006
;     UNIS, spol. s r.o.
;     Jundrovska 33
;     624 00 Brno
;     Czech Republic
;     http      : www.processorexpert.com
;     mail      : info@processorexpert.com
;
;     File-Format-Revisions:
;      - 22.01.2007, V2.12 :
;               - Revision is not related to this file (CPU family)
;      - 01.03.2007, V2.13 :
;               - Flash commands constants values converted to HEX format
;      - 02.03.2007, V2.14 :
;               - Interrupt vector numbers added into .H, see VectorNumber_*
;      - 26.03.2007, V2.15 :
;               - Revision is not related to this file (CPU family)
;
;     CPU Registers Revisions:
;               - none
; ###################################################################

;*** Memory Map and Interrupt Vectors
;******************************************
ROMStart:           equ   $00002080
ROMEnd:             equ   $00007FFF
Z_RAMStart:         equ   $00000080
Z_RAMEnd:           equ   $000000FF
RAMStart:           equ   $00000100
RAMEnd:             equ   $000017FF
RAM1Start:          equ   $00001880
RAM1End:            equ   $0000207F
ROM1Start:          equ   $0000C000
ROM1End:            equ   $0000FFAD
PPAGE_0Start:       equ   $00008000
PPAGE_0End:         equ   $0000A07F
PPAGE_2Start:       equ   $00028000
PPAGE_2End:         equ   $0002BFFF
PPAGE_4Start:       equ   $00048000
PPAGE_4End:         equ   $0004BFFF
PPAGE_5Start:       equ   $00058000
PPAGE_5End:         equ   $0005BFFF
PPAGE_6Start:       equ   $00068000
PPAGE_6End:         equ   $0006BFFF
PPAGE_7Start:       equ   $00078000
PPAGE_7End:         equ   $0007BFFF
;
Vtpm3ovf:           equ   $0000FFC0
Vtpm3ch5:           equ   $0000FFC2
Vtpm3ch4:           equ   $0000FFC4
Vtpm3ch3:           equ   $0000FFC6
Vtpm3ch2:           equ   $0000FFC8
Vtpm3ch1:           equ   $0000FFCA
Vtpm3ch0:           equ   $0000FFCC
Vrtc:               equ   $0000FFCE
Vsci2tx:            equ   $0000FFD0
Vsci2rx:            equ   $0000FFD2
Vsci2err:           equ   $0000FFD4
Vacmpx:             equ   $0000FFD6
Vadc:               equ   $0000FFD8
Vkeyboard:          equ   $0000FFDA
Viicx:              equ   $0000FFDC
Vsci1tx:            equ   $0000FFDE
Vsci1rx:            equ   $0000FFE0
Vsci1err:           equ   $0000FFE2
Vspi1:              equ   $0000FFE4
Vspi2:              equ   $0000FFE6
Vtpm2ovf:           equ   $0000FFE8
Vtpm2ch2:           equ   $0000FFEA
Vtpm2ch1:           equ   $0000FFEC
Vtpm2ch0:           equ   $0000FFEE
Vtpm1ovf:           equ   $0000FFF0
Vtpm1ch2:           equ   $0000FFF2
Vtpm1ch1:           equ   $0000FFF4
Vtpm1ch0:           equ   $0000FFF6
Vlvd:               equ   $0000FFF8
Virq:               equ   $0000FFFA
Vswi:               equ   $0000FFFC
Vreset:             equ   $0000FFFE
;


;*** PTAD - Port A Data Register; 0x00000000 ***
PTAD:               equ    $00000000                                ;*** PTAD - Port A Data Register; 0x00000000 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTAD_PTAD0:         equ    0                                         ; Port A Data Register Bit 0
PTAD_PTAD1:         equ    1                                         ; Port A Data Register Bit 1
PTAD_PTAD2:         equ    2                                         ; Port A Data Register Bit 2
PTAD_PTAD3:         equ    3                                         ; Port A Data Register Bit 3
PTAD_PTAD4:         equ    4                                         ; Port A Data Register Bit 4
PTAD_PTAD5:         equ    5                                         ; Port A Data Register Bit 5
PTAD_PTAD6:         equ    6                                         ; Port A Data Register Bit 6
PTAD_PTAD7:         equ    7                                         ; Port A Data Register Bit 7
; bit position masks
mPTAD_PTAD0:        equ    %00000001
mPTAD_PTAD1:        equ    %00000010
mPTAD_PTAD2:        equ    %00000100
mPTAD_PTAD3:        equ    %00001000
mPTAD_PTAD4:        equ    %00010000
mPTAD_PTAD5:        equ    %00100000
mPTAD_PTAD6:        equ    %01000000
mPTAD_PTAD7:        equ    %10000000


;*** PTADD - Port A Data Direction Register; 0x00000001 ***
PTADD:              equ    $00000001                                ;*** PTADD - Port A Data Direction Register; 0x00000001 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTADD_PTADD0:       equ    0                                         ; Data Direction for Port A Bit 0
PTADD_PTADD1:       equ    1                                         ; Data Direction for Port A Bit 1
PTADD_PTADD2:       equ    2                                         ; Data Direction for Port A Bit 2
PTADD_PTADD3:       equ    3                                         ; Data Direction for Port A Bit 3
PTADD_PTADD4:       equ    4                                         ; Data Direction for Port A Bit 4
PTADD_PTADD5:       equ    5                                         ; Data Direction for Port A Bit 5
PTADD_PTADD6:       equ    6                                         ; Data Direction for Port A Bit 6
PTADD_PTADD7:       equ    7                                         ; Data Direction for Port A Bit 7
; bit position masks
mPTADD_PTADD0:      equ    %00000001
mPTADD_PTADD1:      equ    %00000010
mPTADD_PTADD2:      equ    %00000100
mPTADD_PTADD3:      equ    %00001000
mPTADD_PTADD4:      equ    %00010000
mPTADD_PTADD5:      equ    %00100000
mPTADD_PTADD6:      equ    %01000000
mPTADD_PTADD7:      equ    %10000000


;*** PTBD - Port B Data Register; 0x00000002 ***
PTBD:               equ    $00000002                                ;*** PTBD - Port B Data Register; 0x00000002 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTBD_PTBD0:         equ    0                                         ; Port B Data Register Bit 0
PTBD_PTBD1:         equ    1                                         ; Port B Data Register Bit 1
PTBD_PTBD2:         equ    2                                         ; Port B Data Register Bit 2
PTBD_PTBD3:         equ    3                                         ; Port B Data Register Bit 3
PTBD_PTBD4:         equ    4                                         ; Port B Data Register Bit 4
PTBD_PTBD5:         equ    5                                         ; Port B Data Register Bit 5
PTBD_PTBD6:         equ    6                                         ; Port B Data Register Bit 6
PTBD_PTBD7:         equ    7                                         ; Port B Data Register Bit 7
; bit position masks
mPTBD_PTBD0:        equ    %00000001
mPTBD_PTBD1:        equ    %00000010
mPTBD_PTBD2:        equ    %00000100
mPTBD_PTBD3:        equ    %00001000
mPTBD_PTBD4:        equ    %00010000
mPTBD_PTBD5:        equ    %00100000
mPTBD_PTBD6:        equ    %01000000
mPTBD_PTBD7:        equ    %10000000


;*** PTBDD - Port B Data Direction Register; 0x00000003 ***
PTBDD:              equ    $00000003                                ;*** PTBDD - Port B Data Direction Register; 0x00000003 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTBDD_PTBDD0:       equ    0                                         ; Data Direction for Port B Bit 0
PTBDD_PTBDD1:       equ    1                                         ; Data Direction for Port B Bit 1
PTBDD_PTBDD2:       equ    2                                         ; Data Direction for Port B Bit 2
PTBDD_PTBDD3:       equ    3                                         ; Data Direction for Port B Bit 3
PTBDD_PTBDD4:       equ    4                                         ; Data Direction for Port B Bit 4
PTBDD_PTBDD5:       equ    5                                         ; Data Direction for Port B Bit 5
PTBDD_PTBDD6:       equ    6                                         ; Data Direction for Port B Bit 6
PTBDD_PTBDD7:       equ    7                                         ; Data Direction for Port B Bit 7
; bit position masks
mPTBDD_PTBDD0:      equ    %00000001
mPTBDD_PTBDD1:      equ    %00000010
mPTBDD_PTBDD2:      equ    %00000100
mPTBDD_PTBDD3:      equ    %00001000
mPTBDD_PTBDD4:      equ    %00010000
mPTBDD_PTBDD5:      equ    %00100000
mPTBDD_PTBDD6:      equ    %01000000
mPTBDD_PTBDD7:      equ    %10000000


;*** PTCD - Port C Data Register; 0x00000004 ***
PTCD:               equ    $00000004                                ;*** PTCD - Port C Data Register; 0x00000004 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTCD_PTCD0:         equ    0                                         ; Port C Data Register Bit 0
PTCD_PTCD1:         equ    1                                         ; Port C Data Register Bit 1
PTCD_PTCD2:         equ    2                                         ; Port C Data Register Bit 2
PTCD_PTCD3:         equ    3                                         ; Port C Data Register Bit 3
PTCD_PTCD4:         equ    4                                         ; Port C Data Register Bit 4
PTCD_PTCD5:         equ    5                                         ; Port C Data Register Bit 5
PTCD_PTCD6:         equ    6                                         ; Port C Data Register Bit 6
PTCD_PTCD7:         equ    7                                         ; Port C Data Register Bit 7
; bit position masks
mPTCD_PTCD0:        equ    %00000001
mPTCD_PTCD1:        equ    %00000010
mPTCD_PTCD2:        equ    %00000100
mPTCD_PTCD3:        equ    %00001000
mPTCD_PTCD4:        equ    %00010000
mPTCD_PTCD5:        equ    %00100000
mPTCD_PTCD6:        equ    %01000000
mPTCD_PTCD7:        equ    %10000000


;*** PTCDD - Port C Data Direction Register; 0x00000005 ***
PTCDD:              equ    $00000005                                ;*** PTCDD - Port C Data Direction Register; 0x00000005 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTCDD_PTCDD0:       equ    0                                         ; Data Direction for Port C Bit 0
PTCDD_PTCDD1:       equ    1                                         ; Data Direction for Port C Bit 1
PTCDD_PTCDD2:       equ    2                                         ; Data Direction for Port C Bit 2
PTCDD_PTCDD3:       equ    3                                         ; Data Direction for Port C Bit 3
PTCDD_PTCDD4:       equ    4                                         ; Data Direction for Port C Bit 4
PTCDD_PTCDD5:       equ    5                                         ; Data Direction for Port C Bit 5
PTCDD_PTCDD6:       equ    6                                         ; Data Direction for Port C Bit 6
PTCDD_PTCDD7:       equ    7                                         ; Data Direction for Port C Bit 7
; bit position masks
mPTCDD_PTCDD0:      equ    %00000001
mPTCDD_PTCDD1:      equ    %00000010
mPTCDD_PTCDD2:      equ    %00000100
mPTCDD_PTCDD3:      equ    %00001000
mPTCDD_PTCDD4:      equ    %00010000
mPTCDD_PTCDD5:      equ    %00100000
mPTCDD_PTCDD6:      equ    %01000000
mPTCDD_PTCDD7:      equ    %10000000


;*** PTDD - Port D Data Register; 0x00000006 ***
PTDD:               equ    $00000006                                ;*** PTDD - Port D Data Register; 0x00000006 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTDD_PTDD0:         equ    0                                         ; Port D Data Register Bit 0
PTDD_PTDD1:         equ    1                                         ; Port D Data Register Bit 1
PTDD_PTDD2:         equ    2                                         ; Port D Data Register Bit 2
PTDD_PTDD3:         equ    3                                         ; Port D Data Register Bit 3
PTDD_PTDD4:         equ    4                                         ; Port D Data Register Bit 4
PTDD_PTDD5:         equ    5                                         ; Port D Data Register Bit 5
PTDD_PTDD6:         equ    6                                         ; Port D Data Register Bit 6
PTDD_PTDD7:         equ    7                                         ; Port D Data Register Bit 7
; bit position masks
mPTDD_PTDD0:        equ    %00000001
mPTDD_PTDD1:        equ    %00000010
mPTDD_PTDD2:        equ    %00000100
mPTDD_PTDD3:        equ    %00001000
mPTDD_PTDD4:        equ    %00010000
mPTDD_PTDD5:        equ    %00100000
mPTDD_PTDD6:        equ    %01000000
mPTDD_PTDD7:        equ    %10000000


;*** PTDDD - Port D Data Direction Register; 0x00000007 ***
PTDDD:              equ    $00000007                                ;*** PTDDD - Port D Data Direction Register; 0x00000007 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTDDD_PTDDD0:       equ    0                                         ; Data Direction for Port D Bit 0
PTDDD_PTDDD1:       equ    1                                         ; Data Direction for Port D Bit 1
PTDDD_PTDDD2:       equ    2                                         ; Data Direction for Port D Bit 2
PTDDD_PTDDD3:       equ    3                                         ; Data Direction for Port D Bit 3
PTDDD_PTDDD4:       equ    4                                         ; Data Direction for Port D Bit 4
PTDDD_PTDDD5:       equ    5                                         ; Data Direction for Port D Bit 5
PTDDD_PTDDD6:       equ    6                                         ; Data Direction for Port D Bit 6
PTDDD_PTDDD7:       equ    7                                         ; Data Direction for Port D Bit 7
; bit position masks
mPTDDD_PTDDD0:      equ    %00000001
mPTDDD_PTDDD1:      equ    %00000010
mPTDDD_PTDDD2:      equ    %00000100
mPTDDD_PTDDD3:      equ    %00001000
mPTDDD_PTDDD4:      equ    %00010000
mPTDDD_PTDDD5:      equ    %00100000
mPTDDD_PTDDD6:      equ    %01000000
mPTDDD_PTDDD7:      equ    %10000000


;*** PTED - Port E Data Register; 0x00000008 ***
PTED:               equ    $00000008                                ;*** PTED - Port E Data Register; 0x00000008 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTED_PTED0:         equ    0                                         ; Port E Data Register Bit 0
PTED_PTED1:         equ    1                                         ; Port E Data Register Bit 1
PTED_PTED2:         equ    2                                         ; Port E Data Register Bit 2
PTED_PTED3:         equ    3                                         ; Port E Data Register Bit 3
PTED_PTED4:         equ    4                                         ; Port E Data Register Bit 4
PTED_PTED5:         equ    5                                         ; Port E Data Register Bit 5
PTED_PTED6:         equ    6                                         ; Port E Data Register Bit 6
PTED_PTED7:         equ    7                                         ; Port E Data Register Bit 7
; bit position masks
mPTED_PTED0:        equ    %00000001
mPTED_PTED1:        equ    %00000010
mPTED_PTED2:        equ    %00000100
mPTED_PTED3:        equ    %00001000
mPTED_PTED4:        equ    %00010000
mPTED_PTED5:        equ    %00100000
mPTED_PTED6:        equ    %01000000
mPTED_PTED7:        equ    %10000000


;*** PTEDD - Port E Data Direction Register; 0x00000009 ***
PTEDD:              equ    $00000009                                ;*** PTEDD - Port E Data Direction Register; 0x00000009 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTEDD_PTEDD0:       equ    0                                         ; Data Direction for Port E Bit 0
PTEDD_PTEDD1:       equ    1                                         ; Data Direction for Port E Bit 1
PTEDD_PTEDD2:       equ    2                                         ; Data Direction for Port E Bit 2
PTEDD_PTEDD3:       equ    3                                         ; Data Direction for Port E Bit 3
PTEDD_PTEDD4:       equ    4                                         ; Data Direction for Port E Bit 4
PTEDD_PTEDD5:       equ    5                                         ; Data Direction for Port E Bit 5
PTEDD_PTEDD6:       equ    6                                         ; Data Direction for Port E Bit 6
PTEDD_PTEDD7:       equ    7                                         ; Data Direction for Port E Bit 7
; bit position masks
mPTEDD_PTEDD0:      equ    %00000001
mPTEDD_PTEDD1:      equ    %00000010
mPTEDD_PTEDD2:      equ    %00000100
mPTEDD_PTEDD3:      equ    %00001000
mPTEDD_PTEDD4:      equ    %00010000
mPTEDD_PTEDD5:      equ    %00100000
mPTEDD_PTEDD6:      equ    %01000000
mPTEDD_PTEDD7:      equ    %10000000


;*** PTFD - Port F Data Register; 0x0000000A ***
PTFD:               equ    $0000000A                                ;*** PTFD - Port F Data Register; 0x0000000A ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTFD_PTFD0:         equ    0                                         ; Port F Data Register Bit 0
PTFD_PTFD1:         equ    1                                         ; Port F Data Register Bit 1
PTFD_PTFD2:         equ    2                                         ; Port F Data Register Bit 2
PTFD_PTFD3:         equ    3                                         ; Port F Data Register Bit 3
PTFD_PTFD4:         equ    4                                         ; Port F Data Register Bit 4
PTFD_PTFD5:         equ    5                                         ; Port F Data Register Bit 5
PTFD_PTFD6:         equ    6                                         ; Port F Data Register Bit 6
PTFD_PTFD7:         equ    7                                         ; Port F Data Register Bit 7
; bit position masks
mPTFD_PTFD0:        equ    %00000001
mPTFD_PTFD1:        equ    %00000010
mPTFD_PTFD2:        equ    %00000100
mPTFD_PTFD3:        equ    %00001000
mPTFD_PTFD4:        equ    %00010000
mPTFD_PTFD5:        equ    %00100000
mPTFD_PTFD6:        equ    %01000000
mPTFD_PTFD7:        equ    %10000000


;*** PTFDD - Port F Data Direction Register; 0x0000000B ***
PTFDD:              equ    $0000000B                                ;*** PTFDD - Port F Data Direction Register; 0x0000000B ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTFDD_PTFDD0:       equ    0                                         ; Data Direction for Port F Bit 0
PTFDD_PTFDD1:       equ    1                                         ; Data Direction for Port F Bit 1
PTFDD_PTFDD2:       equ    2                                         ; Data Direction for Port F Bit 2
PTFDD_PTFDD3:       equ    3                                         ; Data Direction for Port F Bit 3
PTFDD_PTFDD4:       equ    4                                         ; Data Direction for Port F Bit 4
PTFDD_PTFDD5:       equ    5                                         ; Data Direction for Port F Bit 5
PTFDD_PTFDD6:       equ    6                                         ; Data Direction for Port F Bit 6
PTFDD_PTFDD7:       equ    7                                         ; Data Direction for Port F Bit 7
; bit position masks
mPTFDD_PTFDD0:      equ    %00000001
mPTFDD_PTFDD1:      equ    %00000010
mPTFDD_PTFDD2:      equ    %00000100
mPTFDD_PTFDD3:      equ    %00001000
mPTFDD_PTFDD4:      equ    %00010000
mPTFDD_PTFDD5:      equ    %00100000
mPTFDD_PTFDD6:      equ    %01000000
mPTFDD_PTFDD7:      equ    %10000000


;*** KBI1SC - KBI1 Status and Control Register; 0x0000000C ***
KBI1SC:             equ    $0000000C                                ;*** KBI1SC - KBI1 Status and Control Register; 0x0000000C ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
KBI1SC_KBIMOD:      equ    0                                         ; Keyboard Detection Mode
KBI1SC_KBIE:        equ    1                                         ; Keyboard Interrupt Enable
KBI1SC_KBACK:       equ    2                                         ; Keyboard Interrupt Acknowledge
KBI1SC_KBF:         equ    3                                         ; Keyboard Interrupt Flag
; bit position masks
mKBI1SC_KBIMOD:     equ    %00000001
mKBI1SC_KBIE:       equ    %00000010
mKBI1SC_KBACK:      equ    %00000100
mKBI1SC_KBF:        equ    %00001000


;*** KBI1PE - KBI1 Pin Enable Register; 0x0000000D ***
KBI1PE:             equ    $0000000D                                ;*** KBI1PE - KBI1 Pin Enable Register; 0x0000000D ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
KBI1PE_KBIPE0:      equ    0                                         ; Keyboard Pin Enable for KBI Port Bit 0
KBI1PE_KBIPE1:      equ    1                                         ; Keyboard Pin Enable for KBI Port Bit 1
KBI1PE_KBIPE2:      equ    2                                         ; Keyboard Pin Enable for KBI Port Bit 2
KBI1PE_KBIPE3:      equ    3                                         ; Keyboard Pin Enable for KBI Port Bit 3
KBI1PE_KBIPE4:      equ    4                                         ; Keyboard Pin Enable for KBI Port Bit 4
KBI1PE_KBIPE5:      equ    5                                         ; Keyboard Pin Enable for KBI Port Bit 5
KBI1PE_KBIPE6:      equ    6                                         ; Keyboard Pin Enable for KBI Port Bit 6
KBI1PE_KBIPE7:      equ    7                                         ; Keyboard Pin Enable for KBI Port Bit 7
; bit position masks
mKBI1PE_KBIPE0:     equ    %00000001
mKBI1PE_KBIPE1:     equ    %00000010
mKBI1PE_KBIPE2:     equ    %00000100
mKBI1PE_KBIPE3:     equ    %00001000
mKBI1PE_KBIPE4:     equ    %00010000
mKBI1PE_KBIPE5:     equ    %00100000
mKBI1PE_KBIPE6:     equ    %01000000
mKBI1PE_KBIPE7:     equ    %10000000


;*** KBI1ES - KBI1 Edge Select Register; 0x0000000E ***
KBI1ES:             equ    $0000000E                                ;*** KBI1ES - KBI1 Edge Select Register; 0x0000000E ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
KBI1ES_KBEDG0:      equ    0                                         ; Keyboard Edge Select Bit 0
KBI1ES_KBEDG1:      equ    1                                         ; Keyboard Edge Select Bit 1
KBI1ES_KBEDG2:      equ    2                                         ; Keyboard Edge Select Bit 2
KBI1ES_KBEDG3:      equ    3                                         ; Keyboard Edge Select Bit 3
KBI1ES_KBEDG4:      equ    4                                         ; Keyboard Edge Select Bit 4
KBI1ES_KBEDG5:      equ    5                                         ; Keyboard Edge Select Bit 5
KBI1ES_KBEDG6:      equ    6                                         ; Keyboard Edge Select Bit 6
KBI1ES_KBEDG7:      equ    7                                         ; Keyboard Edge Select Bit 7
; bit position masks
mKBI1ES_KBEDG0:     equ    %00000001
mKBI1ES_KBEDG1:     equ    %00000010
mKBI1ES_KBEDG2:     equ    %00000100
mKBI1ES_KBEDG3:     equ    %00001000
mKBI1ES_KBEDG4:     equ    %00010000
mKBI1ES_KBEDG5:     equ    %00100000
mKBI1ES_KBEDG6:     equ    %01000000
mKBI1ES_KBEDG7:     equ    %10000000


;*** IRQSC - Interrupt request status and control register; 0x0000000F ***
IRQSC:              equ    $0000000F                                ;*** IRQSC - Interrupt request status and control register; 0x0000000F ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
IRQSC_IRQMOD:       equ    0                                         ; IRQ Detection Mode
IRQSC_IRQIE:        equ    1                                         ; IRQ Interrupt Enable
IRQSC_IRQACK:       equ    2                                         ; IRQ Acknowledge
IRQSC_IRQF:         equ    3                                         ; IRQ Flag
IRQSC_IRQPE:        equ    4                                         ; IRQ Pin Enable
IRQSC_IRQEDG:       equ    5                                         ; IRQ Edge Select
IRQSC_IRQPDD:       equ    6                                         ; IRQ Pull Device Disable
; bit position masks
mIRQSC_IRQMOD:      equ    %00000001
mIRQSC_IRQIE:       equ    %00000010
mIRQSC_IRQACK:      equ    %00000100
mIRQSC_IRQF:        equ    %00001000
mIRQSC_IRQPE:       equ    %00010000
mIRQSC_IRQEDG:      equ    %00100000
mIRQSC_IRQPDD:      equ    %01000000


;*** ADCSC1 - Status and Control Register 1; 0x00000010 ***
ADCSC1:             equ    $00000010                                ;*** ADCSC1 - Status and Control Register 1; 0x00000010 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
ADCSC1_ADCH0:       equ    0                                         ; Input Channel Select Bit 0
ADCSC1_ADCH1:       equ    1                                         ; Input Channel Select Bit 1
ADCSC1_ADCH2:       equ    2                                         ; Input Channel Select Bit 2
ADCSC1_ADCH3:       equ    3                                         ; Input Channel Select Bit 3
ADCSC1_ADCH4:       equ    4                                         ; Input Channel Select Bit 4
ADCSC1_ADCO:        equ    5                                         ; Continuous Conversion Enable - ADCO is used to enable continuous conversions
ADCSC1_AIEN:        equ    6                                         ; Interrupt Enable - AIEN is used to enable conversion complete interrupts. When COCO becomes set while AIEN is high, an interrupt is asserted
ADCSC1_COCO:        equ    7                                         ; Conversion Complete Flag - The COCO flag is a read-only bit which is set each time a conversion is completed when the compare function is disabled (ACFE = 0). When the compare function is enabled (ACFE = 1) the COCO flag is set upon completion of a conversion only if the compare result is true. This bit is cleared whenever ADCSC1 is written or whenever ADCRL is read
; bit position masks
mADCSC1_ADCH0:      equ    %00000001
mADCSC1_ADCH1:      equ    %00000010
mADCSC1_ADCH2:      equ    %00000100
mADCSC1_ADCH3:      equ    %00001000
mADCSC1_ADCH4:      equ    %00010000
mADCSC1_ADCO:       equ    %00100000
mADCSC1_AIEN:       equ    %01000000
mADCSC1_COCO:       equ    %10000000


;*** ADCSC2 - Status and Control Register 2; 0x00000011 ***
ADCSC2:             equ    $00000011                                ;*** ADCSC2 - Status and Control Register 2; 0x00000011 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
ADCSC2_ACFGT:       equ    4                                         ; Compare Function Greater Than Enable-ACFGT is used to configure the compare function to trigger when the result of the conversion of the input being monitored is greater than or equal to the compare value. The compare function defaults to triggering when the result of the compare of the input being monitored is less than the compare value
ADCSC2_ACFE:        equ    5                                         ; Compare Function Enable - ACFE is used to enable the compare function
ADCSC2_ADTRG:       equ    6                                         ; Conversion Trigger Select-ADTRG is used to select the type of trigger to be used for initiating a conversion. Two types of trigger are selectable: software trigger and hardware trigger. When software trigger is selected, a conversion is initiated following a write to ADCSC1. When hardware trigger is selected, a conversion is initiated following the assertion of the ADHWT input
ADCSC2_ADACT:       equ    7                                         ; Conversion Active - ADACT indicates that a conversion is in progress. ADACT is set when a conversion is initiated and cleared when a conversion is completed or aborted
; bit position masks
mADCSC2_ACFGT:      equ    %00010000
mADCSC2_ACFE:       equ    %00100000
mADCSC2_ADTRG:      equ    %01000000
mADCSC2_ADACT:      equ    %10000000


;*** ADCR - Data Result Register; 0x00000012 ***
ADCR:               equ    $00000012                                ;*** ADCR - Data Result Register; 0x00000012 ***


;*** ADCRH - Data Result High Register; 0x00000012 ***
ADCRH:              equ    $00000012                                ;*** ADCRH - Data Result High Register; 0x00000012 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
ADCRH_ADR8:         equ    0                                         ; ADC Result Data Bit 8
ADCRH_ADR9:         equ    1                                         ; ADC Result Data Bit 9
ADCRH_ADR10:        equ    2                                         ; ADC Result Data Bit 10
ADCRH_ADR11:        equ    3                                         ; ADC Result Data Bit 11
; bit position masks
mADCRH_ADR8:        equ    %00000001
mADCRH_ADR9:        equ    %00000010
mADCRH_ADR10:       equ    %00000100
mADCRH_ADR11:       equ    %00001000


;*** ADCRL - Data Result Low Register; 0x00000013 ***
ADCRL:              equ    $00000013                                ;*** ADCRL - Data Result Low Register; 0x00000013 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
ADCRL_ADR0:         equ    0                                         ; ADC Result Data Bit 0
ADCRL_ADR1:         equ    1                                         ; ADC Result Data Bit 1
ADCRL_ADR2:         equ    2                                         ; ADC Result Data Bit 2
ADCRL_ADR3:         equ    3                                         ; ADC Result Data Bit 3
ADCRL_ADR4:         equ    4                                         ; ADC Result Data Bit 4
ADCRL_ADR5:         equ    5                                         ; ADC Result Data Bit 5
ADCRL_ADR6:         equ    6                                         ; ADC Result Data Bit 6
ADCRL_ADR7:         equ    7                                         ; ADC Result Data Bit 7
; bit position masks
mADCRL_ADR0:        equ    %00000001
mADCRL_ADR1:        equ    %00000010
mADCRL_ADR2:        equ    %00000100
mADCRL_ADR3:        equ    %00001000
mADCRL_ADR4:        equ    %00010000
mADCRL_ADR5:        equ    %00100000
mADCRL_ADR6:        equ    %01000000
mADCRL_ADR7:        equ    %10000000


;*** ADCCV - Compare Value Register; 0x00000014 ***
ADCCV:              equ    $00000014                                ;*** ADCCV - Compare Value Register; 0x00000014 ***


;*** ADCCVH - Compare Value High Register; 0x00000014 ***
ADCCVH:             equ    $00000014                                ;*** ADCCVH - Compare Value High Register; 0x00000014 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
ADCCVH_ADCV8:       equ    0                                         ; Compare Function Value 8
ADCCVH_ADCV9:       equ    1                                         ; Compare Function Value 9
ADCCVH_ADCV10:      equ    2                                         ; Compare Function Value 10
ADCCVH_ADCV11:      equ    3                                         ; Compare Function Value 11
; bit position masks
mADCCVH_ADCV8:      equ    %00000001
mADCCVH_ADCV9:      equ    %00000010
mADCCVH_ADCV10:     equ    %00000100
mADCCVH_ADCV11:     equ    %00001000


;*** ADCCVL - Compare Value Low Register; 0x00000015 ***
ADCCVL:             equ    $00000015                                ;*** ADCCVL - Compare Value Low Register; 0x00000015 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
ADCCVL_ADCV0:       equ    0                                         ; Compare Function Value 0
ADCCVL_ADCV1:       equ    1                                         ; Compare Function Value 1
ADCCVL_ADCV2:       equ    2                                         ; Compare Function Value 2
ADCCVL_ADCV3:       equ    3                                         ; Compare Function Value 3
ADCCVL_ADCV4:       equ    4                                         ; Compare Function Value 4
ADCCVL_ADCV5:       equ    5                                         ; Compare Function Value 5
ADCCVL_ADCV6:       equ    6                                         ; Compare Function Value 6
ADCCVL_ADCV7:       equ    7                                         ; Compare Function Value 7
; bit position masks
mADCCVL_ADCV0:      equ    %00000001
mADCCVL_ADCV1:      equ    %00000010
mADCCVL_ADCV2:      equ    %00000100
mADCCVL_ADCV3:      equ    %00001000
mADCCVL_ADCV4:      equ    %00010000
mADCCVL_ADCV5:      equ    %00100000
mADCCVL_ADCV6:      equ    %01000000
mADCCVL_ADCV7:      equ    %10000000


;*** ADCCFG - Configuration Register; 0x00000016 ***
ADCCFG:             equ    $00000016                                ;*** ADCCFG - Configuration Register; 0x00000016 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
ADCCFG_ADICLK0:     equ    0                                         ; Input Clock Select Bit 0
ADCCFG_ADICLK1:     equ    1                                         ; Input Clock Select Bit 1
ADCCFG_MODE0:       equ    2                                         ; Conversion Mode Selection Bit 0
ADCCFG_MODE1:       equ    3                                         ; Conversion Mode Selection Bit 1
ADCCFG_ADLSMP:      equ    4                                         ; Long Sample Time Configuration
ADCCFG_ADIV0:       equ    5                                         ; Clock Divide Select Bit 0
ADCCFG_ADIV1:       equ    6                                         ; Clock Divide Select Bit 1
ADCCFG_ADLPC:       equ    7                                         ; Low Power Configuration
; bit position masks
mADCCFG_ADICLK0:    equ    %00000001
mADCCFG_ADICLK1:    equ    %00000010
mADCCFG_MODE0:      equ    %00000100
mADCCFG_MODE1:      equ    %00001000
mADCCFG_ADLSMP:     equ    %00010000
mADCCFG_ADIV0:      equ    %00100000
mADCCFG_ADIV1:      equ    %01000000
mADCCFG_ADLPC:      equ    %10000000


;*** APCTL1 - Pin Control 1 Register; 0x00000017 ***
APCTL1:             equ    $00000017                                ;*** APCTL1 - Pin Control 1 Register; 0x00000017 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
APCTL1_ADPC0:       equ    0                                         ; ADC Pin Control 0 - ADPC0 is used to control the pin associated with channel AD0
APCTL1_ADPC1:       equ    1                                         ; ADC Pin Control 1 - ADPC1 is used to control the pin associated with channel AD1
APCTL1_ADPC2:       equ    2                                         ; ADC Pin Control 2 - ADPC2 is used to control the pin associated with channel AD2
APCTL1_ADPC3:       equ    3                                         ; ADC Pin Control 3 - ADPC3 is used to control the pin associated with channel AD3
APCTL1_ADPC4:       equ    4                                         ; ADC Pin Control 4 - ADPC4 is used to control the pin associated with channel AD4
APCTL1_ADPC5:       equ    5                                         ; ADC Pin Control 5 - ADPC5 is used to control the pin associated with channel AD5
APCTL1_ADPC6:       equ    6                                         ; ADC Pin Control 6 - ADPC6 is used to control the pin associated with channel AD6
APCTL1_ADPC7:       equ    7                                         ; ADC Pin Control 7 - ADPC7 is used to control the pin associated with channel AD7
; bit position masks
mAPCTL1_ADPC0:      equ    %00000001
mAPCTL1_ADPC1:      equ    %00000010
mAPCTL1_ADPC2:      equ    %00000100
mAPCTL1_ADPC3:      equ    %00001000
mAPCTL1_ADPC4:      equ    %00010000
mAPCTL1_ADPC5:      equ    %00100000
mAPCTL1_ADPC6:      equ    %01000000
mAPCTL1_ADPC7:      equ    %10000000


;*** APCTL2 - Pin Control 2 Register; 0x00000018 ***
APCTL2:             equ    $00000018                                ;*** APCTL2 - Pin Control 2 Register; 0x00000018 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
APCTL2_ADPC8:       equ    0                                         ; ADC Pin Control 8 - ADPC8 is used to control the pin associated with channel AD8
APCTL2_ADPC9:       equ    1                                         ; ADC Pin Control 9 - ADPC9 is used to control the pin associated with channel AD9
APCTL2_ADPC10:      equ    2                                         ; ADC Pin Control 10 - ADPC10 is used to control the pin associated with channel AD10
APCTL2_ADPC11:      equ    3                                         ; ADC Pin Control 11 - ADPC11 is used to control the pin associated with channel AD11
APCTL2_ADPC12:      equ    4                                         ; ADC Pin Control 12 - ADPC12 is used to control the pin associated with channel AD12
APCTL2_ADPC13:      equ    5                                         ; ADC Pin Control 13 - ADPC13 is used to control the pin associated with channel AD13
APCTL2_ADPC14:      equ    6                                         ; ADC Pin Control 14 - ADPC14 is used to control the pin associated with channel AD14
APCTL2_ADPC15:      equ    7                                         ; ADC Pin Control 15 - ADPC15 is used to control the pin associated with channel AD15
; bit position masks
mAPCTL2_ADPC8:      equ    %00000001
mAPCTL2_ADPC9:      equ    %00000010
mAPCTL2_ADPC10:     equ    %00000100
mAPCTL2_ADPC11:     equ    %00001000
mAPCTL2_ADPC12:     equ    %00010000
mAPCTL2_ADPC13:     equ    %00100000
mAPCTL2_ADPC14:     equ    %01000000
mAPCTL2_ADPC15:     equ    %10000000


;*** APCTL3 - Pin Control 3 Register; 0x00000019 ***
APCTL3:             equ    $00000019                                ;*** APCTL3 - Pin Control 3 Register; 0x00000019 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
APCTL3_ADPC16:      equ    0                                         ; ADC Pin Control 16 - ADPC16 is used to control the pin associated with channel AD16
APCTL3_ADPC17:      equ    1                                         ; ADC Pin Control 17 - ADPC17 is used to control the pin associated with channel AD17
APCTL3_ADPC18:      equ    2                                         ; ADC Pin Control 18 - ADPC18 is used to control the pin associated with channel AD18
APCTL3_ADPC19:      equ    3                                         ; ADC Pin Control 19 - ADPC19 is used to control the pin associated with channel AD19
APCTL3_ADPC20:      equ    4                                         ; ADC Pin Control 20 - ADPC20 is used to control the pin associated with channel AD20
APCTL3_ADPC21:      equ    5                                         ; ADC Pin Control 21 - ADPC21 is used to control the pin associated with channel AD21
APCTL3_ADPC22:      equ    6                                         ; ADC Pin Control 22 - ADPC22 is used to control the pin associated with channel AD22
APCTL3_ADPC23:      equ    7                                         ; ADC Pin Control 23 - ADPC23 is used to control the pin associated with channel AD23
; bit position masks
mAPCTL3_ADPC16:     equ    %00000001
mAPCTL3_ADPC17:     equ    %00000010
mAPCTL3_ADPC18:     equ    %00000100
mAPCTL3_ADPC19:     equ    %00001000
mAPCTL3_ADPC20:     equ    %00010000
mAPCTL3_ADPC21:     equ    %00100000
mAPCTL3_ADPC22:     equ    %01000000
mAPCTL3_ADPC23:     equ    %10000000


;*** ACMP1SC - ACMP1 Status and Control Register; 0x0000001A ***
ACMP1SC:            equ    $0000001A                                ;*** ACMP1SC - ACMP1 Status and Control Register; 0x0000001A ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
ACMP1SC_ACMOD0:     equ    0                                         ; Analog Comparator Mode Bit 0
ACMP1SC_ACMOD1:     equ    1                                         ; Analog Comparator Mode Bit 1
ACMP1SC_ACOPE:      equ    2                                         ; Analog Comparator Output Pin Enable
ACMP1SC_ACO:        equ    3                                         ; Analog Comparator Output
ACMP1SC_ACIE:       equ    4                                         ; Analog Comparator Interrupt Enable
ACMP1SC_ACF:        equ    5                                         ; Analog Comparator Flag
ACMP1SC_ACBGS:      equ    6                                         ; Analog Comparator Bandgap Select
ACMP1SC_ACME:       equ    7                                         ; Analog Comparator Module Enable
; bit position masks
mACMP1SC_ACMOD0:    equ    %00000001
mACMP1SC_ACMOD1:    equ    %00000010
mACMP1SC_ACOPE:     equ    %00000100
mACMP1SC_ACO:       equ    %00001000
mACMP1SC_ACIE:      equ    %00010000
mACMP1SC_ACF:       equ    %00100000
mACMP1SC_ACBGS:     equ    %01000000
mACMP1SC_ACME:      equ    %10000000


;*** ACMP2SC - ACMP2 Status and Control Register; 0x0000001B ***
ACMP2SC:            equ    $0000001B                                ;*** ACMP2SC - ACMP2 Status and Control Register; 0x0000001B ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
ACMP2SC_ACMOD0:     equ    0                                         ; Analog Comparator Mode Bit 0
ACMP2SC_ACMOD1:     equ    1                                         ; Analog Comparator Mode Bit 1
ACMP2SC_ACOPE:      equ    2                                         ; Analog Comparator Output Pin Enable
ACMP2SC_ACO:        equ    3                                         ; Analog Comparator Output
ACMP2SC_ACIE:       equ    4                                         ; Analog Comparator Interrupt Enable
ACMP2SC_ACF:        equ    5                                         ; Analog Comparator Flag
ACMP2SC_ACBGS:      equ    6                                         ; Analog Comparator Bandgap Select
ACMP2SC_ACME:       equ    7                                         ; Analog Comparator Module Enable
; bit position masks
mACMP2SC_ACMOD0:    equ    %00000001
mACMP2SC_ACMOD1:    equ    %00000010
mACMP2SC_ACOPE:     equ    %00000100
mACMP2SC_ACO:       equ    %00001000
mACMP2SC_ACIE:      equ    %00010000
mACMP2SC_ACF:       equ    %00100000
mACMP2SC_ACBGS:     equ    %01000000
mACMP2SC_ACME:      equ    %10000000


;*** PTGD - Port G Data Register; 0x0000001C ***
PTGD:               equ    $0000001C                                ;*** PTGD - Port G Data Register; 0x0000001C ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTGD_PTGD0:         equ    0                                         ; Port G Data Register Bit 0
PTGD_PTGD1:         equ    1                                         ; Port G Data Register Bit 1
PTGD_PTGD2:         equ    2                                         ; Port G Data Register Bit 2
PTGD_PTGD3:         equ    3                                         ; Port G Data Register Bit 3
PTGD_PTGD4:         equ    4                                         ; Port G Data Register Bit 4
PTGD_PTGD5:         equ    5                                         ; Port G Data Register Bit 5
PTGD_PTGD6:         equ    6                                         ; Port G Data Register Bit 6
PTGD_PTGD7:         equ    7                                         ; Port G Data Register Bit 7
; bit position masks
mPTGD_PTGD0:        equ    %00000001
mPTGD_PTGD1:        equ    %00000010
mPTGD_PTGD2:        equ    %00000100
mPTGD_PTGD3:        equ    %00001000
mPTGD_PTGD4:        equ    %00010000
mPTGD_PTGD5:        equ    %00100000
mPTGD_PTGD6:        equ    %01000000
mPTGD_PTGD7:        equ    %10000000


;*** PTGDD - Port G Data Direction Register; 0x0000001D ***
PTGDD:              equ    $0000001D                                ;*** PTGDD - Port G Data Direction Register; 0x0000001D ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTGDD_PTGDD0:       equ    0                                         ; Data Direction for Port G Bit 0
PTGDD_PTGDD1:       equ    1                                         ; Data Direction for Port G Bit 1
PTGDD_PTGDD2:       equ    2                                         ; Data Direction for Port G Bit 2
PTGDD_PTGDD3:       equ    3                                         ; Data Direction for Port G Bit 3
PTGDD_PTGDD4:       equ    4                                         ; Data Direction for Port G Bit 4
PTGDD_PTGDD5:       equ    5                                         ; Data Direction for Port G Bit 5
PTGDD_PTGDD6:       equ    6                                         ; Data Direction for Port G Bit 6
PTGDD_PTGDD7:       equ    7                                         ; Data Direction for Port G Bit 7
; bit position masks
mPTGDD_PTGDD0:      equ    %00000001
mPTGDD_PTGDD1:      equ    %00000010
mPTGDD_PTGDD2:      equ    %00000100
mPTGDD_PTGDD3:      equ    %00001000
mPTGDD_PTGDD4:      equ    %00010000
mPTGDD_PTGDD5:      equ    %00100000
mPTGDD_PTGDD6:      equ    %01000000
mPTGDD_PTGDD7:      equ    %10000000


;*** PTHD - Port H Data Register; 0x0000001E ***
PTHD:               equ    $0000001E                                ;*** PTHD - Port H Data Register; 0x0000001E ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTHD_PTHD0:         equ    0                                         ; Port H Data Register Bit 0
PTHD_PTHD1:         equ    1                                         ; Port H Data Register Bit 1
PTHD_PTHD2:         equ    2                                         ; Port H Data Register Bit 2
PTHD_PTHD3:         equ    3                                         ; Port H Data Register Bit 3
PTHD_PTHD4:         equ    4                                         ; Port H Data Register Bit 4
PTHD_PTHD5:         equ    5                                         ; Port H Data Register Bit 5
PTHD_PTHD6:         equ    6                                         ; Port H Data Register Bit 6
PTHD_PTHD7:         equ    7                                         ; Port H Data Register Bit 7
; bit position masks
mPTHD_PTHD0:        equ    %00000001
mPTHD_PTHD1:        equ    %00000010
mPTHD_PTHD2:        equ    %00000100
mPTHD_PTHD3:        equ    %00001000
mPTHD_PTHD4:        equ    %00010000
mPTHD_PTHD5:        equ    %00100000
mPTHD_PTHD6:        equ    %01000000
mPTHD_PTHD7:        equ    %10000000


;*** PTHDD - Port H Data Direction Register; 0x0000001F ***
PTHDD:              equ    $0000001F                                ;*** PTHDD - Port H Data Direction Register; 0x0000001F ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTHDD_PTHDD0:       equ    0                                         ; Data Direction for Port H Bit 0
PTHDD_PTHDD1:       equ    1                                         ; Data Direction for Port H Bit 1
PTHDD_PTHDD2:       equ    2                                         ; Data Direction for Port H Bit 2
PTHDD_PTHDD3:       equ    3                                         ; Data Direction for Port H Bit 3
PTHDD_PTHDD4:       equ    4                                         ; Data Direction for Port H Bit 4
PTHDD_PTHDD5:       equ    5                                         ; Data Direction for Port H Bit 5
PTHDD_PTHDD6:       equ    6                                         ; Data Direction for Port H Bit 6
PTHDD_PTHDD7:       equ    7                                         ; Data Direction for Port H Bit 7
; bit position masks
mPTHDD_PTHDD0:      equ    %00000001
mPTHDD_PTHDD1:      equ    %00000010
mPTHDD_PTHDD2:      equ    %00000100
mPTHDD_PTHDD3:      equ    %00001000
mPTHDD_PTHDD4:      equ    %00010000
mPTHDD_PTHDD5:      equ    %00100000
mPTHDD_PTHDD6:      equ    %01000000
mPTHDD_PTHDD7:      equ    %10000000


;*** SCI1BD - SCI1 Baud Rate Register; 0x00000020 ***
SCI1BD:             equ    $00000020                                ;*** SCI1BD - SCI1 Baud Rate Register; 0x00000020 ***


;*** SCI1BDH - SCI1 Baud Rate Register High; 0x00000020 ***
SCI1BDH:            equ    $00000020                                ;*** SCI1BDH - SCI1 Baud Rate Register High; 0x00000020 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SCI1BDH_SBR8:       equ    0                                         ; Baud Rate Modulo Divisor Bit 8
SCI1BDH_SBR9:       equ    1                                         ; Baud Rate Modulo Divisor Bit 9
SCI1BDH_SBR10:      equ    2                                         ; Baud Rate Modulo Divisor Bit 10
SCI1BDH_SBR11:      equ    3                                         ; Baud Rate Modulo Divisor Bit 11
SCI1BDH_SBR12:      equ    4                                         ; Baud Rate Modulo Divisor Bit 12
SCI1BDH_RXEDGIE:    equ    6                                         ; RxD Input Active Edge Interrupt Enable (for RXEDGIF)
SCI1BDH_LBKDIE:     equ    7                                         ; LIN Break Detect Interrupt Enable (for LBKDIF)
; bit position masks
mSCI1BDH_SBR8:      equ    %00000001
mSCI1BDH_SBR9:      equ    %00000010
mSCI1BDH_SBR10:     equ    %00000100
mSCI1BDH_SBR11:     equ    %00001000
mSCI1BDH_SBR12:     equ    %00010000
mSCI1BDH_RXEDGIE:   equ    %01000000
mSCI1BDH_LBKDIE:    equ    %10000000


;*** SCI1BDL - SCI1 Baud Rate Register Low; 0x00000021 ***
SCI1BDL:            equ    $00000021                                ;*** SCI1BDL - SCI1 Baud Rate Register Low; 0x00000021 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SCI1BDL_SBR0:       equ    0                                         ; Baud Rate Modulo Divisor Bit 0
SCI1BDL_SBR1:       equ    1                                         ; Baud Rate Modulo Divisor Bit 1
SCI1BDL_SBR2:       equ    2                                         ; Baud Rate Modulo Divisor Bit 2
SCI1BDL_SBR3:       equ    3                                         ; Baud Rate Modulo Divisor Bit 3
SCI1BDL_SBR4:       equ    4                                         ; Baud Rate Modulo Divisor Bit 4
SCI1BDL_SBR5:       equ    5                                         ; Baud Rate Modulo Divisor Bit 5
SCI1BDL_SBR6:       equ    6                                         ; Baud Rate Modulo Divisor Bit 6
SCI1BDL_SBR7:       equ    7                                         ; Baud Rate Modulo Divisor Bit 7
; bit position masks
mSCI1BDL_SBR0:      equ    %00000001
mSCI1BDL_SBR1:      equ    %00000010
mSCI1BDL_SBR2:      equ    %00000100
mSCI1BDL_SBR3:      equ    %00001000
mSCI1BDL_SBR4:      equ    %00010000
mSCI1BDL_SBR5:      equ    %00100000
mSCI1BDL_SBR6:      equ    %01000000
mSCI1BDL_SBR7:      equ    %10000000


;*** SCI1C1 - SCI1 Control Register 1; 0x00000022 ***
SCI1C1:             equ    $00000022                                ;*** SCI1C1 - SCI1 Control Register 1; 0x00000022 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SCI1C1_PT:          equ    0                                         ; Parity Type
SCI1C1_PE:          equ    1                                         ; Parity Enable
SCI1C1_ILT:         equ    2                                         ; Idle Line Type Select
SCI1C1_WAKE:        equ    3                                         ; Receiver Wakeup Method Select
SCI1C1_M:           equ    4                                         ; 9-Bit or 8-Bit Mode Select
SCI1C1_RSRC:        equ    5                                         ; Receiver Source Select
SCI1C1_SCISWAI:     equ    6                                         ; SCI Stops in Wait Mode
SCI1C1_LOOPS:       equ    7                                         ; Loop Mode Select
; bit position masks
mSCI1C1_PT:         equ    %00000001
mSCI1C1_PE:         equ    %00000010
mSCI1C1_ILT:        equ    %00000100
mSCI1C1_WAKE:       equ    %00001000
mSCI1C1_M:          equ    %00010000
mSCI1C1_RSRC:       equ    %00100000
mSCI1C1_SCISWAI:    equ    %01000000
mSCI1C1_LOOPS:      equ    %10000000


;*** SCI1C2 - SCI1 Control Register 2; 0x00000023 ***
SCI1C2:             equ    $00000023                                ;*** SCI1C2 - SCI1 Control Register 2; 0x00000023 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SCI1C2_SBK:         equ    0                                         ; Send Break
SCI1C2_RWU:         equ    1                                         ; Receiver Wakeup Control
SCI1C2_RE:          equ    2                                         ; Receiver Enable
SCI1C2_TE:          equ    3                                         ; Transmitter Enable
SCI1C2_ILIE:        equ    4                                         ; Idle Line Interrupt Enable (for IDLE)
SCI1C2_RIE:         equ    5                                         ; Receiver Interrupt Enable (for RDRF)
SCI1C2_TCIE:        equ    6                                         ; Transmission Complete Interrupt Enable (for TC)
SCI1C2_TIE:         equ    7                                         ; Transmit Interrupt Enable (for TDRE)
; bit position masks
mSCI1C2_SBK:        equ    %00000001
mSCI1C2_RWU:        equ    %00000010
mSCI1C2_RE:         equ    %00000100
mSCI1C2_TE:         equ    %00001000
mSCI1C2_ILIE:       equ    %00010000
mSCI1C2_RIE:        equ    %00100000
mSCI1C2_TCIE:       equ    %01000000
mSCI1C2_TIE:        equ    %10000000


;*** SCI1S1 - SCI1 Status Register 1; 0x00000024 ***
SCI1S1:             equ    $00000024                                ;*** SCI1S1 - SCI1 Status Register 1; 0x00000024 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SCI1S1_PF:          equ    0                                         ; Parity Error Flag
SCI1S1_FE:          equ    1                                         ; Framing Error Flag
SCI1S1_NF:          equ    2                                         ; Noise Flag
SCI1S1_OR:          equ    3                                         ; Receiver Overrun Flag
SCI1S1_IDLE:        equ    4                                         ; Idle Line Flag
SCI1S1_RDRF:        equ    5                                         ; Receive Data Register Full Flag
SCI1S1_TC:          equ    6                                         ; Transmission Complete Flag
SCI1S1_TDRE:        equ    7                                         ; Transmit Data Register Empty Flag
; bit position masks
mSCI1S1_PF:         equ    %00000001
mSCI1S1_FE:         equ    %00000010
mSCI1S1_NF:         equ    %00000100
mSCI1S1_OR:         equ    %00001000
mSCI1S1_IDLE:       equ    %00010000
mSCI1S1_RDRF:       equ    %00100000
mSCI1S1_TC:         equ    %01000000
mSCI1S1_TDRE:       equ    %10000000


;*** SCI1S2 - SCI1 Status Register 2; 0x00000025 ***
SCI1S2:             equ    $00000025                                ;*** SCI1S2 - SCI1 Status Register 2; 0x00000025 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SCI1S2_RAF:         equ    0                                         ; Receiver Active Flag
SCI1S2_LBKDE:       equ    1                                         ; LIN Break Detection Enable
SCI1S2_BRK13:       equ    2                                         ; Break Character Generation Length
SCI1S2_RWUID:       equ    3                                         ; Receive Wake Up Idle Detect
SCI1S2_RXINV:       equ    4                                         ; Receive Data Inversion
SCI1S2_RXEDGIF:     equ    6                                         ; RxD Pin Active Edge Interrupt Flag
SCI1S2_LBKDIF:      equ    7                                         ; LIN Break Detect Interrupt Flag
; bit position masks
mSCI1S2_RAF:        equ    %00000001
mSCI1S2_LBKDE:      equ    %00000010
mSCI1S2_BRK13:      equ    %00000100
mSCI1S2_RWUID:      equ    %00001000
mSCI1S2_RXINV:      equ    %00010000
mSCI1S2_RXEDGIF:    equ    %01000000
mSCI1S2_LBKDIF:     equ    %10000000


;*** SCI1C3 - SCI1 Control Register 3; 0x00000026 ***
SCI1C3:             equ    $00000026                                ;*** SCI1C3 - SCI1 Control Register 3; 0x00000026 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SCI1C3_PEIE:        equ    0                                         ; Parity Error Interrupt Enable
SCI1C3_FEIE:        equ    1                                         ; Framing Error Interrupt Enable
SCI1C3_NEIE:        equ    2                                         ; Noise Error Interrupt Enable
SCI1C3_ORIE:        equ    3                                         ; Overrun Interrupt Enable
SCI1C3_TXINV:       equ    4                                         ; Transmit Data Inversion
SCI1C3_TXDIR:       equ    5                                         ; TxD Pin Direction in Single-Wire Mode
SCI1C3_T8:          equ    6                                         ; Ninth Data Bit for Transmitter
SCI1C3_R8:          equ    7                                         ; Ninth Data Bit for Receiver
; bit position masks
mSCI1C3_PEIE:       equ    %00000001
mSCI1C3_FEIE:       equ    %00000010
mSCI1C3_NEIE:       equ    %00000100
mSCI1C3_ORIE:       equ    %00001000
mSCI1C3_TXINV:      equ    %00010000
mSCI1C3_TXDIR:      equ    %00100000
mSCI1C3_T8:         equ    %01000000
mSCI1C3_R8:         equ    %10000000


;*** SCI1D - SCI1 Data Register; 0x00000027 ***
SCI1D:              equ    $00000027                                ;*** SCI1D - SCI1 Data Register; 0x00000027 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SCI1D_R0_T0:        equ    0                                         ; Receive/Transmit Data Bit 0
SCI1D_R1_T1:        equ    1                                         ; Receive/Transmit Data Bit 1
SCI1D_R2_T2:        equ    2                                         ; Receive/Transmit Data Bit 2
SCI1D_R3_T3:        equ    3                                         ; Receive/Transmit Data Bit 3
SCI1D_R4_T4:        equ    4                                         ; Receive/Transmit Data Bit 4
SCI1D_R5_T5:        equ    5                                         ; Receive/Transmit Data Bit 5
SCI1D_R6_T6:        equ    6                                         ; Receive/Transmit Data Bit 6
SCI1D_R7_T7:        equ    7                                         ; Receive/Transmit Data Bit 7
; bit position masks
mSCI1D_R0_T0:       equ    %00000001
mSCI1D_R1_T1:       equ    %00000010
mSCI1D_R2_T2:       equ    %00000100
mSCI1D_R3_T3:       equ    %00001000
mSCI1D_R4_T4:       equ    %00010000
mSCI1D_R5_T5:       equ    %00100000
mSCI1D_R6_T6:       equ    %01000000
mSCI1D_R7_T7:       equ    %10000000


;*** SPI1C1 - SPI1 Control Register 1; 0x00000028 ***
SPI1C1:             equ    $00000028                                ;*** SPI1C1 - SPI1 Control Register 1; 0x00000028 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SPI1C1_LSBFE:       equ    0                                         ; LSB First (Shifter Direction)
SPI1C1_SSOE:        equ    1                                         ; Slave Select Output Enable
SPI1C1_CPHA:        equ    2                                         ; Clock Phase
SPI1C1_CPOL:        equ    3                                         ; Clock Polarity
SPI1C1_MSTR:        equ    4                                         ; Master/Slave Mode Select
SPI1C1_SPTIE:       equ    5                                         ; SPI Transmit Interrupt Enable
SPI1C1_SPE:         equ    6                                         ; SPI System Enable
SPI1C1_SPIE:        equ    7                                         ; SPI Interrupt Enable (for SPRF and MODF)
; bit position masks
mSPI1C1_LSBFE:      equ    %00000001
mSPI1C1_SSOE:       equ    %00000010
mSPI1C1_CPHA:       equ    %00000100
mSPI1C1_CPOL:       equ    %00001000
mSPI1C1_MSTR:       equ    %00010000
mSPI1C1_SPTIE:      equ    %00100000
mSPI1C1_SPE:        equ    %01000000
mSPI1C1_SPIE:       equ    %10000000


;*** SPI1C2 - SPI1 Control Register 2; 0x00000029 ***
SPI1C2:             equ    $00000029                                ;*** SPI1C2 - SPI1 Control Register 2; 0x00000029 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SPI1C2_SPC0:        equ    0                                         ; SPI Pin Control 0
SPI1C2_SPISWAI:     equ    1                                         ; SPI Stop in Wait Mode
SPI1C2_BIDIROE:     equ    3                                         ; Bidirectional Mode Output Enable
SPI1C2_MODFEN:      equ    4                                         ; Master Mode-Fault Function Enable
; bit position masks
mSPI1C2_SPC0:       equ    %00000001
mSPI1C2_SPISWAI:    equ    %00000010
mSPI1C2_BIDIROE:    equ    %00001000
mSPI1C2_MODFEN:     equ    %00010000


;*** SPI1BR - SPI1 Baud Rate Register; 0x0000002A ***
SPI1BR:             equ    $0000002A                                ;*** SPI1BR - SPI1 Baud Rate Register; 0x0000002A ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SPI1BR_SPR0:        equ    0                                         ; SPI Baud Rate Divisor Bit 0
SPI1BR_SPR1:        equ    1                                         ; SPI Baud Rate Divisor Bit 1
SPI1BR_SPR2:        equ    2                                         ; SPI Baud Rate Divisor Bit 2
SPI1BR_SPPR0:       equ    4                                         ; SPI Baud Rate Prescale Divisor Bit 0
SPI1BR_SPPR1:       equ    5                                         ; SPI Baud Rate Prescale Divisor Bit 1
SPI1BR_SPPR2:       equ    6                                         ; SPI Baud Rate Prescale Divisor Bit 2
; bit position masks
mSPI1BR_SPR0:       equ    %00000001
mSPI1BR_SPR1:       equ    %00000010
mSPI1BR_SPR2:       equ    %00000100
mSPI1BR_SPPR0:      equ    %00010000
mSPI1BR_SPPR1:      equ    %00100000
mSPI1BR_SPPR2:      equ    %01000000


;*** SPI1S - SPI1 Status Register; 0x0000002B ***
SPI1S:              equ    $0000002B                                ;*** SPI1S - SPI1 Status Register; 0x0000002B ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SPI1S_MODF:         equ    4                                         ; Master Mode Fault Flag
SPI1S_SPTEF:        equ    5                                         ; SPI Transmit Buffer Empty Flag
SPI1S_SPRF:         equ    7                                         ; SPI Read Buffer Full Flag
; bit position masks
mSPI1S_MODF:        equ    %00010000
mSPI1S_SPTEF:       equ    %00100000
mSPI1S_SPRF:        equ    %10000000


;*** SPI1D - SPI1 Data Register; 0x0000002D ***
SPI1D:              equ    $0000002D                                ;*** SPI1D - SPI1 Data Register; 0x0000002D ***


;*** PTJD - Port J Data Register; 0x0000002E ***
PTJD:               equ    $0000002E                                ;*** PTJD - Port J Data Register; 0x0000002E ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTJD_PTJD0:         equ    0                                         ; Port J Data Register Bit 0
PTJD_PTJD1:         equ    1                                         ; Port J Data Register Bit 1
PTJD_PTJD2:         equ    2                                         ; Port J Data Register Bit 2
PTJD_PTJD3:         equ    3                                         ; Port J Data Register Bit 3
PTJD_PTJD4:         equ    4                                         ; Port J Data Register Bit 4
PTJD_PTJD5:         equ    5                                         ; Port J Data Register Bit 5
PTJD_PTJD6:         equ    6                                         ; Port J Data Register Bit 6
PTJD_PTJD7:         equ    7                                         ; Port J Data Register Bit 7
; bit position masks
mPTJD_PTJD0:        equ    %00000001
mPTJD_PTJD1:        equ    %00000010
mPTJD_PTJD2:        equ    %00000100
mPTJD_PTJD3:        equ    %00001000
mPTJD_PTJD4:        equ    %00010000
mPTJD_PTJD5:        equ    %00100000
mPTJD_PTJD6:        equ    %01000000
mPTJD_PTJD7:        equ    %10000000


;*** PTJDD - Port J Data Direction Register; 0x0000002F ***
PTJDD:              equ    $0000002F                                ;*** PTJDD - Port J Data Direction Register; 0x0000002F ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTJDD_PTJDD0:       equ    0                                         ; Data Direction for Port J Bit 0
PTJDD_PTJDD1:       equ    1                                         ; Data Direction for Port J Bit 1
PTJDD_PTJDD2:       equ    2                                         ; Data Direction for Port J Bit 2
PTJDD_PTJDD3:       equ    3                                         ; Data Direction for Port J Bit 3
PTJDD_PTJDD4:       equ    4                                         ; Data Direction for Port J Bit 4
PTJDD_PTJDD5:       equ    5                                         ; Data Direction for Port J Bit 5
PTJDD_PTJDD6:       equ    6                                         ; Data Direction for Port J Bit 6
PTJDD_PTJDD7:       equ    7                                         ; Data Direction for Port J Bit 7
; bit position masks
mPTJDD_PTJDD0:      equ    %00000001
mPTJDD_PTJDD1:      equ    %00000010
mPTJDD_PTJDD2:      equ    %00000100
mPTJDD_PTJDD3:      equ    %00001000
mPTJDD_PTJDD4:      equ    %00010000
mPTJDD_PTJDD5:      equ    %00100000
mPTJDD_PTJDD6:      equ    %01000000
mPTJDD_PTJDD7:      equ    %10000000


;*** IIC1A - IIC Address Register; 0x00000030 ***
IIC1A:              equ    $00000030                                ;*** IIC1A - IIC Address Register; 0x00000030 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
IIC1A_AD1:          equ    1                                         ; Slave Address Bit 1
IIC1A_AD2:          equ    2                                         ; Slave Address Bit 2
IIC1A_AD3:          equ    3                                         ; Slave Address Bit 3
IIC1A_AD4:          equ    4                                         ; Slave Address Bit 4
IIC1A_AD5:          equ    5                                         ; Slave Address Bit 5
IIC1A_AD6:          equ    6                                         ; Slave Address Bit 6
IIC1A_AD7:          equ    7                                         ; Slave Address Bit 7
; bit position masks
mIIC1A_AD1:         equ    %00000010
mIIC1A_AD2:         equ    %00000100
mIIC1A_AD3:         equ    %00001000
mIIC1A_AD4:         equ    %00010000
mIIC1A_AD5:         equ    %00100000
mIIC1A_AD6:         equ    %01000000
mIIC1A_AD7:         equ    %10000000


;*** IIC1F - IIC Frequency Divider Register; 0x00000031 ***
IIC1F:              equ    $00000031                                ;*** IIC1F - IIC Frequency Divider Register; 0x00000031 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
IIC1F_ICR0:         equ    0                                         ; IIC Clock Rate Bit 0
IIC1F_ICR1:         equ    1                                         ; IIC Clock Rate Bit 1
IIC1F_ICR2:         equ    2                                         ; IIC Clock Rate Bit 2
IIC1F_ICR3:         equ    3                                         ; IIC Clock Rate Bit 3
IIC1F_ICR4:         equ    4                                         ; IIC Clock Rate Bit 4
IIC1F_ICR5:         equ    5                                         ; IIC Clock Rate Bit 5
IIC1F_MULT0:        equ    6                                         ; Multiplier Factor Bit 0
IIC1F_MULT1:        equ    7                                         ; Multiplier Factor Bit 1
; bit position masks
mIIC1F_ICR0:        equ    %00000001
mIIC1F_ICR1:        equ    %00000010
mIIC1F_ICR2:        equ    %00000100
mIIC1F_ICR3:        equ    %00001000
mIIC1F_ICR4:        equ    %00010000
mIIC1F_ICR5:        equ    %00100000
mIIC1F_MULT0:       equ    %01000000
mIIC1F_MULT1:       equ    %10000000


;*** IIC1C1 - IIC Control Register 1; 0x00000032 ***
IIC1C1:             equ    $00000032                                ;*** IIC1C1 - IIC Control Register 1; 0x00000032 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
IIC1C1_RSTA:        equ    2                                         ; Repeat START
IIC1C1_TXAK:        equ    3                                         ; Transmit Acknowledge Enable
IIC1C1_TX:          equ    4                                         ; Transmit Mode Select
IIC1C1_MST:         equ    5                                         ; Master Mode Select
IIC1C1_IICIE:       equ    6                                         ; IIC Interrupt Enable
IIC1C1_IICEN:       equ    7                                         ; IIC Enable
; bit position masks
mIIC1C1_RSTA:       equ    %00000100
mIIC1C1_TXAK:       equ    %00001000
mIIC1C1_TX:         equ    %00010000
mIIC1C1_MST:        equ    %00100000
mIIC1C1_IICIE:      equ    %01000000
mIIC1C1_IICEN:      equ    %10000000


;*** IIC1S - IIC Status Register; 0x00000033 ***
IIC1S:              equ    $00000033                                ;*** IIC1S - IIC Status Register; 0x00000033 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
IIC1S_RXAK:         equ    0                                         ; Receive Acknowledge
IIC1S_IICIF:        equ    1                                         ; IIC Interrupt Flag
IIC1S_SRW:          equ    2                                         ; Slave Read/Write
IIC1S_ARBL:         equ    4                                         ; Arbitration Lost
IIC1S_BUSY:         equ    5                                         ; Bus Busy
IIC1S_IAAS:         equ    6                                         ; Addressed as a Slave
IIC1S_TCF:          equ    7                                         ; Transfer Complete Flag
; bit position masks
mIIC1S_RXAK:        equ    %00000001
mIIC1S_IICIF:       equ    %00000010
mIIC1S_SRW:         equ    %00000100
mIIC1S_ARBL:        equ    %00010000
mIIC1S_BUSY:        equ    %00100000
mIIC1S_IAAS:        equ    %01000000
mIIC1S_TCF:         equ    %10000000


;*** IIC1D - IIC Data I/O Register; 0x00000034 ***
IIC1D:              equ    $00000034                                ;*** IIC1D - IIC Data I/O Register; 0x00000034 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
IIC1D_DATA0:        equ    0                                         ; IIC Data Bit 0
IIC1D_DATA1:        equ    1                                         ; IIC Data Bit 1
IIC1D_DATA2:        equ    2                                         ; IIC Data Bit 2
IIC1D_DATA3:        equ    3                                         ; IIC Data Bit 3
IIC1D_DATA4:        equ    4                                         ; IIC Data Bit 4
IIC1D_DATA5:        equ    5                                         ; IIC Data Bit 5
IIC1D_DATA6:        equ    6                                         ; IIC Data Bit 6
IIC1D_DATA7:        equ    7                                         ; IIC Data Bit 7
; bit position masks
mIIC1D_DATA0:       equ    %00000001
mIIC1D_DATA1:       equ    %00000010
mIIC1D_DATA2:       equ    %00000100
mIIC1D_DATA3:       equ    %00001000
mIIC1D_DATA4:       equ    %00010000
mIIC1D_DATA5:       equ    %00100000
mIIC1D_DATA6:       equ    %01000000
mIIC1D_DATA7:       equ    %10000000


;*** IIC1C2 - IIC Control Register 2; 0x00000035 ***
IIC1C2:             equ    $00000035                                ;*** IIC1C2 - IIC Control Register 2; 0x00000035 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
IIC1C2_AD8:         equ    0                                         ; Slave Address Bit 8
IIC1C2_AD9:         equ    1                                         ; Slave Address Bit 9
IIC1C2_AD10:        equ    2                                         ; Slave Address Bit 10
IIC1C2_ADEXT:       equ    6                                         ; Address Extension
IIC1C2_GCAEN:       equ    7                                         ; General Call Address Enable
; bit position masks
mIIC1C2_AD8:        equ    %00000001
mIIC1C2_AD9:        equ    %00000010
mIIC1C2_AD10:       equ    %00000100
mIIC1C2_ADEXT:      equ    %01000000
mIIC1C2_GCAEN:      equ    %10000000


;*** ICSC1 - ICS Control Register 1; 0x00000038 ***
ICSC1:              equ    $00000038                                ;*** ICSC1 - ICS Control Register 1; 0x00000038 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
ICSC1_IREFSTEN:     equ    0                                         ; Internal Reference Stop Enable
ICSC1_IRCLKEN:      equ    1                                         ; Internal Reference Clock Enable
ICSC1_IREFS:        equ    2                                         ; Internal Reference Select
ICSC1_RDIV0:        equ    3                                         ; Reference Divider, bit 0
ICSC1_RDIV1:        equ    4                                         ; Reference Divider, bit 1
ICSC1_RDIV2:        equ    5                                         ; Reference Divider, bit 2
ICSC1_CLKS0:        equ    6                                         ; Clock Source Select, bit 0
ICSC1_CLKS1:        equ    7                                         ; Clock Source Select, bit 1
; bit position masks
mICSC1_IREFSTEN:    equ    %00000001
mICSC1_IRCLKEN:     equ    %00000010
mICSC1_IREFS:       equ    %00000100
mICSC1_RDIV0:       equ    %00001000
mICSC1_RDIV1:       equ    %00010000
mICSC1_RDIV2:       equ    %00100000
mICSC1_CLKS0:       equ    %01000000
mICSC1_CLKS1:       equ    %10000000


;*** ICSC2 - ICS Control Register 2; 0x00000039 ***
ICSC2:              equ    $00000039                                ;*** ICSC2 - ICS Control Register 2; 0x00000039 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
ICSC2_EREFSTEN:     equ    0                                         ; External Reference Stop Enable
ICSC2_ERCLKEN:      equ    1                                         ; External Reference Enable
ICSC2_EREFS:        equ    2                                         ; External Reference Select
ICSC2_LP:           equ    3                                         ; Low Power Select
ICSC2_HGO:          equ    4                                         ; High Gain Oscillator Select
ICSC2_RANGE:        equ    5                                         ; Frequency Range Select
ICSC2_BDIV0:        equ    6                                         ; Bus Frequency Divider, bit 0
ICSC2_BDIV1:        equ    7                                         ; Bus Frequency Divider, bit 1
; bit position masks
mICSC2_EREFSTEN:    equ    %00000001
mICSC2_ERCLKEN:     equ    %00000010
mICSC2_EREFS:       equ    %00000100
mICSC2_LP:          equ    %00001000
mICSC2_HGO:         equ    %00010000
mICSC2_RANGE:       equ    %00100000
mICSC2_BDIV0:       equ    %01000000
mICSC2_BDIV1:       equ    %10000000


;*** ICSTRM - ICS Trim Register; 0x0000003A ***
ICSTRM:             equ    $0000003A                                ;*** ICSTRM - ICS Trim Register; 0x0000003A ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
ICSTRM_TRIM0:       equ    0                                         ; ICS Trim Setting, bit 0
ICSTRM_TRIM1:       equ    1                                         ; ICS Trim Setting, bit 1
ICSTRM_TRIM2:       equ    2                                         ; ICS Trim Setting, bit 2
ICSTRM_TRIM3:       equ    3                                         ; ICS Trim Setting, bit 3
ICSTRM_TRIM4:       equ    4                                         ; ICS Trim Setting, bit 4
ICSTRM_TRIM5:       equ    5                                         ; ICS Trim Setting, bit 5
ICSTRM_TRIM6:       equ    6                                         ; ICS Trim Setting, bit 6
ICSTRM_TRIM7:       equ    7                                         ; ICS Trim Setting, bit 7
; bit position masks
mICSTRM_TRIM0:      equ    %00000001
mICSTRM_TRIM1:      equ    %00000010
mICSTRM_TRIM2:      equ    %00000100
mICSTRM_TRIM3:      equ    %00001000
mICSTRM_TRIM4:      equ    %00010000
mICSTRM_TRIM5:      equ    %00100000
mICSTRM_TRIM6:      equ    %01000000
mICSTRM_TRIM7:      equ    %10000000


;*** ICSSC - ICS Status and Control Register; 0x0000003B ***
ICSSC:              equ    $0000003B                                ;*** ICSSC - ICS Status and Control Register; 0x0000003B ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
ICSSC_FTRIM:        equ    0                                         ; ICS Fine Trim
ICSSC_OSCINIT:      equ    1                                         ; OSC Initialization
ICSSC_CLKST0:       equ    2                                         ; Clock Mode Status, bit 0
ICSSC_CLKST1:       equ    3                                         ; Clock Mode Status, bit 1
ICSSC_IREFST:       equ    4                                         ; Internal Reference Status
ICSSC_DMX32:        equ    5                                         ; DCO Maximum frequency with 32.768 kHz reference
ICSSC_DRST_DRS0:    equ    6                                         ; DCO Range Status/Range Select, bit 0
ICSSC_DRST_DRS1:    equ    7                                         ; DCO Range Status/Range Select, bit 1
; bit position masks
mICSSC_FTRIM:       equ    %00000001
mICSSC_OSCINIT:     equ    %00000010
mICSSC_CLKST0:      equ    %00000100
mICSSC_CLKST1:      equ    %00001000
mICSSC_IREFST:      equ    %00010000
mICSSC_DMX32:       equ    %00100000
mICSSC_DRST_DRS0:   equ    %01000000
mICSSC_DRST_DRS1:   equ    %10000000


;*** KBI2SC - KBI2 Status and Control Register; 0x0000003C ***
KBI2SC:             equ    $0000003C                                ;*** KBI2SC - KBI2 Status and Control Register; 0x0000003C ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
KBI2SC_KBIMOD:      equ    0                                         ; Keyboard Detection Mode
KBI2SC_KBIE:        equ    1                                         ; Keyboard Interrupt Enable
KBI2SC_KBACK:       equ    2                                         ; Keyboard Interrupt Acknowledge
KBI2SC_KBF:         equ    3                                         ; Keyboard Interrupt Flag
; bit position masks
mKBI2SC_KBIMOD:     equ    %00000001
mKBI2SC_KBIE:       equ    %00000010
mKBI2SC_KBACK:      equ    %00000100
mKBI2SC_KBF:        equ    %00001000


;*** KBI2PE - KBI2 Pin Enable Register; 0x0000003D ***
KBI2PE:             equ    $0000003D                                ;*** KBI2PE - KBI2 Pin Enable Register; 0x0000003D ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
KBI2PE_KBIPE0:      equ    0                                         ; Keyboard Pin Enable for KBI Port Bit 0
KBI2PE_KBIPE1:      equ    1                                         ; Keyboard Pin Enable for KBI Port Bit 1
KBI2PE_KBIPE2:      equ    2                                         ; Keyboard Pin Enable for KBI Port Bit 2
KBI2PE_KBIPE3:      equ    3                                         ; Keyboard Pin Enable for KBI Port Bit 3
KBI2PE_KBIPE4:      equ    4                                         ; Keyboard Pin Enable for KBI Port Bit 4
KBI2PE_KBIPE5:      equ    5                                         ; Keyboard Pin Enable for KBI Port Bit 5
KBI2PE_KBIPE6:      equ    6                                         ; Keyboard Pin Enable for KBI Port Bit 6
KBI2PE_KBIPE7:      equ    7                                         ; Keyboard Pin Enable for KBI Port Bit 7
; bit position masks
mKBI2PE_KBIPE0:     equ    %00000001
mKBI2PE_KBIPE1:     equ    %00000010
mKBI2PE_KBIPE2:     equ    %00000100
mKBI2PE_KBIPE3:     equ    %00001000
mKBI2PE_KBIPE4:     equ    %00010000
mKBI2PE_KBIPE5:     equ    %00100000
mKBI2PE_KBIPE6:     equ    %01000000
mKBI2PE_KBIPE7:     equ    %10000000


;*** KBI2ES - KBI2 Edge Select Register; 0x0000003E ***
KBI2ES:             equ    $0000003E                                ;*** KBI2ES - KBI2 Edge Select Register; 0x0000003E ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
KBI2ES_KBEDG0:      equ    0                                         ; Keyboard Edge Select Bit 0
KBI2ES_KBEDG1:      equ    1                                         ; Keyboard Edge Select Bit 1
KBI2ES_KBEDG2:      equ    2                                         ; Keyboard Edge Select Bit 2
KBI2ES_KBEDG3:      equ    3                                         ; Keyboard Edge Select Bit 3
KBI2ES_KBEDG4:      equ    4                                         ; Keyboard Edge Select Bit 4
KBI2ES_KBEDG5:      equ    5                                         ; Keyboard Edge Select Bit 5
KBI2ES_KBEDG6:      equ    6                                         ; Keyboard Edge Select Bit 6
KBI2ES_KBEDG7:      equ    7                                         ; Keyboard Edge Select Bit 7
; bit position masks
mKBI2ES_KBEDG0:     equ    %00000001
mKBI2ES_KBEDG1:     equ    %00000010
mKBI2ES_KBEDG2:     equ    %00000100
mKBI2ES_KBEDG3:     equ    %00001000
mKBI2ES_KBEDG4:     equ    %00010000
mKBI2ES_KBEDG5:     equ    %00100000
mKBI2ES_KBEDG6:     equ    %01000000
mKBI2ES_KBEDG7:     equ    %10000000


;*** TPM1SC - TPM1 Status and Control Register; 0x00000040 ***
TPM1SC:             equ    $00000040                                ;*** TPM1SC - TPM1 Status and Control Register; 0x00000040 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
TPM1SC_PS0:         equ    0                                         ; Prescale Divisor Select Bit 0
TPM1SC_PS1:         equ    1                                         ; Prescale Divisor Select Bit 1
TPM1SC_PS2:         equ    2                                         ; Prescale Divisor Select Bit 2
TPM1SC_CLKSA:       equ    3                                         ; Clock Source Select A
TPM1SC_CLKSB:       equ    4                                         ; Clock Source Select B
TPM1SC_CPWMS:       equ    5                                         ; Center-Aligned PWM Select
TPM1SC_TOIE:        equ    6                                         ; Timer Overflow Interrupt Enable
TPM1SC_TOF:         equ    7                                         ; Timer Overflow Flag
; bit position masks
mTPM1SC_PS0:        equ    %00000001
mTPM1SC_PS1:        equ    %00000010
mTPM1SC_PS2:        equ    %00000100
mTPM1SC_CLKSA:      equ    %00001000
mTPM1SC_CLKSB:      equ    %00010000
mTPM1SC_CPWMS:      equ    %00100000
mTPM1SC_TOIE:       equ    %01000000
mTPM1SC_TOF:        equ    %10000000


;*** TPM1CNT - TPM1 Timer Counter Register; 0x00000041 ***
TPM1CNT:            equ    $00000041                                ;*** TPM1CNT - TPM1 Timer Counter Register; 0x00000041 ***


;*** TPM1CNTH - TPM1 Timer Counter Register High; 0x00000041 ***
TPM1CNTH:           equ    $00000041                                ;*** TPM1CNTH - TPM1 Timer Counter Register High; 0x00000041 ***


;*** TPM1CNTL - TPM1 Timer Counter Register Low; 0x00000042 ***
TPM1CNTL:           equ    $00000042                                ;*** TPM1CNTL - TPM1 Timer Counter Register Low; 0x00000042 ***


;*** TPM1MOD - TPM1 Timer Counter Modulo Register; 0x00000043 ***
TPM1MOD:            equ    $00000043                                ;*** TPM1MOD - TPM1 Timer Counter Modulo Register; 0x00000043 ***


;*** TPM1MODH - TPM1 Timer Counter Modulo Register High; 0x00000043 ***
TPM1MODH:           equ    $00000043                                ;*** TPM1MODH - TPM1 Timer Counter Modulo Register High; 0x00000043 ***


;*** TPM1MODL - TPM1 Timer Counter Modulo Register Low; 0x00000044 ***
TPM1MODL:           equ    $00000044                                ;*** TPM1MODL - TPM1 Timer Counter Modulo Register Low; 0x00000044 ***


;*** TPM1C0SC - TPM1 Timer Channel 0 Status and Control Register; 0x00000045 ***
TPM1C0SC:           equ    $00000045                                ;*** TPM1C0SC - TPM1 Timer Channel 0 Status and Control Register; 0x00000045 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
TPM1C0SC_ELS0A:     equ    2                                         ; Edge/Level Select Bit A
TPM1C0SC_ELS0B:     equ    3                                         ; Edge/Level Select Bit B
TPM1C0SC_MS0A:      equ    4                                         ; Mode Select A for TPM Channel 0
TPM1C0SC_MS0B:      equ    5                                         ; Mode Select B for TPM Channel 0
TPM1C0SC_CH0IE:     equ    6                                         ; Channel 0 Interrupt Enable
TPM1C0SC_CH0F:      equ    7                                         ; Channel 0 Flag
; bit position masks
mTPM1C0SC_ELS0A:    equ    %00000100
mTPM1C0SC_ELS0B:    equ    %00001000
mTPM1C0SC_MS0A:     equ    %00010000
mTPM1C0SC_MS0B:     equ    %00100000
mTPM1C0SC_CH0IE:    equ    %01000000
mTPM1C0SC_CH0F:     equ    %10000000


;*** TPM1C0V - TPM1 Timer Channel 0 Value Register; 0x00000046 ***
TPM1C0V:            equ    $00000046                                ;*** TPM1C0V - TPM1 Timer Channel 0 Value Register; 0x00000046 ***


;*** TPM1C0VH - TPM1 Timer Channel 0 Value Register High; 0x00000046 ***
TPM1C0VH:           equ    $00000046                                ;*** TPM1C0VH - TPM1 Timer Channel 0 Value Register High; 0x00000046 ***


;*** TPM1C0VL - TPM1 Timer Channel 0 Value Register Low; 0x00000047 ***
TPM1C0VL:           equ    $00000047                                ;*** TPM1C0VL - TPM1 Timer Channel 0 Value Register Low; 0x00000047 ***


;*** TPM1C1SC - TPM1 Timer Channel 1 Status and Control Register; 0x00000048 ***
TPM1C1SC:           equ    $00000048                                ;*** TPM1C1SC - TPM1 Timer Channel 1 Status and Control Register; 0x00000048 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
TPM1C1SC_ELS1A:     equ    2                                         ; Edge/Level Select Bit A
TPM1C1SC_ELS1B:     equ    3                                         ; Edge/Level Select Bit B
TPM1C1SC_MS1A:      equ    4                                         ; Mode Select A for TPM Channel 1
TPM1C1SC_MS1B:      equ    5                                         ; Mode Select B for TPM Channel 1
TPM1C1SC_CH1IE:     equ    6                                         ; Channel 1 Interrupt Enable
TPM1C1SC_CH1F:      equ    7                                         ; Channel 1 Flag
; bit position masks
mTPM1C1SC_ELS1A:    equ    %00000100
mTPM1C1SC_ELS1B:    equ    %00001000
mTPM1C1SC_MS1A:     equ    %00010000
mTPM1C1SC_MS1B:     equ    %00100000
mTPM1C1SC_CH1IE:    equ    %01000000
mTPM1C1SC_CH1F:     equ    %10000000


;*** TPM1C1V - TPM1 Timer Channel 1 Value Register; 0x00000049 ***
TPM1C1V:            equ    $00000049                                ;*** TPM1C1V - TPM1 Timer Channel 1 Value Register; 0x00000049 ***


;*** TPM1C1VH - TPM1 Timer Channel 1 Value Register High; 0x00000049 ***
TPM1C1VH:           equ    $00000049                                ;*** TPM1C1VH - TPM1 Timer Channel 1 Value Register High; 0x00000049 ***


;*** TPM1C1VL - TPM1 Timer Channel 1 Value Register Low; 0x0000004A ***
TPM1C1VL:           equ    $0000004A                                ;*** TPM1C1VL - TPM1 Timer Channel 1 Value Register Low; 0x0000004A ***


;*** TPM1C2SC - TPM1 Timer Channel 2 Status and Control Register; 0x0000004B ***
TPM1C2SC:           equ    $0000004B                                ;*** TPM1C2SC - TPM1 Timer Channel 2 Status and Control Register; 0x0000004B ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
TPM1C2SC_ELS2A:     equ    2                                         ; Edge/Level Select Bit A
TPM1C2SC_ELS2B:     equ    3                                         ; Edge/Level Select Bit B
TPM1C2SC_MS2A:      equ    4                                         ; Mode Select A for TPM Channel 2
TPM1C2SC_MS2B:      equ    5                                         ; Mode Select B for TPM Channel 2
TPM1C2SC_CH2IE:     equ    6                                         ; Channel 2 Interrupt Enable
TPM1C2SC_CH2F:      equ    7                                         ; Channel 2 Flag
; bit position masks
mTPM1C2SC_ELS2A:    equ    %00000100
mTPM1C2SC_ELS2B:    equ    %00001000
mTPM1C2SC_MS2A:     equ    %00010000
mTPM1C2SC_MS2B:     equ    %00100000
mTPM1C2SC_CH2IE:    equ    %01000000
mTPM1C2SC_CH2F:     equ    %10000000


;*** TPM1C2V - TPM1 Timer Channel 2 Value Register; 0x0000004C ***
TPM1C2V:            equ    $0000004C                                ;*** TPM1C2V - TPM1 Timer Channel 2 Value Register; 0x0000004C ***


;*** TPM1C2VH - TPM1 Timer Channel 2 Value Register High; 0x0000004C ***
TPM1C2VH:           equ    $0000004C                                ;*** TPM1C2VH - TPM1 Timer Channel 2 Value Register High; 0x0000004C ***


;*** TPM1C2VL - TPM1 Timer Channel 2 Value Register Low; 0x0000004D ***
TPM1C2VL:           equ    $0000004D                                ;*** TPM1C2VL - TPM1 Timer Channel 2 Value Register Low; 0x0000004D ***


;*** TPM2SC - TPM2 Status and Control Register; 0x00000050 ***
TPM2SC:             equ    $00000050                                ;*** TPM2SC - TPM2 Status and Control Register; 0x00000050 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
TPM2SC_PS0:         equ    0                                         ; Prescale Divisor Select Bit 0
TPM2SC_PS1:         equ    1                                         ; Prescale Divisor Select Bit 1
TPM2SC_PS2:         equ    2                                         ; Prescale Divisor Select Bit 2
TPM2SC_CLKSA:       equ    3                                         ; Clock Source Select A
TPM2SC_CLKSB:       equ    4                                         ; Clock Source Select B
TPM2SC_CPWMS:       equ    5                                         ; Center-Aligned PWM Select
TPM2SC_TOIE:        equ    6                                         ; Timer Overflow Interrupt Enable
TPM2SC_TOF:         equ    7                                         ; Timer Overflow Flag
; bit position masks
mTPM2SC_PS0:        equ    %00000001
mTPM2SC_PS1:        equ    %00000010
mTPM2SC_PS2:        equ    %00000100
mTPM2SC_CLKSA:      equ    %00001000
mTPM2SC_CLKSB:      equ    %00010000
mTPM2SC_CPWMS:      equ    %00100000
mTPM2SC_TOIE:       equ    %01000000
mTPM2SC_TOF:        equ    %10000000


;*** TPM2CNT - TPM2 Timer Counter Register; 0x00000051 ***
TPM2CNT:            equ    $00000051                                ;*** TPM2CNT - TPM2 Timer Counter Register; 0x00000051 ***


;*** TPM2CNTH - TPM2 Timer Counter Register High; 0x00000051 ***
TPM2CNTH:           equ    $00000051                                ;*** TPM2CNTH - TPM2 Timer Counter Register High; 0x00000051 ***


;*** TPM2CNTL - TPM2 Timer Counter Register Low; 0x00000052 ***
TPM2CNTL:           equ    $00000052                                ;*** TPM2CNTL - TPM2 Timer Counter Register Low; 0x00000052 ***


;*** TPM2MOD - TPM2 Timer Counter Modulo Register; 0x00000053 ***
TPM2MOD:            equ    $00000053                                ;*** TPM2MOD - TPM2 Timer Counter Modulo Register; 0x00000053 ***


;*** TPM2MODH - TPM2 Timer Counter Modulo Register High; 0x00000053 ***
TPM2MODH:           equ    $00000053                                ;*** TPM2MODH - TPM2 Timer Counter Modulo Register High; 0x00000053 ***


;*** TPM2MODL - TPM2 Timer Counter Modulo Register Low; 0x00000054 ***
TPM2MODL:           equ    $00000054                                ;*** TPM2MODL - TPM2 Timer Counter Modulo Register Low; 0x00000054 ***


;*** TPM2C0SC - TPM2 Timer Channel 0 Status and Control Register; 0x00000055 ***
TPM2C0SC:           equ    $00000055                                ;*** TPM2C0SC - TPM2 Timer Channel 0 Status and Control Register; 0x00000055 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
TPM2C0SC_ELS0A:     equ    2                                         ; Edge/Level Select Bit A
TPM2C0SC_ELS0B:     equ    3                                         ; Edge/Level Select Bit B
TPM2C0SC_MS0A:      equ    4                                         ; Mode Select A for TPM Channel 0
TPM2C0SC_MS0B:      equ    5                                         ; Mode Select B for TPM Channel 0
TPM2C0SC_CH0IE:     equ    6                                         ; Channel 0 Interrupt Enable
TPM2C0SC_CH0F:      equ    7                                         ; Channel 0 Flag
; bit position masks
mTPM2C0SC_ELS0A:    equ    %00000100
mTPM2C0SC_ELS0B:    equ    %00001000
mTPM2C0SC_MS0A:     equ    %00010000
mTPM2C0SC_MS0B:     equ    %00100000
mTPM2C0SC_CH0IE:    equ    %01000000
mTPM2C0SC_CH0F:     equ    %10000000


;*** TPM2C0V - TPM2 Timer Channel 0 Value Register; 0x00000056 ***
TPM2C0V:            equ    $00000056                                ;*** TPM2C0V - TPM2 Timer Channel 0 Value Register; 0x00000056 ***


;*** TPM2C0VH - TPM2 Timer Channel 0 Value Register High; 0x00000056 ***
TPM2C0VH:           equ    $00000056                                ;*** TPM2C0VH - TPM2 Timer Channel 0 Value Register High; 0x00000056 ***


;*** TPM2C0VL - TPM2 Timer Channel 0 Value Register Low; 0x00000057 ***
TPM2C0VL:           equ    $00000057                                ;*** TPM2C0VL - TPM2 Timer Channel 0 Value Register Low; 0x00000057 ***


;*** TPM2C1SC - TPM2 Timer Channel 1 Status and Control Register; 0x00000058 ***
TPM2C1SC:           equ    $00000058                                ;*** TPM2C1SC - TPM2 Timer Channel 1 Status and Control Register; 0x00000058 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
TPM2C1SC_ELS1A:     equ    2                                         ; Edge/Level Select Bit A
TPM2C1SC_ELS1B:     equ    3                                         ; Edge/Level Select Bit B
TPM2C1SC_MS1A:      equ    4                                         ; Mode Select A for TPM Channel 1
TPM2C1SC_MS1B:      equ    5                                         ; Mode Select B for TPM Channel 1
TPM2C1SC_CH1IE:     equ    6                                         ; Channel 1 Interrupt Enable
TPM2C1SC_CH1F:      equ    7                                         ; Channel 1 Flag
; bit position masks
mTPM2C1SC_ELS1A:    equ    %00000100
mTPM2C1SC_ELS1B:    equ    %00001000
mTPM2C1SC_MS1A:     equ    %00010000
mTPM2C1SC_MS1B:     equ    %00100000
mTPM2C1SC_CH1IE:    equ    %01000000
mTPM2C1SC_CH1F:     equ    %10000000


;*** TPM2C1V - TPM2 Timer Channel 1 Value Register; 0x00000059 ***
TPM2C1V:            equ    $00000059                                ;*** TPM2C1V - TPM2 Timer Channel 1 Value Register; 0x00000059 ***


;*** TPM2C1VH - TPM2 Timer Channel 1 Value Register High; 0x00000059 ***
TPM2C1VH:           equ    $00000059                                ;*** TPM2C1VH - TPM2 Timer Channel 1 Value Register High; 0x00000059 ***


;*** TPM2C1VL - TPM2 Timer Channel 1 Value Register Low; 0x0000005A ***
TPM2C1VL:           equ    $0000005A                                ;*** TPM2C1VL - TPM2 Timer Channel 1 Value Register Low; 0x0000005A ***


;*** TPM2C2SC - TPM2 Timer Channel 2 Status and Control Register; 0x0000005B ***
TPM2C2SC:           equ    $0000005B                                ;*** TPM2C2SC - TPM2 Timer Channel 2 Status and Control Register; 0x0000005B ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
TPM2C2SC_ELS2A:     equ    2                                         ; Edge/Level Select Bit A
TPM2C2SC_ELS2B:     equ    3                                         ; Edge/Level Select Bit B
TPM2C2SC_MS2A:      equ    4                                         ; Mode Select A for TPM Channel 2
TPM2C2SC_MS2B:      equ    5                                         ; Mode Select B for TPM Channel 2
TPM2C2SC_CH2IE:     equ    6                                         ; Channel 2 Interrupt Enable
TPM2C2SC_CH2F:      equ    7                                         ; Channel 2 Flag
; bit position masks
mTPM2C2SC_ELS2A:    equ    %00000100
mTPM2C2SC_ELS2B:    equ    %00001000
mTPM2C2SC_MS2A:     equ    %00010000
mTPM2C2SC_MS2B:     equ    %00100000
mTPM2C2SC_CH2IE:    equ    %01000000
mTPM2C2SC_CH2F:     equ    %10000000


;*** TPM2C2V - TPM2 Timer Channel 2 Value Register; 0x0000005C ***
TPM2C2V:            equ    $0000005C                                ;*** TPM2C2V - TPM2 Timer Channel 2 Value Register; 0x0000005C ***


;*** TPM2C2VH - TPM2 Timer Channel 2 Value Register High; 0x0000005C ***
TPM2C2VH:           equ    $0000005C                                ;*** TPM2C2VH - TPM2 Timer Channel 2 Value Register High; 0x0000005C ***


;*** TPM2C2VL - TPM2 Timer Channel 2 Value Register Low; 0x0000005D ***
TPM2C2VL:           equ    $0000005D                                ;*** TPM2C2VL - TPM2 Timer Channel 2 Value Register Low; 0x0000005D ***


;*** TPM3SC - TPM3 Status and Control Register; 0x00000060 ***
TPM3SC:             equ    $00000060                                ;*** TPM3SC - TPM3 Status and Control Register; 0x00000060 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
TPM3SC_PS0:         equ    0                                         ; Prescale Divisor Select Bit 0
TPM3SC_PS1:         equ    1                                         ; Prescale Divisor Select Bit 1
TPM3SC_PS2:         equ    2                                         ; Prescale Divisor Select Bit 2
TPM3SC_CLKSA:       equ    3                                         ; Clock Source Select A
TPM3SC_CLKSB:       equ    4                                         ; Clock Source Select B
TPM3SC_CPWMS:       equ    5                                         ; Center-Aligned PWM Select
TPM3SC_TOIE:        equ    6                                         ; Timer Overflow Interrupt Enable
TPM3SC_TOF:         equ    7                                         ; Timer Overflow Flag
; bit position masks
mTPM3SC_PS0:        equ    %00000001
mTPM3SC_PS1:        equ    %00000010
mTPM3SC_PS2:        equ    %00000100
mTPM3SC_CLKSA:      equ    %00001000
mTPM3SC_CLKSB:      equ    %00010000
mTPM3SC_CPWMS:      equ    %00100000
mTPM3SC_TOIE:       equ    %01000000
mTPM3SC_TOF:        equ    %10000000


;*** TPM3CNT - TPM3 Timer Counter Register; 0x00000061 ***
TPM3CNT:            equ    $00000061                                ;*** TPM3CNT - TPM3 Timer Counter Register; 0x00000061 ***


;*** TPM3CNTH - TPM3 Timer Counter Register High; 0x00000061 ***
TPM3CNTH:           equ    $00000061                                ;*** TPM3CNTH - TPM3 Timer Counter Register High; 0x00000061 ***


;*** TPM3CNTL - TPM3 Timer Counter Register Low; 0x00000062 ***
TPM3CNTL:           equ    $00000062                                ;*** TPM3CNTL - TPM3 Timer Counter Register Low; 0x00000062 ***


;*** TPM3MOD - TPM3 Timer Counter Modulo Register; 0x00000063 ***
TPM3MOD:            equ    $00000063                                ;*** TPM3MOD - TPM3 Timer Counter Modulo Register; 0x00000063 ***


;*** TPM3MODH - TPM3 Timer Counter Modulo Register High; 0x00000063 ***
TPM3MODH:           equ    $00000063                                ;*** TPM3MODH - TPM3 Timer Counter Modulo Register High; 0x00000063 ***


;*** TPM3MODL - TPM3 Timer Counter Modulo Register Low; 0x00000064 ***
TPM3MODL:           equ    $00000064                                ;*** TPM3MODL - TPM3 Timer Counter Modulo Register Low; 0x00000064 ***


;*** TPM3C0SC - TPM3 Timer Channel 0 Status and Control Register; 0x00000065 ***
TPM3C0SC:           equ    $00000065                                ;*** TPM3C0SC - TPM3 Timer Channel 0 Status and Control Register; 0x00000065 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
TPM3C0SC_ELS0A:     equ    2                                         ; Edge/Level Select Bit A
TPM3C0SC_ELS0B:     equ    3                                         ; Edge/Level Select Bit B
TPM3C0SC_MS0A:      equ    4                                         ; Mode Select A for TPM Channel 0
TPM3C0SC_MS0B:      equ    5                                         ; Mode Select B for TPM Channel 0
TPM3C0SC_CH0IE:     equ    6                                         ; Channel 0 Interrupt Enable
TPM3C0SC_CH0F:      equ    7                                         ; Channel 0 Flag
; bit position masks
mTPM3C0SC_ELS0A:    equ    %00000100
mTPM3C0SC_ELS0B:    equ    %00001000
mTPM3C0SC_MS0A:     equ    %00010000
mTPM3C0SC_MS0B:     equ    %00100000
mTPM3C0SC_CH0IE:    equ    %01000000
mTPM3C0SC_CH0F:     equ    %10000000


;*** TPM3C0V - TPM3 Timer Channel 0 Value Register; 0x00000066 ***
TPM3C0V:            equ    $00000066                                ;*** TPM3C0V - TPM3 Timer Channel 0 Value Register; 0x00000066 ***


;*** TPM3C0VH - TPM3 Timer Channel 0 Value Register High; 0x00000066 ***
TPM3C0VH:           equ    $00000066                                ;*** TPM3C0VH - TPM3 Timer Channel 0 Value Register High; 0x00000066 ***


;*** TPM3C0VL - TPM3 Timer Channel 0 Value Register Low; 0x00000067 ***
TPM3C0VL:           equ    $00000067                                ;*** TPM3C0VL - TPM3 Timer Channel 0 Value Register Low; 0x00000067 ***


;*** TPM3C1SC - TPM3 Timer Channel 1 Status and Control Register; 0x00000068 ***
TPM3C1SC:           equ    $00000068                                ;*** TPM3C1SC - TPM3 Timer Channel 1 Status and Control Register; 0x00000068 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
TPM3C1SC_ELS1A:     equ    2                                         ; Edge/Level Select Bit A
TPM3C1SC_ELS1B:     equ    3                                         ; Edge/Level Select Bit B
TPM3C1SC_MS1A:      equ    4                                         ; Mode Select A for TPM Channel 1
TPM3C1SC_MS1B:      equ    5                                         ; Mode Select B for TPM Channel 1
TPM3C1SC_CH1IE:     equ    6                                         ; Channel 1 Interrupt Enable
TPM3C1SC_CH1F:      equ    7                                         ; Channel 1 Flag
; bit position masks
mTPM3C1SC_ELS1A:    equ    %00000100
mTPM3C1SC_ELS1B:    equ    %00001000
mTPM3C1SC_MS1A:     equ    %00010000
mTPM3C1SC_MS1B:     equ    %00100000
mTPM3C1SC_CH1IE:    equ    %01000000
mTPM3C1SC_CH1F:     equ    %10000000


;*** TPM3C1V - TPM3 Timer Channel 1 Value Register; 0x00000069 ***
TPM3C1V:            equ    $00000069                                ;*** TPM3C1V - TPM3 Timer Channel 1 Value Register; 0x00000069 ***


;*** TPM3C1VH - TPM3 Timer Channel 1 Value Register High; 0x00000069 ***
TPM3C1VH:           equ    $00000069                                ;*** TPM3C1VH - TPM3 Timer Channel 1 Value Register High; 0x00000069 ***


;*** TPM3C1VL - TPM3 Timer Channel 1 Value Register Low; 0x0000006A ***
TPM3C1VL:           equ    $0000006A                                ;*** TPM3C1VL - TPM3 Timer Channel 1 Value Register Low; 0x0000006A ***


;*** TPM3C2SC - TPM3 Timer Channel 2 Status and Control Register; 0x0000006B ***
TPM3C2SC:           equ    $0000006B                                ;*** TPM3C2SC - TPM3 Timer Channel 2 Status and Control Register; 0x0000006B ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
TPM3C2SC_ELS2A:     equ    2                                         ; Edge/Level Select Bit A
TPM3C2SC_ELS2B:     equ    3                                         ; Edge/Level Select Bit B
TPM3C2SC_MS2A:      equ    4                                         ; Mode Select A for TPM Channel 2
TPM3C2SC_MS2B:      equ    5                                         ; Mode Select B for TPM Channel 2
TPM3C2SC_CH2IE:     equ    6                                         ; Channel 2 Interrupt Enable
TPM3C2SC_CH2F:      equ    7                                         ; Channel 2 Flag
; bit position masks
mTPM3C2SC_ELS2A:    equ    %00000100
mTPM3C2SC_ELS2B:    equ    %00001000
mTPM3C2SC_MS2A:     equ    %00010000
mTPM3C2SC_MS2B:     equ    %00100000
mTPM3C2SC_CH2IE:    equ    %01000000
mTPM3C2SC_CH2F:     equ    %10000000


;*** TPM3C2V - TPM3 Timer Channel 2 Value Register; 0x0000006C ***
TPM3C2V:            equ    $0000006C                                ;*** TPM3C2V - TPM3 Timer Channel 2 Value Register; 0x0000006C ***


;*** TPM3C2VH - TPM3 Timer Channel 2 Value Register High; 0x0000006C ***
TPM3C2VH:           equ    $0000006C                                ;*** TPM3C2VH - TPM3 Timer Channel 2 Value Register High; 0x0000006C ***


;*** TPM3C2VL - TPM3 Timer Channel 2 Value Register Low; 0x0000006D ***
TPM3C2VL:           equ    $0000006D                                ;*** TPM3C2VL - TPM3 Timer Channel 2 Value Register Low; 0x0000006D ***


;*** TPM3C3SC - TPM3 Timer Channel 3 Status and Control Register; 0x0000006E ***
TPM3C3SC:           equ    $0000006E                                ;*** TPM3C3SC - TPM3 Timer Channel 3 Status and Control Register; 0x0000006E ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
TPM3C3SC_ELS3A:     equ    2                                         ; Edge/Level Select Bit A
TPM3C3SC_ELS3B:     equ    3                                         ; Edge/Level Select Bit B
TPM3C3SC_MS3A:      equ    4                                         ; Mode Select A for TPM Channel 3
TPM3C3SC_MS3B:      equ    5                                         ; Mode Select B for TPM Channel 3
TPM3C3SC_CH3IE:     equ    6                                         ; Channel 3 Interrupt Enable
TPM3C3SC_CH3F:      equ    7                                         ; Channel 3 Flag
; bit position masks
mTPM3C3SC_ELS3A:    equ    %00000100
mTPM3C3SC_ELS3B:    equ    %00001000
mTPM3C3SC_MS3A:     equ    %00010000
mTPM3C3SC_MS3B:     equ    %00100000
mTPM3C3SC_CH3IE:    equ    %01000000
mTPM3C3SC_CH3F:     equ    %10000000


;*** TPM3C3V - TPM3 Timer Channel 3 Value Register; 0x0000006F ***
TPM3C3V:            equ    $0000006F                                ;*** TPM3C3V - TPM3 Timer Channel 3 Value Register; 0x0000006F ***


;*** TPM3C3VH - TPM3 Timer Channel 3 Value Register High; 0x0000006F ***
TPM3C3VH:           equ    $0000006F                                ;*** TPM3C3VH - TPM3 Timer Channel 3 Value Register High; 0x0000006F ***


;*** TPM3C3VL - TPM3 Timer Channel 3 Value Register Low; 0x00000070 ***
TPM3C3VL:           equ    $00000070                                ;*** TPM3C3VL - TPM3 Timer Channel 3 Value Register Low; 0x00000070 ***


;*** TPM3C4SC - TPM3 Timer Channel 4 Status and Control Register; 0x00000071 ***
TPM3C4SC:           equ    $00000071                                ;*** TPM3C4SC - TPM3 Timer Channel 4 Status and Control Register; 0x00000071 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
TPM3C4SC_ELS4A:     equ    2                                         ; Edge/Level Select Bit A
TPM3C4SC_ELS4B:     equ    3                                         ; Edge/Level Select Bit B
TPM3C4SC_MS4A:      equ    4                                         ; Mode Select A for TPM Channel 4
TPM3C4SC_MS4B:      equ    5                                         ; Mode Select B for TPM Channel 4
TPM3C4SC_CH4IE:     equ    6                                         ; Channel 4 Interrupt Enable
TPM3C4SC_CH4F:      equ    7                                         ; Channel 4 Flag
; bit position masks
mTPM3C4SC_ELS4A:    equ    %00000100
mTPM3C4SC_ELS4B:    equ    %00001000
mTPM3C4SC_MS4A:     equ    %00010000
mTPM3C4SC_MS4B:     equ    %00100000
mTPM3C4SC_CH4IE:    equ    %01000000
mTPM3C4SC_CH4F:     equ    %10000000


;*** TPM3C4V - TPM3 Timer Channel 4 Value Register; 0x00000072 ***
TPM3C4V:            equ    $00000072                                ;*** TPM3C4V - TPM3 Timer Channel 4 Value Register; 0x00000072 ***


;*** TPM3C4VH - TPM3 Timer Channel 4 Value Register High; 0x00000072 ***
TPM3C4VH:           equ    $00000072                                ;*** TPM3C4VH - TPM3 Timer Channel 4 Value Register High; 0x00000072 ***


;*** TPM3C4VL - TPM3 Timer Channel 4 Value Register Low; 0x00000073 ***
TPM3C4VL:           equ    $00000073                                ;*** TPM3C4VL - TPM3 Timer Channel 4 Value Register Low; 0x00000073 ***


;*** TPM3C5SC - TPM3 Timer Channel 5 Status and Control Register; 0x00000074 ***
TPM3C5SC:           equ    $00000074                                ;*** TPM3C5SC - TPM3 Timer Channel 5 Status and Control Register; 0x00000074 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
TPM3C5SC_ELS5A:     equ    2                                         ; Edge/Level Select Bit A
TPM3C5SC_ELS5B:     equ    3                                         ; Edge/Level Select Bit B
TPM3C5SC_MS5A:      equ    4                                         ; Mode Select A for TPM Channel 5
TPM3C5SC_MS5B:      equ    5                                         ; Mode Select B for TPM Channel 5
TPM3C5SC_CH5IE:     equ    6                                         ; Channel 5 Interrupt Enable
TPM3C5SC_CH5F:      equ    7                                         ; Channel 5 Flag
; bit position masks
mTPM3C5SC_ELS5A:    equ    %00000100
mTPM3C5SC_ELS5B:    equ    %00001000
mTPM3C5SC_MS5A:     equ    %00010000
mTPM3C5SC_MS5B:     equ    %00100000
mTPM3C5SC_CH5IE:    equ    %01000000
mTPM3C5SC_CH5F:     equ    %10000000


;*** TPM3C5V - TPM3 Timer Channel 5 Value Register; 0x00000075 ***
TPM3C5V:            equ    $00000075                                ;*** TPM3C5V - TPM3 Timer Channel 5 Value Register; 0x00000075 ***


;*** TPM3C5VH - TPM3 Timer Channel 5 Value Register High; 0x00000075 ***
TPM3C5VH:           equ    $00000075                                ;*** TPM3C5VH - TPM3 Timer Channel 5 Value Register High; 0x00000075 ***


;*** TPM3C5VL - TPM3 Timer Channel 5 Value Register Low; 0x00000076 ***
TPM3C5VL:           equ    $00000076                                ;*** TPM3C5VL - TPM3 Timer Channel 5 Value Register Low; 0x00000076 ***


;*** PPAGE - Program Page Register; 0x00000078 ***
PPAGE:              equ    $00000078                                ;*** PPAGE - Program Page Register; 0x00000078 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PPAGE_XA14:         equ    0                                         ; Extended address, bit 14
PPAGE_XA15:         equ    1                                         ; Extended address, bit 15
PPAGE_XA16:         equ    2                                         ; Extended address, bit 16
; bit position masks
mPPAGE_XA14:        equ    %00000001
mPPAGE_XA15:        equ    %00000010
mPPAGE_XA16:        equ    %00000100


;*** LAP2 - Linear Address Pointer Register 2; 0x00000079 ***
LAP2:               equ    $00000079                                ;*** LAP2 - Linear Address Pointer Register 2; 0x00000079 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
LAP2_LA16:          equ    0                                         ; Linear address pointer, bit 16
; bit position masks
mLAP2_LA16:         equ    %00000001


;*** LAP1 - Linear Address Pointer Register 1; 0x0000007A ***
LAP1:               equ    $0000007A                                ;*** LAP1 - Linear Address Pointer Register 1; 0x0000007A ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
LAP1_LA8:           equ    0                                         ; Linear address pointer, bit 8
LAP1_LA9:           equ    1                                         ; Linear address pointer, bit 9
LAP1_LA10:          equ    2                                         ; Linear address pointer, bit 10
LAP1_LA11:          equ    3                                         ; Linear address pointer, bit 11
LAP1_LA12:          equ    4                                         ; Linear address pointer, bit 12
LAP1_LA13:          equ    5                                         ; Linear address pointer, bit 13
LAP1_LA14:          equ    6                                         ; Linear address pointer, bit 14
LAP1_LA15:          equ    7                                         ; Linear address pointer, bit 15
; bit position masks
mLAP1_LA8:          equ    %00000001
mLAP1_LA9:          equ    %00000010
mLAP1_LA10:         equ    %00000100
mLAP1_LA11:         equ    %00001000
mLAP1_LA12:         equ    %00010000
mLAP1_LA13:         equ    %00100000
mLAP1_LA14:         equ    %01000000
mLAP1_LA15:         equ    %10000000


;*** LAP0 - Linear Address Pointer Register 0; 0x0000007B ***
LAP0:               equ    $0000007B                                ;*** LAP0 - Linear Address Pointer Register 0; 0x0000007B ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
LAP0_LA0:           equ    0                                         ; Linear address pointer, bit 0
LAP0_LA1:           equ    1                                         ; Linear address pointer, bit 1
LAP0_LA2:           equ    2                                         ; Linear address pointer, bit 2
LAP0_LA3:           equ    3                                         ; Linear address pointer, bit 3
LAP0_LA4:           equ    4                                         ; Linear address pointer, bit 4
LAP0_LA5:           equ    5                                         ; Linear address pointer, bit 5
LAP0_LA6:           equ    6                                         ; Linear address pointer, bit 6
LAP0_LA7:           equ    7                                         ; Linear address pointer, bit 7
; bit position masks
mLAP0_LA0:          equ    %00000001
mLAP0_LA1:          equ    %00000010
mLAP0_LA2:          equ    %00000100
mLAP0_LA3:          equ    %00001000
mLAP0_LA4:          equ    %00010000
mLAP0_LA5:          equ    %00100000
mLAP0_LA6:          equ    %01000000
mLAP0_LA7:          equ    %10000000


;*** LWP - Linear Word Post Increment Register; 0x0000007C ***
LWP:                equ    $0000007C                                ;*** LWP - Linear Word Post Increment Register; 0x0000007C ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
LWP_D0:             equ    0                                         ; Data value bit 0
LWP_D1:             equ    1                                         ; Data value bit 1
LWP_D2:             equ    2                                         ; Data value bit 2
LWP_D3:             equ    3                                         ; Data value bit 3
LWP_D4:             equ    4                                         ; Data value bit 4
LWP_D5:             equ    5                                         ; Data value bit 5
LWP_D6:             equ    6                                         ; Data value bit 6
LWP_D7:             equ    7                                         ; Data value bit 7
; bit position masks
mLWP_D0:            equ    %00000001
mLWP_D1:            equ    %00000010
mLWP_D2:            equ    %00000100
mLWP_D3:            equ    %00001000
mLWP_D4:            equ    %00010000
mLWP_D5:            equ    %00100000
mLWP_D6:            equ    %01000000
mLWP_D7:            equ    %10000000


;*** LBP - Linear Byte Post Increment Register; 0x0000007D ***
LBP:                equ    $0000007D                                ;*** LBP - Linear Byte Post Increment Register; 0x0000007D ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
LBP_D0:             equ    0                                         ; Data value bit 0
LBP_D1:             equ    1                                         ; Data value bit 1
LBP_D2:             equ    2                                         ; Data value bit 2
LBP_D3:             equ    3                                         ; Data value bit 3
LBP_D4:             equ    4                                         ; Data value bit 4
LBP_D5:             equ    5                                         ; Data value bit 5
LBP_D6:             equ    6                                         ; Data value bit 6
LBP_D7:             equ    7                                         ; Data value bit 7
; bit position masks
mLBP_D0:            equ    %00000001
mLBP_D1:            equ    %00000010
mLBP_D2:            equ    %00000100
mLBP_D3:            equ    %00001000
mLBP_D4:            equ    %00010000
mLBP_D5:            equ    %00100000
mLBP_D6:            equ    %01000000
mLBP_D7:            equ    %10000000


;*** LB - Linear Byte Register; 0x0000007E ***
LB:                 equ    $0000007E                                ;*** LB - Linear Byte Register; 0x0000007E ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
LB_D0:              equ    0                                         ; Data value bit 0
LB_D1:              equ    1                                         ; Data value bit 1
LB_D2:              equ    2                                         ; Data value bit 2
LB_D3:              equ    3                                         ; Data value bit 3
LB_D4:              equ    4                                         ; Data value bit 4
LB_D5:              equ    5                                         ; Data value bit 5
LB_D6:              equ    6                                         ; Data value bit 6
LB_D7:              equ    7                                         ; Data value bit 7
; bit position masks
mLB_D0:             equ    %00000001
mLB_D1:             equ    %00000010
mLB_D2:             equ    %00000100
mLB_D3:             equ    %00001000
mLB_D4:             equ    %00010000
mLB_D5:             equ    %00100000
mLB_D6:             equ    %01000000
mLB_D7:             equ    %10000000


;*** LAPAB - Linear Address Pointer Add Byte Register; 0x0000007F ***
LAPAB:              equ    $0000007F                                ;*** LAPAB - Linear Address Pointer Add Byte Register; 0x0000007F ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
LAPAB_D0:           equ    0                                         ; Data value bit 0
LAPAB_D1:           equ    1                                         ; Data value bit 1
LAPAB_D2:           equ    2                                         ; Data value bit 2
LAPAB_D3:           equ    3                                         ; Data value bit 3
LAPAB_D4:           equ    4                                         ; Data value bit 4
LAPAB_D5:           equ    5                                         ; Data value bit 5
LAPAB_D6:           equ    6                                         ; Data value bit 6
LAPAB_D7:           equ    7                                         ; Data value bit 7
; bit position masks
mLAPAB_D0:          equ    %00000001
mLAPAB_D1:          equ    %00000010
mLAPAB_D2:          equ    %00000100
mLAPAB_D3:          equ    %00001000
mLAPAB_D4:          equ    %00010000
mLAPAB_D5:          equ    %00100000
mLAPAB_D6:          equ    %01000000
mLAPAB_D7:          equ    %10000000


;*** SRS - System Reset Status Register; 0x00001800 ***
SRS:                equ    $00001800                                ;*** SRS - System Reset Status Register; 0x00001800 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SRS_LVD:            equ    1                                         ; Low Voltage Detect
SRS_ILOP:           equ    4                                         ; Illegal Opcode
SRS_COP:            equ    5                                         ; Computer Operating Properly (COP) Watchdog
SRS_PIN:            equ    6                                         ; External Reset Pin
SRS_POR:            equ    7                                         ; Power-On Reset
; bit position masks
mSRS_LVD:           equ    %00000010
mSRS_ILOP:          equ    %00010000
mSRS_COP:           equ    %00100000
mSRS_PIN:           equ    %01000000
mSRS_POR:           equ    %10000000


;*** SBDFR - System Background Debug Force Reset Register; 0x00001801 ***
SBDFR:              equ    $00001801                                ;*** SBDFR - System Background Debug Force Reset Register; 0x00001801 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SBDFR_BDFR:         equ    0                                         ; Background Debug Force Reset
; bit position masks
mSBDFR_BDFR:        equ    %00000001


;*** SOPT1 - System Options Register 1; 0x00001802 ***
SOPT1:              equ    $00001802                                ;*** SOPT1 - System Options Register 1; 0x00001802 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SOPT1_RSTPE:        equ    0                                         ; RESET Pin Enable
SOPT1_BKGDPE:       equ    1                                         ; Background Debug Mode Pin Enable
SOPT1_RSTOPE:       equ    2                                         ; RSTO Pin Enable
SOPT1_STOPE:        equ    5                                         ; Stop Mode Enable
SOPT1_COPT:         equ    6                                         ; COP Watchdog Timeout
SOPT1_COPE:         equ    7                                         ; COP Watchdog Enable
; bit position masks
mSOPT1_RSTPE:       equ    %00000001
mSOPT1_BKGDPE:      equ    %00000010
mSOPT1_RSTOPE:      equ    %00000100
mSOPT1_STOPE:       equ    %00100000
mSOPT1_COPT:        equ    %01000000
mSOPT1_COPE:        equ    %10000000


;*** SOPT2 - System Options Register 2; 0x00001803 ***
SOPT2:              equ    $00001803                                ;*** SOPT2 - System Options Register 2; 0x00001803 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SOPT2_ACIC1:        equ    0                                         ; Analog Comparator 1 to Input Capture Enable
SOPT2_IIC1PS:       equ    1                                         ; IIC1 Pin Select
SOPT2_ACIC2:        equ    2                                         ; Analog Comparator 2 to Input Capture Enable
SOPT2_SPI1PS:       equ    3                                         ; SPI1 Pin Select
SOPT2_COPCLKS:      equ    7                                         ; COP Watchdog Clock Select
; bit position masks
mSOPT2_ACIC1:       equ    %00000001
mSOPT2_IIC1PS:      equ    %00000010
mSOPT2_ACIC2:       equ    %00000100
mSOPT2_SPI1PS:      equ    %00001000
mSOPT2_COPCLKS:     equ    %10000000


;*** SDID - System Device Identification Register; 0x00001806 ***
SDID:               equ    $00001806                                ;*** SDID - System Device Identification Register; 0x00001806 ***


;*** SDIDH - System Device Identification Register High; 0x00001806 ***
SDIDH:              equ    $00001806                                ;*** SDIDH - System Device Identification Register High; 0x00001806 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SDIDH_ID8:          equ    0                                         ; Part Identification Number, bit 8
SDIDH_ID9:          equ    1                                         ; Part Identification Number, bit 9
SDIDH_ID10:         equ    2                                         ; Part Identification Number, bit 10
SDIDH_ID11:         equ    3                                         ; Part Identification Number, bit 11
; bit position masks
mSDIDH_ID8:         equ    %00000001
mSDIDH_ID9:         equ    %00000010
mSDIDH_ID10:        equ    %00000100
mSDIDH_ID11:        equ    %00001000


;*** SDIDL - System Device Identification Register Low; 0x00001807 ***
SDIDL:              equ    $00001807                                ;*** SDIDL - System Device Identification Register Low; 0x00001807 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SDIDL_ID0:          equ    0                                         ; Part Identification Number, bit 0
SDIDL_ID1:          equ    1                                         ; Part Identification Number, bit 1
SDIDL_ID2:          equ    2                                         ; Part Identification Number, bit 2
SDIDL_ID3:          equ    3                                         ; Part Identification Number, bit 3
SDIDL_ID4:          equ    4                                         ; Part Identification Number, bit 4
SDIDL_ID5:          equ    5                                         ; Part Identification Number, bit 5
SDIDL_ID6:          equ    6                                         ; Part Identification Number, bit 6
SDIDL_ID7:          equ    7                                         ; Part Identification Number, bit 7
; bit position masks
mSDIDL_ID0:         equ    %00000001
mSDIDL_ID1:         equ    %00000010
mSDIDL_ID2:         equ    %00000100
mSDIDL_ID3:         equ    %00001000
mSDIDL_ID4:         equ    %00010000
mSDIDL_ID5:         equ    %00100000
mSDIDL_ID6:         equ    %01000000
mSDIDL_ID7:         equ    %10000000


;*** SPMSC1 - System Power Management Status and Control 1 Register; 0x00001808 ***
SPMSC1:             equ    $00001808                                ;*** SPMSC1 - System Power Management Status and Control 1 Register; 0x00001808 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SPMSC1_BGBE:        equ    0                                         ; Bandgap Buffer Enable
SPMSC1_LVDE:        equ    2                                         ; Low-Voltage Detect Enable
SPMSC1_LVDSE:       equ    3                                         ; Low-Voltage Detect Stop Enable
SPMSC1_LVDRE:       equ    4                                         ; Low-Voltage Detect Reset Enable
SPMSC1_LVDIE:       equ    5                                         ; Low-Voltage Detect Interrupt Enable
SPMSC1_LVDACK:      equ    6                                         ; Low-Voltage Detect Acknowledge
SPMSC1_LVDF:        equ    7                                         ; Low-Voltage Detect Flag
; bit position masks
mSPMSC1_BGBE:       equ    %00000001
mSPMSC1_LVDE:       equ    %00000100
mSPMSC1_LVDSE:      equ    %00001000
mSPMSC1_LVDRE:      equ    %00010000
mSPMSC1_LVDIE:      equ    %00100000
mSPMSC1_LVDACK:     equ    %01000000
mSPMSC1_LVDF:       equ    %10000000


;*** SPMSC2 - System Power Management Status and Control 2 Register; 0x00001809 ***
SPMSC2:             equ    $00001809                                ;*** SPMSC2 - System Power Management Status and Control 2 Register; 0x00001809 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SPMSC2_PPDC:        equ    0                                         ; Partial Power Down Control
SPMSC2_PPDE:        equ    1                                         ; Partial Power-Down Enable
SPMSC2_PPDACK:      equ    2                                         ; Partial Power Down Acknowledge
SPMSC2_PPDF:        equ    3                                         ; Partial Power Down Flag
SPMSC2_LPWUI:       equ    5                                         ; Low Power Wake Up on Interrupt
SPMSC2_LPRS:        equ    6                                         ; Low Power Regulator Status
SPMSC2_LPR:         equ    7                                         ; Low Power Regulator Control
; bit position masks
mSPMSC2_PPDC:       equ    %00000001
mSPMSC2_PPDE:       equ    %00000010
mSPMSC2_PPDACK:     equ    %00000100
mSPMSC2_PPDF:       equ    %00001000
mSPMSC2_LPWUI:      equ    %00100000
mSPMSC2_LPRS:       equ    %01000000
mSPMSC2_LPR:        equ    %10000000


;*** SPMSC3 - System Power Management Status and Control 3 Register; 0x0000180B ***
SPMSC3:             equ    $0000180B                                ;*** SPMSC3 - System Power Management Status and Control 3 Register; 0x0000180B ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SPMSC3_LVWIE:       equ    3                                         ; Low-Voltage Warning Interrupt Enable
SPMSC3_LVWV:        equ    4                                         ; Low-Voltage Warning Voltage Select
SPMSC3_LVDV:        equ    5                                         ; Low-Voltage Detect Voltage Select
SPMSC3_LVWACK:      equ    6                                         ; Low-Voltage Warning Acknowledge
SPMSC3_LVWF:        equ    7                                         ; Low-Voltage Warning Flag
; bit position masks
mSPMSC3_LVWIE:      equ    %00001000
mSPMSC3_LVWV:       equ    %00010000
mSPMSC3_LVDV:       equ    %00100000
mSPMSC3_LVWACK:     equ    %01000000
mSPMSC3_LVWF:       equ    %10000000


;*** SCGC1 - System Clock Gating Control 1 Register; 0x0000180E ***
SCGC1:              equ    $0000180E                                ;*** SCGC1 - System Clock Gating Control 1 Register; 0x0000180E ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SCGC1_SCI1:         equ    0                                         ; SCI1 Clock Gate Control
SCGC1_SCI2:         equ    1                                         ; SCI2 Clock Gate Control
SCGC1_IIC1:         equ    2                                         ; IIC1 Clock Gate Control
SCGC1_IIC2:         equ    3                                         ; IIC2 Clock Gate Control
SCGC1_ADC:          equ    4                                         ; ADC Clock Gate Control
SCGC1_TPM1:         equ    5                                         ; TPM1 Clock Gate Control
SCGC1_TPM2:         equ    6                                         ; TPM2 Clock Gate Control
SCGC1_TPM3:         equ    7                                         ; TPM3 Clock Gate Control
; bit position masks
mSCGC1_SCI1:        equ    %00000001
mSCGC1_SCI2:        equ    %00000010
mSCGC1_IIC1:        equ    %00000100
mSCGC1_IIC2:        equ    %00001000
mSCGC1_ADC:         equ    %00010000
mSCGC1_TPM1:        equ    %00100000
mSCGC1_TPM2:        equ    %01000000
mSCGC1_TPM3:        equ    %10000000


;*** SCGC2 - System Clock Gating Control 2 Register; 0x0000180F ***
SCGC2:              equ    $0000180F                                ;*** SCGC2 - System Clock Gating Control 2 Register; 0x0000180F ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SCGC2_SPI1:         equ    0                                         ; SPI1 Clock Gate Control
SCGC2_SPI2:         equ    1                                         ; SPI2 Clock Gate Control
SCGC2_RTC:          equ    2                                         ; RTC Clock Gate Control
SCGC2_ACMP:         equ    3                                         ; ACMP Clock Gate Control
SCGC2_KBI:          equ    4                                         ; KBI Clock Gate Control
SCGC2_IRQ:          equ    5                                         ; IRQ Clock Gate Control
SCGC2_FLS:          equ    6                                         ; FLASH Register Clock Gate Control
SCGC2_DBG:          equ    7                                         ; DBG Clock Gate Control
; bit position masks
mSCGC2_SPI1:        equ    %00000001
mSCGC2_SPI2:        equ    %00000010
mSCGC2_RTC:         equ    %00000100
mSCGC2_ACMP:        equ    %00001000
mSCGC2_KBI:         equ    %00010000
mSCGC2_IRQ:         equ    %00100000
mSCGC2_FLS:         equ    %01000000
mSCGC2_DBG:         equ    %10000000


;*** DBGCA - Debug Comparator A Register; 0x00001810 ***
DBGCA:              equ    $00001810                                ;*** DBGCA - Debug Comparator A Register; 0x00001810 ***


;*** DBGCAH - Debug Comparator A High Register; 0x00001810 ***
DBGCAH:             equ    $00001810                                ;*** DBGCAH - Debug Comparator A High Register; 0x00001810 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
DBGCAH_Bit8:        equ    0                                         ; Comparator A High Compare Bit 8
DBGCAH_Bit9:        equ    1                                         ; Comparator A High Compare Bit 9
DBGCAH_Bit10:       equ    2                                         ; Comparator A High Compare Bit 10
DBGCAH_Bit11:       equ    3                                         ; Comparator A High Compare Bit 11
DBGCAH_Bit12:       equ    4                                         ; Comparator A High Compare Bit 12
DBGCAH_Bit13:       equ    5                                         ; Comparator A High Compare Bit 13
DBGCAH_Bit14:       equ    6                                         ; Comparator A High Compare Bit 14
DBGCAH_Bit15:       equ    7                                         ; Comparator A High Compare Bit 15
; bit position masks
mDBGCAH_Bit8:       equ    %00000001
mDBGCAH_Bit9:       equ    %00000010
mDBGCAH_Bit10:      equ    %00000100
mDBGCAH_Bit11:      equ    %00001000
mDBGCAH_Bit12:      equ    %00010000
mDBGCAH_Bit13:      equ    %00100000
mDBGCAH_Bit14:      equ    %01000000
mDBGCAH_Bit15:      equ    %10000000


;*** DBGCAL - Debug Comparator A Low Register; 0x00001811 ***
DBGCAL:             equ    $00001811                                ;*** DBGCAL - Debug Comparator A Low Register; 0x00001811 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
DBGCAL_Bit0:        equ    0                                         ; Comparator A Low Compare Bit 0
DBGCAL_Bit1:        equ    1                                         ; Comparator A Low Compare Bit 1
DBGCAL_Bit2:        equ    2                                         ; Comparator A Low Compare Bit 2
DBGCAL_Bit3:        equ    3                                         ; Comparator A Low Compare Bit 3
DBGCAL_Bit4:        equ    4                                         ; Comparator A Low Compare Bit 4
DBGCAL_Bit5:        equ    5                                         ; Comparator A Low Compare Bit 5
DBGCAL_Bit6:        equ    6                                         ; Comparator A Low Compare Bit 6
DBGCAL_Bit7:        equ    7                                         ; Comparator A Low Compare Bit 7
; bit position masks
mDBGCAL_Bit0:       equ    %00000001
mDBGCAL_Bit1:       equ    %00000010
mDBGCAL_Bit2:       equ    %00000100
mDBGCAL_Bit3:       equ    %00001000
mDBGCAL_Bit4:       equ    %00010000
mDBGCAL_Bit5:       equ    %00100000
mDBGCAL_Bit6:       equ    %01000000
mDBGCAL_Bit7:       equ    %10000000


;*** DBGCB - Debug Comparator B Register; 0x00001812 ***
DBGCB:              equ    $00001812                                ;*** DBGCB - Debug Comparator B Register; 0x00001812 ***


;*** DBGCBH - Debug Comparator B High Register; 0x00001812 ***
DBGCBH:             equ    $00001812                                ;*** DBGCBH - Debug Comparator B High Register; 0x00001812 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
DBGCBH_Bit8:        equ    0                                         ; Comparator B High Compare Bit 8
DBGCBH_Bit9:        equ    1                                         ; Comparator B High Compare Bit 9
DBGCBH_Bit10:       equ    2                                         ; Comparator B High Compare Bit 10
DBGCBH_Bit11:       equ    3                                         ; Comparator B High Compare Bit 11
DBGCBH_Bit12:       equ    4                                         ; Comparator B High Compare Bit 12
DBGCBH_Bit13:       equ    5                                         ; Comparator B High Compare Bit 13
DBGCBH_Bit14:       equ    6                                         ; Comparator B High Compare Bit 14
DBGCBH_Bit15:       equ    7                                         ; Comparator B High Compare Bit 15
; bit position masks
mDBGCBH_Bit8:       equ    %00000001
mDBGCBH_Bit9:       equ    %00000010
mDBGCBH_Bit10:      equ    %00000100
mDBGCBH_Bit11:      equ    %00001000
mDBGCBH_Bit12:      equ    %00010000
mDBGCBH_Bit13:      equ    %00100000
mDBGCBH_Bit14:      equ    %01000000
mDBGCBH_Bit15:      equ    %10000000


;*** DBGCBL - Debug Comparator B Low Register; 0x00001813 ***
DBGCBL:             equ    $00001813                                ;*** DBGCBL - Debug Comparator B Low Register; 0x00001813 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
DBGCBL_Bit0:        equ    0                                         ; Comparator B Low Compare Bit 0
DBGCBL_Bit1:        equ    1                                         ; Comparator B Low Compare Bit 1
DBGCBL_Bit2:        equ    2                                         ; Comparator B Low Compare Bit 2
DBGCBL_Bit3:        equ    3                                         ; Comparator B Low Compare Bit 3
DBGCBL_Bit4:        equ    4                                         ; Comparator B Low Compare Bit 4
DBGCBL_Bit5:        equ    5                                         ; Comparator B Low Compare Bit 5
DBGCBL_Bit6:        equ    6                                         ; Comparator B Low Compare Bit 6
DBGCBL_Bit7:        equ    7                                         ; Comparator B Low Compare Bit 7
; bit position masks
mDBGCBL_Bit0:       equ    %00000001
mDBGCBL_Bit1:       equ    %00000010
mDBGCBL_Bit2:       equ    %00000100
mDBGCBL_Bit3:       equ    %00001000
mDBGCBL_Bit4:       equ    %00010000
mDBGCBL_Bit5:       equ    %00100000
mDBGCBL_Bit6:       equ    %01000000
mDBGCBL_Bit7:       equ    %10000000


;*** DBGCC - Debug Comparator C Register; 0x00001814 ***
DBGCC:              equ    $00001814                                ;*** DBGCC - Debug Comparator C Register; 0x00001814 ***


;*** DBGCCH - Debug Comparator C High Register; 0x00001814 ***
DBGCCH:             equ    $00001814                                ;*** DBGCCH - Debug Comparator C High Register; 0x00001814 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
DBGCCH_Bit8:        equ    0                                         ; Comparator C High Compare Bit 8
DBGCCH_Bit9:        equ    1                                         ; Comparator C High Compare Bit 9
DBGCCH_Bit10:       equ    2                                         ; Comparator C High Compare Bit 10
DBGCCH_Bit11:       equ    3                                         ; Comparator C High Compare Bit 11
DBGCCH_Bit12:       equ    4                                         ; Comparator C High Compare Bit 12
DBGCCH_Bit13:       equ    5                                         ; Comparator C High Compare Bit 13
DBGCCH_Bit14:       equ    6                                         ; Comparator C High Compare Bit 14
DBGCCH_Bit15:       equ    7                                         ; Comparator C High Compare Bit 15
; bit position masks
mDBGCCH_Bit8:       equ    %00000001
mDBGCCH_Bit9:       equ    %00000010
mDBGCCH_Bit10:      equ    %00000100
mDBGCCH_Bit11:      equ    %00001000
mDBGCCH_Bit12:      equ    %00010000
mDBGCCH_Bit13:      equ    %00100000
mDBGCCH_Bit14:      equ    %01000000
mDBGCCH_Bit15:      equ    %10000000


;*** DBGCCL - Debug Comparator C Low Register; 0x00001815 ***
DBGCCL:             equ    $00001815                                ;*** DBGCCL - Debug Comparator C Low Register; 0x00001815 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
DBGCCL_Bit0:        equ    0                                         ; Comparator C Low Compare Bit 0
DBGCCL_Bit1:        equ    1                                         ; Comparator C Low Compare Bit 1
DBGCCL_Bit2:        equ    2                                         ; Comparator C Low Compare Bit 2
DBGCCL_Bit3:        equ    3                                         ; Comparator C Low Compare Bit 3
DBGCCL_Bit4:        equ    4                                         ; Comparator C Low Compare Bit 4
DBGCCL_Bit5:        equ    5                                         ; Comparator C Low Compare Bit 5
DBGCCL_Bit6:        equ    6                                         ; Comparator C Low Compare Bit 6
DBGCCL_Bit7:        equ    7                                         ; Comparator C Low Compare Bit 7
; bit position masks
mDBGCCL_Bit0:       equ    %00000001
mDBGCCL_Bit1:       equ    %00000010
mDBGCCL_Bit2:       equ    %00000100
mDBGCCL_Bit3:       equ    %00001000
mDBGCCL_Bit4:       equ    %00010000
mDBGCCL_Bit5:       equ    %00100000
mDBGCCL_Bit6:       equ    %01000000
mDBGCCL_Bit7:       equ    %10000000


;*** DBGF - Debug FIFO Register; 0x00001816 ***
DBGF:               equ    $00001816                                ;*** DBGF - Debug FIFO Register; 0x00001816 ***


;*** DBGFH - Debug FIFO High Register; 0x00001816 ***
DBGFH:              equ    $00001816                                ;*** DBGFH - Debug FIFO High Register; 0x00001816 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
DBGFH_Bit8:         equ    0                                         ; FIFO High Data Bit 8
DBGFH_Bit9:         equ    1                                         ; FIFO High Data Bit 9
DBGFH_Bit10:        equ    2                                         ; FIFO High Data Bit 10
DBGFH_Bit11:        equ    3                                         ; FIFO High Data Bit 11
DBGFH_Bit12:        equ    4                                         ; FIFO High Data Bit 12
DBGFH_Bit13:        equ    5                                         ; FIFO High Data Bit 13
DBGFH_Bit14:        equ    6                                         ; FIFO High Data Bit 14
DBGFH_Bit15:        equ    7                                         ; FIFO High Data Bit 15
; bit position masks
mDBGFH_Bit8:        equ    %00000001
mDBGFH_Bit9:        equ    %00000010
mDBGFH_Bit10:       equ    %00000100
mDBGFH_Bit11:       equ    %00001000
mDBGFH_Bit12:       equ    %00010000
mDBGFH_Bit13:       equ    %00100000
mDBGFH_Bit14:       equ    %01000000
mDBGFH_Bit15:       equ    %10000000


;*** DBGFL - Debug FIFO Low Register; 0x00001817 ***
DBGFL:              equ    $00001817                                ;*** DBGFL - Debug FIFO Low Register; 0x00001817 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
DBGFL_Bit0:         equ    0                                         ; FIFO Low Data Bit 0
DBGFL_Bit1:         equ    1                                         ; FIFO Low Data Bit 1
DBGFL_Bit2:         equ    2                                         ; FIFO Low Data Bit 2
DBGFL_Bit3:         equ    3                                         ; FIFO Low Data Bit 3
DBGFL_Bit4:         equ    4                                         ; FIFO Low Data Bit 4
DBGFL_Bit5:         equ    5                                         ; FIFO Low Data Bit 5
DBGFL_Bit6:         equ    6                                         ; FIFO Low Data Bit 6
DBGFL_Bit7:         equ    7                                         ; FIFO Low Data Bit 7
; bit position masks
mDBGFL_Bit0:        equ    %00000001
mDBGFL_Bit1:        equ    %00000010
mDBGFL_Bit2:        equ    %00000100
mDBGFL_Bit3:        equ    %00001000
mDBGFL_Bit4:        equ    %00010000
mDBGFL_Bit5:        equ    %00100000
mDBGFL_Bit6:        equ    %01000000
mDBGFL_Bit7:        equ    %10000000


;*** DBGCAX - Debug Comparator A Extension Register; 0x00001818 ***
DBGCAX:             equ    $00001818                                ;*** DBGCAX - Debug Comparator A Extension Register; 0x00001818 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
DBGCAX_Bit16:       equ    0                                         ; omparator A Extended Address Bit 16 Compare Bit
DBGCAX_PAGSEL:      equ    5                                         ; Comparator A Page Select Bit
DBGCAX_RWA:         equ    6                                         ; Read/Write Comparator A Value Bit
DBGCAX_RWAEN:       equ    7                                         ; Read/Write Comparator A Enable Bit
; bit position masks
mDBGCAX_Bit16:      equ    %00000001
mDBGCAX_PAGSEL:     equ    %00100000
mDBGCAX_RWA:        equ    %01000000
mDBGCAX_RWAEN:      equ    %10000000


;*** DBGCBX - Debug Comparator B Extension Register; 0x00001819 ***
DBGCBX:             equ    $00001819                                ;*** DBGCBX - Debug Comparator B Extension Register; 0x00001819 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
DBGCBX_Bit16:       equ    0                                         ; omparator B Extended Address Bit 16 Compare Bit
DBGCBX_PAGSEL:      equ    5                                         ; Comparator B Page Select Bit
DBGCBX_RWB:         equ    6                                         ; Read/Write Comparator B Value Bit
DBGCBX_RWBEN:       equ    7                                         ; Read/Write Comparator B Enable Bit
; bit position masks
mDBGCBX_Bit16:      equ    %00000001
mDBGCBX_PAGSEL:     equ    %00100000
mDBGCBX_RWB:        equ    %01000000
mDBGCBX_RWBEN:      equ    %10000000


;*** DBGCCX - Debug Comparator C Extension Register; 0x0000181A ***
DBGCCX:             equ    $0000181A                                ;*** DBGCCX - Debug Comparator C Extension Register; 0x0000181A ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
DBGCCX_Bit16:       equ    0                                         ; omparator C Extended Address Bit 16 Compare Bit
DBGCCX_PAGSEL:      equ    5                                         ; Comparator C Page Select Bit
DBGCCX_RWC:         equ    6                                         ; Read/Write Comparator C Value Bit
DBGCCX_RWCEN:       equ    7                                         ; Read/Write Comparator C Enable Bit
; bit position masks
mDBGCCX_Bit16:      equ    %00000001
mDBGCCX_PAGSEL:     equ    %00100000
mDBGCCX_RWC:        equ    %01000000
mDBGCCX_RWCEN:      equ    %10000000


;*** DBGFX - Debug FIFO Extended Information Register; 0x0000181B ***
DBGFX:              equ    $0000181B                                ;*** DBGFX - Debug FIFO Extended Information Register; 0x0000181B ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
DBGFX_Bit16:        equ    0                                         ; Extended Address Bit 16
DBGFX_PPACC:        equ    7                                         ; PPAGE Access Indicator Bit
; bit position masks
mDBGFX_Bit16:       equ    %00000001
mDBGFX_PPACC:       equ    %10000000


;*** DBGC - Debug Control Register; 0x0000181C ***
DBGC:               equ    $0000181C                                ;*** DBGC - Debug Control Register; 0x0000181C ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
DBGC_LOOP1:         equ    0                                         ; Select LOOP1 Capture Mode
DBGC_BRKEN:         equ    4                                         ; Break Enable Bit
DBGC_TAG:           equ    5                                         ; Tag or Force Bit
DBGC_ARM:           equ    6                                         ; Arm Bit
DBGC_DBGEN:         equ    7                                         ; DBG Module Enable Bit
; bit position masks
mDBGC_LOOP1:        equ    %00000001
mDBGC_BRKEN:        equ    %00010000
mDBGC_TAG:          equ    %00100000
mDBGC_ARM:          equ    %01000000
mDBGC_DBGEN:        equ    %10000000


;*** DBGT - Debug Trigger Register; 0x0000181D ***
DBGT:               equ    $0000181D                                ;*** DBGT - Debug Trigger Register; 0x0000181D ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
DBGT_TRG0:          equ    0                                         ; Trigger Mode Bit 0
DBGT_TRG1:          equ    1                                         ; Trigger Mode Bit 1
DBGT_TRG2:          equ    2                                         ; Trigger Mode Bit 2
DBGT_TRG3:          equ    3                                         ; Trigger Mode Bit 3
DBGT_BEGIN:         equ    6                                         ; Begin/End Trigger Bit
DBGT_TRGSEL:        equ    7                                         ; Trigger Selection Bit
; bit position masks
mDBGT_TRG0:         equ    %00000001
mDBGT_TRG1:         equ    %00000010
mDBGT_TRG2:         equ    %00000100
mDBGT_TRG3:         equ    %00001000
mDBGT_BEGIN:        equ    %01000000
mDBGT_TRGSEL:       equ    %10000000


;*** DBGS - Debug Status Register; 0x0000181E ***
DBGS:               equ    $0000181E                                ;*** DBGS - Debug Status Register; 0x0000181E ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
DBGS_ARMF:          equ    0                                         ; Arm Flag Bit
DBGS_CF:            equ    5                                         ; Trigger C Match Bit
DBGS_BF:            equ    6                                         ; Trigger B Match Bit
DBGS_AF:            equ    7                                         ; Trigger A Match Bit
; bit position masks
mDBGS_ARMF:         equ    %00000001
mDBGS_CF:           equ    %00100000
mDBGS_BF:           equ    %01000000
mDBGS_AF:           equ    %10000000


;*** DBGCNT - Debug Count Status Register; 0x0000181F ***
DBGCNT:             equ    $0000181F                                ;*** DBGCNT - Debug Count Status Register; 0x0000181F ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
DBGCNT_CNT0:        equ    0                                         ; FIFO Valid Count Bits, bit 0
DBGCNT_CNT1:        equ    1                                         ; FIFO Valid Count Bits, bit 1
DBGCNT_CNT2:        equ    2                                         ; FIFO Valid Count Bits, bit 2
DBGCNT_CNT3:        equ    3                                         ; FIFO Valid Count Bits, bit 3
; bit position masks
mDBGCNT_CNT0:       equ    %00000001
mDBGCNT_CNT1:       equ    %00000010
mDBGCNT_CNT2:       equ    %00000100
mDBGCNT_CNT3:       equ    %00001000


;*** FCDIV - FLASH Clock Divider Register; 0x00001820 ***
FCDIV:              equ    $00001820                                ;*** FCDIV - FLASH Clock Divider Register; 0x00001820 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
FCDIV_FDIV0:        equ    0                                         ; Divisor for FLASH Clock Divider, bit 0
FCDIV_FDIV1:        equ    1                                         ; Divisor for FLASH Clock Divider, bit 1
FCDIV_FDIV2:        equ    2                                         ; Divisor for FLASH Clock Divider, bit 2
FCDIV_FDIV3:        equ    3                                         ; Divisor for FLASH Clock Divider, bit 3
FCDIV_FDIV4:        equ    4                                         ; Divisor for FLASH Clock Divider, bit 4
FCDIV_FDIV5:        equ    5                                         ; Divisor for FLASH Clock Divider, bit 5
FCDIV_PRDIV8:       equ    6                                         ; Prescale (Divide) FLASH Clock by 8
FCDIV_FDIVLD:       equ    7                                         ; Divisor Loaded Status Flag
; bit position masks
mFCDIV_FDIV0:       equ    %00000001
mFCDIV_FDIV1:       equ    %00000010
mFCDIV_FDIV2:       equ    %00000100
mFCDIV_FDIV3:       equ    %00001000
mFCDIV_FDIV4:       equ    %00010000
mFCDIV_FDIV5:       equ    %00100000
mFCDIV_PRDIV8:      equ    %01000000
mFCDIV_FDIVLD:      equ    %10000000


;*** FOPT - Flash Options Register; 0x00001821 ***
FOPT:               equ    $00001821                                ;*** FOPT - Flash Options Register; 0x00001821 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
FOPT_SEC0:          equ    0                                         ; Flash Security Bit 0
FOPT_SEC1:          equ    1                                         ; Flash Security Bit 1
FOPT_KEYEN0:        equ    6                                         ; Backdoor Key Security Enable Bit 0
FOPT_KEYEN1:        equ    7                                         ; Backdoor Key Security Enable Bit 1
; bit position masks
mFOPT_SEC0:         equ    %00000001
mFOPT_SEC1:         equ    %00000010
mFOPT_KEYEN0:       equ    %01000000
mFOPT_KEYEN1:       equ    %10000000


;*** FCNFG - Flash Configuration Register; 0x00001823 ***
FCNFG:              equ    $00001823                                ;*** FCNFG - Flash Configuration Register; 0x00001823 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
FCNFG_KEYACC:       equ    5                                         ; Enable Security Key Writing
; bit position masks
mFCNFG_KEYACC:      equ    %00100000


;*** FPROT - Flash Protection Register; 0x00001824 ***
FPROT:              equ    $00001824                                ;*** FPROT - Flash Protection Register; 0x00001824 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
FPROT_FPOPEN:       equ    0                                         ; Flash Protection Open
FPROT_FPS0:         equ    1                                         ; Flash Protection Size, bit 0
FPROT_FPS1:         equ    2                                         ; Flash Protection Size, bit 1
FPROT_FPS2:         equ    3                                         ; Flash Protection Size, bit 2
FPROT_FPS3:         equ    4                                         ; Flash Protection Size, bit 3
FPROT_FPS4:         equ    5                                         ; Flash Protection Size, bit 4
FPROT_FPS5:         equ    6                                         ; Flash Protection Size, bit 5
FPROT_FPS6:         equ    7                                         ; Flash Protection Size, bit 6
; bit position masks
mFPROT_FPOPEN:      equ    %00000001
mFPROT_FPS0:        equ    %00000010
mFPROT_FPS1:        equ    %00000100
mFPROT_FPS2:        equ    %00001000
mFPROT_FPS3:        equ    %00010000
mFPROT_FPS4:        equ    %00100000
mFPROT_FPS5:        equ    %01000000
mFPROT_FPS6:        equ    %10000000


;*** FSTAT - Flash Status Register; 0x00001825 ***
FSTAT:              equ    $00001825                                ;*** FSTAT - Flash Status Register; 0x00001825 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
FSTAT_FBLANK:       equ    2                                         ; FLASH Flag Indicating the Erase Verify Operation Status
FSTAT_FACCERR:      equ    4                                         ; FLASH Access Error Flag
FSTAT_FPVIOL:       equ    5                                         ; FLASH Protection Violation Flag
FSTAT_FCCF:         equ    6                                         ; FLASH Command Complete Interrupt Flag
FSTAT_FCBEF:        equ    7                                         ; FLASH Command Buffer Empty Flag
; bit position masks
;mFSTAT_FBLANK:      equ    %00000100
;mFSTAT_FACCERR:     equ    %00010000
;mFSTAT_FPVIOL:      equ    %00100000
;mFSTAT_FCCF:        equ    %01000000
;mFSTAT_FCBEF:       equ    %10000000
mFBLANK:      equ    %00000100
mFACCERR:     equ    %00010000
mFPVIOL:      equ    %00100000
mFCCF:        equ    %01000000
mFCBEF:       equ    %10000000

;*** FCMD - Flash Command Register; 0x00001826 ***
FCMD:               equ    $00001826                                ;*** FCMD - Flash Command Register; 0x00001826 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
FCMD_FCMD0:         equ    0                                         ; Flash Command, bit 0
FCMD_FCMD1:         equ    1                                         ; Flash Command, bit 1
FCMD_FCMD2:         equ    2                                         ; Flash Command, bit 2
FCMD_FCMD3:         equ    3                                         ; Flash Command, bit 3
FCMD_FCMD4:         equ    4                                         ; Flash Command, bit 4
FCMD_FCMD5:         equ    5                                         ; Flash Command, bit 5
FCMD_FCMD6:         equ    6                                         ; Flash Command, bit 6
; bit position masks
mFCMD_FCMD0:        equ    %00000001
mFCMD_FCMD1:        equ    %00000010
mFCMD_FCMD2:        equ    %00000100
mFCMD_FCMD3:        equ    %00001000
mFCMD_FCMD4:        equ    %00010000
mFCMD_FCMD5:        equ    %00100000
mFCMD_FCMD6:        equ    %01000000


;*** RTCSC - RTC Status and Control Register; 0x00001830 ***
RTCSC:              equ    $00001830                                ;*** RTCSC - RTC Status and Control Register; 0x00001830 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
RTCSC_RTCPS0:       equ    0                                         ; Real-Time Clock Prescaler Select, bit 0
RTCSC_RTCPS1:       equ    1                                         ; Real-Time Clock Prescaler Select, bit 1
RTCSC_RTCPS2:       equ    2                                         ; Real-Time Clock Prescaler Select, bit 2
RTCSC_RTCPS3:       equ    3                                         ; Real-Time Clock Prescaler Select, bit 3
RTCSC_RTIE:         equ    4                                         ; Real-Time Interrupt Enable
RTCSC_RTCLKS0:      equ    5                                         ; Real-Time Clock Source Select, bit 0
RTCSC_RTCLKS1:      equ    6                                         ; Real-Time Clock Source Select, bit 1
RTCSC_RTIF:         equ    7                                         ; Real-Time Interrupt Flag
; bit position masks
mRTCSC_RTCPS0:      equ    %00000001
mRTCSC_RTCPS1:      equ    %00000010
mRTCSC_RTCPS2:      equ    %00000100
mRTCSC_RTCPS3:      equ    %00001000
mRTCSC_RTIE:        equ    %00010000
mRTCSC_RTCLKS0:     equ    %00100000
mRTCSC_RTCLKS1:     equ    %01000000
mRTCSC_RTIF:        equ    %10000000


;*** RTCCNT - RTC Counter Register; 0x00001831 ***
RTCCNT:             equ    $00001831                                ;*** RTCCNT - RTC Counter Register; 0x00001831 ***


;*** RTCMOD - RTC Modulo Register; 0x00001832 ***
RTCMOD:             equ    $00001832                                ;*** RTCMOD - RTC Modulo Register; 0x00001832 ***


;*** SPI2C1 - SPI2 Control Register 1; 0x00001838 ***
SPI2C1:             equ    $00001838                                ;*** SPI2C1 - SPI2 Control Register 1; 0x00001838 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SPI2C1_LSBFE:       equ    0                                         ; LSB First (Shifter Direction)
SPI2C1_SSOE:        equ    1                                         ; Slave Select Output Enable
SPI2C1_CPHA:        equ    2                                         ; Clock Phase
SPI2C1_CPOL:        equ    3                                         ; Clock Polarity
SPI2C1_MSTR:        equ    4                                         ; Master/Slave Mode Select
SPI2C1_SPTIE:       equ    5                                         ; SPI Transmit Interrupt Enable
SPI2C1_SPE:         equ    6                                         ; SPI System Enable
SPI2C1_SPIE:        equ    7                                         ; SPI Interrupt Enable (for SPRF and MODF)
; bit position masks
mSPI2C1_LSBFE:      equ    %00000001
mSPI2C1_SSOE:       equ    %00000010
mSPI2C1_CPHA:       equ    %00000100
mSPI2C1_CPOL:       equ    %00001000
mSPI2C1_MSTR:       equ    %00010000
mSPI2C1_SPTIE:      equ    %00100000
mSPI2C1_SPE:        equ    %01000000
mSPI2C1_SPIE:       equ    %10000000


;*** SPI2C2 - SPI2 Control Register 2; 0x00001839 ***
SPI2C2:             equ    $00001839                                ;*** SPI2C2 - SPI2 Control Register 2; 0x00001839 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SPI2C2_SPC0:        equ    0                                         ; SPI Pin Control 0
SPI2C2_SPISWAI:     equ    1                                         ; SPI Stop in Wait Mode
SPI2C2_BIDIROE:     equ    3                                         ; Bidirectional Mode Output Enable
SPI2C2_MODFEN:      equ    4                                         ; Master Mode-Fault Function Enable
; bit position masks
mSPI2C2_SPC0:       equ    %00000001
mSPI2C2_SPISWAI:    equ    %00000010
mSPI2C2_BIDIROE:    equ    %00001000
mSPI2C2_MODFEN:     equ    %00010000


;*** SPI2BR - SPI2 Baud Rate Register; 0x0000183A ***
SPI2BR:             equ    $0000183A                                ;*** SPI2BR - SPI2 Baud Rate Register; 0x0000183A ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SPI2BR_SPR0:        equ    0                                         ; SPI Baud Rate Divisor Bit 0
SPI2BR_SPR1:        equ    1                                         ; SPI Baud Rate Divisor Bit 1
SPI2BR_SPR2:        equ    2                                         ; SPI Baud Rate Divisor Bit 2
SPI2BR_SPPR0:       equ    4                                         ; SPI Baud Rate Prescale Divisor Bit 0
SPI2BR_SPPR1:       equ    5                                         ; SPI Baud Rate Prescale Divisor Bit 1
SPI2BR_SPPR2:       equ    6                                         ; SPI Baud Rate Prescale Divisor Bit 2
; bit position masks
mSPI2BR_SPR0:       equ    %00000001
mSPI2BR_SPR1:       equ    %00000010
mSPI2BR_SPR2:       equ    %00000100
mSPI2BR_SPPR0:      equ    %00010000
mSPI2BR_SPPR1:      equ    %00100000
mSPI2BR_SPPR2:      equ    %01000000


;*** SPI2S - SPI2 Status Register; 0x0000183B ***
SPI2S:              equ    $0000183B                                ;*** SPI2S - SPI2 Status Register; 0x0000183B ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SPI2S_MODF:         equ    4                                         ; Master Mode Fault Flag
SPI2S_SPTEF:        equ    5                                         ; SPI Transmit Buffer Empty Flag
SPI2S_SPRF:         equ    7                                         ; SPI Read Buffer Full Flag
; bit position masks
mSPI2S_MODF:        equ    %00010000
mSPI2S_SPTEF:       equ    %00100000
mSPI2S_SPRF:        equ    %10000000


;*** SPI2D - SPI2 Data Register; 0x0000183D ***
SPI2D:              equ    $0000183D                                ;*** SPI2D - SPI2 Data Register; 0x0000183D ***


;*** PTAPE - Port A Pull Enable Register; 0x00001840 ***
PTAPE:              equ    $00001840                                ;*** PTAPE - Port A Pull Enable Register; 0x00001840 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTAPE_PTAPE0:       equ    0                                         ; Internal Pull Enable for Port A Bit 0
PTAPE_PTAPE1:       equ    1                                         ; Internal Pull Enable for Port A Bit 1
PTAPE_PTAPE2:       equ    2                                         ; Internal Pull Enable for Port A Bit 2
PTAPE_PTAPE3:       equ    3                                         ; Internal Pull Enable for Port A Bit 3
PTAPE_PTAPE4:       equ    4                                         ; Internal Pull Enable for Port A Bit 4
PTAPE_PTAPE5:       equ    5                                         ; Internal Pull Enable for Port A Bit 5
PTAPE_PTAPE6:       equ    6                                         ; Internal Pull Enable for Port A Bit 6
PTAPE_PTAPE7:       equ    7                                         ; Internal Pull Enable for Port A Bit 7
; bit position masks
mPTAPE_PTAPE0:      equ    %00000001
mPTAPE_PTAPE1:      equ    %00000010
mPTAPE_PTAPE2:      equ    %00000100
mPTAPE_PTAPE3:      equ    %00001000
mPTAPE_PTAPE4:      equ    %00010000
mPTAPE_PTAPE5:      equ    %00100000
mPTAPE_PTAPE6:      equ    %01000000
mPTAPE_PTAPE7:      equ    %10000000


;*** PTASE - Port A Slew Rate Enable Register; 0x00001841 ***
PTASE:              equ    $00001841                                ;*** PTASE - Port A Slew Rate Enable Register; 0x00001841 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTASE_PTASE0:       equ    0                                         ; Output Slew Rate Enable for Port A Bit 0
PTASE_PTASE1:       equ    1                                         ; Output Slew Rate Enable for Port A Bit 1
PTASE_PTASE2:       equ    2                                         ; Output Slew Rate Enable for Port A Bit 2
PTASE_PTASE3:       equ    3                                         ; Output Slew Rate Enable for Port A Bit 3
PTASE_PTASE4:       equ    4                                         ; Output Slew Rate Enable for Port A Bit 4
PTASE_PTASE5:       equ    5                                         ; Output Slew Rate Enable for Port A Bit 5
PTASE_PTASE6:       equ    6                                         ; Output Slew Rate Enable for Port A Bit 6
PTASE_PTASE7:       equ    7                                         ; Output Slew Rate Enable for Port A Bit 7
; bit position masks
mPTASE_PTASE0:      equ    %00000001
mPTASE_PTASE1:      equ    %00000010
mPTASE_PTASE2:      equ    %00000100
mPTASE_PTASE3:      equ    %00001000
mPTASE_PTASE4:      equ    %00010000
mPTASE_PTASE5:      equ    %00100000
mPTASE_PTASE6:      equ    %01000000
mPTASE_PTASE7:      equ    %10000000


;*** PTADS - Port A Drive Strength Selection Register; 0x00001842 ***
PTADS:              equ    $00001842                                ;*** PTADS - Port A Drive Strength Selection Register; 0x00001842 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTADS_PTADS0:       equ    0                                         ; Output Drive Strength Selection for Port A Bit 0
PTADS_PTADS1:       equ    1                                         ; Output Drive Strength Selection for Port A Bit 1
PTADS_PTADS2:       equ    2                                         ; Output Drive Strength Selection for Port A Bit 2
PTADS_PTADS3:       equ    3                                         ; Output Drive Strength Selection for Port A Bit 3
PTADS_PTADS4:       equ    4                                         ; Output Drive Strength Selection for Port A Bit 4
PTADS_PTADS5:       equ    5                                         ; Output Drive Strength Selection for Port A Bit 5
PTADS_PTADS6:       equ    6                                         ; Output Drive Strength Selection for Port A Bit 6
PTADS_PTADS7:       equ    7                                         ; Output Drive Strength Selection for Port A Bit 7
; bit position masks
mPTADS_PTADS0:      equ    %00000001
mPTADS_PTADS1:      equ    %00000010
mPTADS_PTADS2:      equ    %00000100
mPTADS_PTADS3:      equ    %00001000
mPTADS_PTADS4:      equ    %00010000
mPTADS_PTADS5:      equ    %00100000
mPTADS_PTADS6:      equ    %01000000
mPTADS_PTADS7:      equ    %10000000


;*** PTBPE - Port B Pull Enable Register; 0x00001844 ***
PTBPE:              equ    $00001844                                ;*** PTBPE - Port B Pull Enable Register; 0x00001844 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTBPE_PTBPE0:       equ    0                                         ; Internal Pull Enable for Port B Bit 0
PTBPE_PTBPE1:       equ    1                                         ; Internal Pull Enable for Port B Bit 1
PTBPE_PTBPE2:       equ    2                                         ; Internal Pull Enable for Port B Bit 2
PTBPE_PTBPE3:       equ    3                                         ; Internal Pull Enable for Port B Bit 3
PTBPE_PTBPE4:       equ    4                                         ; Internal Pull Enable for Port B Bit 4
PTBPE_PTBPE5:       equ    5                                         ; Internal Pull Enable for Port B Bit 5
PTBPE_PTBPE6:       equ    6                                         ; Internal Pull Enable for Port B Bit 6
PTBPE_PTBPE7:       equ    7                                         ; Internal Pull Enable for Port B Bit 7
; bit position masks
mPTBPE_PTBPE0:      equ    %00000001
mPTBPE_PTBPE1:      equ    %00000010
mPTBPE_PTBPE2:      equ    %00000100
mPTBPE_PTBPE3:      equ    %00001000
mPTBPE_PTBPE4:      equ    %00010000
mPTBPE_PTBPE5:      equ    %00100000
mPTBPE_PTBPE6:      equ    %01000000
mPTBPE_PTBPE7:      equ    %10000000


;*** PTBSE - Port B Slew Rate Enable Register; 0x00001845 ***
PTBSE:              equ    $00001845                                ;*** PTBSE - Port B Slew Rate Enable Register; 0x00001845 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTBSE_PTBSE0:       equ    0                                         ; Output Slew Rate Enable for Port B Bit 0
PTBSE_PTBSE1:       equ    1                                         ; Output Slew Rate Enable for Port B Bit 1
PTBSE_PTBSE2:       equ    2                                         ; Output Slew Rate Enable for Port B Bit 2
PTBSE_PTBSE3:       equ    3                                         ; Output Slew Rate Enable for Port B Bit 3
PTBSE_PTBSE4:       equ    4                                         ; Output Slew Rate Enable for Port B Bit 4
PTBSE_PTBSE5:       equ    5                                         ; Output Slew Rate Enable for Port B Bit 5
PTBSE_PTBSE6:       equ    6                                         ; Output Slew Rate Enable for Port B Bit 6
PTBSE_PTBSE7:       equ    7                                         ; Output Slew Rate Enable for Port B Bit 7
; bit position masks
mPTBSE_PTBSE0:      equ    %00000001
mPTBSE_PTBSE1:      equ    %00000010
mPTBSE_PTBSE2:      equ    %00000100
mPTBSE_PTBSE3:      equ    %00001000
mPTBSE_PTBSE4:      equ    %00010000
mPTBSE_PTBSE5:      equ    %00100000
mPTBSE_PTBSE6:      equ    %01000000
mPTBSE_PTBSE7:      equ    %10000000


;*** PTBDS - Port B Drive Strength Selection Register; 0x00001846 ***
PTBDS:              equ    $00001846                                ;*** PTBDS - Port B Drive Strength Selection Register; 0x00001846 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTBDS_PTBDS0:       equ    0                                         ; Output Drive Strength Selection for Port B Bit 0
PTBDS_PTBDS1:       equ    1                                         ; Output Drive Strength Selection for Port B Bit 1
PTBDS_PTBDS2:       equ    2                                         ; Output Drive Strength Selection for Port B Bit 2
PTBDS_PTBDS3:       equ    3                                         ; Output Drive Strength Selection for Port B Bit 3
PTBDS_PTBDS4:       equ    4                                         ; Output Drive Strength Selection for Port B Bit 4
PTBDS_PTBDS5:       equ    5                                         ; Output Drive Strength Selection for Port B Bit 5
PTBDS_PTBDS6:       equ    6                                         ; Output Drive Strength Selection for Port B Bit 6
PTBDS_PTBDS7:       equ    7                                         ; Output Drive Strength Selection for Port B Bit 7
; bit position masks
mPTBDS_PTBDS0:      equ    %00000001
mPTBDS_PTBDS1:      equ    %00000010
mPTBDS_PTBDS2:      equ    %00000100
mPTBDS_PTBDS3:      equ    %00001000
mPTBDS_PTBDS4:      equ    %00010000
mPTBDS_PTBDS5:      equ    %00100000
mPTBDS_PTBDS6:      equ    %01000000
mPTBDS_PTBDS7:      equ    %10000000


;*** PTCPE - Port C Pull Enable Register; 0x00001848 ***
PTCPE:              equ    $00001848                                ;*** PTCPE - Port C Pull Enable Register; 0x00001848 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTCPE_PTCPE0:       equ    0                                         ; Internal Pull Enable for Port C Bit 0
PTCPE_PTCPE1:       equ    1                                         ; Internal Pull Enable for Port C Bit 1
PTCPE_PTCPE2:       equ    2                                         ; Internal Pull Enable for Port C Bit 2
PTCPE_PTCPE3:       equ    3                                         ; Internal Pull Enable for Port C Bit 3
PTCPE_PTCPE4:       equ    4                                         ; Internal Pull Enable for Port C Bit 4
PTCPE_PTCPE5:       equ    5                                         ; Internal Pull Enable for Port C Bit 5
PTCPE_PTCPE6:       equ    6                                         ; Internal Pull Enable for Port C Bit 6
PTCPE_PTCPE7:       equ    7                                         ; Internal Pull Enable for Port C Bit 7
; bit position masks
mPTCPE_PTCPE0:      equ    %00000001
mPTCPE_PTCPE1:      equ    %00000010
mPTCPE_PTCPE2:      equ    %00000100
mPTCPE_PTCPE3:      equ    %00001000
mPTCPE_PTCPE4:      equ    %00010000
mPTCPE_PTCPE5:      equ    %00100000
mPTCPE_PTCPE6:      equ    %01000000
mPTCPE_PTCPE7:      equ    %10000000


;*** PTCSE - Port C Slew Rate Enable Register; 0x00001849 ***
PTCSE:              equ    $00001849                                ;*** PTCSE - Port C Slew Rate Enable Register; 0x00001849 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTCSE_PTCSE0:       equ    0                                         ; Output Slew Rate Enable for Port C Bit 0
PTCSE_PTCSE1:       equ    1                                         ; Output Slew Rate Enable for Port C Bit 1
PTCSE_PTCSE2:       equ    2                                         ; Output Slew Rate Enable for Port C Bit 2
PTCSE_PTCSE3:       equ    3                                         ; Output Slew Rate Enable for Port C Bit 3
PTCSE_PTCSE4:       equ    4                                         ; Output Slew Rate Enable for Port C Bit 4
PTCSE_PTCSE5:       equ    5                                         ; Output Slew Rate Enable for Port C Bit 5
PTCSE_PTCSE6:       equ    6                                         ; Output Slew Rate Enable for Port C Bit 6
PTCSE_PTCSE7:       equ    7                                         ; Output Slew Rate Enable for Port C Bit 7
; bit position masks
mPTCSE_PTCSE0:      equ    %00000001
mPTCSE_PTCSE1:      equ    %00000010
mPTCSE_PTCSE2:      equ    %00000100
mPTCSE_PTCSE3:      equ    %00001000
mPTCSE_PTCSE4:      equ    %00010000
mPTCSE_PTCSE5:      equ    %00100000
mPTCSE_PTCSE6:      equ    %01000000
mPTCSE_PTCSE7:      equ    %10000000


;*** PTCDS - Port C Drive Strength Selection Register; 0x0000184A ***
PTCDS:              equ    $0000184A                                ;*** PTCDS - Port C Drive Strength Selection Register; 0x0000184A ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTCDS_PTCDS0:       equ    0                                         ; Output Drive Strength Selection for Port C Bit 0
PTCDS_PTCDS1:       equ    1                                         ; Output Drive Strength Selection for Port C Bit 1
PTCDS_PTCDS2:       equ    2                                         ; Output Drive Strength Selection for Port C Bit 2
PTCDS_PTCDS3:       equ    3                                         ; Output Drive Strength Selection for Port C Bit 3
PTCDS_PTCDS4:       equ    4                                         ; Output Drive Strength Selection for Port C Bit 4
PTCDS_PTCDS5:       equ    5                                         ; Output Drive Strength Selection for Port C Bit 5
PTCDS_PTCDS6:       equ    6                                         ; Output Drive Strength Selection for Port C Bit 6
PTCDS_PTCDS7:       equ    7                                         ; Output Drive Strength Selection for Port C Bit 7
; bit position masks
mPTCDS_PTCDS0:      equ    %00000001
mPTCDS_PTCDS1:      equ    %00000010
mPTCDS_PTCDS2:      equ    %00000100
mPTCDS_PTCDS3:      equ    %00001000
mPTCDS_PTCDS4:      equ    %00010000
mPTCDS_PTCDS5:      equ    %00100000
mPTCDS_PTCDS6:      equ    %01000000
mPTCDS_PTCDS7:      equ    %10000000


;*** PTDPE - Port D Pull Enable Register; 0x0000184C ***
PTDPE:              equ    $0000184C                                ;*** PTDPE - Port D Pull Enable Register; 0x0000184C ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTDPE_PTDPE0:       equ    0                                         ; Internal Pull Enable for Port D Bit 0
PTDPE_PTDPE1:       equ    1                                         ; Internal Pull Enable for Port D Bit 1
PTDPE_PTDPE2:       equ    2                                         ; Internal Pull Enable for Port D Bit 2
PTDPE_PTDPE3:       equ    3                                         ; Internal Pull Enable for Port D Bit 3
PTDPE_PTDPE4:       equ    4                                         ; Internal Pull Enable for Port D Bit 4
PTDPE_PTDPE5:       equ    5                                         ; Internal Pull Enable for Port D Bit 5
PTDPE_PTDPE6:       equ    6                                         ; Internal Pull Enable for Port D Bit 6
PTDPE_PTDPE7:       equ    7                                         ; Internal Pull Enable for Port D Bit 7
; bit position masks
mPTDPE_PTDPE0:      equ    %00000001
mPTDPE_PTDPE1:      equ    %00000010
mPTDPE_PTDPE2:      equ    %00000100
mPTDPE_PTDPE3:      equ    %00001000
mPTDPE_PTDPE4:      equ    %00010000
mPTDPE_PTDPE5:      equ    %00100000
mPTDPE_PTDPE6:      equ    %01000000
mPTDPE_PTDPE7:      equ    %10000000


;*** PTDSE - Port D Slew Rate Enable Register; 0x0000184D ***
PTDSE:              equ    $0000184D                                ;*** PTDSE - Port D Slew Rate Enable Register; 0x0000184D ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTDSE_PTDSE0:       equ    0                                         ; Output Slew Rate Enable for Port D Bit 0
PTDSE_PTDSE1:       equ    1                                         ; Output Slew Rate Enable for Port D Bit 1
PTDSE_PTDSE2:       equ    2                                         ; Output Slew Rate Enable for Port D Bit 2
PTDSE_PTDSE3:       equ    3                                         ; Output Slew Rate Enable for Port D Bit 3
PTDSE_PTDSE4:       equ    4                                         ; Output Slew Rate Enable for Port D Bit 4
PTDSE_PTDSE5:       equ    5                                         ; Output Slew Rate Enable for Port D Bit 5
PTDSE_PTDSE6:       equ    6                                         ; Output Slew Rate Enable for Port D Bit 6
PTDSE_PTDSE7:       equ    7                                         ; Output Slew Rate Enable for Port D Bit 7
; bit position masks
mPTDSE_PTDSE0:      equ    %00000001
mPTDSE_PTDSE1:      equ    %00000010
mPTDSE_PTDSE2:      equ    %00000100
mPTDSE_PTDSE3:      equ    %00001000
mPTDSE_PTDSE4:      equ    %00010000
mPTDSE_PTDSE5:      equ    %00100000
mPTDSE_PTDSE6:      equ    %01000000
mPTDSE_PTDSE7:      equ    %10000000


;*** PTDDS - Port D Drive Strength Selection Register; 0x0000184E ***
PTDDS:              equ    $0000184E                                ;*** PTDDS - Port D Drive Strength Selection Register; 0x0000184E ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTDDS_PTDDS0:       equ    0                                         ; Output Drive Strength Selection for Port D Bit 0
PTDDS_PTDDS1:       equ    1                                         ; Output Drive Strength Selection for Port D Bit 1
PTDDS_PTDDS2:       equ    2                                         ; Output Drive Strength Selection for Port D Bit 2
PTDDS_PTDDS3:       equ    3                                         ; Output Drive Strength Selection for Port D Bit 3
PTDDS_PTDDS4:       equ    4                                         ; Output Drive Strength Selection for Port D Bit 4
PTDDS_PTDDS5:       equ    5                                         ; Output Drive Strength Selection for Port D Bit 5
PTDDS_PTDDS6:       equ    6                                         ; Output Drive Strength Selection for Port D Bit 6
PTDDS_PTDDS7:       equ    7                                         ; Output Drive Strength Selection for Port D Bit 7
; bit position masks
mPTDDS_PTDDS0:      equ    %00000001
mPTDDS_PTDDS1:      equ    %00000010
mPTDDS_PTDDS2:      equ    %00000100
mPTDDS_PTDDS3:      equ    %00001000
mPTDDS_PTDDS4:      equ    %00010000
mPTDDS_PTDDS5:      equ    %00100000
mPTDDS_PTDDS6:      equ    %01000000
mPTDDS_PTDDS7:      equ    %10000000


;*** PTEPE - Port E Pull Enable Register; 0x00001850 ***
PTEPE:              equ    $00001850                                ;*** PTEPE - Port E Pull Enable Register; 0x00001850 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTEPE_PTEPE0:       equ    0                                         ; Internal Pull Enable for Port E Bit 0
PTEPE_PTEPE1:       equ    1                                         ; Internal Pull Enable for Port E Bit 1
PTEPE_PTEPE2:       equ    2                                         ; Internal Pull Enable for Port E Bit 2
PTEPE_PTEPE3:       equ    3                                         ; Internal Pull Enable for Port E Bit 3
PTEPE_PTEPE4:       equ    4                                         ; Internal Pull Enable for Port E Bit 4
PTEPE_PTEPE5:       equ    5                                         ; Internal Pull Enable for Port E Bit 5
PTEPE_PTEPE6:       equ    6                                         ; Internal Pull Enable for Port E Bit 6
PTEPE_PTEPE7:       equ    7                                         ; Internal Pull Enable for Port E Bit 7
; bit position masks
mPTEPE_PTEPE0:      equ    %00000001
mPTEPE_PTEPE1:      equ    %00000010
mPTEPE_PTEPE2:      equ    %00000100
mPTEPE_PTEPE3:      equ    %00001000
mPTEPE_PTEPE4:      equ    %00010000
mPTEPE_PTEPE5:      equ    %00100000
mPTEPE_PTEPE6:      equ    %01000000
mPTEPE_PTEPE7:      equ    %10000000


;*** PTESE - Port E Slew Rate Enable Register; 0x00001851 ***
PTESE:              equ    $00001851                                ;*** PTESE - Port E Slew Rate Enable Register; 0x00001851 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTESE_PTESE0:       equ    0                                         ; Output Slew Rate Enable for Port E Bit 0
PTESE_PTESE1:       equ    1                                         ; Output Slew Rate Enable for Port E Bit 1
PTESE_PTESE2:       equ    2                                         ; Output Slew Rate Enable for Port E Bit 2
PTESE_PTESE3:       equ    3                                         ; Output Slew Rate Enable for Port E Bit 3
PTESE_PTESE4:       equ    4                                         ; Output Slew Rate Enable for Port E Bit 4
PTESE_PTESE5:       equ    5                                         ; Output Slew Rate Enable for Port E Bit 5
PTESE_PTESE6:       equ    6                                         ; Output Slew Rate Enable for Port E Bit 6
PTESE_PTESE7:       equ    7                                         ; Output Slew Rate Enable for Port E Bit 7
; bit position masks
mPTESE_PTESE0:      equ    %00000001
mPTESE_PTESE1:      equ    %00000010
mPTESE_PTESE2:      equ    %00000100
mPTESE_PTESE3:      equ    %00001000
mPTESE_PTESE4:      equ    %00010000
mPTESE_PTESE5:      equ    %00100000
mPTESE_PTESE6:      equ    %01000000
mPTESE_PTESE7:      equ    %10000000


;*** PTEDS - Port E Drive Strength Selection Register; 0x00001852 ***
PTEDS:              equ    $00001852                                ;*** PTEDS - Port E Drive Strength Selection Register; 0x00001852 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTEDS_PTEDS0:       equ    0                                         ; Output Drive Strength Selection for Port E Bit 0
PTEDS_PTEDS1:       equ    1                                         ; Output Drive Strength Selection for Port E Bit 1
PTEDS_PTEDS2:       equ    2                                         ; Output Drive Strength Selection for Port E Bit 2
PTEDS_PTEDS3:       equ    3                                         ; Output Drive Strength Selection for Port E Bit 3
PTEDS_PTEDS4:       equ    4                                         ; Output Drive Strength Selection for Port E Bit 4
PTEDS_PTEDS5:       equ    5                                         ; Output Drive Strength Selection for Port E Bit 5
PTEDS_PTEDS6:       equ    6                                         ; Output Drive Strength Selection for Port E Bit 6
PTEDS_PTEDS7:       equ    7                                         ; Output Drive Strength Selection for Port E Bit 7
; bit position masks
mPTEDS_PTEDS0:      equ    %00000001
mPTEDS_PTEDS1:      equ    %00000010
mPTEDS_PTEDS2:      equ    %00000100
mPTEDS_PTEDS3:      equ    %00001000
mPTEDS_PTEDS4:      equ    %00010000
mPTEDS_PTEDS5:      equ    %00100000
mPTEDS_PTEDS6:      equ    %01000000
mPTEDS_PTEDS7:      equ    %10000000


;*** PTFPE - Port F Pull Enable Register; 0x00001854 ***
PTFPE:              equ    $00001854                                ;*** PTFPE - Port F Pull Enable Register; 0x00001854 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTFPE_PTFPE0:       equ    0                                         ; Internal Pull Enable for Port F Bit 0
PTFPE_PTFPE1:       equ    1                                         ; Internal Pull Enable for Port F Bit 1
PTFPE_PTFPE2:       equ    2                                         ; Internal Pull Enable for Port F Bit 2
PTFPE_PTFPE3:       equ    3                                         ; Internal Pull Enable for Port F Bit 3
PTFPE_PTFPE4:       equ    4                                         ; Internal Pull Enable for Port F Bit 4
PTFPE_PTFPE5:       equ    5                                         ; Internal Pull Enable for Port F Bit 5
PTFPE_PTFPE6:       equ    6                                         ; Internal Pull Enable for Port F Bit 6
PTFPE_PTFPE7:       equ    7                                         ; Internal Pull Enable for Port F Bit 7
; bit position masks
mPTFPE_PTFPE0:      equ    %00000001
mPTFPE_PTFPE1:      equ    %00000010
mPTFPE_PTFPE2:      equ    %00000100
mPTFPE_PTFPE3:      equ    %00001000
mPTFPE_PTFPE4:      equ    %00010000
mPTFPE_PTFPE5:      equ    %00100000
mPTFPE_PTFPE6:      equ    %01000000
mPTFPE_PTFPE7:      equ    %10000000


;*** PTFSE - Port F Slew Rate Enable Register; 0x00001855 ***
PTFSE:              equ    $00001855                                ;*** PTFSE - Port F Slew Rate Enable Register; 0x00001855 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTFSE_PTFSE0:       equ    0                                         ; Output Slew Rate Enable for Port F Bit 0
PTFSE_PTFSE1:       equ    1                                         ; Output Slew Rate Enable for Port F Bit 1
PTFSE_PTFSE2:       equ    2                                         ; Output Slew Rate Enable for Port F Bit 2
PTFSE_PTFSE3:       equ    3                                         ; Output Slew Rate Enable for Port F Bit 3
PTFSE_PTFSE4:       equ    4                                         ; Output Slew Rate Enable for Port F Bit 4
PTFSE_PTFSE5:       equ    5                                         ; Output Slew Rate Enable for Port F Bit 5
PTFSE_PTFSE6:       equ    6                                         ; Output Slew Rate Enable for Port F Bit 6
PTFSE_PTFSE7:       equ    7                                         ; Output Slew Rate Enable for Port F Bit 7
; bit position masks
mPTFSE_PTFSE0:      equ    %00000001
mPTFSE_PTFSE1:      equ    %00000010
mPTFSE_PTFSE2:      equ    %00000100
mPTFSE_PTFSE3:      equ    %00001000
mPTFSE_PTFSE4:      equ    %00010000
mPTFSE_PTFSE5:      equ    %00100000
mPTFSE_PTFSE6:      equ    %01000000
mPTFSE_PTFSE7:      equ    %10000000


;*** PTFDS - Port F Drive Strength Selection Register; 0x00001856 ***
PTFDS:              equ    $00001856                                ;*** PTFDS - Port F Drive Strength Selection Register; 0x00001856 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTFDS_PTFDS0:       equ    0                                         ; Output Drive Strength Selection for Port F Bit 0
PTFDS_PTFDS1:       equ    1                                         ; Output Drive Strength Selection for Port F Bit 1
PTFDS_PTFDS2:       equ    2                                         ; Output Drive Strength Selection for Port F Bit 2
PTFDS_PTFDS3:       equ    3                                         ; Output Drive Strength Selection for Port F Bit 3
PTFDS_PTFDS4:       equ    4                                         ; Output Drive Strength Selection for Port F Bit 4
PTFDS_PTFDS5:       equ    5                                         ; Output Drive Strength Selection for Port F Bit 5
PTFDS_PTFDS6:       equ    6                                         ; Output Drive Strength Selection for Port F Bit 6
PTFDS_PTFDS7:       equ    7                                         ; Output Drive Strength Selection for Port F Bit 7
; bit position masks
mPTFDS_PTFDS0:      equ    %00000001
mPTFDS_PTFDS1:      equ    %00000010
mPTFDS_PTFDS2:      equ    %00000100
mPTFDS_PTFDS3:      equ    %00001000
mPTFDS_PTFDS4:      equ    %00010000
mPTFDS_PTFDS5:      equ    %00100000
mPTFDS_PTFDS6:      equ    %01000000
mPTFDS_PTFDS7:      equ    %10000000


;*** PTGPE - Port G Pull Enable Register; 0x00001858 ***
PTGPE:              equ    $00001858                                ;*** PTGPE - Port G Pull Enable Register; 0x00001858 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTGPE_PTGPE0:       equ    0                                         ; Internal Pull Enable for Port G Bit 0
PTGPE_PTGPE1:       equ    1                                         ; Internal Pull Enable for Port G Bit 1
PTGPE_PTGPE2:       equ    2                                         ; Internal Pull Enable for Port G Bit 2
PTGPE_PTGPE3:       equ    3                                         ; Internal Pull Enable for Port G Bit 3
PTGPE_PTGPE4:       equ    4                                         ; Internal Pull Enable for Port G Bit 4
PTGPE_PTGPE5:       equ    5                                         ; Internal Pull Enable for Port G Bit 5
PTGPE_PTGPE6:       equ    6                                         ; Internal Pull Enable for Port G Bit 6
PTGPE_PTGPE7:       equ    7                                         ; Internal Pull Enable for Port G Bit 7
; bit position masks
mPTGPE_PTGPE0:      equ    %00000001
mPTGPE_PTGPE1:      equ    %00000010
mPTGPE_PTGPE2:      equ    %00000100
mPTGPE_PTGPE3:      equ    %00001000
mPTGPE_PTGPE4:      equ    %00010000
mPTGPE_PTGPE5:      equ    %00100000
mPTGPE_PTGPE6:      equ    %01000000
mPTGPE_PTGPE7:      equ    %10000000


;*** PTGSE - Port G Slew Rate Enable Register; 0x00001859 ***
PTGSE:              equ    $00001859                                ;*** PTGSE - Port G Slew Rate Enable Register; 0x00001859 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTGSE_PTGSE0:       equ    0                                         ; Output Slew Rate Enable for Port G Bit 0
PTGSE_PTGSE1:       equ    1                                         ; Output Slew Rate Enable for Port G Bit 1
PTGSE_PTGSE2:       equ    2                                         ; Output Slew Rate Enable for Port G Bit 2
PTGSE_PTGSE3:       equ    3                                         ; Output Slew Rate Enable for Port G Bit 3
PTGSE_PTGSE4:       equ    4                                         ; Output Slew Rate Enable for Port G Bit 4
PTGSE_PTGSE5:       equ    5                                         ; Output Slew Rate Enable for Port G Bit 5
PTGSE_PTGSE6:       equ    6                                         ; Output Slew Rate Enable for Port G Bit 6
PTGSE_PTGSE7:       equ    7                                         ; Output Slew Rate Enable for Port G Bit 7
; bit position masks
mPTGSE_PTGSE0:      equ    %00000001
mPTGSE_PTGSE1:      equ    %00000010
mPTGSE_PTGSE2:      equ    %00000100
mPTGSE_PTGSE3:      equ    %00001000
mPTGSE_PTGSE4:      equ    %00010000
mPTGSE_PTGSE5:      equ    %00100000
mPTGSE_PTGSE6:      equ    %01000000
mPTGSE_PTGSE7:      equ    %10000000


;*** PTGDS - Port G Drive Strength Selection Register; 0x0000185A ***
PTGDS:              equ    $0000185A                                ;*** PTGDS - Port G Drive Strength Selection Register; 0x0000185A ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTGDS_PTGDS0:       equ    0                                         ; Output Drive Strength Selection for Port G Bit 0
PTGDS_PTGDS1:       equ    1                                         ; Output Drive Strength Selection for Port G Bit 1
PTGDS_PTGDS2:       equ    2                                         ; Output Drive Strength Selection for Port G Bit 2
PTGDS_PTGDS3:       equ    3                                         ; Output Drive Strength Selection for Port G Bit 3
PTGDS_PTGDS4:       equ    4                                         ; Output Drive Strength Selection for Port G Bit 4
PTGDS_PTGDS5:       equ    5                                         ; Output Drive Strength Selection for Port G Bit 5
PTGDS_PTGDS6:       equ    6                                         ; Output Drive Strength Selection for Port G Bit 6
PTGDS_PTGDS7:       equ    7                                         ; Output Drive Strength Selection for Port G Bit 7
; bit position masks
mPTGDS_PTGDS0:      equ    %00000001
mPTGDS_PTGDS1:      equ    %00000010
mPTGDS_PTGDS2:      equ    %00000100
mPTGDS_PTGDS3:      equ    %00001000
mPTGDS_PTGDS4:      equ    %00010000
mPTGDS_PTGDS5:      equ    %00100000
mPTGDS_PTGDS6:      equ    %01000000
mPTGDS_PTGDS7:      equ    %10000000


;*** PTHPE - Port H Pull Enable Register; 0x0000185C ***
PTHPE:              equ    $0000185C                                ;*** PTHPE - Port H Pull Enable Register; 0x0000185C ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTHPE_PTHPE0:       equ    0                                         ; Internal Pull Enable for Port H Bit 0
PTHPE_PTHPE1:       equ    1                                         ; Internal Pull Enable for Port H Bit 1
PTHPE_PTHPE2:       equ    2                                         ; Internal Pull Enable for Port H Bit 2
PTHPE_PTHPE3:       equ    3                                         ; Internal Pull Enable for Port H Bit 3
PTHPE_PTHPE4:       equ    4                                         ; Internal Pull Enable for Port H Bit 4
PTHPE_PTHPE5:       equ    5                                         ; Internal Pull Enable for Port H Bit 5
PTHPE_PTHPE6:       equ    6                                         ; Internal Pull Enable for Port H Bit 6
PTHPE_PTHPE7:       equ    7                                         ; Internal Pull Enable for Port H Bit 7
; bit position masks
mPTHPE_PTHPE0:      equ    %00000001
mPTHPE_PTHPE1:      equ    %00000010
mPTHPE_PTHPE2:      equ    %00000100
mPTHPE_PTHPE3:      equ    %00001000
mPTHPE_PTHPE4:      equ    %00010000
mPTHPE_PTHPE5:      equ    %00100000
mPTHPE_PTHPE6:      equ    %01000000
mPTHPE_PTHPE7:      equ    %10000000


;*** PTHSE - Port H Slew Rate Enable Register; 0x0000185D ***
PTHSE:              equ    $0000185D                                ;*** PTHSE - Port H Slew Rate Enable Register; 0x0000185D ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTHSE_PTHSE0:       equ    0                                         ; Output Slew Rate Enable for Port H Bit 0
PTHSE_PTHSE1:       equ    1                                         ; Output Slew Rate Enable for Port H Bit 1
PTHSE_PTHSE2:       equ    2                                         ; Output Slew Rate Enable for Port H Bit 2
PTHSE_PTHSE3:       equ    3                                         ; Output Slew Rate Enable for Port H Bit 3
PTHSE_PTHSE4:       equ    4                                         ; Output Slew Rate Enable for Port H Bit 4
PTHSE_PTHSE5:       equ    5                                         ; Output Slew Rate Enable for Port H Bit 5
PTHSE_PTHSE6:       equ    6                                         ; Output Slew Rate Enable for Port H Bit 6
PTHSE_PTHSE7:       equ    7                                         ; Output Slew Rate Enable for Port H Bit 7
; bit position masks
mPTHSE_PTHSE0:      equ    %00000001
mPTHSE_PTHSE1:      equ    %00000010
mPTHSE_PTHSE2:      equ    %00000100
mPTHSE_PTHSE3:      equ    %00001000
mPTHSE_PTHSE4:      equ    %00010000
mPTHSE_PTHSE5:      equ    %00100000
mPTHSE_PTHSE6:      equ    %01000000
mPTHSE_PTHSE7:      equ    %10000000


;*** PTHDS - Port H Drive Strength Selection Register; 0x0000185E ***
PTHDS:              equ    $0000185E                                ;*** PTHDS - Port H Drive Strength Selection Register; 0x0000185E ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTHDS_PTHDS0:       equ    0                                         ; Output Drive Strength Selection for Port H Bit 0
PTHDS_PTHDS1:       equ    1                                         ; Output Drive Strength Selection for Port H Bit 1
PTHDS_PTHDS2:       equ    2                                         ; Output Drive Strength Selection for Port H Bit 2
PTHDS_PTHDS3:       equ    3                                         ; Output Drive Strength Selection for Port H Bit 3
PTHDS_PTHDS4:       equ    4                                         ; Output Drive Strength Selection for Port H Bit 4
PTHDS_PTHDS5:       equ    5                                         ; Output Drive Strength Selection for Port H Bit 5
PTHDS_PTHDS6:       equ    6                                         ; Output Drive Strength Selection for Port H Bit 6
PTHDS_PTHDS7:       equ    7                                         ; Output Drive Strength Selection for Port H Bit 7
; bit position masks
mPTHDS_PTHDS0:      equ    %00000001
mPTHDS_PTHDS1:      equ    %00000010
mPTHDS_PTHDS2:      equ    %00000100
mPTHDS_PTHDS3:      equ    %00001000
mPTHDS_PTHDS4:      equ    %00010000
mPTHDS_PTHDS5:      equ    %00100000
mPTHDS_PTHDS6:      equ    %01000000
mPTHDS_PTHDS7:      equ    %10000000


;*** PTJPE - Port J Pull Enable Register; 0x00001860 ***
PTJPE:              equ    $00001860                                ;*** PTJPE - Port J Pull Enable Register; 0x00001860 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTJPE_PTJPE0:       equ    0                                         ; Internal Pull Enable for Port J Bit 0
PTJPE_PTJPE1:       equ    1                                         ; Internal Pull Enable for Port J Bit 1
PTJPE_PTJPE2:       equ    2                                         ; Internal Pull Enable for Port J Bit 2
PTJPE_PTJPE3:       equ    3                                         ; Internal Pull Enable for Port J Bit 3
PTJPE_PTJPE4:       equ    4                                         ; Internal Pull Enable for Port J Bit 4
PTJPE_PTJPE5:       equ    5                                         ; Internal Pull Enable for Port J Bit 5
PTJPE_PTJPE6:       equ    6                                         ; Internal Pull Enable for Port J Bit 6
PTJPE_PTJPE7:       equ    7                                         ; Internal Pull Enable for Port J Bit 7
; bit position masks
mPTJPE_PTJPE0:      equ    %00000001
mPTJPE_PTJPE1:      equ    %00000010
mPTJPE_PTJPE2:      equ    %00000100
mPTJPE_PTJPE3:      equ    %00001000
mPTJPE_PTJPE4:      equ    %00010000
mPTJPE_PTJPE5:      equ    %00100000
mPTJPE_PTJPE6:      equ    %01000000
mPTJPE_PTJPE7:      equ    %10000000


;*** PTJSE - Port J Slew Rate Enable Register; 0x00001861 ***
PTJSE:              equ    $00001861                                ;*** PTJSE - Port J Slew Rate Enable Register; 0x00001861 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTJSE_PTJSE0:       equ    0                                         ; Output Slew Rate Enable for Port J Bit 0
PTJSE_PTJSE1:       equ    1                                         ; Output Slew Rate Enable for Port J Bit 1
PTJSE_PTJSE2:       equ    2                                         ; Output Slew Rate Enable for Port J Bit 2
PTJSE_PTJSE3:       equ    3                                         ; Output Slew Rate Enable for Port J Bit 3
PTJSE_PTJSE4:       equ    4                                         ; Output Slew Rate Enable for Port J Bit 4
PTJSE_PTJSE5:       equ    5                                         ; Output Slew Rate Enable for Port J Bit 5
PTJSE_PTJSE6:       equ    6                                         ; Output Slew Rate Enable for Port J Bit 6
PTJSE_PTJSE7:       equ    7                                         ; Output Slew Rate Enable for Port J Bit 7
; bit position masks
mPTJSE_PTJSE0:      equ    %00000001
mPTJSE_PTJSE1:      equ    %00000010
mPTJSE_PTJSE2:      equ    %00000100
mPTJSE_PTJSE3:      equ    %00001000
mPTJSE_PTJSE4:      equ    %00010000
mPTJSE_PTJSE5:      equ    %00100000
mPTJSE_PTJSE6:      equ    %01000000
mPTJSE_PTJSE7:      equ    %10000000


;*** PTJDS - Port J Drive Strength Selection Register; 0x00001862 ***
PTJDS:              equ    $00001862                                ;*** PTJDS - Port J Drive Strength Selection Register; 0x00001862 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTJDS_PTJDS0:       equ    0                                         ; Output Drive Strength Selection for Port J Bit 0
PTJDS_PTJDS1:       equ    1                                         ; Output Drive Strength Selection for Port J Bit 1
PTJDS_PTJDS2:       equ    2                                         ; Output Drive Strength Selection for Port J Bit 2
PTJDS_PTJDS3:       equ    3                                         ; Output Drive Strength Selection for Port J Bit 3
PTJDS_PTJDS4:       equ    4                                         ; Output Drive Strength Selection for Port J Bit 4
PTJDS_PTJDS5:       equ    5                                         ; Output Drive Strength Selection for Port J Bit 5
PTJDS_PTJDS6:       equ    6                                         ; Output Drive Strength Selection for Port J Bit 6
PTJDS_PTJDS7:       equ    7                                         ; Output Drive Strength Selection for Port J Bit 7
; bit position masks
mPTJDS_PTJDS0:      equ    %00000001
mPTJDS_PTJDS1:      equ    %00000010
mPTJDS_PTJDS2:      equ    %00000100
mPTJDS_PTJDS3:      equ    %00001000
mPTJDS_PTJDS4:      equ    %00010000
mPTJDS_PTJDS5:      equ    %00100000
mPTJDS_PTJDS6:      equ    %01000000
mPTJDS_PTJDS7:      equ    %10000000


;*** IIC2A - IIC Address Register; 0x00001868 ***
IIC2A:              equ    $00001868                                ;*** IIC2A - IIC Address Register; 0x00001868 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
IIC2A_AD1:          equ    1                                         ; Slave Address Bit 1
IIC2A_AD2:          equ    2                                         ; Slave Address Bit 2
IIC2A_AD3:          equ    3                                         ; Slave Address Bit 3
IIC2A_AD4:          equ    4                                         ; Slave Address Bit 4
IIC2A_AD5:          equ    5                                         ; Slave Address Bit 5
IIC2A_AD6:          equ    6                                         ; Slave Address Bit 6
IIC2A_AD7:          equ    7                                         ; Slave Address Bit 7
; bit position masks
mIIC2A_AD1:         equ    %00000010
mIIC2A_AD2:         equ    %00000100
mIIC2A_AD3:         equ    %00001000
mIIC2A_AD4:         equ    %00010000
mIIC2A_AD5:         equ    %00100000
mIIC2A_AD6:         equ    %01000000
mIIC2A_AD7:         equ    %10000000


;*** IIC2F - IIC Frequency Divider Register; 0x00001869 ***
IIC2F:              equ    $00001869                                ;*** IIC2F - IIC Frequency Divider Register; 0x00001869 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
IIC2F_ICR0:         equ    0                                         ; IIC Clock Rate Bit 0
IIC2F_ICR1:         equ    1                                         ; IIC Clock Rate Bit 1
IIC2F_ICR2:         equ    2                                         ; IIC Clock Rate Bit 2
IIC2F_ICR3:         equ    3                                         ; IIC Clock Rate Bit 3
IIC2F_ICR4:         equ    4                                         ; IIC Clock Rate Bit 4
IIC2F_ICR5:         equ    5                                         ; IIC Clock Rate Bit 5
IIC2F_MULT0:        equ    6                                         ; Multiplier Factor Bit 0
IIC2F_MULT1:        equ    7                                         ; Multiplier Factor Bit 1
; bit position masks
mIIC2F_ICR0:        equ    %00000001
mIIC2F_ICR1:        equ    %00000010
mIIC2F_ICR2:        equ    %00000100
mIIC2F_ICR3:        equ    %00001000
mIIC2F_ICR4:        equ    %00010000
mIIC2F_ICR5:        equ    %00100000
mIIC2F_MULT0:       equ    %01000000
mIIC2F_MULT1:       equ    %10000000


;*** IIC2C1 - IIC Control Register 1; 0x0000186A ***
IIC2C1:             equ    $0000186A                                ;*** IIC2C1 - IIC Control Register 1; 0x0000186A ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
IIC2C1_RSTA:        equ    2                                         ; Repeat START
IIC2C1_TXAK:        equ    3                                         ; Transmit Acknowledge Enable
IIC2C1_TX:          equ    4                                         ; Transmit Mode Select
IIC2C1_MST:         equ    5                                         ; Master Mode Select
IIC2C1_IICIE:       equ    6                                         ; IIC Interrupt Enable
IIC2C1_IICEN:       equ    7                                         ; IIC Enable
; bit position masks
mIIC2C1_RSTA:       equ    %00000100
mIIC2C1_TXAK:       equ    %00001000
mIIC2C1_TX:         equ    %00010000
mIIC2C1_MST:        equ    %00100000
mIIC2C1_IICIE:      equ    %01000000
mIIC2C1_IICEN:      equ    %10000000


;*** IIC2S - IIC Status Register; 0x0000186B ***
IIC2S:              equ    $0000186B                                ;*** IIC2S - IIC Status Register; 0x0000186B ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
IIC2S_RXAK:         equ    0                                         ; Receive Acknowledge
IIC2S_IICIF:        equ    1                                         ; IIC Interrupt Flag
IIC2S_SRW:          equ    2                                         ; Slave Read/Write
IIC2S_ARBL:         equ    4                                         ; Arbitration Lost
IIC2S_BUSY:         equ    5                                         ; Bus Busy
IIC2S_IAAS:         equ    6                                         ; Addressed as a Slave
IIC2S_TCF:          equ    7                                         ; Transfer Complete Flag
; bit position masks
mIIC2S_RXAK:        equ    %00000001
mIIC2S_IICIF:       equ    %00000010
mIIC2S_SRW:         equ    %00000100
mIIC2S_ARBL:        equ    %00010000
mIIC2S_BUSY:        equ    %00100000
mIIC2S_IAAS:        equ    %01000000
mIIC2S_TCF:         equ    %10000000


;*** IIC2D - IIC Data I/O Register; 0x0000186C ***
IIC2D:              equ    $0000186C                                ;*** IIC2D - IIC Data I/O Register; 0x0000186C ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
IIC2D_DATA0:        equ    0                                         ; IIC Data Bit 0
IIC2D_DATA1:        equ    1                                         ; IIC Data Bit 1
IIC2D_DATA2:        equ    2                                         ; IIC Data Bit 2
IIC2D_DATA3:        equ    3                                         ; IIC Data Bit 3
IIC2D_DATA4:        equ    4                                         ; IIC Data Bit 4
IIC2D_DATA5:        equ    5                                         ; IIC Data Bit 5
IIC2D_DATA6:        equ    6                                         ; IIC Data Bit 6
IIC2D_DATA7:        equ    7                                         ; IIC Data Bit 7
; bit position masks
mIIC2D_DATA0:       equ    %00000001
mIIC2D_DATA1:       equ    %00000010
mIIC2D_DATA2:       equ    %00000100
mIIC2D_DATA3:       equ    %00001000
mIIC2D_DATA4:       equ    %00010000
mIIC2D_DATA5:       equ    %00100000
mIIC2D_DATA6:       equ    %01000000
mIIC2D_DATA7:       equ    %10000000


;*** IIC2C2 - IIC Control Register 2; 0x0000186D ***
IIC2C2:             equ    $0000186D                                ;*** IIC2C2 - IIC Control Register 2; 0x0000186D ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
IIC2C2_AD8:         equ    0                                         ; Slave Address Bit 8
IIC2C2_AD9:         equ    1                                         ; Slave Address Bit 9
IIC2C2_AD10:        equ    2                                         ; Slave Address Bit 10
IIC2C2_ADEXT:       equ    6                                         ; Address Extension
IIC2C2_GCAEN:       equ    7                                         ; General Call Address Enable
; bit position masks
mIIC2C2_AD8:        equ    %00000001
mIIC2C2_AD9:        equ    %00000010
mIIC2C2_AD10:       equ    %00000100
mIIC2C2_ADEXT:      equ    %01000000
mIIC2C2_GCAEN:      equ    %10000000


;*** SCI2BD - SCI2 Baud Rate Register; 0x00001870 ***
SCI2BD:             equ    $00001870                                ;*** SCI2BD - SCI2 Baud Rate Register; 0x00001870 ***


;*** SCI2BDH - SCI2 Baud Rate Register High; 0x00001870 ***
SCI2BDH:            equ    $00001870                                ;*** SCI2BDH - SCI2 Baud Rate Register High; 0x00001870 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SCI2BDH_SBR8:       equ    0                                         ; Baud Rate Modulo Divisor Bit 8
SCI2BDH_SBR9:       equ    1                                         ; Baud Rate Modulo Divisor Bit 9
SCI2BDH_SBR10:      equ    2                                         ; Baud Rate Modulo Divisor Bit 10
SCI2BDH_SBR11:      equ    3                                         ; Baud Rate Modulo Divisor Bit 11
SCI2BDH_SBR12:      equ    4                                         ; Baud Rate Modulo Divisor Bit 12
SCI2BDH_RXEDGIE:    equ    6                                         ; RxD Input Active Edge Interrupt Enable (for RXEDGIF)
SCI2BDH_LBKDIE:     equ    7                                         ; LIN Break Detect Interrupt Enable (for LBKDIF)
; bit position masks
mSCI2BDH_SBR8:      equ    %00000001
mSCI2BDH_SBR9:      equ    %00000010
mSCI2BDH_SBR10:     equ    %00000100
mSCI2BDH_SBR11:     equ    %00001000
mSCI2BDH_SBR12:     equ    %00010000
mSCI2BDH_RXEDGIE:   equ    %01000000
mSCI2BDH_LBKDIE:    equ    %10000000


;*** SCI2BDL - SCI2 Baud Rate Register Low; 0x00001871 ***
SCI2BDL:            equ    $00001871                                ;*** SCI2BDL - SCI2 Baud Rate Register Low; 0x00001871 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SCI2BDL_SBR0:       equ    0                                         ; Baud Rate Modulo Divisor Bit 0
SCI2BDL_SBR1:       equ    1                                         ; Baud Rate Modulo Divisor Bit 1
SCI2BDL_SBR2:       equ    2                                         ; Baud Rate Modulo Divisor Bit 2
SCI2BDL_SBR3:       equ    3                                         ; Baud Rate Modulo Divisor Bit 3
SCI2BDL_SBR4:       equ    4                                         ; Baud Rate Modulo Divisor Bit 4
SCI2BDL_SBR5:       equ    5                                         ; Baud Rate Modulo Divisor Bit 5
SCI2BDL_SBR6:       equ    6                                         ; Baud Rate Modulo Divisor Bit 6
SCI2BDL_SBR7:       equ    7                                         ; Baud Rate Modulo Divisor Bit 7
; bit position masks
mSCI2BDL_SBR0:      equ    %00000001
mSCI2BDL_SBR1:      equ    %00000010
mSCI2BDL_SBR2:      equ    %00000100
mSCI2BDL_SBR3:      equ    %00001000
mSCI2BDL_SBR4:      equ    %00010000
mSCI2BDL_SBR5:      equ    %00100000
mSCI2BDL_SBR6:      equ    %01000000
mSCI2BDL_SBR7:      equ    %10000000


;*** SCI2C1 - SCI2 Control Register 1; 0x00001872 ***
SCI2C1:             equ    $00001872                                ;*** SCI2C1 - SCI2 Control Register 1; 0x00001872 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SCI2C1_PT:          equ    0                                         ; Parity Type
SCI2C1_PE:          equ    1                                         ; Parity Enable
SCI2C1_ILT:         equ    2                                         ; Idle Line Type Select
SCI2C1_WAKE:        equ    3                                         ; Receiver Wakeup Method Select
SCI2C1_M:           equ    4                                         ; 9-Bit or 8-Bit Mode Select
SCI2C1_RSRC:        equ    5                                         ; Receiver Source Select
SCI2C1_SCISWAI:     equ    6                                         ; SCI Stops in Wait Mode
SCI2C1_LOOPS:       equ    7                                         ; Loop Mode Select
; bit position masks
mSCI2C1_PT:         equ    %00000001
mSCI2C1_PE:         equ    %00000010
mSCI2C1_ILT:        equ    %00000100
mSCI2C1_WAKE:       equ    %00001000
mSCI2C1_M:          equ    %00010000
mSCI2C1_RSRC:       equ    %00100000
mSCI2C1_SCISWAI:    equ    %01000000
mSCI2C1_LOOPS:      equ    %10000000


;*** SCI2C2 - SCI2 Control Register 2; 0x00001873 ***
SCI2C2:             equ    $00001873                                ;*** SCI2C2 - SCI2 Control Register 2; 0x00001873 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SCI2C2_SBK:         equ    0                                         ; Send Break
SCI2C2_RWU:         equ    1                                         ; Receiver Wakeup Control
SCI2C2_RE:          equ    2                                         ; Receiver Enable
SCI2C2_TE:          equ    3                                         ; Transmitter Enable
SCI2C2_ILIE:        equ    4                                         ; Idle Line Interrupt Enable (for IDLE)
SCI2C2_RIE:         equ    5                                         ; Receiver Interrupt Enable (for RDRF)
SCI2C2_TCIE:        equ    6                                         ; Transmission Complete Interrupt Enable (for TC)
SCI2C2_TIE:         equ    7                                         ; Transmit Interrupt Enable (for TDRE)
; bit position masks
mSCI2C2_SBK:        equ    %00000001
mSCI2C2_RWU:        equ    %00000010
mSCI2C2_RE:         equ    %00000100
mSCI2C2_TE:         equ    %00001000
mSCI2C2_ILIE:       equ    %00010000
mSCI2C2_RIE:        equ    %00100000
mSCI2C2_TCIE:       equ    %01000000
mSCI2C2_TIE:        equ    %10000000


;*** SCI2S1 - SCI2 Status Register 1; 0x00001874 ***
SCI2S1:             equ    $00001874                                ;*** SCI2S1 - SCI2 Status Register 1; 0x00001874 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SCI2S1_PF:          equ    0                                         ; Parity Error Flag
SCI2S1_FE:          equ    1                                         ; Framing Error Flag
SCI2S1_NF:          equ    2                                         ; Noise Flag
SCI2S1_OR:          equ    3                                         ; Receiver Overrun Flag
SCI2S1_IDLE:        equ    4                                         ; Idle Line Flag
SCI2S1_RDRF:        equ    5                                         ; Receive Data Register Full Flag
SCI2S1_TC:          equ    6                                         ; Transmission Complete Flag
SCI2S1_TDRE:        equ    7                                         ; Transmit Data Register Empty Flag
; bit position masks
mSCI2S1_PF:         equ    %00000001
mSCI2S1_FE:         equ    %00000010
mSCI2S1_NF:         equ    %00000100
mSCI2S1_OR:         equ    %00001000
mSCI2S1_IDLE:       equ    %00010000
mSCI2S1_RDRF:       equ    %00100000
mSCI2S1_TC:         equ    %01000000
mSCI2S1_TDRE:       equ    %10000000


;*** SCI2S2 - SCI2 Status Register 2; 0x00001875 ***
SCI2S2:             equ    $00001875                                ;*** SCI2S2 - SCI2 Status Register 2; 0x00001875 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SCI2S2_RAF:         equ    0                                         ; Receiver Active Flag
SCI2S2_LBKDE:       equ    1                                         ; LIN Break Detection Enable
SCI2S2_BRK13:       equ    2                                         ; Break Character Generation Length
SCI2S2_RWUID:       equ    3                                         ; Receive Wake Up Idle Detect
SCI2S2_RXINV:       equ    4                                         ; Receive Data Inversion
SCI2S2_RXEDGIF:     equ    6                                         ; RxD Pin Active Edge Interrupt Flag
SCI2S2_LBKDIF:      equ    7                                         ; LIN Break Detect Interrupt Flag
; bit position masks
mSCI2S2_RAF:        equ    %00000001
mSCI2S2_LBKDE:      equ    %00000010
mSCI2S2_BRK13:      equ    %00000100
mSCI2S2_RWUID:      equ    %00001000
mSCI2S2_RXINV:      equ    %00010000
mSCI2S2_RXEDGIF:    equ    %01000000
mSCI2S2_LBKDIF:     equ    %10000000


;*** SCI2C3 - SCI2 Control Register 3; 0x00001876 ***
SCI2C3:             equ    $00001876                                ;*** SCI2C3 - SCI2 Control Register 3; 0x00001876 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SCI2C3_PEIE:        equ    0                                         ; Parity Error Interrupt Enable
SCI2C3_FEIE:        equ    1                                         ; Framing Error Interrupt Enable
SCI2C3_NEIE:        equ    2                                         ; Noise Error Interrupt Enable
SCI2C3_ORIE:        equ    3                                         ; Overrun Interrupt Enable
SCI2C3_TXINV:       equ    4                                         ; Transmit Data Inversion
SCI2C3_TXDIR:       equ    5                                         ; TxD Pin Direction in Single-Wire Mode
SCI2C3_T8:          equ    6                                         ; Ninth Data Bit for Transmitter
SCI2C3_R8:          equ    7                                         ; Ninth Data Bit for Receiver
; bit position masks
mSCI2C3_PEIE:       equ    %00000001
mSCI2C3_FEIE:       equ    %00000010
mSCI2C3_NEIE:       equ    %00000100
mSCI2C3_ORIE:       equ    %00001000
mSCI2C3_TXINV:      equ    %00010000
mSCI2C3_TXDIR:      equ    %00100000
mSCI2C3_T8:         equ    %01000000
mSCI2C3_R8:         equ    %10000000


;*** SCI2D - SCI2 Data Register; 0x00001877 ***
SCI2D:              equ    $00001877                                ;*** SCI2D - SCI2 Data Register; 0x00001877 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
SCI2D_R0_T0:        equ    0                                         ; Receive/Transmit Data Bit 0
SCI2D_R1_T1:        equ    1                                         ; Receive/Transmit Data Bit 1
SCI2D_R2_T2:        equ    2                                         ; Receive/Transmit Data Bit 2
SCI2D_R3_T3:        equ    3                                         ; Receive/Transmit Data Bit 3
SCI2D_R4_T4:        equ    4                                         ; Receive/Transmit Data Bit 4
SCI2D_R5_T5:        equ    5                                         ; Receive/Transmit Data Bit 5
SCI2D_R6_T6:        equ    6                                         ; Receive/Transmit Data Bit 6
SCI2D_R7_T7:        equ    7                                         ; Receive/Transmit Data Bit 7
; bit position masks
mSCI2D_R0_T0:       equ    %00000001
mSCI2D_R1_T1:       equ    %00000010
mSCI2D_R2_T2:       equ    %00000100
mSCI2D_R3_T3:       equ    %00001000
mSCI2D_R4_T4:       equ    %00010000
mSCI2D_R5_T5:       equ    %00100000
mSCI2D_R6_T6:       equ    %01000000
mSCI2D_R7_T7:       equ    %10000000


;*** PTCSET - Port C Data Set Register; 0x00001878 ***
PTCSET:             equ    $00001878                                ;*** PTCSET - Port C Data Set Register; 0x00001878 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTCSET_PTCSET0:     equ    0                                         ; Data Set for Port C Bit 0
PTCSET_PTCSET1:     equ    1                                         ; Data Set for Port C Bit 1
PTCSET_PTCSET2:     equ    2                                         ; Data Set for Port C Bit 2
PTCSET_PTCSET3:     equ    3                                         ; Data Set for Port C Bit 3
PTCSET_PTCSET4:     equ    4                                         ; Data Set for Port C Bit 4
PTCSET_PTCSET5:     equ    5                                         ; Data Set for Port C Bit 5
PTCSET_PTCSET6:     equ    6                                         ; Data Set for Port C Bit 6
PTCSET_PTCSET7:     equ    7                                         ; Data Set for Port C Bit 7
; bit position masks
mPTCSET_PTCSET0:    equ    %00000001
mPTCSET_PTCSET1:    equ    %00000010
mPTCSET_PTCSET2:    equ    %00000100
mPTCSET_PTCSET3:    equ    %00001000
mPTCSET_PTCSET4:    equ    %00010000
mPTCSET_PTCSET5:    equ    %00100000
mPTCSET_PTCSET6:    equ    %01000000
mPTCSET_PTCSET7:    equ    %10000000


;*** PTESET - Port E Data Set Register; 0x00001879 ***
PTESET:             equ    $00001879                                ;*** PTESET - Port E Data Set Register; 0x00001879 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTESET_PTESET0:     equ    0                                         ; Data Set for Port E Bit 0
PTESET_PTESET1:     equ    1                                         ; Data Set for Port E Bit 1
PTESET_PTESET2:     equ    2                                         ; Data Set for Port E Bit 2
PTESET_PTESET3:     equ    3                                         ; Data Set for Port E Bit 3
PTESET_PTESET4:     equ    4                                         ; Data Set for Port E Bit 4
PTESET_PTESET5:     equ    5                                         ; Data Set for Port E Bit 5
PTESET_PTESET6:     equ    6                                         ; Data Set for Port E Bit 6
PTESET_PTESET7:     equ    7                                         ; Data Set for Port E Bit 7
; bit position masks
mPTESET_PTESET0:    equ    %00000001
mPTESET_PTESET1:    equ    %00000010
mPTESET_PTESET2:    equ    %00000100
mPTESET_PTESET3:    equ    %00001000
mPTESET_PTESET4:    equ    %00010000
mPTESET_PTESET5:    equ    %00100000
mPTESET_PTESET6:    equ    %01000000
mPTESET_PTESET7:    equ    %10000000


;*** PTCCLR - Port C Data Clear Register; 0x0000187A ***
PTCCLR:             equ    $0000187A                                ;*** PTCCLR - Port C Data Clear Register; 0x0000187A ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTCCLR_PTCCLR0:     equ    0                                         ; Data Clear for Port C Bit 0
PTCCLR_PTCCLR1:     equ    1                                         ; Data Clear for Port C Bit 1
PTCCLR_PTCCLR2:     equ    2                                         ; Data Clear for Port C Bit 2
PTCCLR_PTCCLR3:     equ    3                                         ; Data Clear for Port C Bit 3
PTCCLR_PTCCLR4:     equ    4                                         ; Data Clear for Port C Bit 4
PTCCLR_PTCCLR5:     equ    5                                         ; Data Clear for Port C Bit 5
PTCCLR_PTCCLR6:     equ    6                                         ; Data Clear for Port C Bit 6
PTCCLR_PTCCLR7:     equ    7                                         ; Data Clear for Port C Bit 7
; bit position masks
mPTCCLR_PTCCLR0:    equ    %00000001
mPTCCLR_PTCCLR1:    equ    %00000010
mPTCCLR_PTCCLR2:    equ    %00000100
mPTCCLR_PTCCLR3:    equ    %00001000
mPTCCLR_PTCCLR4:    equ    %00010000
mPTCCLR_PTCCLR5:    equ    %00100000
mPTCCLR_PTCCLR6:    equ    %01000000
mPTCCLR_PTCCLR7:    equ    %10000000


;*** PTECLR - Port E Data Clear Register; 0x0000187B ***
PTECLR:             equ    $0000187B                                ;*** PTECLR - Port E Data Clear Register; 0x0000187B ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTECLR_PTECLR0:     equ    0                                         ; Data Clear for Port E Bit 0
PTECLR_PTECLR1:     equ    1                                         ; Data Clear for Port E Bit 1
PTECLR_PTECLR2:     equ    2                                         ; Data Clear for Port E Bit 2
PTECLR_PTECLR3:     equ    3                                         ; Data Clear for Port E Bit 3
PTECLR_PTECLR4:     equ    4                                         ; Data Clear for Port E Bit 4
PTECLR_PTECLR5:     equ    5                                         ; Data Clear for Port E Bit 5
PTECLR_PTECLR6:     equ    6                                         ; Data Clear for Port E Bit 6
PTECLR_PTECLR7:     equ    7                                         ; Data Clear for Port E Bit 7
; bit position masks
mPTECLR_PTECLR0:    equ    %00000001
mPTECLR_PTECLR1:    equ    %00000010
mPTECLR_PTECLR2:    equ    %00000100
mPTECLR_PTECLR3:    equ    %00001000
mPTECLR_PTECLR4:    equ    %00010000
mPTECLR_PTECLR5:    equ    %00100000
mPTECLR_PTECLR6:    equ    %01000000
mPTECLR_PTECLR7:    equ    %10000000


;*** PTCTOG - Port C Toggle Register; 0x0000187C ***
PTCTOG:             equ    $0000187C                                ;*** PTCTOG - Port C Toggle Register; 0x0000187C ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTCTOG_PTCTOG0:     equ    0                                         ; Toggle Enable for Port C Bit 0
PTCTOG_PTCTOG1:     equ    1                                         ; Toggle Enable for Port C Bit 1
PTCTOG_PTCTOG2:     equ    2                                         ; Toggle Enable for Port C Bit 2
PTCTOG_PTCTOG3:     equ    3                                         ; Toggle Enable for Port C Bit 3
PTCTOG_PTCTOG4:     equ    4                                         ; Toggle Enable for Port C Bit 4
PTCTOG_PTCTOG5:     equ    5                                         ; Toggle Enable for Port C Bit 5
PTCTOG_PTCTOG6:     equ    6                                         ; Toggle Enable for Port C Bit 6
PTCTOG_PTCTOG7:     equ    7                                         ; Toggle Enable for Port C Bit 7
; bit position masks
mPTCTOG_PTCTOG0:    equ    %00000001
mPTCTOG_PTCTOG1:    equ    %00000010
mPTCTOG_PTCTOG2:    equ    %00000100
mPTCTOG_PTCTOG3:    equ    %00001000
mPTCTOG_PTCTOG4:    equ    %00010000
mPTCTOG_PTCTOG5:    equ    %00100000
mPTCTOG_PTCTOG6:    equ    %01000000
mPTCTOG_PTCTOG7:    equ    %10000000


;*** PTETOG - Port E Toggle Register; 0x0000187D ***
PTETOG:             equ    $0000187D                                ;*** PTETOG - Port E Toggle Register; 0x0000187D ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
PTETOG_PTETOG0:     equ    0                                         ; Toggle Enable for Port E Bit 0
PTETOG_PTETOG1:     equ    1                                         ; Toggle Enable for Port E Bit 1
PTETOG_PTETOG2:     equ    2                                         ; Toggle Enable for Port E Bit 2
PTETOG_PTETOG3:     equ    3                                         ; Toggle Enable for Port E Bit 3
PTETOG_PTETOG4:     equ    4                                         ; Toggle Enable for Port E Bit 4
PTETOG_PTETOG5:     equ    5                                         ; Toggle Enable for Port E Bit 5
PTETOG_PTETOG6:     equ    6                                         ; Toggle Enable for Port E Bit 6
PTETOG_PTETOG7:     equ    7                                         ; Toggle Enable for Port E Bit 7
; bit position masks
mPTETOG_PTETOG0:    equ    %00000001
mPTETOG_PTETOG1:    equ    %00000010
mPTETOG_PTETOG2:    equ    %00000100
mPTETOG_PTETOG3:    equ    %00001000
mPTETOG_PTETOG4:    equ    %00010000
mPTETOG_PTETOG5:    equ    %00100000
mPTETOG_PTETOG6:    equ    %01000000
mPTETOG_PTETOG7:    equ    %10000000


;*** NVFTRIM - Nonvolatile ICS Fine Trim; 0x0000FFAE ***
NVFTRIM:            equ    $0000FFAE                                ;*** NVFTRIM - Nonvolatile ICS Fine Trim; 0x0000FFAE ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
NVFTRIM_FTRIM:      equ    0                                         ; ICS Fine Trim
; bit position masks
mNVFTRIM_FTRIM:     equ    %00000001


;*** NVICSTRM - Nonvolatile ICS Trim Register; 0x0000FFAF ***
NVICSTRM:           equ    $0000FFAF                                ;*** NVICSTRM - Nonvolatile ICS Trim Register; 0x0000FFAF ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
NVICSTRM_TRIM0:     equ    0                                         ; ICS Trim Setting, bit 0
NVICSTRM_TRIM1:     equ    1                                         ; ICS Trim Setting, bit 1
NVICSTRM_TRIM2:     equ    2                                         ; ICS Trim Setting, bit 2
NVICSTRM_TRIM3:     equ    3                                         ; ICS Trim Setting, bit 3
NVICSTRM_TRIM4:     equ    4                                         ; ICS Trim Setting, bit 4
NVICSTRM_TRIM5:     equ    5                                         ; ICS Trim Setting, bit 5
NVICSTRM_TRIM6:     equ    6                                         ; ICS Trim Setting, bit 6
NVICSTRM_TRIM7:     equ    7                                         ; ICS Trim Setting, bit 7
; bit position masks
mNVICSTRM_TRIM0:    equ    %00000001
mNVICSTRM_TRIM1:    equ    %00000010
mNVICSTRM_TRIM2:    equ    %00000100
mNVICSTRM_TRIM3:    equ    %00001000
mNVICSTRM_TRIM4:    equ    %00010000
mNVICSTRM_TRIM5:    equ    %00100000
mNVICSTRM_TRIM6:    equ    %01000000
mNVICSTRM_TRIM7:    equ    %10000000


;*** NVBACKKEY0 - Backdoor Comparison Key 0; 0x0000FFB0 ***
NVBACKKEY0:         equ    $0000FFB0                                ;*** NVBACKKEY0 - Backdoor Comparison Key 0; 0x0000FFB0 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
NVBACKKEY0_KEY0:    equ    0                                         ; Backdoor Comparison Key 0 Bits, bit 0
NVBACKKEY0_KEY1:    equ    1                                         ; Backdoor Comparison Key 0 Bits, bit 1
NVBACKKEY0_KEY2:    equ    2                                         ; Backdoor Comparison Key 0 Bits, bit 2
NVBACKKEY0_KEY3:    equ    3                                         ; Backdoor Comparison Key 0 Bits, bit 3
NVBACKKEY0_KEY4:    equ    4                                         ; Backdoor Comparison Key 0 Bits, bit 4
NVBACKKEY0_KEY5:    equ    5                                         ; Backdoor Comparison Key 0 Bits, bit 5
NVBACKKEY0_KEY6:    equ    6                                         ; Backdoor Comparison Key 0 Bits, bit 6
NVBACKKEY0_KEY7:    equ    7                                         ; Backdoor Comparison Key 0 Bits, bit 7
; bit position masks
mNVBACKKEY0_KEY0:   equ    %00000001
mNVBACKKEY0_KEY1:   equ    %00000010
mNVBACKKEY0_KEY2:   equ    %00000100
mNVBACKKEY0_KEY3:   equ    %00001000
mNVBACKKEY0_KEY4:   equ    %00010000
mNVBACKKEY0_KEY5:   equ    %00100000
mNVBACKKEY0_KEY6:   equ    %01000000
mNVBACKKEY0_KEY7:   equ    %10000000


;*** NVBACKKEY1 - Backdoor Comparison Key 1; 0x0000FFB1 ***
NVBACKKEY1:         equ    $0000FFB1                                ;*** NVBACKKEY1 - Backdoor Comparison Key 1; 0x0000FFB1 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
NVBACKKEY1_KEY0:    equ    0                                         ; Backdoor Comparison Key 1 Bits, bit 0
NVBACKKEY1_KEY1:    equ    1                                         ; Backdoor Comparison Key 1 Bits, bit 1
NVBACKKEY1_KEY2:    equ    2                                         ; Backdoor Comparison Key 1 Bits, bit 2
NVBACKKEY1_KEY3:    equ    3                                         ; Backdoor Comparison Key 1 Bits, bit 3
NVBACKKEY1_KEY4:    equ    4                                         ; Backdoor Comparison Key 1 Bits, bit 4
NVBACKKEY1_KEY5:    equ    5                                         ; Backdoor Comparison Key 1 Bits, bit 5
NVBACKKEY1_KEY6:    equ    6                                         ; Backdoor Comparison Key 1 Bits, bit 6
NVBACKKEY1_KEY7:    equ    7                                         ; Backdoor Comparison Key 1 Bits, bit 7
; bit position masks
mNVBACKKEY1_KEY0:   equ    %00000001
mNVBACKKEY1_KEY1:   equ    %00000010
mNVBACKKEY1_KEY2:   equ    %00000100
mNVBACKKEY1_KEY3:   equ    %00001000
mNVBACKKEY1_KEY4:   equ    %00010000
mNVBACKKEY1_KEY5:   equ    %00100000
mNVBACKKEY1_KEY6:   equ    %01000000
mNVBACKKEY1_KEY7:   equ    %10000000


;*** NVBACKKEY2 - Backdoor Comparison Key 2; 0x0000FFB2 ***
NVBACKKEY2:         equ    $0000FFB2                                ;*** NVBACKKEY2 - Backdoor Comparison Key 2; 0x0000FFB2 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
NVBACKKEY2_KEY0:    equ    0                                         ; Backdoor Comparison Key 2 Bits, bit 0
NVBACKKEY2_KEY1:    equ    1                                         ; Backdoor Comparison Key 2 Bits, bit 1
NVBACKKEY2_KEY2:    equ    2                                         ; Backdoor Comparison Key 2 Bits, bit 2
NVBACKKEY2_KEY3:    equ    3                                         ; Backdoor Comparison Key 2 Bits, bit 3
NVBACKKEY2_KEY4:    equ    4                                         ; Backdoor Comparison Key 2 Bits, bit 4
NVBACKKEY2_KEY5:    equ    5                                         ; Backdoor Comparison Key 2 Bits, bit 5
NVBACKKEY2_KEY6:    equ    6                                         ; Backdoor Comparison Key 2 Bits, bit 6
NVBACKKEY2_KEY7:    equ    7                                         ; Backdoor Comparison Key 2 Bits, bit 7
; bit position masks
mNVBACKKEY2_KEY0:   equ    %00000001
mNVBACKKEY2_KEY1:   equ    %00000010
mNVBACKKEY2_KEY2:   equ    %00000100
mNVBACKKEY2_KEY3:   equ    %00001000
mNVBACKKEY2_KEY4:   equ    %00010000
mNVBACKKEY2_KEY5:   equ    %00100000
mNVBACKKEY2_KEY6:   equ    %01000000
mNVBACKKEY2_KEY7:   equ    %10000000


;*** NVBACKKEY3 - Backdoor Comparison Key 3; 0x0000FFB3 ***
NVBACKKEY3:         equ    $0000FFB3                                ;*** NVBACKKEY3 - Backdoor Comparison Key 3; 0x0000FFB3 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
NVBACKKEY3_KEY0:    equ    0                                         ; Backdoor Comparison Key 3 Bits, bit 0
NVBACKKEY3_KEY1:    equ    1                                         ; Backdoor Comparison Key 3 Bits, bit 1
NVBACKKEY3_KEY2:    equ    2                                         ; Backdoor Comparison Key 3 Bits, bit 2
NVBACKKEY3_KEY3:    equ    3                                         ; Backdoor Comparison Key 3 Bits, bit 3
NVBACKKEY3_KEY4:    equ    4                                         ; Backdoor Comparison Key 3 Bits, bit 4
NVBACKKEY3_KEY5:    equ    5                                         ; Backdoor Comparison Key 3 Bits, bit 5
NVBACKKEY3_KEY6:    equ    6                                         ; Backdoor Comparison Key 3 Bits, bit 6
NVBACKKEY3_KEY7:    equ    7                                         ; Backdoor Comparison Key 3 Bits, bit 7
; bit position masks
mNVBACKKEY3_KEY0:   equ    %00000001
mNVBACKKEY3_KEY1:   equ    %00000010
mNVBACKKEY3_KEY2:   equ    %00000100
mNVBACKKEY3_KEY3:   equ    %00001000
mNVBACKKEY3_KEY4:   equ    %00010000
mNVBACKKEY3_KEY5:   equ    %00100000
mNVBACKKEY3_KEY6:   equ    %01000000
mNVBACKKEY3_KEY7:   equ    %10000000


;*** NVBACKKEY4 - Backdoor Comparison Key 4; 0x0000FFB4 ***
NVBACKKEY4:         equ    $0000FFB4                                ;*** NVBACKKEY4 - Backdoor Comparison Key 4; 0x0000FFB4 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
NVBACKKEY4_KEY0:    equ    0                                         ; Backdoor Comparison Key 4 Bits, bit 0
NVBACKKEY4_KEY1:    equ    1                                         ; Backdoor Comparison Key 4 Bits, bit 1
NVBACKKEY4_KEY2:    equ    2                                         ; Backdoor Comparison Key 4 Bits, bit 2
NVBACKKEY4_KEY3:    equ    3                                         ; Backdoor Comparison Key 4 Bits, bit 3
NVBACKKEY4_KEY4:    equ    4                                         ; Backdoor Comparison Key 4 Bits, bit 4
NVBACKKEY4_KEY5:    equ    5                                         ; Backdoor Comparison Key 4 Bits, bit 5
NVBACKKEY4_KEY6:    equ    6                                         ; Backdoor Comparison Key 4 Bits, bit 6
NVBACKKEY4_KEY7:    equ    7                                         ; Backdoor Comparison Key 4 Bits, bit 7
; bit position masks
mNVBACKKEY4_KEY0:   equ    %00000001
mNVBACKKEY4_KEY1:   equ    %00000010
mNVBACKKEY4_KEY2:   equ    %00000100
mNVBACKKEY4_KEY3:   equ    %00001000
mNVBACKKEY4_KEY4:   equ    %00010000
mNVBACKKEY4_KEY5:   equ    %00100000
mNVBACKKEY4_KEY6:   equ    %01000000
mNVBACKKEY4_KEY7:   equ    %10000000


;*** NVBACKKEY5 - Backdoor Comparison Key 5; 0x0000FFB5 ***
NVBACKKEY5:         equ    $0000FFB5                                ;*** NVBACKKEY5 - Backdoor Comparison Key 5; 0x0000FFB5 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
NVBACKKEY5_KEY0:    equ    0                                         ; Backdoor Comparison Key 5 Bits, bit 0
NVBACKKEY5_KEY1:    equ    1                                         ; Backdoor Comparison Key 5 Bits, bit 1
NVBACKKEY5_KEY2:    equ    2                                         ; Backdoor Comparison Key 5 Bits, bit 2
NVBACKKEY5_KEY3:    equ    3                                         ; Backdoor Comparison Key 5 Bits, bit 3
NVBACKKEY5_KEY4:    equ    4                                         ; Backdoor Comparison Key 5 Bits, bit 4
NVBACKKEY5_KEY5:    equ    5                                         ; Backdoor Comparison Key 5 Bits, bit 5
NVBACKKEY5_KEY6:    equ    6                                         ; Backdoor Comparison Key 5 Bits, bit 6
NVBACKKEY5_KEY7:    equ    7                                         ; Backdoor Comparison Key 5 Bits, bit 7
; bit position masks
mNVBACKKEY5_KEY0:   equ    %00000001
mNVBACKKEY5_KEY1:   equ    %00000010
mNVBACKKEY5_KEY2:   equ    %00000100
mNVBACKKEY5_KEY3:   equ    %00001000
mNVBACKKEY5_KEY4:   equ    %00010000
mNVBACKKEY5_KEY5:   equ    %00100000
mNVBACKKEY5_KEY6:   equ    %01000000
mNVBACKKEY5_KEY7:   equ    %10000000


;*** NVBACKKEY6 - Backdoor Comparison Key 6; 0x0000FFB6 ***
NVBACKKEY6:         equ    $0000FFB6                                ;*** NVBACKKEY6 - Backdoor Comparison Key 6; 0x0000FFB6 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
NVBACKKEY6_KEY0:    equ    0                                         ; Backdoor Comparison Key 6 Bits, bit 0
NVBACKKEY6_KEY1:    equ    1                                         ; Backdoor Comparison Key 6 Bits, bit 1
NVBACKKEY6_KEY2:    equ    2                                         ; Backdoor Comparison Key 6 Bits, bit 2
NVBACKKEY6_KEY3:    equ    3                                         ; Backdoor Comparison Key 6 Bits, bit 3
NVBACKKEY6_KEY4:    equ    4                                         ; Backdoor Comparison Key 6 Bits, bit 4
NVBACKKEY6_KEY5:    equ    5                                         ; Backdoor Comparison Key 6 Bits, bit 5
NVBACKKEY6_KEY6:    equ    6                                         ; Backdoor Comparison Key 6 Bits, bit 6
NVBACKKEY6_KEY7:    equ    7                                         ; Backdoor Comparison Key 6 Bits, bit 7
; bit position masks
mNVBACKKEY6_KEY0:   equ    %00000001
mNVBACKKEY6_KEY1:   equ    %00000010
mNVBACKKEY6_KEY2:   equ    %00000100
mNVBACKKEY6_KEY3:   equ    %00001000
mNVBACKKEY6_KEY4:   equ    %00010000
mNVBACKKEY6_KEY5:   equ    %00100000
mNVBACKKEY6_KEY6:   equ    %01000000
mNVBACKKEY6_KEY7:   equ    %10000000


;*** NVBACKKEY7 - Backdoor Comparison Key 7; 0x0000FFB7 ***
NVBACKKEY7:         equ    $0000FFB7                                ;*** NVBACKKEY7 - Backdoor Comparison Key 7; 0x0000FFB7 ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
NVBACKKEY7_KEY0:    equ    0                                         ; Backdoor Comparison Key 7 Bits, bit 0
NVBACKKEY7_KEY1:    equ    1                                         ; Backdoor Comparison Key 7 Bits, bit 1
NVBACKKEY7_KEY2:    equ    2                                         ; Backdoor Comparison Key 7 Bits, bit 2
NVBACKKEY7_KEY3:    equ    3                                         ; Backdoor Comparison Key 7 Bits, bit 3
NVBACKKEY7_KEY4:    equ    4                                         ; Backdoor Comparison Key 7 Bits, bit 4
NVBACKKEY7_KEY5:    equ    5                                         ; Backdoor Comparison Key 7 Bits, bit 5
NVBACKKEY7_KEY6:    equ    6                                         ; Backdoor Comparison Key 7 Bits, bit 6
NVBACKKEY7_KEY7:    equ    7                                         ; Backdoor Comparison Key 7 Bits, bit 7
; bit position masks
mNVBACKKEY7_KEY0:   equ    %00000001
mNVBACKKEY7_KEY1:   equ    %00000010
mNVBACKKEY7_KEY2:   equ    %00000100
mNVBACKKEY7_KEY3:   equ    %00001000
mNVBACKKEY7_KEY4:   equ    %00010000
mNVBACKKEY7_KEY5:   equ    %00100000
mNVBACKKEY7_KEY6:   equ    %01000000
mNVBACKKEY7_KEY7:   equ    %10000000


;*** NVPROT - Nonvolatile Flash Protection Register; 0x0000FFBD ***
NVPROT:             equ    $0000FFBD                                ;*** NVPROT - Nonvolatile Flash Protection Register; 0x0000FFBD ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
NVPROT_FPOPEN:      equ    0                                         ; Flash Protection Open
NVPROT_FPS0:        equ    1                                         ; Flash Protection Size, bit 0
NVPROT_FPS1:        equ    2                                         ; Flash Protection Size, bit 1
NVPROT_FPS2:        equ    3                                         ; Flash Protection Size, bit 2
NVPROT_FPS3:        equ    4                                         ; Flash Protection Size, bit 3
NVPROT_FPS4:        equ    5                                         ; Flash Protection Size, bit 4
NVPROT_FPS5:        equ    6                                         ; Flash Protection Size, bit 5
NVPROT_FPS6:        equ    7                                         ; Flash Protection Size, bit 6
; bit position masks
mNVPROT_FPOPEN:     equ    %00000001
mNVPROT_FPS0:       equ    %00000010
mNVPROT_FPS1:       equ    %00000100
mNVPROT_FPS2:       equ    %00001000
mNVPROT_FPS3:       equ    %00010000
mNVPROT_FPS4:       equ    %00100000
mNVPROT_FPS5:       equ    %01000000
mNVPROT_FPS6:       equ    %10000000


;*** NVOPT - Nonvolatile Flash Options Register; 0x0000FFBF ***
NVOPT:              equ    $0000FFBF                                ;*** NVOPT - Nonvolatile Flash Options Register; 0x0000FFBF ***
; bit numbers for usage in BCLR, BSET, BRCLR and BRSET
NVOPT_SEC0:         equ    0                                         ; Flash Security Bit 0
NVOPT_SEC1:         equ    1                                         ; Flash Security Bit 1
NVOPT_KEYEN0:       equ    6                                         ; Backdoor Key Security Enable Bit 0
NVOPT_KEYEN1:       equ    7                                         ; Backdoor Key Security Enable Bit 1
; bit position masks
mNVOPT_SEC0:        equ    %00000001
mNVOPT_SEC1:        equ    %00000010
mNVOPT_KEYEN0:      equ    %01000000
mNVOPT_KEYEN1:      equ    %10000000



; Flash commands
mBlank:             equ     $05
mBurstProg:         equ     $25
mByteProg:          equ     $20
mMassErase:         equ     $41
mPageErase:         equ     $40


;***********************************************
;**   D E P R E C I A T E D   S Y M B O L S   **
;***********************************************
        IFNDEF  __GENERATE_APPLICATION__                            ; not supported for absolute assembler
                    XREF    This_symb_has_been_depreciated
        ENDIF

; EOF
