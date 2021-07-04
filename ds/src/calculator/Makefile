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

CALCULATOR=calculator
STACK=stack

test = $(CALCULATOR)_test

OBJNAMES=$(CALCULATOR).o $(STACK).o $(test).o

OBJECTS = $(addprefix $(OBJDIR)/,$(OBJNAMES))

INCLUDE = $(I_DIR)/$(SORTED).h $(I_DIR)/utl.h



.PHONY: clean all run read
all: $(CALCULATOR).out

$(CALCULATOR).out: $(OBJDIR)/$(CALCULATOR).o $(OBJDIR)/$(test).o $(LIBDIR)/lib$(STACK).so
	$(CC) $(LDFLAGS) $^ -o $@ -l$(STACK)

$(LIBDIR)/lib$(STACK).so: $(OBJDIR)/$(STACK).o $(I_DIR)/$(STACK).h $(I_DIR)/utl.h
	$(CC) -shared $^ -o $@

#STACK
$(OBJDIR)/$(STACK).o: ../$(STACK)/$(STACK).c $(I_DIR)/$(STACK).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -fpic -c $< -o $@ -I $(I_DIR)

#CALCULATOR
$(OBJDIR)/$(CALCULATOR).o: ../$(CALCULATOR)/$(CALCULATOR).c $(I_DIR)/$(CALCULATOR).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -c $< -o $@ -I $(I_DIR)

#test
$(OBJDIR)/$(test).o: $(T_DIR)/$(test).c $(I_DIR)/$(CALCULATOR).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -c $< -o $@ -I $(I_DIR)


#run
run:
	./$(CALCULATOR).out

runv:
	valgrind --leak-check=yes --track-origins=yes ./$(CALCULATOR).out

gdb:
	gdbtui ./$(CALCULATOR).out

#clean
clean:
	rm $(calculator).out $(OBJECTS)
