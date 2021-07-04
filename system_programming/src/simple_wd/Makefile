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
TARGET=simple_wd
DUMMY=dummy

# List of object file names
OBJNAMES = $(TARGET).o $(TARGET)_test.o

# List of object file paths.
OBJECTS = $(addprefix $(OBJDIR)/,$(OBJNAMES))

.PHONY: clean all run build

src = $(TARGET).c
test = $(T_DIR)/$(TARGET)_test.c

all: build a.out

a.out: $(DUMMY).out $(OBJDIR)/$(TARGET)_test.o $(LIBDIR)/lib$(TARGET).so $(I_DIR)/$(TARGET).h
	$(CC) $(LDFLAGS) $^ -o $@ -l$(TARGET) 

$(LIBDIR)/lib$(TARGET).so: $(OBJDIR)/$(TARGET).o 
	$(CC) -shared $< -o $@

$(OBJDIR)/$(TARGET).o: $(TARGET).c $(I_DIR)/$(TARGET).h 
	$(CC) $(CFLAGS) -fpic -c $< -o $@ -I $(I_DIR)

$(OBJDIR)/$(TARGET)_test.o: $(T_DIR)/$(TARGET)_test.c $(I_DIR)/$(TARGET).h 
	$(CC) $(CFLAGS) -c $< -o $@ -I $(I_DIR)

$(DUMMY).out : ./$(DUMMY).c
	$(CC) $(CFLAGS) $< -o $@

build:
	mkdir -p ../../obj -p ../../lib	

run0:
	./a.out 0
	
run1:
	./a.out 1

gdb:
	gdbtui ./a.out	

runv:
	valgrind --leak-check=yes --track-origins=yes ./a.out	

clean:
	rm a.out ; rm -r ../../lib ; rm -r ../../obj ; rm dummy.out;
