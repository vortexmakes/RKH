Building RKH blinky demo over OSEK on EduCIAA NXP

1- Copy all content of \rkh\sources into \CIAA\Firmware\externals\rkh
2- Create RKH Makefile ciaa-library into \CIAA\Firmware\externals\rkh\mak
   with content:

	LIBS				+= ext_rkh
	# library path
	ext_rkh_PATH		= $(ROOT_DIR)$(DS)externals$(DS)rkh
	# library source path
	ext_rkh_SRC_PATH	= $(ext_rkh_PATH)$(DS)source
	   
	# library include path
	ext_rkh_INC_PATH	= $(ext_rkh_PATH)$(DS)source$(DS)include
	
	# library source files
	ext_rkh_SRC_FILES	+= $(wildcard $(ext_rkh_SRC_PATH)$(DS)*.c)	\
	   $(wildcard $(ext_rkh_SRC_PATH)$(DS)portable$(DS)osek$(DS)ciaa$(DS)*.c)
 

3- Copy demo files to \CIAA\Firmware\examples\rkh_blinky 
4- Add project path entry to Makefile.mine
     PROJECT_PATH ?= examples$(DS)rkh_blinky
5- Open CIAA-IDE
6- make_clean to generate Rtos in order to project .oil
7- build demo project.

TODO: integrate building with CIAA Firmware witout coping demo files to CIAA directory
