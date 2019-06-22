FLAGS=-g -std=c11 -Wall

uppercase: uppercase.o data.o datum.o error.o io.o math.o stack.o state_machine.o system.o vartable.o
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

