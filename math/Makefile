CC=gcc
INCDIRS=-I../uppercase -I../data -I../system
CFLAGS=-g -std=c11 -Wall $(INCDIRS)

libmath.a: math.o
	ar rcs $@ $^

clean:
	rm -f *.o *.a

