CC=gcc
CFLAGS=-I. -Wall -finput-charset=UTF-8 -fexec-charset=UTF-8 -pedantic 
LIBS=-lm

all: main clean 

main: main.o commands time classes
	$(CC) -o airport_simulator.exe main.o commands.o time.o classes.o $(CFLAGS) $(LIBS)

commands:
	$(CC) -o commands.o -c source/commands.c $(CFLAGS) $(LIBS)

time:
	$(CC) -o time.o -c source/c_time.c $(CFLAGS) $(LIBS)

classes:
	$(CC) -o classes.o -c source/classes.c $(CFLAGS) $(LIBS)

clean:
	rm -f *.o

exec:
	./airport_simulator.exe

.PHONY: clean