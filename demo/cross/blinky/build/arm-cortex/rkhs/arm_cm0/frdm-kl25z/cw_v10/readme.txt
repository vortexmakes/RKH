/**
\page cross_frdm_kl25 "Kinetis KL25/48Mhz ARM Cortex M-0 processor"
\image html rkh_bunner.jpg

Running Blinky RKH demo on Freescale ARM Cortex-M0F demostration board 

<A HREF="http://www.freescale.com/webapp/sps/site/
prod_summary.jsp?code=FRDM-KL25Z">FRDM-KL25Z</A> 
<A HREF="http://www.freescale.com/webapp/sps/site/
prod_summary.jsp?code=KL2">Kinetis KL2</A>.
This is a guide to how to setup and use the demo board to evaluate the RKH 
framework. It assumes a prior knowledge on board features and development 
environment.

<STRONG>Blinky demo BSP</STRONG>

- Blink state is shown through target board D3 RGB led on PA[4].
- Tracing info through UART0_TXD assigned to PA[2] connected to Open SDA
usb to serial port at 115200 8N1.
- LPTMR0 at LPO clock 1Khz is used to trace time stamp.

*/
