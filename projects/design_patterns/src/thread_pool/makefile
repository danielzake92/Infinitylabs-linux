#######################################################################################
# SUBJECT: thread_pool makefile
#
# DEVELOPER: Daniel Zaken
#
#######################################################################################
#Variable Definitions

CP_PATH = ../../../ds

TDIR = ../../test
IDIR = ../../include


TARGET = thread_pool

TSQUEUE = thread_safe_que


CINC = -I $(IDIR) -I $(CP_PATH)/include -I $(CP_PATH)/test -I /usr/include/boost
ADDLIB = -lboost_system -lboost_thread -lpthread 
CC = g++ -std=c++98 -pedantic-errors -Wall -Wextra -pthread -g $(CINC) 
##########################################################################################################

all: $(TARGET).out

##########################################################################################################

$(TARGET).out: $(TARGET)_test.o $(TARGET).o logger.o singleton.o
	$(CC) $^ $(ADDLIB) -o $@

############################################################################################################
#creates object files

$(TARGET)_test.o: $(TDIR)/$(TARGET)_test.cpp $(IDIR)/$(TARGET).hpp
	$(CC) -c $<
	
$(TARGET).o: $(TARGET).cpp $(IDIR)/$(TARGET).hpp
	$(CC) -c $<

logger.o: ../logger/logger.cpp $(IDIR)/logger.hpp
	$(CC) -c $<

singleton.o: ../singleton/singleton.cpp $(IDIR)/singleton.hpp
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
