###############################################################################
# 	FILENAME:	makefile    		AUTHOR: DanielZ 		LAB: RD100	  	  #
#																			  #
#	TARGETS:	logger.o 												  #
#																			  #
#				logger.out												  #
#																			  #
###############################################################################
#Variable Definitions

TDIR = ../../test
IDIR = ../../include
IDIR2 = ../../../ds/include
TARGET = logger
ADDLIB = -lboost_system -lboost_thread -lpthread 
CC = g++ -std=c++98 -pedantic-errors -Wall -Wextra -g -I $(IDIR) -I $(TDIR) -I $(IDIR2)
#CC = g++ -I $(IDIR) -I $(TDIR)


##########################################################################################################

all: $(TARGET).out

##########################################################################################################

$(TARGET).out: $(TARGET).o $(TARGET)_test.o $(IDIR)/$(TARGET).hpp
	$(CC) $(TARGET)_test.o $(TARGET).o $(ADDLIB) -o $@

############################################################################################################
#creates object files

$(TARGET).o: $(TARGET).cpp $(IDIR)/$(TARGET).hpp
	$(CC) -c $^

$(TARGET)_test.o: $(TDIR)/$(TARGET)_test.cpp 
	$(CC) -c $<

############################################################################################################
#Utilities
.PHONY: clean all except source file

run:
	@./$(TARGET).out

runv:
	@valgrind --leak-check=yes --track-origins=yes ./$(TARGET).out

clean:
	@rm -f *.o *.out
