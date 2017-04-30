CC=g++
CFLAGS=-Wall -Wno-unknown-pragmas
LDIR=../lib/
IDIR=../includes/
BDIR=../bin/
LFLAGS=-L$(LDIR) -lgdal-20

all: pointer

pointer: pointer.cpp
	$(CC) -o $(BDIR)$@.exe $^ $(CFLAGS) -I$(IDIR) $(LFLAGS)

