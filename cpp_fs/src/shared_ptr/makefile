#######################################################################################
# SUBJECT: shared_ptr makefile
#
# DEVELOPER: Or Katz
#
#######################################################################################
#Variable Definitions

TDIR = ../../test
IDIR = ../../include
TARGET = shared_ptr
CC = g++ -pthread -std=c++98 -pedantic-errors -Wall -Wextra -g -I $(IDIR) -I $(TDIR)


##########################################################################################################

all: $(TARGET).out

##########################################################################################################

$(TARGET).out: $(TARGET).o $(TARGET)_test.o
	$(CC) $(TARGET)_test.o $(TARGET).o -o $@

############################################################################################################
#creates object files

$(TARGET).o: $(TARGET).cpp $(IDIR)/$(TARGET).hpp
	$(CC) -c $(TARGET).cpp

$(TARGET)_test.o: $(TDIR)/$(TARGET)_test.cpp
	$(CC) -c $(TDIR)/$(TARGET)_test.cpp

############################################################################################################
#Utilities
.PHONY: clean all except source file

run:
	./$(TARGET).out

runv:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET).out

clean:
	rm *.o *.out