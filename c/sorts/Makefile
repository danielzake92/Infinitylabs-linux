# directories.
UTLPATH = ../../ds/include

# Compilation details.
CC = gcc
CFLAGS_DEB = -ansi -pedantic-errors -Wall -Wextra -g 
CFLAGS_REL = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
# Target name
TARGET=sorts

# List of object file names
OBJ = $(TARGET).o $(TARGET)_test.o

.PHONY: all run deb clean open

all: $(TARGET).out

$(TARGET).out: $(TARGET).o $(TARGET)_test.o
	$(CC) $^ -o $@

$(TARGET).o: $(TARGET).c $(UTLPATH)/utl.h $(TARGET).h
	$(CC) $(CFLAGS_REL) -c $< -o $@ -I $(UTLPATH)

$(TARGET)_test.o: $(TARGET)_test.c $(UTLPATH)/utl.h $(TARGET).h
	$(CC) $(CFLAGS_REL) -c $< -o $@ -I $(UTLPATH)

gdb:
	gdbtui ./$(TARGET).out
run:
	./$(TARGET).out

runv:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET).out

clean:
	rm $(TARGET).out $(OBJ)
	
open:
	atom $(TARGET).c; atom $(TARGET)_test.c; atom $(TARGET).h	
