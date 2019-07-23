CC=gcc
INCDIRS=-I../interface -I../math -I../system
CFLAGS=-g -std=c11 -Wall $(INCDIRS)

libdata.a: data.o
	ar rcs $@ $^

clean:
	rm -f *.o *.a

