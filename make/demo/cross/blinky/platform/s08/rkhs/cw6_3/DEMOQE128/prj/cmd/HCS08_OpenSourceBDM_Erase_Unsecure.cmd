// ver 2.1 (16-Oct-06)
// HCS08 erasing + unsecuring command file:
// These commands mass erase the chip then program the security byte to 0xFE (unsecured state + backdoor key mechanism enabled).
 
// Evaluate the clock divider to set in FCDIV register:

DEFINEVALUEDLG "Information required to unsecure the device" "FCDIV" 19 "To unsecure the device, the command script needs \nthe correct value for FCDIV onchip register.\n\nIf the bus frequency is less than 10 MHz, the value\nto store in FCDIV is equal to:\n \"bus frequency (kHz) / 175\"\n\nIf the bus frequency is higher than 10 MHz, the value\nto store in FCDIV is equal to:\n \" bus frequency (kHz) / 1400  + 64\"\n(+64 (0x40) is to set PRDIV8 flag)\n\nDatasheet proposed values:\n\nbus frequency\t\tFCDIV value (decimal)\n\n 20 \tMHz\t\t76\n 10 \tMHz\t\t49\n  8 \tMHz\t\t39\n  4 \tMHz\t\t19\n  2 \tMHz\t\t9\n  1 \tMHz\t\t4\n200 \tkHz\t\t0\n150 \tkHz\t\t0\n"

// An average programming clock of 175 kHz is chosen.
 
// If the bus frequency is less than 10 MHz, the value to store
// in FCDIV is equal to " bus frequency (kHz) / 175 ".
 
// If the bus frequency is higher than 10 MHz, the value to store
// in FCDIV is equal to " bus frequency (kHz) / 1400  + 0x40 (to set PRDIV8 flag)".
 
// Datasheet proposed values:
//
// bus frequency     FCDIV value (decimal)
// 
//  20 MHz            76
//  10 MHz            49
//   8 MHz            39
//   4 MHz            19
//   2 MHz             9
//   1 MHz             4
// 200 kHz             0
// 150 kHz             0   
 
 
FLASH release
 
wb 0x1802 3     // disable COP clearing SIMOPT register + set BKGDPE and RSTPE (when available)
wb 0x1825 0x30  // clear FPVIOL and FACCERR in FSTAT register
wb 0x1824 0xff  // remove all flash protections clearing FPROT register
wb 0x1820 FCDIV // set clock divider FCDIV register 
                // Please see below to find how to evaluate this constant value.    
                  
//mass erase flash
wb 0x1825 0x30 // clear FPVIOL and FACCERR in FSTAT register
wb 0xff80 0    // (dummy) write to flash array to buffer address and data
wb 0x1826 0x41 // write MASS ERASE command in FCMD register
wb 0x1825 0x80 // set FCBEF in FSTAT register to execute the command 
wait 20
 
//blankcheck flash
wb 0x1825 0x30 // clear FPVIOL and FACCERR in FSTAT register
wb 0xff80 0    // (dummy) write to flash array to buffer address and data  
wb 0x1826 0x5  // write BLANK CHECK command in FCMD register 
wb 0x1825 0x80 // set FCBEF in FSTAT register to execute the command 
wait 20
 
//reprogram Security byte to Unsecure state
wb 0x1820 FCDIV // set clock divider FCDIV register 
wb 0x1825 0x30 // clear FPVIOL and FACCERR in FSTAT register
wb 0xffbf 0xfe // write NVFEOPT register in flash array to UNSECURED state with Backdoor Key Mechanism enabled
wb 0x1826 0x20 // write BYTE PROGRAM command in FCMD register  
wb 0x1825 0x80 // set FCBEF in FSTAT register to execute the command 
wait 10

DMM RELEASECACHES // release memory data caches

reset
 
undef FCDIV

