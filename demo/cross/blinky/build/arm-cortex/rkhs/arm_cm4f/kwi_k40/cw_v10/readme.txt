/**
\page cross_kwi_K40 "Kinetis K40/100Mhz ARM Cortex M-4 processor"
\image html rkh_bunner.jpg

Running Blinky RKH demo on Freescale ARM Cortex-M4 demostration board 
<A HREF="https://www.freescale.com/webapp/sps/site/
prod_summary.jsp?code=KWIKSTIK-K40">KWIKSTIK-K40</A> 
<A HREF="http://www.freescale.com/webapp/sps/site/
prod_summary.jsp?code=K40_100&nodeId=01624698C9DE2DDDAB">Kinetis K40</A>
This is a guide to how to setup and use the demo board to evaluate the RKH 
framework. It assumes a prior knowledge on board features and development 
environment.

This is a guide to how to setup and use the demo board to evaluate the RKH 
framework. It assumes a prior knowledge on board features and development 
environment.

<STRONG>Project organization</STRONG>

\code
\-cw_v10
   \-prj	
   | +-blinky_twr_k40     	- Blinky demo CW10 directory.
   | +-cm4f                 - CPU inicialization.
   | \-drv					- Drivers
   | | +-kuart              - Kinetis UART driver. 
   | | +-slcd               - Kinetis SLCD driver from KWISTIK-DEMO
   | | +-sleep              - miliseconds time delay.
   | bsp.c					- Board support package source file.c.
   | bsp.h					- Board support package header file.
   | readme.h				- This guide file.
\endcode


<STRONG>Blinky demo BSP</STRONG>

- Blink state is shown through target board LCD, texts ON/OFF are
  shown according to the blink state on/off.
- Tracing info through UART5_TXD assigned to PTE.8 available on TWR header A.44
  compatible with TWR-SER board at 115200 8N1.
*/
