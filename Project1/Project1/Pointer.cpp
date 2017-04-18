//
//  Pointer.cpp
//  Project1
//
//  Created by jr2339 on 4/16/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include "Pointer.hpp"
using namespace std;

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

uint64_t Page::get_next_address(){
    if (is_full()) {
        cout <<" The Page is Full\n"<<endl;
        return 0;
    }
    else{
        return root_pointer_address + current_poistion++;
    }
}

//==============================================MemoryAllocator========================================//
MemoryAllocator::MemoryAllocator(int size){
    struct_size = (unsigned int) size;
    per_page_size = get_page_size(struct_size)/struct_size;
    cout <<"Struct Size" << struct_size <<endl;
    cout<<"Per-Page is " <<per_page_size<<endl;
    next_page_address =1;
    addPage();
}


//tring to free the Memory
MemoryAllocator::~MemoryAllocator(){
    //destroys the list by removing all elements
    //from the list and sets size of list to zero.
    pages.clear();
}


uint64_t MemoryAllocator::allocate() {
    Page *p = pages.back();
    if (p->is_full()) {
        p = addPage();
    }
    return p->get_next_address();
}

Page* MemoryAllocator::addPage(){
    uint64_t root_pointer_address = next_page_address;
    next_page_address = next_page_address + per_page_size;
    Page* p = new Page(struct_size,per_page_size,root_pointer_address);
    pages.push_back(p);
    return p;
}




























