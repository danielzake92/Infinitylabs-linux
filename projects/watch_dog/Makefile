MAKE_SCHEDULAR_PATH=../../ds/src/scheduler
DS_LIB=../../ds/lib


#######################################################################################
# SUBJECT: Watch Dog MAKEFILE
#
# DEVELOPER: Or Katz				TEAM: YELLOW
#
#######################################################################################
#Variable Definitions

IDIR1 = ./include
IDIR2 = ../../ds/include
ODIR = ./obj
LDIR = ./lib
SRC = ./src
DSDIR = ../../ds/src
ORIGIN = $(LDIR)
TDIR = ./test
OUTDIR = ./out

TARGET1 = watchdog_main
TARGET2 = watchdog_test

DS_SRCS = scheduler.c task.c uid.c dynamic_vector.c heap.c pq_heap.c
DS_OBJS_DEBUG = $(addprefix $(ODIR)/,$(patsubst %.c,%_DEBUG.o,$(notdir $(DS_SRCS))))
DS_OBJS_RELEASE = $(addprefix $(ODIR)/,$(patsubst %.c,%_RELEASE.o,$(notdir $(DS_SRCS))))

CC = gcc -pthread -ansi -pedantic-errors -Wall -Wextra -I $(IDIR1) -I $(IDIR2) -fPIC
DEBUG = -g
RELEASE = -DNDEBUG -O3

deps := $(patsubst %.o,%.d,$(OBJS))
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)

##########################################################################################################

all: build debug release move

##########################################################################################################
#builds release version

release: build $(LDIR)/lib_watchdog_RELEASE.so $(TARGET1)_RELEASE.out $(TARGET2)_RELEASE.out

$(TARGET2)_RELEASE.out: $(TDIR)/$(TARGET2).c
	$(CC) $^ -L$(ORIGIN) -Wl,-rpath=$(ORIGIN) -o $@ -l_watchdog_RELEASE

$(TARGET1)_RELEASE.out: $(SRC)/$(TARGET1).c
	$(CC) $^ -L$(ORIGIN) -Wl,-rpath=$(ORIGIN) -o $@ -l_watchdog_RELEASE

$(LDIR)/lib_watchdog_RELEASE.so: $(DS_OBJS_RELEASE) $(ODIR)/watchdog_RELEASE.o
	$(CC) -shared $(DS_OBJS_RELEASE) $(ODIR)/watchdog_RELEASE.o -o $@


#watchdog
$(ODIR)/watchdog_RELEASE.o: $(SRC)/watchdog.c
	$(CC) -c $< -o $@ $(DEPFLAGS)
#scheduler
$(ODIR)/%_RELEASE.o: $(DSDIR)/scheduler/%.c
	$(CC) -c $(RELEASE) $< -o $@ $(DEPFLAGS)
#task
$(ODIR)/%_RELEASE.o: $(DSDIR)/task/%.c
	$(CC) -c $(RELEASE) $< -o $@ $(DEPFLAGS)
#uid
$(ODIR)/%_RELEASE.o: $(DSDIR)/uid/%.c
	$(CC) -c $(RELEASE) $< -o $@ $(DEPFLAGS)
#pq_heap
$(ODIR)/%_RELEASE.o: $(DSDIR)/pq_heap/%.c
	$(CC) -c $(RELEASE) $< -o $@ $(DEPFLAGS)
#heap
$(ODIR)/%_RELEASE.o: $(DSDIR)/heap/%.c
	$(CC) -c $(RELEASE) $< -o $@ $(DEPFLAGS)
#dynamic vector
$(ODIR)/%_RELEASE.o: $(DSDIR)/dynamic_vector/%.c
	$(CC) -c $(RELEASE) $< -o $@ $(DEPFLAGS)

############################################################################################################
#builds debug version

debug: build $(LDIR)/lib_watchdog_DEBUG.so $(TARGET1)_DEBUG.out $(TARGET2)_DEBUG.out

$(TARGET1)_DEBUG.out: $(SRC)/$(TARGET1).c
	$(CC) $(DEBUG) $^ -L$(ORIGIN) -Wl,-rpath=$(ORIGIN) -o $@ -l_watchdog_DEBUG

$(LDIR)/lib_watchdog_DEBUG.so: $(DS_OBJS_DEBUG) $(ODIR)/watchdog_DEBUG.o
	$(CC) $(DEBUG) -shared $(DS_OBJS_DEBUG) $(ODIR)/watchdog_DEBUG.o -o $@

$(TARGET2)_DEBUG.out: $(TDIR)/$(TARGET2).c
	$(CC) $(DEBUG) $^ -L$(ORIGIN) -Wl,-rpath=$(ORIGIN) -o $@ -l_watchdog_DEBUG


#watchdog
$(ODIR)/watchdog_DEBUG.o: $(SRC)/watchdog.c
	$(CC) -c $(DEBUG) $< -o $@ $(DEPFLAGS)
#scheduler
$(ODIR)/%_DEBUG.o: $(DSDIR)/scheduler/%.c
	$(CC) -c $(DEBUG) $< -o $@ $(DEPFLAGS)
#uid
$(ODIR)/%_DEBUG.o: $(DSDIR)/uid/%.c
	$(CC) -c $(DEBUG) $< -o $@ $(DEPFLAGS)
#pq_heap
$(ODIR)/%_DEBUG.o: $(DSDIR)/pq_heap/%.c
	$(CC) -c $(DEBUG) $< -o $@ $(DEPFLAGS)
#heap
$(ODIR)/%_DEBUG.o: $(DSDIR)/heap/%.c
	$(CC) -c $(DEBUG) $< -o $@ $(DEPFLAGS)
#dynamic vector
$(ODIR)/%_DEBUG.o: $(DSDIR)/dynamic_vector/%.c
	$(CC) -c $(DEBUG) $< -o $@ $(DEPFLAGS)
############################################################################################################
#Utilities
.PHONY: clean all except source file build	move


build:
	mkdir -p obj -p lib -p export -p out;

move:
	mv *.out $(OUTDIR)

clean:
	rm -r $(ODIR) -r ./export -r $(LDIR) -r $(OUTDIR); rm /dev/shm/sem.*

run:
	@./out/watchdog_test_DEBUG.out &

runv:
	@valgrind --leak-check=yes --track-origins=yes ./out/watchdog_test_DEBUG.out  &

kill1:
	killall -9 watchdog_main_D

kill2:
	killall -9 watchdog_test_D 

killall: kill1 kill2

spec: run sleep

sleep:
	sleep 1; killall -9 watchdog_main_D;
	
	
# cp $(DS_LIB)/libscheduler.so ./lib/libscheduler.so
# make -C $(MAKE_SCHEDULAR_PATH);