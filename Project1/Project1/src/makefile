CC=g++
CFLAGS=-Wall
LDIR=../lib/
IDIR=../includes/
BDIR=../bin/

all: pointer pt_custom

debug: pointer_d pt_custom_d

pointer: pointer.cpp
	$(CC) -c -o$(LDIR)$@.o $^ $(CFLAGS) -I$(IDIR)

pt_custom: Prefix_Trie_custom.cpp $(LDIR)pointer.o
	$(CC) -o$(BDIR)$@.exe $^ $(CFLAGS) -I$(IDIR)
pointer_d: pointer.cpp
	$(CC) -c -o$(LDIR)$@.o $^ $(CFLAGS) -I$(IDIR) -g

pt_custom_d: Prefix_Trie_custom.cpp $(LDIR)pointer.o
	$(CC) -o$(BDIR)$@.exe $^ $(CFLAGS) -I$(IDIR) -g
