subject=stack

IDIR = ~/git/ds/include
TDIR = ~/git/quizzes/parentheses

GD = gcc -ansi -pedantic-errors -Wall -Wextra -g -I $(IDIR)
DGNL = gcc -ansi -pedantic-errors -Wall -Wextra -g -c -I $(IDIR)

GR = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I $(IDIR)
RGNL = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -c -I $(IDIR)

tester =_$(t)

TEST =parentheses
CFILE = $(subject)

TEST2 = $(TEST).c
CFILE2 = $(CFILE).c


G: test_o cfile_o 
	$(GD) *.o 
	rm *.o
	./a.out	
		
test_o: $(TDIR)/$(TEST2)
	$(DGNL) $(TDIR)/$(TEST2)
		
cfile_o: $(CFILE2)
	$(DGNL) $(CFILE2)

clean: 
	rm *.o

run:
	./a.out
