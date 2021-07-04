# directories.
UTLPATH = ../../ds/include

# Compilation details.
CC = gcc
CFLAGS_DEB = -ansi -pedantic-errors -Wall -Wextra -g
CFLAGS_REL = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
# Target name
HEADER=ds_exam
TARGET=$(HEADER)_imp

# List of object file names
OBJ = $(TARGET).o $(HEADER)_test.o

.PHONY: build run deb clean

build: $(TARGET).out

$(TARGET).out: $(TARGET).o $(HEADER)_test.o
	$(CC) $^ -o $@

$(TARGET).o: $(TARGET).c $(UTLPATH)/utl.h $(HEADER).h
	$(CC) $(CFLAGS_DEB) -c $< -o $@ -I $(UTLPATH)

$(HEADER)_test.o: $(HEADER)_test.c $(UTLPATH)/utl.h $(HEADER).h
	$(CC) $(CFLAGS_DEB) -c $< -o $@ -I $(UTLPATH)

deb:
	gdbtui ./$(TARGET).out
run:
	./$(TARGET).out

runv:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET).out

clean:
	rm $(TARGET).out $(OBJ)
