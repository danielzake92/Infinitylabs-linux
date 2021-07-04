###############################################################################
# 	FILENAME:	makefile    		AUTHOR: DanielZ 		LAB: RD100	  	  #
#																			  #
#	TARGETS:	rcstring.o (DEBUG/RELEASE)									  #
#				lib_rcstring.so (DEBUG/RELEASE)							  #
#				a.out														  #
#																			  #
###############################################################################

# subject name
SUBJECT = rcstring

# directories: h/hpp files, so files, o files, bin files
IDIR = ../../include
LDIR = ../../lib
ODIR = ../../obj
TDIR = ../../test
BDIR = .

# dependancies
# none

# compilation details
CC = g++
CFLAGS = -std=c++98 -pedantic-errors -Wall -Wextra -I $(IDIR)	
LDFLAGS = -L $(LDIR) -Wl,-rpath=$(LDIR)
DEBUG = -g
RELEASE = -DNDEBUG -O3

# list of object file names
OBJNAMES = $(SUBJECT).o $(SUBJECT)_test.o

# list of object file paths
OBJECTS = $(addprefix $(ODIR)/,$(OBJNAMES))

.PHONY: a.out clean all release debug

# in case of core dump test file won't be deleted
.PRECIOUS: a.out

all: a.out

###############################################################################
# creates executibles for "a.out" (debug) & "<subject>" (release), 
# both in bin folder

a.out: debug
	$(CC) $(CFLAGS) $(DEBUG) $(TDIR)/$(SUBJECT)_test.cpp $(LDFLAGS) $(LDIR)/lib_$(SUBJECT)_DEBUG.so -o $@

###############################################################################
# builds debug version

debug: $(LDIR)/lib_$(SUBJECT)_DEBUG.so

$(LDIR)/lib_$(SUBJECT)_DEBUG.so: $(ODIR)/$(SUBJECT)_DEBUG.o
	$(CC) -shared $< -o $@
	
$(ODIR)/$(SUBJECT)_DEBUG.o: $(SUBJECT).cpp
	$(CC) -c -fpic $(CFLAGS) $(DEBUG) $< -o $@ 

###############################################################################
# builds release version

release: $(LDIR)/lib_$(SUBJECT)_RELEASE.so

$(LDIR)/lib_$(SUBJECT)_RELEASE.so: $(ODIR)/$(SUBJECT)_RELEASE.o
	$(CC) -shared $< -o $@
	
$(ODIR)/$(SUBJECT)_RELEASE.o: $(SUBJECT).cpp
	$(CC) -c -fpic $(CFLAGS) $(RELEASE) $< -o $@ 

###############################################################################
# utilities
clean:
	rm  ./a.out ./core $(BDIR)/$(SUBJECT) $(ODIR)/$(SUBJECT)*.d $(ODIR)/$(SUBJECT)*.o $(LDIR)/lib_$(SUBJECT)*.so
