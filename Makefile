TARGET = program

CC = gcc

COMPILE = $(CC) -c
LINK = $(CC)

CFLAGS = -Wall -std=c11
LFLAGS = -Wall
INCLUD = -Iinclude
LIBRAR = -Llib

SRCDIR = src
OBJDIR = obj
BINDIR = bin
INSDIR = /usr/bin

SOURCES = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/*.c) 
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
BINARY  = $(BINDIR)/$(TARGET)

TESTFILE = tmp/testfile.u

$(BINARY): $(OBJECTS)
	test -d $(@D) || mkdir $(@D)
	$(LINK) $? -o $@ $(LFLAGS) $(LIBRAR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	test -d $(@D) || mkdir $(@D)
	$(COMPILE) $< -o $@ $(CFLAGS) $(INCLUD)

clean:
	rm -r $(OBJDIR) $(BINDIR)

install:
	cp $(BINDIR)/$(TARGET) $(INSDIR)

uninstall:
	rm $(INSDIR)/$(TARGET)

test:
	$(BINARY) $(TESTFILE)