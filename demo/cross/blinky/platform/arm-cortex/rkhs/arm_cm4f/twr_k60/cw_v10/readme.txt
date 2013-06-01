/**
\page cross_twr_K60 "Kinetis K60/100Mhz ARM Cortex M-4F processor"

Running Blinky RKH demo on Freescale Cortex M4 demostration board TWR_K60_100MHz.

This is a guide to how to setup and use the demo board to evaluate the RKH 
framework. It assumes a prior knowledge on board features and development 
environment.

<STRONG>Project organization<\STRONG>

\code

\---cw_v10
    |   
    \---prj						 - Blinky LPCXpresso Workspace.
    |   +---.metadata			 - Workspace internal directory.
    |   \---blinky				 - Workspace internal directory.
    |       |   .cproject		 - Workspace internal file.
    |       |   .project		 - Workspace internal file.
    |       +---.settings		 - Workspace internal directory.
	|		+---Project_Settings - Blinky project settings.
    |       \---Sources			 - Blinky project CPU dependent files.
    |           \---bsp			
    |               +---cm4f	 - Peripherals inicialization, ISR´s and time stamp.
    |
    |   bsp.c					- Board support package source file.
    |   bsp.h					- Board support package header file.
    |   gpio.h					- Routines to handle GPIO´s.
    |   readme.txt				- This guide file.
    |   uart.c					- Routines to handle serial port.
    |   uart.h					- Serial driver prototipes.

\endcode


<STRONG>Blinky demo BSP<\STRONG>

- Blink state is shown through target board D7 on PA[4].
- Tracing info through UART3_TXD assigned to PC[17] on J8 connector of TWR-SER at 115200 8N1.

*/
