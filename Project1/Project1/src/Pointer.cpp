//
//  Pointer.cpp
//  Project1
//
//  Created by jr2339 on 4/19/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include "Pointer.hpp"
/***********************************************************************
 uint64_t: Integer type with a width of exactly 64 bits which is 8 bytes.
 root_address: assign with any number, at here, we assign it to 1 as the 1st page address
 max_count: variable be used to check our page is full or not
 current_offet: index to node we are current visiting
 Memory: Total memory for each page is the sum of all Nodes
 ************************************************************************/

Page::Page(uint64_t address, unsigned int max, unsigned int size){
    root_address = address;
    max_count = max;
    Node_size = size;
    current_offset = 0;
    memory = malloc(Node_size * max_count);
}
/*******************************************************************************
 ~Page()
 -Default deconstructor.  Deletes All Nodes in each page.
 ******************************************************************************/

Page::~Page(){
    free(memory);
}
/*******************************************************************************
 Page::is_full()
 -Using current_offsets and max_count to check page is filled with node or not
 ******************************************************************************/

bool Page::is_full(){
    if (current_offset != max_count) {
        return false;
    }
    return true;
}
/*******************************************************************************
 Page::get_next_address()
 -If the page is not full, we using root_address 
 and offset to show the Node Address in the pase
 ******************************************************************************/

uint64_t Page::get_next_address(){
    if (is_full()) {
        return 0;
    }
    return root_address + current_offset++;
}
/*******************************************************************************
 Page::get_memory_of(unsigned int offset)
 -We need to decide the node locate in which page
 and we can return how many memory we need
 ******************************************************************************/
void *Page::get_memory_of(unsigned int offset) {
    memory = static_cast<char *>(memory) + (offset * Node_size);
    return memory;
}


/******************************************************************************
 ******************************************************************************
 ******************************************************************************
 ******************************************************************************
 ******************************************************************************
 ******************************************************************************/

/***********************************************************************
After we figure out page construct, we will allocate memory
 ************************************************************************/

MemoryAllocator::MemoryAllocator(int size){
    Node_size = (unsigned int)size;
    per_page_size = get_total_page_size(Node_size)/Node_size;
    //init the 1st page address
    next_page_address = 1;
    addPage();
}
/*******************************************************************************
 ~MemoryAllocator()
 -Default deconstructor.  Deletes All Pages in allocated Memory.
 ******************************************************************************/
MemoryAllocator::~MemoryAllocator(){
    for (uint64_t i = pages.size()-1 ; i>-1; i--) {
        delete(pages[i]);
    }
    pages.clear();
}
/*******************************************************************************
 allocator()
Allcoate enough memory to store our pages
 ******************************************************************************/

uint64_t MemoryAllocator::allocate(){
    Page *p = pages.back();
    if (p->is_full()) {
        p = addPage();
    }
    return p->get_next_address();
}

/*******************************************************************************
 memory()
 get memory
 ******************************************************************************/
void* MemoryAllocator::memory(uint64_t virtual_pointer){
    if (!virtual_pointer) {
        return NULL;
    }
    uint64_t page_id = ((uint64_t)(virtual_pointer-(uint64_t)next_page_address))/per_page_size;
    unsigned int struct_id = virtual_pointer % per_page_size;
    
    return pages.at(page_id)->get_memory_of(struct_id);
 
}
/*******************************************************************************
addPage()
Used for page is not enough
 ******************************************************************************/
Page* MemoryAllocator::addPage(){
    uint64_t root_address = next_page_address;
    next_page_address = next_page_address + per_page_size;
    Page* p = new Page(root_address,per_page_size,Node_size);
    pages.push_back(p);
    return p;
    
}

/*******************************************************************************
get_total_page_size(unsigned int Node_size)
How many memory do we need
 ******************************************************************************/
unsigned int MemoryAllocator::get_total_page_size(unsigned int Node_size){
    unsigned int pointer_size = sizeof(void*);
    Node_size *= 1024;
    
    //least common multiple
    unsigned int lcm = (Node_size > pointer_size) ? Node_size : pointer_size;
    do {
        if (lcm % Node_size == 0 && lcm % pointer_size ==0) {
            break;
        }
        else{
            ++lcm;
        }
    } while (true);
    
    return lcm;
}























