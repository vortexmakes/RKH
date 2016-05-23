###############################################################################
#
#                                Framework RKH
#                                -------------
#
#            State-machine framework for reactive embedded systems
#
#                      Copyright (C) 2010 Leandro Francucci.
#          All rights reserved. Protected by international copyright laws.
#
#
#  RKH is free software: you can redistribute it and/or modify it under the
#  terms of the GNU General Public License as published by the Free Software
#  Foundation, either version 3 of the License, or (at your option) any
#  later version.
#
#  RKH is distributed in the hope that it will be useful, but WITHOUT ANY
#  WARRANTY; without even the implied warranty of MERCHANTABILITY or
#  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
#  more details.
#
#  You should have received a copy of the GNU General Public License along
#  with RKH, see copying.txt file.
#
#  Contact information:
#  RKH web site:   http://sourceforge.net/projects/rkh-reactivesys/
#  e-mail:         francuccilea@gmail.com
#
###############################################################################
#
#  \file       Makefile
#
#  \brief      Main RKH Make file
#
###############################################################################
#
# Development history 
#
#  2016.05.19  LeFr  v0.0.01  Initial version
#
###############################################################################
#
# Autors
#  DaBa  Dario Baliña  dariosb@gmail.com
#
###############################################################################

RKH_SRC_PATH  		 = $(RKH_PATH)$(DS)source
RKH_INC_PATH         = $(RKH_SRC_PATH)$(DS)include
RKH_PORT_PATH		 = $(RKH_SRC_PATH)$(DS)portable$(DS)osek$(DS)ciaa

RKH_SRC_FILES		 = $(wildcard $(RKH_SRC_PATH)$(DS)*.c)
RKH_SRC_FILES		+= $(wildcard $(RKH_PORT_PATH)$(DS)*.c)

CFLAGS += -D$(RKH_PLATFORM)

###############################################################################
# Rule to compile RKH sources
%.o : $(RKH_SRC_PATH)$(DS)%.c 
	@echo ' '
	@echo =====================================================================
	@echo Compiling RKH Source 'c' file: $<
	@echo ' '
	$(CC) $(CFLAGS) $(call cp4c,$<) -o $(OBJ_DIR)$(DS)$@
ifeq ($(MAKE_DEPENDENCIES),1)
	@echo ' '
	@echo Generating dependencies...
	$(CC) -MM $(CFLAGS) $(call cp4c,$<) > $(OBJ_DIR)$(DS)$(@:.o=.d)
else
	@echo ' '
	@echo Skipping make dependencies...
endif

ifeq (1,1)
###############################################################################
# Rule to compile RKH port
# TODO: May can be merged both rules?
%.o : $(RKH_PORT_PATH)$(DS)%.c
	@echo ' '
	@echo =====================================================================
	@echo Compiling RKH Port 'c' file: $<
	@echo ' '
	$(CC) $(CFLAGS) $(call cp4c,$<) -o $(OBJ_DIR)$(DS)$@
ifeq ($(MAKE_DEPENDENCIES),1)
	@echo ' '
	@echo Generating dependencies...
	$(CC) -MM $(CFLAGS) $(call cp4c,$<) > $(OBJ_DIR)$(DS)$(@:.o=.d)
else
	@echo ' '
	@echo Skipping make dependencies...
endif
endif

	 	
