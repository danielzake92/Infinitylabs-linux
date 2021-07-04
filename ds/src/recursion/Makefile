# directories.
I_DIR = ../../include
LIBDIR = ../../lib
OBJDIR = ../../obj
T_DIR = ../../test


# Compilation details.
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
S_LINK = -c
LDFLAGS = -L$(LIBDIR) -Wl,-rpath=$(LIBDIR)


#Main goal for the makefile

# Target name

RECURSION=recursion
STACK=stack

test = $(RECURSION)_test

OBJNAMES=$(RECURSION).o $(STACK).o $(test).o

OBJECTS = $(addprefix $(OBJDIR)/,$(OBJNAMES))

INCLUDE = $(I_DIR)/$(SORTED).h $(I_DIR)/utl.h



.PHONY: clean all run open
all: $(RECURSION).out

$(RECURSION).out: $(OBJDIR)/$(RECURSION).o $(OBJDIR)/$(test).o $(LIBDIR)/lib$(STACK).so
	$(CC) $(LDFLAGS) $^ -o $@ -l$(STACK)

$(LIBDIR)/lib$(STACK).so: $(OBJDIR)/$(STACK).o $(I_DIR)/$(STACK).h $(I_DIR)/utl.h
	$(CC) -shared $^ -o $@

#STACK
$(OBJDIR)/$(STACK).o: ../$(STACK)/$(STACK).c $(I_DIR)/$(STACK).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -fpic -c $< -o $@ -I $(I_DIR)

#RECURSION
$(OBJDIR)/$(RECURSION).o: ../$(RECURSION)/$(RECURSION).c $(I_DIR)/$(RECURSION).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -c $< -o $@ -I $(I_DIR)

#test
$(OBJDIR)/$(test).o: $(T_DIR)/$(test).c $(I_DIR)/$(RECURSION).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -c $< -o $@ -I $(I_DIR)


#run
run:
	./$(RECURSION).out

runv:
	valgrind --leak-check=yes --track-origins=yes ./$(RECURSION).out

gdb:
	gdbtui ./$(RECURSION).out

#clean
clean:
	rm $(RECURSION).out $(OBJECTS)
	
open:
	atom $(RECURSION).c	; atom $(T_DIR)/$(test).c ; atom $(I_DIR)/$(RECURSION).h ;
	

	
