CC=g++
CFLAGS=-Wall -Wno-unknown-pragmas
LDIR=../lib/
IDIR=../includes/
BDIR=../bin/

all: pointer

pointer: pointer.cpp
	$(CC) -O $(LDIR) $^ $(CFLAGS) -I$(IDIR) $(LFLAGS)
