# --------------------- PROJECT ----------------------

PROJECT = uppercase

# -------------------- DIRECTORIES -------------------

LIBDIR = lib
SRCDIR = src
OBJDIR = obj
BINDIR = bin
INSDIR = /usr/bin

# ----------------------- TEST -----------------------

# Program arguments
TESTARGS = testfile.u

# ---------------------- CONFIG ----------------------

# Shell command
SHELL = /bin/bash -O globstar

# Compiler
CC = gcc

# Flags
FLAGS = -std=c11 -Wall

# ---------------------- MAKEFILE --------------------

# File
TARGET = $(PROJECT)

# Directories
INCLUDS = $(shell ls *.h)
SOURCES = $(shell ls *.c)
OBJECTS = $(patsubst %.c,%.o, $(SOURCES))

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(FLAGS) 

%.o: %.c
	$(CC) -c -o $@ $^ $(FLAGS)

clean:
	rm -f -r $(TARGET) $(OBJECTS) 
	rm -f $(TARGET).exe.stackdump

install: $(BINARY)
	cp $(TARGET) $(INSDIR)

uninstall:
	rm $(INSDIR)/$(TARGET)

run: $(TARGET)
	./$(TARGET) $(TESTARGS)
