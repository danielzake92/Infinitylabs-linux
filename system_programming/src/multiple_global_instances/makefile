CFLAGS = -g
CC=gcc

all: static_main.out static_rdynamic_main.out dynamic_main.out
	echo done

f1.o: f1.c
	$(CC) $(CFLAGS) -c -fPIC f1.c -o f1.o

libf1.so: f1.c
	$(CC) $(CFLAGS) f1.o -shared -o libf1.so

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

#for thje explicit usage "dlopen() & dlsym() & dlclose()"
static_main.out: main.o f1.o
	$(CC) $(CFLAGS) main.o f1.o -ldl -o static_main.out

static_rdynamic_main.out: main.o f1.o
	$(CC) $(CFLAGS) main.o f1.o -ldl -o static_rdynamic_main.out -rdynamic

#for implicit usage here ldd includes libf1.so bacause "-lf1"
dynamic_main.out: main.o libf1.so
	$(CC) $(CFLAGS) -L. main.o -Wl,-rpath=. -lf1 -ldl -o dynamic_main.out







read1:
	readelf -a ./static_main.out
read2:
	readelf -a ./static_rdynamic_main.out
read3:
	readelf -a ./dynamic_main.out

run1:
	./static_main.out
run2:
	./static_rdynamic_main.out
run3:
	./dynamic_main.out

ldd1:
	ldd ./static_main.out
ldd2:
	ldd ./static_rdynamic_main.out
ldd3:
	ldd ./dynamic_main.out

deb1:
	gdb ./static_main.out
deb2:
	gdb ./static_rdynamic_main.out
deb3:
	gdb ./dynamic_main.out

clean:
	rm *.o *.out *.so
