# directories.
I_DIR = ../../include
LIBDIR = ../../lib
OBJDIR = ../../obj
T_DIR = ../../test

# Compilation details.
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g 
ADD_FLAG= -D _POSIX_C_SOURCE
ADD2_FLAG = -D_POSIX_C_SOURCE=199309L
S_LINK = -c
LDFLAGS = -L$(LIBDIR) -Wl,-rpath=$(LIBDIR)

# Target name
TARGET=ping_pong
PONG=pong
PONG3=ex3_pong

# List of object file names
OBJNAMES = $(TARGET).o $(TARGET)_test.o

# List of object file paths.
OBJECTS = $(addprefix $(OBJDIR)/,$(OBJNAMES))

.PHONY: clean all run build kill

src = $(TARGET).c
test = $(T_DIR)/$(TARGET)_test.c

all: build a.out 

a.out: $(PONG).out $(OBJDIR)/$(TARGET)_test.o $(LIBDIR)/lib$(TARGET).so $(I_DIR)/$(TARGET).h
	$(CC) $(LDFLAGS) $^ -o $@ -l$(TARGET) 

$(LIBDIR)/lib$(TARGET).so: $(OBJDIR)/$(TARGET).o 
	$(CC) -shared $< -o $@

$(OBJDIR)/$(TARGET).o: $(TARGET).c $(I_DIR)/$(TARGET).h 
	$(CC) $(CFLAGS) $(ADD_FLAG) -fpic -c $< -o $@ -I $(I_DIR)

$(OBJDIR)/$(TARGET)_test.o: $(T_DIR)/$(TARGET)_test.c $(I_DIR)/$(TARGET).h 
	$(CC) $(CFLAGS) $(ADD_FLAG) -c $< -o $@ -I $(I_DIR)

$(PONG).out : $(PONG).c $(OBJDIR)/$(TARGET).o
	$(CC) $(CFLAGS) $(ADD_FLAG) $^ -o $@ -I $(I_DIR)
	
$(PONG3).out : $(PONG3).c $(OBJDIR)/$(TARGET).o
	$(CC) $(CFLAGS) $(ADD2_FLAG) $^ -o $@ -I $(I_DIR)		

build:
	mkdir -p ../../obj -p ../../lib	

run:
	./a.out 

run1:
	./a.out 0
	
run2:
	./a.out 1

runv:
	valgrind --leak-check=yes --track-origins=yes ./a.out	

clean:
	rm a.out ; rm -r ../../lib ; rm -r ../../obj ; rm $(PONG).out;

kill:
	killall -9 a.out; killall -9 pong.out; killall -9 make;		
