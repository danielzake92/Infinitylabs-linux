IDIR1 = ../../include
IDIR2 = ../../../ds/include
LDIR = .
SLLFILE = ../../../ds/src/doubly_linked_list/doubly_linked_list.c
QFILE = ../../../ds/src/circular_buffer/circular_buffer.c

GD = gcc -ansi -pedantic-errors -Wall -Wextra -g -I $(IDIR1) -I $(IDIR2) -pthread
GR = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I $(IDIR1) -I $(IDIR2) -pthread 

  #If the first argument is "run"...
ifeq (run,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
RUN_ARG := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
$(eval $(RUN_ARG):;@:)
endif


prog: # ...


run: prog
	./*.out

debug:
	$(GD) $(LDIR)/ex1.c -o ex1.out 
	$(GD) $(LDIR)/ex2.c $(SLLFILE) -o ex2.out 
	$(GD) $(LDIR)/ex3.c $(SLLFILE) -o ex3.out 
	$(GD) $(LDIR)/ex4.c $(QFILE) -o ex4.out 
	$(GD) $(LDIR)/ex5.c $(QFILE) -o ex5.out 
	$(GD) $(LDIR)/ex6.c $(QFILE) -o ex6.out
	$(GD) $(LDIR)/ex7.c $(QFILE) -o ex7.out
	$(GD) $(LDIR)/ex8.c $(QFILE) -o ex8.out
release:
	$(GR) $(LDIR)/ex1.c -o ex1.out 
	$(GR) $(LDIR)/ex2.c $(SLLFILE) -o ex2.out 
	$(GR) $(LDIR)/ex3.c $(SLLFILE) -o ex3.out 
	$(GR) $(LDIR)/ex4.c $(QFILE) -o ex4.out 
	$(GR) $(LDIR)/ex5.c $(QFILE) -o ex5.out 
	$(GR) $(LDIR)/ex6.c $(QFILE) -o ex6.out 
	$(GR) $(LDIR)/ex7.c $(QFILE) -o ex7.out 
	$(GR) $(LDIR)/ex8.c $(QFILE) -o ex8.out 

clean: 
	rm *.out 
