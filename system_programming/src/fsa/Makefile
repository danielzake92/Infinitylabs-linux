subject=fsa

DSDIR = ~/git/ds/include
IDIR = ~/git/system_programming/include
TDIR = ~/git/system_programming/test

GD = gcc -ansi -pedantic-errors -Wall -Wextra -g -I $(IDIR) -I $(DSDIR)
DGNL = gcc -ansi -pedantic-errors -Wall -Wextra -g -c -I $(IDIR) -I $(DSDIR)

GR = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I $(IDIR) -I $(DSDIR)
RGNL = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -c -I $(IDIR) -I $(DSDIR) 

tester = $(t)

TEST = $(subject)_test_$(tester)
CFILE_1 = $(subject)

TEST_C = $(TEST).c
CFILE_C1 = $(CFILE_1).c

G: test_o cfile1_o 
	$(GD) *.o 
	rm *.o
	./a.out
		
test_o: $(TDIR)/$(TEST_C)
	$(DGNL) $(TDIR)/$(TEST_C)
		
cfile1_o: $(CFILE_C1)
	$(DGNL) $(CFILE_C1)

clean: 
	rm *.o

run:
	./a.out
