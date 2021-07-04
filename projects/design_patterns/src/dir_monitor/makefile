###############################################################################
# 	FILENAME:	makefile    		AUTHOR: DanielZ 		LAB: RD100	  	  #
#																			  #
#	TARGETS:	dir_monitor.o 												  #
#																			  #
#				dir_monitor.out												  #
#																			  #
###############################################################################
#Variable Definitions

TDIR = ../../test
IDIR = ../../include
TARGET = dir_monitor
LINKEDLIB = -lboost_system -lboost_thread -lpthread -ldl
CC = g++ -std=c++98 -pedantic-errors -Wall -Wextra -g -I $(IDIR) -I $(TDIR) -I ../../../ds/include


##########################################################################################################

all: build $(TARGET).out 

##########################################################################################################

$(TARGET).out: $(TARGET).o $(TARGET)_test.o $(IDIR)/$(TARGET).hpp singleton.o logger.o 
	$(CC) $^ $(LINKEDLIB) -o $@

############################################################################################################
#creates object files

$(TARGET).o: $(TARGET).cpp $(IDIR)/$(TARGET).hpp
	$(CC) -c $<

$(TARGET)_test.o: $(TDIR)/$(TARGET)_test.cpp
	$(CC) -c $<

logger.o: ../logger/logger.cpp $(IDIR)/logger.hpp
	$(CC) -c $<

singleton.o: ../singleton/singleton.cpp $(IDIR)/singleton.hpp
	$(CC) -c $<
############################################################################################################

test_dir/lib$(TARGET)_share.so: test_dir/$(TARGET)_share.cpp
	$(CC) -shared -fPIC $< -o $@
############################################################################################################
#Utilities
.PHONY: clean all except source file

build:
	mkdir -p test_dir

run:
	@./$(TARGET).out

runv:
	@valgrind --leak-check=yes --track-origins=yes ./$(TARGET).out
runh:
	@valgrind --tool=helgrind ./$(TARGET).out

clean:
	@rm -f *.o *.out test_dir/*.so

clean_shared:
	@rm -f test_dir/*.so

test: test_dir/lib$(TARGET)_share.so
	mkdir -p test_dir;
	touch test_dir/short1.to test_dir/short2.to;
	touch test_dir/med_size.to test_dir/much_longer_wow_long.to;
	rm -f test_dir/*.to