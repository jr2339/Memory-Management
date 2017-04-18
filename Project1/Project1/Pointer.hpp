//
//  Pointer.hpp
//  Project1
//
//  Created by jr2339 on 4/16/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#ifndef Pointer_hpp
#define Pointer_hpp

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <iostream>
//tring to allocate memory by using C language, it looks lije to difficult
//So, I am tring to use C++ to solve it
class Page{
public:
    Page(unsigned int size,unsigned int max,uint64_t addr);
    ~Page();
    
    bool is_full();
    uint64_t get_next_address();
    
    
private:
    void* memory;
    unsigned int struct_size;
    unsigned int max_count;
    unsigned int current_poistion;
    uint64_t root_pointer_address; // unit64_t means this variable at here is 8 bytes
    
};


class MemoryAllocator{
public:
    MemoryAllocator(int size);
    ~MemoryAllocator();
    
    uint64_t allocate();
    void* reference(uint64_t virtual_pointer);
    
private:
    unsigned int struct_size;
    unsigned int per_page_size;
    uint64_t next_page_address;
    
    std::vector<Page*> pages;
    
    Page* addPage();
    unsigned int get_page_size(unsigned int struct_size);
   
};



#endif /* Pointer_hpp */
