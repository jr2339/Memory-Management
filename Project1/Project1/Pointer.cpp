//
//  Pointer.cpp
//  Project1
//
//  Created by jr2339 on 4/16/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include "Pointer.hpp"
#include <iostream>

Page::Page(unsigned int size,unsigned int max,uint64_t addr){
    
    root_pointer_address = addr;
    current_poistion = 0;
    max_count = max;
    struct_size = size;
    memory = malloc(struct_size*max_count);// still has some questions at here
    //Allocate the memory for our page
    //int total = pow(256, page_number);
    //memory = malloc(sizeof(char)*total);
}


Page::~Page(){
    free(memory);
}


//To check our current page is full or not
//If it is, we need to add one more page if we still need more space
bool Page::is_full(){
    if (current_poistion == max_count) {
        return true;
    }
    else{
        return false;
    }
}

//return the pointer address

uint64_t Page::get_next_pointer_address(){
    if (is_full()) {
        std::cout <<" The Page is Full\n"<<std::endl;
        return 0;
    }
    else{
        return root_pointer_address + current_poistion++;
    }
}

//==============================================MemoryAllocator========================================//
MemoryAllocator::MemoryAllocator(int size){
    
}

































