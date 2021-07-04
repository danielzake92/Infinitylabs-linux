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

VECTOR=dynamic_vector
HEAP=heap

test = $(HEAP)_test

OBJNAMES=$(VECTOR).o $(HEAP).o 

OBJECTS = $(addprefix $(OBJDIR)/,$(OBJNAMES))

INCLUDE = $(I_DIR)/$(HEAP).h $(I_DIR)/utl.h


.PHONY: clean all release debug

all: a.out

a.out: $(OBJDIR)/$(test).o $(LIBDIR)/lib$(HEAP).so 
	$(CC) $(LDFLAGS) $^ -o $@ -l$(HEAP)

$(LIBDIR)/lib$(HEAP).so: $(OBJECTS)
	$(CC) -shared $^ -o $@
	
#VECTOR
$(OBJDIR)/$(VECTOR).o: ../$(VECTOR)/$(VECTOR).c $(I_DIR)/$(VECTOR).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -fpic -c $< -o $@ -I $(I_DIR)
#HEAP	
$(OBJDIR)/$(HEAP).o: ../$(HEAP)/$(HEAP).c $(I_DIR)/$(VECTOR).h $(I_DIR)/$(HEAP).h $(I_DIR)/utl.h
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















