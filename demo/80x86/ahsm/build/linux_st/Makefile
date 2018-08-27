PROGNAME=rkh

CC=gcc
APPSRCPATH=$(PWD)/../..
RKHSRCPATH=$(PWD)/../../../../../source

RKHMOD_FWK=$(RKHSRCPATH)/fwk
RKHMOD_MEMPOOL=$(RKHSRCPATH)/mempool
RKHMOD_QUEUE=$(RKHSRCPATH)/queue
RKHMOD_SM=$(RKHSRCPATH)/sm
RKHMOD_SMA=$(RKHSRCPATH)/sma
RKHMOD_TMR=$(RKHSRCPATH)/tmr
RKHMOD_TRC=$(RKHSRCPATH)/trc
RKH_PORT= $(RKHSRCPATH)/portable/80x86/linux_st/gnu
RKHBSP = $(PWD)/../../../../libbsp/platform/80x86/linux

PORTFILE=rkhport

DEFINE= -D__LNXGNU__
CFLAGS = -ansi -Wall -I$(APPSRCPATH) -I$(RKHMOD_FWK)/inc -I$(RKHMOD_MEMPOOL)/inc \
		     -I$(RKHMOD_QUEUE)/inc -I$(RKHMOD_SM)/inc -I$(RKHMOD_SMA)/inc \
			 -I$(RKHMOD_TMR)/inc -I$(RKHMOD_TRC)/inc -I$(RKH_PORT) \
			 -I$(RKHBSP) -I$(RKHBSP)/../../../common
LDFLAGS	= -lc -pthread 

rkhobjects:=$(patsubst %.c,%.o,$(wildcard $(RKHSRCPATH)/*.c)) 

app_objs:=$(patsubst %.c,%.o,$(wildcard $(APPSRCPATH)/*.c)) 

rkhfwk_objs:=$(patsubst %.c,%.o,$(wildcard $(RKHMOD_FWK)/src/*.c)) 
rkhmempool_objs:=$(patsubst %.c,%.o,$(wildcard $(RKHMOD_MEMPOOL)/src/*.c)) 
rkhqueue_objs:=$(patsubst %.c,%.o,$(wildcard $(RKHMOD_QUEUE)/src/*.c)) 
rkhsm_objs:=$(patsubst %.c,%.o,$(wildcard $(RKHMOD_SM)/src/*.c)) 
rkhsma_objs:=$(patsubst %.c,%.o,$(wildcard $(RKHMOD_SMA)/src/*.c)) 
rkhtmr_objs:=$(patsubst %.c,%.o,$(wildcard $(RKHMOD_TMR)/src/*.c)) 
rkhtrc_objs:=$(patsubst %.c,%.o,$(wildcard $(RKHMOD_TRC)/src/*.c)) 
rkhport_obj:=$(patsubst %.c,%.o,$(wildcard $(RKH_PORT)/*.c)) 
rkhbsp_obj:=$(patsubst %.c,%.o,$(wildcard $(RKHBSP)/*.c)) 


rkh:=$(patsubst $(RKHSRCPATH)/%, %,$(rkhobjects)) 

app:=$(patsubst $(APPSRCPATH)/%, %,$(app_objs)) 

fwk:=$(patsubst $(RKHMOD_FWK)/src/%, %,$(rkhfwk_objs)) 
mempool:=$(patsubst $(RKHMOD_MEMPOOL)/src/%, %,$(rkhmempool_objs)) 
queue:=$(patsubst $(RKHMOD_QUEUE)/src/%, %,$(rkhqueue_objs)) 
:q
:q
sm:=$(patsubst $(RKHMOD_SM)/src/%, %,$(rkhsm_objs)) 
sma:=$(patsubst $(RKHMOD_SMA)/src/%, %,$(rkhsma_objs)) 
tmr:=$(patsubst $(RKHMOD_TMR)/src/%, %,$(rkhtmr_objs)) 
trc:=$(patsubst $(RKHMOD_TRC)/src/%, %,$(rkhtrc_objs)) 
port:=$(patsubst $(RKH_PORT)/%, %,$(rkhport_obj)) 
rkhbsp:=$(patsubst $(RKHBSP)/%, %,$(rkhbsp_obj)) 

objects:=$(patsubst %.c,%.o,$(wildcard *.c))

$(PROGNAME): $(objects) $(app_objs) $(rkhobjects) $(rkhfwk_objs) \
			 $(rkhmempool_objs) $(rkhqueue_objs) $(rkhsm_objs) \
			 $(rkhsma_objs) $(rkhtmr_objs) $(rkhtrc_objs) \
			 $(rkhport_obj) $(rkhbsp_obj)
	@$(CC) -o $@ $(objects) $(app) $(rkh) $(fwk) $(mempool) \
			  $(queue) $(sm) $(sma) $(tmr) $(trc) $(port) $(rkhbsp) \
			  $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $(DEFINE) $<

clean: 
	/bin/rm -rf *.o *~ $(PROGNAME) 

tags:
	ctags -R $(RKHSRCPATH) $(PWD)
