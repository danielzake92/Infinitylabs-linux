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

DOUBLY=doubly_linked_list
SORTED=sorted_list
PQ=priority_queue

test = $(PQ)_test

OBJNAMES=$(DOUBLY).o $(SORTED).o $(PQ).o 

OBJECTS = $(addprefix $(OBJDIR)/,$(OBJNAMES))

INCLUDE = $(I_DIR)/$(PQ).h $(I_DIR)/utl.h


.PHONY: clean all release debug

all: a.out

a.out: $(OBJDIR)/$(test).o $(LIBDIR)/lib$(PQ).so 
	$(CC) $(LDFLAGS) $^ -o $@ -l$(PQ)

$(LIBDIR)/lib$(PQ).so: $(OBJECTS)
	$(CC) -shared $^ -o $@
	
#DOUBLY
$(OBJDIR)/$(DOUBLY).o: ../$(DOUBLY)/$(DOUBLY).c $(I_DIR)/$(DOUBLY).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -fpic -c $< -o $@ -I $(I_DIR)
#SORTED	
$(OBJDIR)/$(SORTED).o: ../$(SORTED)/$(SORTED).c $(I_DIR)/$(DOUBLY).h $(I_DIR)/$(SORTED).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -fpic -c $< -o $@ -I $(I_DIR)
#PQ		
$(OBJDIR)/$(PQ).o: ../$(PQ)/$(PQ).c $(I_DIR)/$(PQ).h $(I_DIR)/$(SORTED).h $(I_DIR)/utl.h
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















