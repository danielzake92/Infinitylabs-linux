#######################################################################################
# SUBJECT: cpp2c makefile
#
# DEVELOPER: Itamar Aron
#
#######################################################################################
#Variable Definitions

TDIR = ../../test
IDIR = ../../include
TARGET = cpp2c
CC = g++ -std=c++98 -pedantic-errors -Wall -Wextra -g -I $(IDIR)
C = gcc -pedantic-errors -Wall -Wextra -g -I $(IDIR)

##########################################################################################################

all: c cpp 

##########################################################################################################
#creates an executable

c:
	$(C) $(TARGET).c $(TDIR)/$(TARGET)_test.c -o c.out

cpp: $(TARGET).o 
	$(CC) $(TARGET).o

run:
	@./c.out

meld:
	@./c.out >> c.txt;
	@./a.out >> cpp.txt;
	@meld cpp.txt c.txt;
	@rm *.txt

diff:
	@./c.out >> c.txt;
	@./a.out >> cpp.txt;
	@echo "\e[1;31m**********DIFF_TEST**********\e[0m";
	@diff -y cpp.txt c.txt;
	@echo "\e[1;31m***********SUMMARY**********\e[0m";
	@diff -s cpp.txt c.txt;
	@rm *.txt

############################################################################################################
#creates object files

$(TARGET).o: $(TARGET).cpp
	$(CC) -c $(TARGET).cpp


############################################################################################################
#Utilities
.PHONY: clean all except source file

clean:
	rm -f *.o *.out *.txt