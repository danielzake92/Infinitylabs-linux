#######################################################################################
# SUBJECT: DATA STRUCTURES MAKEFILE
#
# DEVELOPER: Or Katz				TEAM: YELLOW
#
#######################################################################################
#Variable Definitions
NAME = data_structures
LDIR = ./lib
TDIR = ./test
ODIR = ./obj
IDIR = ./include
SDIR = ./src
SRCS = $(shell find $(SDIR) -type f -name "*.c")
OBJS_DEBUG = $(addprefix $(ODIR)/,$(patsubst %.c,%_DEBUG.o,$(notdir $(SRCS))))
OBJS_RELEASE = $(addprefix $(ODIR)/,$(patsubst %.c,%_RELEASE.o,$(notdir $(SRCS))))
DEBUG = -g
RELEASE = -DNDEBUG -O3
TESTS_SRC = $(wildcard $(TDIR)/*.c)
TESTS = $(patsubst %.c,%.out,$(TESTS_SRC))
CC = gcc -ansi -pedantic-errors -Wall -Wextra -I $(IDIR) -fPIC	

#auto dependency
deps := $(patsubst %.o,%.d,$(OBJS)) 
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)


##########################################################################################################

# default which creates both debug and release version
all: build debug release 

##########################################################################################################
#creates executibles for each test in datastructures directory and runs them, also will build debug library if necessary
test: $(TESTS)

$(TESTS): $(TESTS_SRC) debug
	$(CC) $(filter-out -fPIC, $(CFLAGS)) $(patsubst %.out,%.c,$@) -o $@ -L$(LDIR) -Wl,-rpath=../$(LDIR) -l_$(NAME)_DEBUG -lm -lpthread;
############################################################################################################
#builds debug version
debug: build $(LDIR)/lib_$(NAME)_DEBUG.so

$(LDIR)/lib_$(NAME)_DEBUG.so: $(OBJS_DEBUG)
	$(CC) -shared -o $@ $(OBJS_DEBUG)

$(ODIR)/%_DEBUG.o: $(SDIR)/*/%.c
	echo $<
	$(CC) -c $(DEBUG) $< -o $@ $(DEPFLAGS)	
#############################################################################################################
#builds release version	
release: build $(LDIR)/lib_$(NAME)_RELEASE.so

$(LDIR)/lib_$(NAME)_RELEASE.so: $(OBJS_RELEASE)
	$(CC) -shared -o $@ $(OBJS_RELEASE)
	
$(ODIR)/%_RELEASE.o: $(SDIR)/*/%.c 
	$(CC) -c $(RELEASE) $< -o $@ $(DEPFLAGS)	

# If the first argument is "run"...
ifeq (run,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
RUN_ARG := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
$(eval $(RUN_ARG):;@:)
endif

# If the first argument is "runv"...
ifeq (runv,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
RUN_ARG := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
$(eval $(RUN_ARG):;@:)
endif

prog: # ...

run: prog
	cd test ; ./$(RUN_ARG)_test.out

runv: prog
	cd test ; valgrind --leak-check=yes --track-origins=yes ./$(RUN_ARG)_test.out	

build:
	mkdir -p obj -p lib	

############################################################################################################
#Utilities
.PHONY: clean all release debug test run makedir

clean:
	rm -f ./test/*.out; rm -r ./obj
	
	
