MAIN=mergesort

CC=gcc

CCFLAGS=-Wall

LIB=-pthread

SOURCES=$(wildcard *.c)

HEADERS=$(wildcard *.h)

OBJECTS=$(SOURCES: .c=.o)

PROGRAMDIR=.

all: $(MAIN)

$(MAIN): $(OBJECTS)
	$(CC) $(LIB) $(OBJECTS) -o $(PROGRAMDIR)/$(MAIN)

.c.o:
	$(CC) $(CCFLAGS) $(INCLUDES) $(LIBS) -c $< -o $@

clean:
	rm -f $(PROGRAMDIR)/$(MAIN)