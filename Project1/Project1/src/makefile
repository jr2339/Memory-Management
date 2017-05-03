CC=g++
CFLAGS=-Wall -Wno-format
LDIR=../lib/
IDIR=../includes/
BDIR=../bin/


all: create page mem_layer pt_custom pt_os 

debug: pointer_d pt_custom_d

create:
	mkdir -p $(BDIR)
	mkdir -p $(LDIR)

page: Page.cpp
	$(CC) -c -o$(LDIR)$@.o $^ $(CFLAGS) -I$(IDIR)

mem_layer: MemoryAllocator.cpp
	$(CC) -c -o$(LDIR)$@.o $^ $(CFLAGS) -I$(IDIR)

pt_custom: Prefix_Trie_custom.cpp $(LDIR)page.o $(LDIR)mem_layer.o
	$(CC) -o$(BDIR)$@.exe $^ $(CFLAGS) -I$(IDIR)

pt_os: Prefix_Trie_os.cpp 
	$(CC) -o$(BDIR)$@.exe $^ $(CFLAGS) -I$(IDIR)

pointer_d: Pointer.cpp
	$(CC) -c -o$(LDIR)$@.o $^ $(CFLAGS) -I$(IDIR) -ggdb

pt_custom_d: Prefix_Trie_custom.cpp $(LDIR)pointer.o
	$(CC) -o$(BDIR)$@.exe $^ $(CFLAGS) -I$(IDIR) -ggdb
