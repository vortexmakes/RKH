PROGNAME=rkh

CC=gcc
RKHSRCPATH=$(PWD)/../../source
PORTPATH= $(RKHSRCPATH)/portable

DEFINE= -D__LNXGCC__
CFLAGS = -g -Wall -I$(RKHSRCPATH)/include -I$(PWD) -I$(PORTPATH) 
LDFLAGS	= -lc  

rkhobjects:=$(patsubst %.c,%.o,$(wildcard $(RKHSRCPATH)/*.c)) 
rkh:=$(patsubst $(RKHSRCPATH)/%, %,$(rkhobjects)) 


objects:=$(patsubst %.c,%.o,$(wildcard *.c))

$(PROGNAME): $(objects) $(rkhobjects) 
	@$(CC) -o $@ $(objects) $(rkh) $(LDFLAGS)


%.o: %.c
	@$(CC) $(CFLAGS) -c $(DEFINE) $<

clean: 
	/bin/rm -rf *.o *~ $(PROGNAME) 

tags:
	ctags -R $(RKHSRCPATH) $(PWD)
