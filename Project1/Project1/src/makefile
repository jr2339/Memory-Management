CC=g++
CFLAGS=-Wall -Wno-unknown-pragmas
LDIR=../lib/
IDIR=../includes/
BDIR=../bin/

all: pointer

pointer: pointer.cpp
	$(CC) -c -o$(LDIR)$@.o $^ $(CFLAGS) -I$(IDIR) $(LFLAGS)
