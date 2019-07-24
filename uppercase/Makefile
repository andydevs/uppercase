CC=gcc
CFLAGS=-g -std=c11 -Wall -I..
LDFLAGS=-L../math -L../data -L../system 
LDLIBS=-lmath -ldata -lsystem

uppercase: uppercase.o datum_stack.o char_stack.o statemachine.o vartable.o datum.o error.o program.o

clean:
	rm -f uppercase *.o

