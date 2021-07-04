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

# Target name
TARGET=bitarray

# List of object file names
OBJNAMES = $(TARGET).o $(TARGET)_test.o

# List of object file paths.
OBJECTS = $(addprefix $(OBJDIR)/,$(OBJNAMES))

.PHONY: clean all release debug

src = $(TARGET).c
test = $(T_DIR)/$(TARGET)_test.c

all: a.out

a.out: $(OBJDIR)/$(TARGET)_test.o $(LIBDIR)/lib$(TARGET).so $(I_DIR)/$(TARGET).h 
	$(CC) $(LDFLAGS) $^ -o $@ -l$(TARGET)
	
$(LIBDIR)/lib$(TARGET).so: $(OBJDIR)/$(TARGET).o $(I_DIR)/utl.h
	$(CC) -shared $< -o $@
	
$(OBJDIR)/$(TARGET).o: $(TARGET).c $(I_DIR)/$(TARGET).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -fpic -c $< -o $@ -I $(I_DIR)	

$(OBJDIR)/$(TARGET)_test.o: $(T_DIR)/$(TARGET)_test.c $(I_DIR)/$(TARGET).h $(I_DIR)/utl.h
	$(CC) $(CFLAGS) -c $< -o $@ -I $(I_DIR)	


test: 
	./a.out 
clean:
	rm a.out $(OBJECTS) 

