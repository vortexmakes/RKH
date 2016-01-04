/**
\page cross_frdmk64f FRDMK64F for K64 processor
\image html rkh_bunner.jpg

Running Shared RKH demo on Freescale <A HREF="http://www.freescale.com/
webapp/sps/site/prod_summary.jsp?code=K64_120">K64F120</A> demostration 
board <A HREF="http://www.freescale.com/webapp/sps/site/
prod_summary.jsp?code=FRDM-K64F">FRDMK64F120</A>.
This is a guide to how to setup the demo board to evaluate the RKH 
framework. It assumes a prior knowledge on board features and development 
environment.
This demo use native RKH scheduler (rkhs).

<STRONG>Folder tree</STRONG>

\code
\-frdm-k64f\kds\
    +-board			- Low level KSDK access.
    +-switch		- Minimal debouncing switch handler.
    +-prj			- KDS "shared_frdmk64f_ucosiii_ksdk" project.
    |  bsp.c		- Board support package source file.
    |  bsp.h		- Board support package header file.
    |  readme.txt	- This guide file.
\endcode

<STRONG>Eclipse project organization</STRONG>

This project use KSDK_1.2.0, you must set it´s installation path to the 
PROJECT_KSDK_PATH variable, before to build.
\code
\-shared_frdmk64f_ksdk\
	+- bsp			- Board support package files.
	+- rkh			- RKH source files.
	+- SDK			- KSDK platform library for FRDMK64F.
	+- shared		- Shared demo aplication.

<STRONG>Shared demo BSP</STRONG>
	
- The RGB Led D12 shown which client request is running on server.
- Each Client have your own color, Client 1-4: RED, GREEN, BLUE, YELLOW
- Pressing SW2 button introduce a PAUSE event.
- Paused state is shown with a WHITE in RGB led.
- Tracing info through SDA Virtual COM interface at 115200 8N1.
- Debugging info through UART3 at 115200 8N1 on J1 pins: 2(RXD), 4(TXD).
- FRDMK64F is compatible with R3 shields, <A HREF="http://shieldlist.org/
cutedigi/rs232"> CuteDigi RS232 Shield can be used to adapt to RS232 levels
the debugging info.

*/
