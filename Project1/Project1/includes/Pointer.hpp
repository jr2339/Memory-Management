//
//  Pointer.hpp
//  Project1
//
//  Created by jr2339 on 4/19/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#ifndef Pointer_hpp
#define Pointer_hpp

#include "Prefix_Trie.hpp"
#include <iostream>
#include <fstream>
#include <stdint.h> //including <cstdint> gives an error...?

#define NPAGECHARS 3
#define NOFFSETCHARS 2


//@TODO remove using namespace std?  It's typically considered bad practice
using namespace std;


#define NPAGECHARS 3
#define NOFFSETCHARS 2

struct pointer{
    unsigned char page[NPAGECHARS];
    unsigned char offset[NOFFSETCHARS];
};

class Page{
public:
    Page(uint64_t address, unsigned int max, size_t size);
    ~Page();
    bool is_full();
    uint64_t get_next_address();
  uint64_t getRootAddress();
    void *get_memory_of(unsigned int offset);
    void *get_reference_of(unsigned int offset);

private:
    void *memory;
    const size_t Node_size;
    const unsigned int max_count;
    unsigned int current_offset;
    const uint64_t root_address;
};



class MemoryAllocator{
public:
    MemoryAllocator(int Node_size);
    ~MemoryAllocator();
    uint64_t allocate();
    void* memory(uint64_t virtual_pointer);
    void* reference(uint64_t vortual_pointer);
  void smalloc(pointer *ptr);
  pointer smalloc();
  uint64_t charsToUint64(unsigned char chars, char numChars);
  void uint64ToChars(uint64_t intVal, char numChars, unsigned char *outArray);

private:
    const size_t Node_size;
    const unsigned int per_page_size;
    uint64_t next_page_address;
    vector<Page*>pages;

    Page* addPage();
    unsigned int get_total_page_size(unsigned int Node_size);
};



//store one header and one DNA sequence, we put each record to one Node and store it to the trie 
struct record{
    string header;
    string sequence;
};
#endif /* Pointer_hpp */
