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
using namespace std;


#define NPAGECHARS 3
#define NOFFSETCHARS 2



class Page{
public:
    Page(uint64_t address, unsigned int max, unsigned int size);
    ~Page();
    
    bool is_full();
    uint64_t get_next_address();
    void *get_memory_of(unsigned int offset);
    
private:
    void *memory;
    unsigned int Node_size;
    unsigned int max_count;
    unsigned int current_offset;
    uint64_t root_address;
    
};



class MemoryAllocator{
public:
    MemoryAllocator(int Node_size);
    ~MemoryAllocator();
    
    uint64_t allocate();
    void* memory(uint64_t virtual_pointer);
    
private:
    unsigned int Node_size;
    unsigned int per_page_size;
    uint64_t next_page_address;
    vector<Page*>pages;
    
    Page* addPage();
    unsigned int get_total_page_size(unsigned int Node_size);
};



struct pointer{
    char page[NPAGECHARS];
    char offset[NOFFSETCHARS];
};

//store one header and one DNA sequence, we put each record to one Node and store it to the trie 
struct record{
    string header;
    string sequence;
};



#endif /* Pointer_hpp */
