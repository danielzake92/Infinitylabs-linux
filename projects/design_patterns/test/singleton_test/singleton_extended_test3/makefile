###############################################################################
# 	FILENAME:	makefile    		AUTHOR: DanielZ 		LAB: RD100	  	  #
#																			  #
#	TARGETS:	singleton.o 												  #
#																			  #
#				singleton.out												  #
#																			  #
###############################################################################
#Variable Definitions

IDIR = ../../../include
ADDLIB = -lboost_system -lboost_thread -lpthread 
CC = g++ -std=c++98 -pedantic-errors -Wall -Wextra -g -I $(IDIR)

LFLAGS = -shared -fPIC

TARGET = singleton

MAIN = main
FILE1 = file1

##########################################################################################################

all: $(MAIN).out lib$(FILE1).so

##########################################################################################################

$(MAIN).out: $(MAIN).o 
	$(CC) -rdynamic  $^ -ldl -o $@

############################################################################################################
#creates object files
$(MAIN).o: $(MAIN).cpp $(IDIR)/$(TARGET).hpp
	$(CC) -c $<

lib$(FILE1).so: $(FILE1).cpp $(IDIR)/$(TARGET).hpp
	$(CC) -rdynamic $(LFLAGS) $< -o $@

############################################################################################################
#Utilities
.PHONY: clean all except source file

run:
	@./$(MAIN).out

runv:
	@valgrind --leak-check=yes --track-origins=yes ./$(MAIN).out

runh:
	@valgrind --tool=helgrind ./$(MAIN).out

clean:
	@rm -f *.o *.out *.so
