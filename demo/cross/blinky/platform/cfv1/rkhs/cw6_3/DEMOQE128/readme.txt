/**
\page cross_demoqe128_cfv1 DEMOQE128 for Coldfire V1 processor
\image html rkh_bunner.jpg

Running Blinky RKH demo on Freescale <A HREF="http://www.freescale.com/
webapp/sps/site/prod_summary.jsp?code=MCF51QE">MCF51QE128</A> demostration 
board <A HREF="http://www.freescale.com/webapp/sps/site/
prod_summary.jsp?code=DEMOQE128">DEMOQE128</A>.
This is a guide to how to setup and use the demo board to evaluate the RKH 
framework. It assumes a prior knowledge on board features and development 
environment.

<STRONG>Before to start you must check this jumper settings</STRONG>

- J6: RXD-PTB0 close
- J7: TXD-PTB1 close
- J8: COM_EN ON.
- J9: at least PTC0 position close.
- J17: EXTAL close, XTAL close.
- J18: RESET_EN close, STLED_EN close.

<STRONG>Project organization</STRONG>

\code
\-DEMOQE128
    +-gpio			- Routines to handle GPIO's.
    +-mcu			- Peripherals inicialization, ISR's and time stamp.
    +-prj			- Blinky CW63 Project, run "blinky.mcp" to start demo.
    +-serial		- Routines to handle serial port.
    |   bsp.c		- Board support package source file.
    |   bsp.h		- Board support package header file.
    |   readme.txt	- This guide file.
\endcode

<STRONG>Blinky demo BSP</STRONG>
	
- Blink state is shown through PTC0 Led.
- Tracing info through DB9 board connector at 57600 8N1.

*/
