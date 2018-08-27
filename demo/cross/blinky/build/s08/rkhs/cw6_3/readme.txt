/**
\page cross_demoqe128_s08 DEMOQE128 for S08 processor
\image html rkh_bunner.jpg

Running Blinky RKH demo on Freescale <A HREF="http://www.freescale.com/
webapp/sps/site/prod_summary.jsp?code=S08QE">S08QE128</A> demostration 
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

<STRONG>Blinky demo BSP</STRONG>
	
- Blink state is shown through PTC0 Led.
- Tracing info through DB9 board connector at 57600 8N1.

*/
