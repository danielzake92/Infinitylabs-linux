#######################################################################################
# SUBJECT: IPC MAKEFILE
#
# DEVELOPER: Or Katz				TEAM: YELLOW
#
#######################################################################################
#Variable Definitions

TDIR = ../../test
IDIR = ../../include
TARGET1 = unnamed_pipe

TARGET2 = named_pipe
TARGET2.1 = fifo_pong

TARGET3 = p1_message_queue
TARGET3.2 = p2_message_queue
TARGET3.3 = p3_message_queue
TARGET3.4 = p4_message_queue

TARGET4 = p1_shm
TARGET4.2 = p2_shm
TARGET4.3 = p3_shm
TARGET4.4 = p4_shm

CC = gcc -std=c99 -pedantic-errors -Wall -Wextra -g

##########################################################################################################
all: shm unnamedpipe namedpipe namedpipe messagequeue

##########################################################################################################
unnamedpipe: $(TARGET1).out
namedpipe: $(TARGET2).out $(TARGET2.1).out
messagequeue: $(TARGET3).out $(TARGET3.2).out $(TARGET3.3).out $(TARGET3.4).out
shm: $(TARGET4).out $(TARGET4.2).out $(TARGET4.3).out $(TARGET4.4).out
##########################################################################################################
$(TARGET1).out: $(TARGET1).c
	$(CC) $(TARGET1).c -o $@
##########################################################################################################
$(TARGET2).out: $(TARGET2).c
	$(CC) $(TARGET2).c -o $@
$(TARGET2.1).out: $(TARGET2.1).c
	$(CC) $(TARGET2.1).c -o $@
##########################################################################################################
$(TARGET3).out: $(TARGET3).c
	$(CC) $(TARGET3).c -o $@
$(TARGET3.2).out: $(TARGET3.2).c
	$(CC) $(TARGET3.2).c -o $@
$(TARGET3.3).out: $(TARGET3.3).c
	$(CC) $(TARGET3.3).c -o $@
$(TARGET3.4).out: $(TARGET3.4).c
	$(CC) $(TARGET3.4).c -o $@
############################################################################################################
$(TARGET4).out: $(TARGET4).c
	$(CC) $(TARGET4).c -o $@
$(TARGET4.2).out: $(TARGET4.2).c
	$(CC) $(TARGET4.2).c -o $@
$(TARGET4.3).out: $(TARGET4.3).c
	$(CC) $(TARGET4.3).c -o $@
$(TARGET4.4).out: $(TARGET4.4).c
	$(CC) $(TARGET4.4).c -o $@
############################################################################################################
#Utilities
.PHONY: clean all except source file


run1:
	@./$(TARGET1).out;

run2:
	@./named_pipe.out& ./fifo_pong.out;
run3:
	@./$(TARGET3).out;
	@./$(TARGET3.2).out;
	@./$(TARGET3.3).out;
	@./$(TARGET3.4).out;

run4:
	@./$(TARGET4).out;
	@./$(TARGET4.2).out;
	@./$(TARGET4.3).out;
	@./$(TARGET4.4).out;
	@ipcs -m;

kill1:
	killall -9 $(TARGET1).out;

kill2:
	killall -9 $(TARGET2).out;
	killall -9 $(TARGET2.1).out;

clean:
	rm -f *.out *.txt
