/**
\page cross_lpcx1769 LPCXPresso for ARM Cortex-M3 LPC1769 processor
\image html rkh_bunner.jpg

Running Blinky RKH demo on NXP ARM Cortex-M3 demostration board 
<A HREF="http://www.embeddedartists.com/products/lpcxpresso/
lpc1769_xpr.php">LPCXpresso</A> 
<A HREF="http://www.nxp.com/products/microcontrollers/cortex_m3/
LPC1769FBD100.html">LPC1769</A>.
This is a guide to how to setup and use the demo board to evaluate the RKH 
framework. It assumes a prior knowledge on board features and development 
environment.

<STRONG>Project organization</STRONG>

\code
\-codered
  \-prj						- Blinky LPCXpresso Workspace.
  | +-.metadata				- Workspace internal directory.
  | \-blinky				- Workspace internal directory.
  | | | .cproject			- Workspace internal file.
  | | | .project			- Workspace internal file.
  | | +-.settings			- Workspace internal directory.
  | | \-src					- Blinky project CPU dependent files.
  | |   \-bsp			
  | |     +-lpc17xx			- Peripherals inicialization, ISR's and time stamp.
  | | bsp.c					- Board support package source file.
  | | bsp.h					- Board support package header file.
  | | gpio.h				- Routines to handle GPIO's.
  | | readme.txt			- This guide file.
  | | uart.c				- Routines to handle serial port.
  | | uart.h				- Serial driver prototipes.
\endcode

<STRONG>Blinky demo BSP</STRONG>

- Blink state is shown through target board LED2 on P0[22].
- Tracing info through UART0_TXD assigned to P0[2] on J6.21 connector at 38400 8N1.
  To interface the demo board with Trazer PC software, you may use the simple
  circuit shown below to convert UART0_TXD signal to RS232 levels.

<B>LPCXpresso expansion Connector</B>

\code
                                +3.3V
                                |
    J6.28 [VIO]  o--------------x
                                |
                                |                   
                      10K     |<  
    J6.21 [TXD0] >---/\/\/\---|   BC557 
                              |\
                                |                 Female DB9
                                |                   
                                +-------------<-o [TXD] Pin-3
                                |                   
                                '---/\/\/\---->-o [RXD] Pin-2   --> To PC Serial COM
                                     10K             

     J6.1 [GND]  o--------------x---------------o [GND] Pin-5
                                |
                               GND       
\endcode
*/
