/**
\page cross_frdmk64f_rkhs FRDMK64F for K64 processor
\image html rkh_bunner.jpg

Running Shared RKH demo on Freescale <A HREF="http://www.nxp.com/products/
software-and-tools/hardware-development-tools/freedom-development-boards/
freedom-development-platform-for-kinetis-k64-k63-and-k24-mcus:
FRDM-K64F?tid=vanFRDM-K64F">FRDM-K64F</A>.
This is a guide to how to setup the demo board to evaluate the RKH 
framework. It assumes a prior knowledge on board features and development 
environment.
This demo use native RKH scheduler (rkhs).

<STRONG>Eclipse setup</STRONG>

This project use KSDK_1.2.0, you must set it's installation path to the 
PROJECT_KSDK_PATH variable, before to build.

<STRONG>Shared demo BSP</STRONG>
	
- The RGB Led D12 shown which client request is running on server.
- Each Client have your own color, Client 1-4: RED, GREEN, BLUE, YELLOW
- Pressing SW2 button introduce a PAUSE event.
- Paused state is shown with a WHITE in RGB led.
- Tracing info through SDA Virtual COM interface at 115200 8N1.
- Debugging info through UART3 at 115200 8N1 on J1 pins: 2(RXD), 4(TXD).
- FRDMK64F is compatible with R3 shields, <A HREF="http://shieldlist.org/
cutedigi/rs232"> CuteDigi RS232 Shield </A> can be used to adapt to RS232 levels
the debugging info.

*/
