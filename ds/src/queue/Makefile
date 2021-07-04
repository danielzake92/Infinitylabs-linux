# directories.
I_DIR = ../../include
LIBDIR = ../../lib
OBJDIR = ../../obj
T_DIR = ../../test


SCHED_DIR := ../TaskScheduler
TASK_DIR := ../TaskScheduler

# Compilation details. 
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g 
S_LINK = -c
LDFLAGS = -L$(LIBDIR) -Wl,-rpath=$(LIBDIR)


#Main goal for the makefile

# Target name

QUEUE=queue
SINGLY=singly_linked_list

test = $(QUEUE)_test

OBJNAMES=$(QUEUE).o $(SINGLY).o 

OBJECTS = $(addprefix $(OBJDIR)/,$(OBJNAMES))

INCLUDE = $(I_DIR)/$(SINGLY).h $(I_DIR)/utl.h


.PHONY: clean all release debug

all: a.out

a.out: $(OBJDIR)/$(test).o $(LIBDIR)/lib$(QUEUE).so 
	$(CC) $(LDFLAGS) $^ -o $@ -l$(QUEUE)

$(LIBDIR)/lib$(QUEUE).so: $(OBJECTS)
	$(CC) -shared $^ -o $@
	
#QUEUE
$(OBJDIR)/$(QUEUE).o: ../$(QUEUE)/$(QUEUE).c $(I_DIR)/$(QUEUE).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -fpic -c $< -o $@ -I $(I_DIR)
#SINGLY	
$(OBJDIR)/$(SINGLY).o: ../$(SINGLY)/$(SINGLY).c $(I_DIR)/$(QUEUE).h $(I_DIR)/$(SINGLY).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -fpic -c $< -o $@ -I $(I_DIR)

#test
$(OBJDIR)/$(test).o: $(T_DIR)/$(test).c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(I_DIR)	
	
		
#run
test:
	./a.out
#clean
clean:
	rm a.out $(OBJECTS) 















