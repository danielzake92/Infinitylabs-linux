#######################################################################################
# SUBJECT: IPC MAKEFILE
#
# DEVELOPER: Daniel Z				TEAM: YELLOW
#
#######################################################################################
#Variable Definitions

LIBDIR = ./help_lib
INCDIR = ./include

util = tcp_udp

ex1 = udp_pong
ex1.2 = udp_ping

ex2 = tcp_pong
ex2.2 = tcp_ping

ex3 = udp_broadcast
ex3.2 = udp_cli1
ex3.3 = udp_cli2
ex3.4 = udp_cli3

CC = gcc -std=c99 -pedantic-errors -Wall -Wextra -g -pthread -I$(INCDIR)

##########################################################################################################
all: udp tcp broadcast util

##########################################################################################################
util: $(LIBDIR)/$(util).o
udp: ex1/$(ex1).out ex1/$(ex1.2).out
tcp: ex2/$(ex2).out ex2/$(ex2.2).out
broadcast: ex3/$(ex3).out ex3/$(ex3.2).out ex3/$(ex3.3).out ex3/$(ex3.4).out
##########################################################################################################

$(LIBDIR)/$(util).o: $(LIBDIR)/$(util).c $(INCDIR)/$(util).h
	$(CC) -c $(LIBDIR)/$(util).c -o $@
##########################################################################################################

ex1/$(ex1).out: ex1/$(ex1).c $(LIBDIR)/$(util).o $(INCDIR)/$(util).h
	$(CC) $^ -o $@

ex1/$(ex1.2).out: ex1/$(ex1.2).c $(LIBDIR)/$(util).o $(INCDIR)/$(util).h
	$(CC) $^ -o $@

##########################################################################################################
ex2/$(ex2).out: ex2/$(ex2).c $(LIBDIR)/$(util).o $(INCDIR)/$(util).h
	$(CC) $^ -o $@

ex2/$(ex2.2).out: ex2/$(ex2.2).c $(LIBDIR)/$(util).o $(INCDIR)/$(util).h
	$(CC) $^ -o $@
############################################################################################################
ex3/$(ex3).out: ex3/$(ex3).c $(LIBDIR)/$(util).o $(INCDIR)/$(util).h
	$(CC) ex3/$(ex3).c -o $@

ex3/$(ex3.2).out: ex3/$(ex3.2).c $(LIBDIR)/$(util).o $(INCDIR)/$(util).h
	$(CC) $^ -o $@

ex3/$(ex3.3).out: ex3/$(ex3.3).c $(LIBDIR)/$(util).o $(INCDIR)/$(util).h
	$(CC) $^ -o $@	

ex3/$(ex3.4).out: ex3/$(ex3.4).c $(LIBDIR)/$(util).o $(INCDIR)/$(util).h
	$(CC) $^ -o $@		
############################################################################################################
#Utilities
.PHONY: clean all except source file

run1:
	@ex1/$(ex1).out& ex1/$(ex1.2).out;

run2:
	@ex2/$(ex2).out& ex2/$(ex2.2).out;

run3:
	@ex3/$(ex3.2).out& ex3/$(ex3.3).out& ex3/$(ex3.4).out& ex3/$(ex3).out	

kill1:
	killall -9 $(ex1).out;
	killall -9 $(ex1.2).out;
kill2:	
	killall -9 $(ex2).out;
	killall -9 $(ex2.2).out;

clean:
	rm -f **/*.out 
