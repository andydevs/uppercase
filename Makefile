CC=gcc
CFLAGS=-g -std=c11 -Wall -Iprogram -Imodules

.PHONY: clean install uninstall run

uppercase: program/uppercase.o program/datum_stack.o program/char_stack.o program/statemachine.o program/vartable.o program/datum.o program/error.o program/program.o modules/math.o modules/system.o modules/data.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm -f uppercase **/*.o

install: uppercase
	cp uppercase /usr/bin 

uninstall:
	rm /usr/bin/uppercase

run: uppercase
	./uppercase testfile.u

