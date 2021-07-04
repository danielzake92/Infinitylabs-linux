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

DOUBLY=doubly_linked_list
HASH=hash_table

test = $(HASH)_test

OBJNAMES=$(DOUBLY).o $(HASH).o 

OBJECTS = $(addprefix $(OBJDIR)/,$(OBJNAMES))

INCLUDE = $(I_DIR)/$(HASH).h $(I_DIR)/utl.h


.PHONY: clean all run runv

all: a.out

a.out: $(OBJDIR)/$(test).o $(LIBDIR)/lib$(HASH).so 
	$(CC) $(LDFLAGS) $^ -o $@ -l$(HASH) -lm

$(LIBDIR)/lib$(HASH).so: $(OBJECTS)
	$(CC) -shared $^ -o $@
	
#DOUBLY
$(OBJDIR)/$(DOUBLY).o: ../$(DOUBLY)/$(DOUBLY).c $(I_DIR)/$(DOUBLY).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -fpic -c $< -o $@ -I $(I_DIR)
#HASH	
$(OBJDIR)/$(HASH).o: ../$(HASH)/$(HASH).c $(I_DIR)/$(DOUBLY).h $(I_DIR)/$(HASH).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -fpic -c $< -o $@ -I $(I_DIR)

#test
$(OBJDIR)/$(test).o: $(T_DIR)/$(test).c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(I_DIR)	
	
		
#run
run:
	./a.out

runv:
	valgrind --leak-check=yes --track-origins=yes --max-stackframe=4072096 -s ./a.out

#clean
clean:
	rm a.out $(OBJECTS) $(LIBDIR)/lib$(HASH).so















