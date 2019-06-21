TARGET=uppercase
INCLUDS=$(shell ls *.h)
SOURCES=$(shell ls *.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
FLAGS=-g -std=c11 -Wall

uppercase: $(OBJECTS)
	gcc $^ -o $@ $(FLAGS) 

%.o: %.c
	gcc -c -o $@ $^ $(FLAGS)

clean:
	rm -f uppercase *.o

install: uppercase
	cp uppercase /usr/bin 

uninstall:
	rm /usr/bin/uppercase

run: uppercase
	./uppercase testfile.u
