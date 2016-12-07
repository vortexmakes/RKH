PROGNAME=rkh

CC=gcc
RKHSRCPATH=$(PWD)/../../../../../source
PORTPATH= $(RKHSRCPATH)/portable/80x86/linux_st/gnu
PORTFILE=rkhport

DEFINE= -D__LNXGNU__
CFLAGS = -ansi -Wall -I$(RKHSRCPATH)/include -I$(PWD) -I$(PORTPATH) 
LDFLAGS	= -lc -pthread 

rkhobjects:=$(patsubst %.c,%.o,$(wildcard $(RKHSRCPATH)/*.c)) 
portobj:=$(patsubst %.c,%.o,$(wildcard $(PORTPATH)/*.c)) 
rkh:=$(patsubst $(RKHSRCPATH)/%, %,$(rkhobjects)) 


objects:=$(patsubst %.c,%.o,$(wildcard *.c))

$(PROGNAME): $(objects) $(rkhobjects) $(portobj) 
	@$(CC) -o $@ $(objects) $(rkh) $(PORTFILE).o $(LDFLAGS)


%.o: %.c
	@$(CC) $(CFLAGS) -c $(DEFINE) $<

clean: 
	/bin/rm -rf *.o *~ $(PROGNAME) 

tags:
	ctags -R $(RKHSRCPATH) $(PWD)
