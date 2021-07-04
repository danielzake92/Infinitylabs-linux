# directories.
I_DIR = ./
LIBDIR = ./
OBJDIR = ./
T_DIR = ./

# Compilation details.
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
S_LINK = -c
LDFLAGS = -L$(LIBDIR) -Wl,-rpath=$(LIBDIR)

# Target name
TARGET=mapping2

# List of object file names
OBJNAMES = $(TARGET).o $(TARGET)_test.o

# List of object file paths.
OBJECTS = $(addprefix $(OBJDIR)/,$(OBJNAMES))

.PHONY: clean all release debug read

src=$(TARGET).c
test=$(TARGET)_test.c


imp: $(TARGET)_imp.out 
	
exp: $(TARGET)_exp.out
	
#make excecutable
$(TARGET)_imp.out: $(TARGET)_test.c lib$(TARGET).so
	$(CC) $(CFLAGS) $(LDFLAGS) -no-pie $< -o $@ -l$(TARGET)

$(TARGET)_exp.out: $(TARGET)_test.c 
	$(CC) $(CFLAGS) -no-pie $< -o $@ -ldl

lib$(TARGET).so: $(TARGET).c
	$(CC) $(CFLAGS) -fpic -shared $< -o $@ -I $(I_DIR)


#run excecutable
test:
	./$(TARGET).out

read_imp:
	readelf -d $(TARGET)_imp.out

read_exp:
	readelf -d $(TARGET)_exp.out

gdb_imp:
	gdbtui ./$(TARGET)_imp.out

gdb_exp:
	gdbtui ./$(TARGET)_exp.out	
	
#clean excecutable & object
clean:
	rm $(TARGET)_imp.out $(TARGET)_exp.out $(OBJECTS) $(LIBDIR)/lib$(TARGET).so
