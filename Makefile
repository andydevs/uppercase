CC=gcc
CFLAGS=-g -std=c11 -Wall

.PHONY: clean install uninstall run

uppercase: uppercase.o data.o datum.o error.o io.o math.o stack.o statemachine.o system.o vartable.o

clean:
	rm -f uppercase *.o

install: uppercase
	cp uppercase /usr/bin 

uninstall:
	rm /usr/bin/uppercase

run: uppercase
	./uppercase testfile.u

