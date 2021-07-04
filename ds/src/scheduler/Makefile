# directories.
I_DIR = ../../include
LIBDIR = ../../lib
OBJDIR = ../../obj
T_DIR = ../../test

# Compilation details. 
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra 

DEBUG = -g
RELEASE = -DNDEBUG -O3

S_LINK = -c
LDFLAGS = -L$(LIBDIR) -Wl,-rpath=$(LIBDIR)


#Main goal for the makefile
GOAL=scheduler

# Target name

VECTOR=dynamic_vector
HEAP=heap
PQ=pq_heap
UID=uid
TASK=task
test = $(GOAL)_test

OBJNAMES= $(HEAP).o $(PQ).o $(UID).o $(TASK).o $(GOAL).o $(VECTOR).o

OBJECTS = $(addprefix $(OBJDIR)/,$(OBJNAMES))

SRCS= ../$(HEAP)/$(HEAP).c ../$(PQ)/$(PQ).c ../$(UID)/$(UID).c ../$(TASK)/$(TASK).c ../$(GOAL)/$(GOAL).c ../$(VECTOR)/$(VECTOR).c

INCLUDE = $(I_DIR)/$(UID).h $(I_DIR)/$(TASK).h $(I_DIR)/$(GOAL).h $(I_DIR)/utl.h $(I_DIR)/$(HEAP).h $(I_DIR)/$(PQ).h $(I_DIR)/$(VECTOR).h

#auto dependency
deps := $(patsubst %.o,%.d,$(OBJECTS)) 
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)

.PHONY: clean all build




all: build a.out

a.out: $(OBJDIR)/$(test).o $(LIBDIR)/lib$(GOAL).so 
	$(CC) $(LDFLAGS) $^ -o $@ -l$(GOAL)

$(LIBDIR)/lib$(GOAL).so: $(OBJECTS)
	$(CC) -shared $^ -o $@


# $(OBJDIR)/%_DEBUG.o: $(SRCS)
# 	$(CC) $(CFLAGS) -c $(DEBUG) $< -o $@ $(DEPFLAGS)	

#DYNAMIC_VECTOR
$(OBJDIR)/$(VECTOR).o: ../$(VECTOR)/$(VECTOR).c $(I_DIR)/utl.h $(I_DIR)/$(VECTOR).h
	$(CC) $(CFLAGS) -fpic -c $< -o $@ -I $(I_DIR)

#HEAP	
$(OBJDIR)/$(HEAP).o: ../$(HEAP)/$(HEAP).c ../$(VECTOR)/$(VECTOR).c $(I_DIR)/$(HEAP).h $(I_DIR)/utl.h $(I_DIR)/$(VECTOR).h
	$(CC) $(CFLAGS) -fpic -c $< -o $@ -I $(I_DIR)
#PQ		
$(OBJDIR)/$(PQ).o: ../$(PQ)/$(PQ).c ../$(HEAP)/$(HEAP).c $(I_DIR)/$(PQ).h $(I_DIR)/$(HEAP).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -fpic -c $< -o $@ -I $(I_DIR)	
#UID			
$(OBJDIR)/$(UID).o: ../$(UID)/$(UID).c $(I_DIR)/$(UID).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -fpic -c $< -o $@ -I $(I_DIR)	
#TASK
$(OBJDIR)/$(TASK).o: ../$(GOAL)/$(TASK).c $(I_DIR)/$(TASK).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -fpic -c $< -o $@ -I $(I_DIR)	
#scheduler
$(OBJDIR)/$(GOAL).o: ../$(GOAL)/$(GOAL).c ../$(PQ)/$(PQ).c $(I_DIR)/$(GOAL).h $(I_DIR)/utl.h $(I_DIR)/$(HEAP).h
	$(CC) $(CFLAGS) -c $< -o $@ -I $(I_DIR)	
#test
$(OBJDIR)/$(test).o: $(T_DIR)/$(test).c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(I_DIR)	

build:
	mkdir -p ../../obj -p ../../lib	


#run
test:
	./a.out
#clean
clean:
	rm -f a.out $(OBJECTS)















