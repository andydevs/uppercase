CC=gcc
INCDIRS=-I../interface -I../data -I../math
CFLAGS=-g -std=c11 -Wall $(INCDIRS)

libsystem.a: system.o
	ar rcs $@ $^

clean:
	rm -f *.o *.a

