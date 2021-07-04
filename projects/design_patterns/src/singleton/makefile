###############################################################################
# 	FILENAME:	makefile    		AUTHOR: DanielZ 		LAB: RD100	  	  #
#																			  #
#	TARGETS:	singleton.o 												  #
#																			  #
#				singleton.out												  #
#																			  #
###############################################################################
#Variable Definitions

TDIR = ../../test
IDIR = ../../include
TARGET = singleton
ADDLIB = -lboost_system -lboost_thread -lpthread 
CC = g++ -std=c++98 -pedantic-errors -Wall -Wextra -g -I $(IDIR) -I $(TDIR) -I ../../../ds/include
#CC = g++ -I $(IDIR) -I $(TDIR)


##########################################################################################################

all: $(TARGET).out

##########################################################################################################

$(TARGET).out: $(TARGET).o $(TARGET)_test.o logger.o
	$(CC) $^ $(ADDLIB) -o $@

############################################################################################################
#creates object files

$(TARGET).o: $(TARGET).cpp $(IDIR)/$(TARGET).hpp
	$(CC) -c $<

logger.o: ../logger/logger.cpp $(IDIR)/logger.hpp
	$(CC) -c $<

$(TARGET)_test.o: $(TDIR)/$(TARGET)_test.cpp
	$(CC) -c $<

############################################################################################################
#Utilities
.PHONY: clean all except source file

run:
	@./$(TARGET).out

runv:
	@valgrind --leak-check=yes --track-origins=yes ./$(TARGET).out

runh:
	@valgrind --tool=helgrind ./$(TARGET).out

clean:
	@rm -f *.o *.out
