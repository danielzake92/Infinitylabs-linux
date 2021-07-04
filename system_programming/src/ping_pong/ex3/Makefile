
# Compilation details.
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g 
ADD_FLAG = -D_POSIX_C_SOURCE=199309L
LDFLAGS = -L$(LIBDIR) -Wl,-rpath=$(LIBDIR)

# Target name
PING=ping
PONG=pong



.PHONY: clean all run build kill



all: $(PONG).out $(PING).out



$(PONG).out : $(PONG).c 
	$(CC) $(CFLAGS) $(ADD_FLAG) $< -o $@ 

$(PING).out : $(PING).c 
	$(CC) $(CFLAGS) $(ADD_FLAG) $< -o $@ 	
	

ping:
	./ping.out 

clean:
	rm $(PING).out ; rm $(PONG).out ; 

kill:
	killall -9 $(PING).out; killall -9 $(PONG).out; killall -9 make;		
