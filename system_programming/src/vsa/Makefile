MAINFOLDER =system_programming
subject=vsa

DSDIR = ~/git/ds/include
IDIR = ~/git/$(MAINFOLDER)/include
TDIR = ~/git/$(MAINFOLDER)/test

GD = gcc -ansi -pedantic-errors -Wall -Wextra -g -I $(IDIR) -I $(DSDIR)
DGNL = gcc -ansi -pedantic-errors -Wall -Wextra -g -c -I $(IDIR) -I $(DSDIR)

GR = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I $(IDIR) -I $(DSDIR)
RGNL = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -c -I $(IDIR) -I $(DSDIR)

tester =_$(t)

TEST = $(subject)_test$(tester)
CFILE = $(subject)

TEST_C = $(TEST).c
CFILE_C = $(CFILE).c

status = $(g)

ifeq ($(status),D)
G: G_test_o G_cfile_o 
	$(GD) *.o 
	rm *.o
	./a.out	
else 
R: R_test_o R_cfile_o 
	$(GR) *.o 
	rm *.o
	./a.out
endif
		
G_test_o: $(TDIR)/$(TEST_C)
	$(DGNL) $(TDIR)/$(TEST_C)
		
G_cfile_o: $(CFILE_C)
	$(DGNL) $(CFILE_C)
	

R_test_o: $(TDIR)/$(TEST_C)
	$(RGNL) $(TDIR)/$(TEST_C)
		
R_cfile_o: $(CFILE_C)
	$(RGNL) $(CFILE_C)
	

clean: 
	rm *.o

run:
	./a.out
	
gdb:
	gdbtui a.out	

core:
	gdb a.out core	
	
