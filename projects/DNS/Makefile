#######################################################################################
# SUBJECT: DNS MAKEFILE
#
# DEVELOPER: Danie Zaken				
#
#######################################################################################
#Variable Definitions


SDIR = ./src
IDIR = ./include
TDIR = ./test

LDIR = ./lib
ODIR = ./obj
BDIR = ./bin
EDIR = ./export

#design patterns paths
DPDIR = ../design_patterns
DPINCDIR = $(DPDIR)/include

#thread safe queue include
TSQINCDIR = ../ds/include

# FM_SRCS = dir_monitor.cpp logger.cpp reactor.cpp thread_pool.cpp
# FM_OBJS_DEBUG = $(addprefix $(ODIR)/,$(patsubst %.c,%_DEBUG.o,$(notdir $(DS_SRCS))))
# FM_OBJS_DEBUG = $(addprefix $(ODIR)/,$(patsubst %.c,%_DEBUG.o,$(notdir $(DS_SRCS))))

# deps := $(patsubst %.o,%.d,$(OBJS))
# -include $(deps)
# DEPFLAGS = -MMD -MF $(@:.o=.d)

INCFLAGS = -I $(IDIR) -I $(DPINCDIR) -I $(TSQINCDIR) 
CC = g++ -std=c++98 -pedantic-errors -Wall -Wextra $(INCFLAGS)
LINKFLAGS = -L$(LDIR) -Wl,-rpath=$(LDIR)
ADDLIB = -lboost_system -lboost_thread -lpthread -ldl
DEBUG = -g
RELEASE = -DNDEBUG -O3

DIR_MONITOR = dir_monitor
LOGGER = logger
REACTOR = reactor
THREAD_POOL = thread_pool
INPUT_MEDIATOR = input_mediator
STARTUP = startup
HANDLETON = singleton

MASTER = master

.PHONY: clean all except source file build	

all: build $(BDIR)/$(MASTER)_DEBUG.out 

#######################################################################################
## master##

$(BDIR)/$(MASTER)_DEBUG.out: $(SDIR)/$(MASTER).cpp \
							 $(LDIR)/lib_framework_DEBUG.so \
							 $(LDIR)/lib_input_proxy_DEBUG.so \
							 $(IDIR)/$(MASTER).hpp

	$(CC) $^ $(ADDLIB) $(LINKFLAGS) -o $@ 


#######################################################################################
## DEBUG###
#framework.so build 

FM_OBJ_DEBUG = $(ODIR)/$(DIR_MONITOR)_DEBUG.o \
		   		 $(ODIR)/$(LOGGER)_DEBUG.o \
		   		 $(ODIR)/$(REACTOR)_DEBUG.o \
		   		 $(ODIR)/$(THREAD_POOL)_DEBUG.o \
		   		 $(ODIR)/$(INPUT_MEDIATOR)_DEBUG.o \
		   		 $(ODIR)/$(STARTUP)_DEBUG.o \
				 $(ODIR)/$(HANDLETON)_DEBUG.o

$(LDIR)/lib_framework_DEBUG.so: $(FM_OBJ_DEBUG) 
	$(CC) -shared $(FM_OBJ_DEBUG) -o $@

#######################################################################################
#dir_monitor
$(ODIR)/$(DIR_MONITOR)_DEBUG.o: $(DPDIR)/src/$(DIR_MONITOR)/$(DIR_MONITOR).cpp \
								$(ODIR)/$(LOGGER)_DEBUG.o \
								$(ODIR)/$(HANDLETON)_DEBUG.o \
								$(DPINCDIR)/$(DIR_MONITOR).hpp \
								$(DPINCDIR)/dispatcher.hpp 

	$(CC) $(DEBUG) -c -fPIC $< -o $@ -I $(DPINCDIR)

#######################################################################################
#logger
$(ODIR)/$(LOGGER)_DEBUG.o: $(DPDIR)/src/$(LOGGER)/$(LOGGER).cpp \
						   $(DPINCDIR)/$(LOGGER).hpp \
						   $(TSQINCDIR)/thread_safe_que.hpp

	$(CC) $(DEBUG) -c -fPIC $< -o $@ -I $(DPINCDIR) -I $(TSQINCDIR)

#######################################################################################
#reactor
$(ODIR)/$(REACTOR)_DEBUG.o: $(DPDIR)/src/$(REACTOR)/$(REACTOR).cpp \
							$(ODIR)/$(LOGGER)_DEBUG.o \
							$(ODIR)/$(HANDLETON)_DEBUG.o \
							$(DPINCDIR)/$(REACTOR).hpp

	$(CC) $(DEBUG) -c -fPIC $< -o $@ -I $(DPINCDIR)

#######################################################################################
#thread_pool
$(ODIR)/$(THREAD_POOL)_DEBUG.o: $(DPDIR)/src/$(THREAD_POOL)/$(THREAD_POOL).cpp \
								$(ODIR)/$(LOGGER)_DEBUG.o \
								$(ODIR)/$(HANDLETON)_DEBUG.o \
								$(DPINCDIR)/$(THREAD_POOL).hpp \
								$(TSQINCDIR)/thread_safe_que.hpp

	$(CC) $(DEBUG) -c -fPIC $< -o $@ -I $(DPINCDIR) -I $(TSQINCDIR)

#######################################################################################
#input_mediator
$(ODIR)/$(INPUT_MEDIATOR)_DEBUG.o: $(SDIR)/$(INPUT_MEDIATOR).cpp \
								   $(IDIR)/$(INPUT_MEDIATOR).hpp \
								   $(IDIR)/input_proxy.hpp \
								   $(IDIR)/input_mediator_packet.hpp \
								   $(DPINCDIR)/reactor.hpp

	$(CC) $(DEBUG) -c -fPIC $< -o $@ -I $(DPINCDIR) -I $(IDIR) 

#######################################################################################
#startup
$(ODIR)/$(STARTUP)_DEBUG.o: $(SDIR)/$(STARTUP).cpp 
	$(CC) $(DEBUG) -c -fPIC $< -o $@ $(INCFLAGS) 

#######################################################################################
#handleton

$(ODIR)/$(HANDLETON)_DEBUG.o: $(SDIR)/handleton.cpp \
							  $(ODIR)/$(LOGGER)_DEBUG.o \
							  $(ODIR)/$(THREAD_POOL)_DEBUG.o \
							  $(DPINCDIR)/$(HANDLETON).hpp \
							  $(DPINCDIR)/factory.hpp

	$(CC) -c $(DEBUG) -fPIC $< -o $@ -I $(DPINCDIR)

#######################################################################################
#input_proxy
$(ODIR)/input_proxy_DEBUG.o: $(SDIR)/input_proxy.cpp \
							 $(IDIR)/input_proxy.hpp 

	$(CC) -c $(DEBUG) -fPIC $< -o $@  -I $(IDIR) 

#######################################################################################
#input_proxy so
$(LDIR)/lib_input_proxy_DEBUG.so: $(ODIR)/input_proxy_DEBUG.o 
	$(CC) -shared $< -o $@




build:
	@mkdir -p ./obj ./lib ./bin ./export ./test/shared_object 

clean:
	@rm -rf ./lib ./obj ./bin ./export;
	@rm -f ./test/log

log:
	@cat ./test/log

run:
	@rm -f ./test/log
	@./bin/$(MASTER)_DEBUG.out
	
#Utilities