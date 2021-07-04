###############################################################################
# 	FILENAME:	makefile    		AUTHOR: DanielZ 		LAB: RD100	  	  #
#																			  #
#	TARGETS:	dispacher.o 												  #
#																			  #
#				dispacher.out												  #
#																			  #
###############################################################################
#Variable Definitions

TDIR = ../../test
IDIR = ../../include
TARGET = dispatcher
LINKEDLIB = -lboost_system -lboost_thread -lpthread 
CC = g++ -std=c++98 -pedantic-errors -Wall -Wextra -g -pthread -I $(IDIR) -I $(TDIR)
#CC = g++ -I $(IDIR) -I $(TDIR)


##########################################################################################################

all: $(TARGET).out

##########################################################################################################

$(TARGET).out: $(TARGET).o $(TARGET)_test.o
	$(CC) $^ $(LINKEDLIB) -o $@

############################################################################################################
#creates object files

$(TARGET).o: $(TARGET).cpp $(IDIR)/$(TARGET).hpp
	$(CC) -c $<

$(TARGET)_test.o: $(TDIR)/$(TARGET)_test.cpp $(IDIR)/$(TARGET).hpp
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
