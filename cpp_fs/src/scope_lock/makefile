#######################################################################################
# SUBJECT: string makefile
#
# DEVELOPER: Or Katz
#
#######################################################################################
#Variable Definitions

TDIR = ../../test
IDIR = ../../include
TARGET = scope_lock
CC = g++ -pthread -std=c++98 -pedantic-errors -Wall -Wextra -g -I $(IDIR)


##########################################################################################################

all: $(TARGET).out

##########################################################################################################
#creates an executable for avl DS

$(TARGET).out:  $(TARGET)_test.o
	$(CC) $(TARGET)_test.o -o $@

############################################################################################################
#creates object files

$(TARGET)_test.o: $(TDIR)/$(TARGET)_test.cpp
	$(CC) -c $(TDIR)/$(TARGET)_test.cpp

############################################################################################################
#Utilities
.PHONY: clean all except source file

clean:
	rm *.o *.out
