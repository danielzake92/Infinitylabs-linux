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

BIT=bitarray
KNIGHTS=knights_tour

test = $(KNIGHTS)_test

OBJNAMES=$(BIT).o $(KNIGHTS).o 

OBJECTS = $(addprefix $(OBJDIR)/,$(OBJNAMES))

INCLUDE = $(I_DIR)/$(KNIGHTS).h $(I_DIR)/utl.h


.PHONY: clean all release debug

all: a.out

a.out: $(OBJDIR)/$(test).o $(LIBDIR)/lib$(KNIGHTS).so 
	$(CC) $(LDFLAGS) $^ -o $@ -l$(KNIGHTS)

$(LIBDIR)/lib$(KNIGHTS).so: $(OBJECTS)
	$(CC) -shared $^ -o $@
	
#BIT
$(OBJDIR)/$(BIT).o: ../$(BIT)/$(BIT).c $(I_DIR)/$(BIT).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -fpic -c $< -o $@ -I $(I_DIR)
#KNIGHTS	
$(OBJDIR)/$(KNIGHTS).o: ../$(KNIGHTS)/$(KNIGHTS).c $(I_DIR)/$(BIT).h $(I_DIR)/$(KNIGHTS).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -fpic -c $< -o $@ -I $(I_DIR)

#test
$(OBJDIR)/$(test).o: $(T_DIR)/$(test).c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(I_DIR)	
	
#run
run:
	./a.out

runv:
	valgrind --leak-check=yes --track-origins=yes -s ./a.out	
	
#clean
clean:
	rm a.out $(OBJECTS) 















