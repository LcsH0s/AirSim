CC=gcc
CFLAGS=-I. -Wall -finput-charset=UTF-8 -fexec-charset=UTF-8 -pedantic 
LIBS=-lm -lncurses -lpthread

all: main clean exec

main: main.o commands time
	$(CC) -o exe main.o commands.o time.o $(CFLAGS) $(LIBS)

commands:
	$(CC) -o commands.o -c source/commands.c $(CFLAGS) $(LIBS)

time:
	$(CC) -o time.o -c source/c_time.c $(CFLAGS) $(LIBS)

clean:
	rm -f *.o

exec:
	./exe

.PHONY: clean