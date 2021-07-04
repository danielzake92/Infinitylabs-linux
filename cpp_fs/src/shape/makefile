#######################################################################################
# SUBJECT: string makefile
#
# DEVELOPER: Or Katz
#
#######################################################################################
#Variable Definitions

TDIR = ../../test
IDIR = ../../include
TARGET = shape
CC = g++ -std=c++98 -pedantic-errors -Wall -Wextra -g -I $(IDIR) 


##########################################################################################################

all: $(TARGET).out

##########################################################################################################
#creates an executable for avl DS

$(TARGET).out: $(TARGET).o $(TARGET)_test.o
	$(CC) $(TARGET)_test.o $(TARGET).o -o $@

############################################################################################################
#creates object files

$(TARGET).o: $(TARGET).cpp $(IDIR)/$(TARGET).hpp $(IDIR)/line.hpp $(IDIR)/circle.hpp $(IDIR)/square.hpp $(IDIR)/rectangle.hpp
	$(CC) -c $(TARGET).cpp

$(TARGET)_test.o: $(TDIR)/$(TARGET)_test.cpp
	$(CC) -c $(TDIR)/$(TARGET)_test.cpp

############################################################################################################
#Utilities
.PHONY: clean all except source file

clean:
	rm *.o *.out

run:
	./$(TARGET).out	

runv:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET).out	