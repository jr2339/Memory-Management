//
//  Pointer.cpp
//  Project1
//
//  Created by jr2339 on 4/19/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include "Pointer.hpp"


Page::Page(uint64_t address, unsigned int max, unsigned int size){
    root_address = address;
    max_count = max;
    Node_size = size;
    current_offset = 0;
    memory = malloc(Node_size * max_count);
}


Page::~Page(){
    free(memory);
}


bool Page::is_full(){
    if (current_offset != max_count) {
        return false;
    }
    return true;
}



uint64_t Page::get_next_address(){
    if (is_full()) {
        return 0;
    }
    return root_address + current_offset++;
}

void *Page::get_reference_of(unsigned int offset) {
    memory = static_cast<char *>(memory) + (offset * Node_size);
    return memory;
}


MemoryAllocator::MemoryAllocator(int size){
    Node_size = (unsigned int)size;
    per_page_size = get_page_size(Node_size)/Node_size;
    cout << "Node Size " << Node_size << endl;
    cout << "Per-Page Size " << per_page_size << endl;
    next_page_address = 1;
    addPage();
    
}

MemoryAllocator::~MemoryAllocator(){
    for (uint64_t i = pages.size()-1 ; i>-1; i--) {
        delete(pages[i]);
    }
    pages.clear();
}

uint64_t MemoryAllocator::allocate(){
    Page *p = pages.back();
    if (p->is_full()) {
        p = addPage();
    }
    return p->get_next_address();
}


void* MemoryAllocator::reference(uint64_t virtual_pointer){
    if (!virtual_pointer) {
        return NULL;
    }
    uint64_t page_id = ((uint64_t)(virtual_pointer-(uint64_t)next_page_address))/per_page_size;
    unsigned int struct_id = virtual_pointer % per_page_size;
    try {
        return pages.at(page_id)->get_reference_of(struct_id);
    } catch (...) {
        cout << virtual_pointer << endl;
        cout << page_id << endl;
        cout << struct_id << endl;
        throw "Reference died";
    }
}

Page* MemoryAllocator::addPage(){
    uint64_t root_address = next_page_address;
    next_page_address = next_page_address + per_page_size;
    Page* p = new Page(root_address,per_page_size,Node_size);
    pages.push_back(p);
    return p;
    
}




























