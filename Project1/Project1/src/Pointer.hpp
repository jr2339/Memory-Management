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
#include <stdint.h> //including <cstdint> gives an error...?

using namespace std;


class Page{
public:
    Page(uint64_t address, unsigned int max, unsigned int size);
    ~Page();
    
    bool is_full();
    uint64_t get_next_address();
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
    void* reference(uint64_t vortual_pointer);
    
private:
    const size_t Node_size;
    const unsigned int per_page_size;
    uint64_t next_page_address;
    vector<Page*>pages;
    
    Page* addPage();
    unsigned int get_page_size(unsigned int Node_size);
};





#endif /* Pointer_hpp */
