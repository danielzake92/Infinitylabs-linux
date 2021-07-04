#######################################################################################
# SUBJECT: EXT2 MAKEFILE
#
# DEVELOPER: Or Katz				TEAM: RD100
#
#######################################################################################
#Variable Definitions

TDIR = ../../test
IDIR = ../../include
TARGET = ext2
CC = gcc -g -ansi -pedantic-errors -Wall -Wextra -I $(IDIR)


##########################################################################################################

all: $(TARGET).out

##########################################################################################################
#creates an executable for ext2

$(TARGET).out: $(TARGET)_test.o $(TARGET).o 
	$(CC) $(TARGET)_test.o $(TARGET).o -o $@

############################################################################################################
#creates object files

$(TARGET).o: $(TARGET).c $(IDIR)/$(TARGET).h
	$(CC) -c $(TARGET).c

$(TARGET)_test.o: $(TDIR)/$(TARGET)_test.c
	$(CC) -c $(TDIR)/$(TARGET)_test.c

############################################################################################################
#Utilities
.PHONY: clean all except source file

run:
	sudo ./ext2.out 

runv:
	sudo valgrind --leak-check=yes --track-origins=yes 

clean:
	rm *.o *.out