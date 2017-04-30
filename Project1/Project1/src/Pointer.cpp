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
 Page has these attributes:
 1.root_address: assign with any number, at here, we assign it to 1 as the 1st page address
 2.max_count: variable be used to check our page is full or not
 3.current_offet: index to node we are current visiting
 4.Memory: Total memory for each page is the sum of all Nodes
 ************************************************************************/

Page::Page(uint64_t address, unsigned int max, unsigned int size):
  //uses an initializer list to set const class member variables
    Node_size(size), max_count(max),root_address(address){
    current_offset = 0;
    memory = malloc(Node_size * max_count); //Space for Each Page
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
 -If the page is not full, we use current_offset to find the offset within the
    page.
 ******************************************************************************/

uint64_t Page::get_next_address(){
    if (is_full()) {
        cout << "This Page is full" <<endl;
        return 0;
    }
    return current_offset++;
}


/*******************************************************************************
                                getRootAddress()
   - Getter for root_address (page index)
 ******************************************************************************/
uint64_t Page::getRootAddress(){
  return root_address;
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

MemoryAllocator::MemoryAllocator(int size):
  // use an initializer list to set const class member variables
  Node_size(size),per_page_size(NOFFSETCHARS * Node_size){
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
addPage()
Used for page is not enough
 ******************************************************************************/
Page* MemoryAllocator::addPage(){
    uint64_t root_address = next_page_address++;
    Page* p = new Page(root_address,per_page_size,Node_size);
    pages.push_back(p);
    return p;
}

/*******************************************************************************
                             smalloc()
    - Small memory allocate
    - Creates a new pointer object and fills it with information regarding the
        memory location to which it points.
*******************************************************************************/
pointer MemoryAllocator::smalloc(){
  struct pointer ptr;
  Page *p = pages.back();
  if (p->is_full()) {
    p = addPage();
  }
  uint64ToChars(pages.back()->getRootAddress(), (char)NPAGECHARS, (unsigned char*)(&(ptr.page)));
  uint64ToChars(p->get_next_address(), (char)NOFFSETCHARS, (unsigned char*)(&(ptr.offset)));
  return ptr;
}

/*******************************************************************************
                             smalloc()
    -small memory allocate
    -Uses a preallocated pointer.  Fills the pointer with information regarding
       the memory location to which it points.
*******************************************************************************/
void MemoryAllocator::smalloc(pointer *ptr){
  Page *p = pages.back();
  if (p->is_full()) {
    p = addPage();
  }
  uint64ToChars(pages.back()->getRootAddress(), (char)NPAGECHARS, (unsigned char*)(&(ptr->page)));
  uint64ToChars(p->get_next_address(), (char)NOFFSETCHARS, (unsigned char*)(&(ptr->offset)));
}

/*******************************************************************************
                             charsToUint64()
    -converts char array to uint64_t
*******************************************************************************/
uint64_t charsToUint64(unsigned char *chars, char numChars){
  uint64_t uintVal = 0;
  for(int i = 0; i < numChars; i++){
    uintVal = uintVal | (chars[i] << ((numChars-(i+1))*8));
  }
  return uintVal;
}


/*******************************************************************************
                             uint64ToChars()
    - Converts uint64 to an array of characters.
    - Outputs directly into outArray.
*******************************************************************************/
void MemoryAllocator::uint64ToChars(uint64_t intVal, char numChars, unsigned char *outArray){
  // Cast int to char * so that we can iterate over bytes
  unsigned char *newVal = (unsigned char*) &intVal;
  // We have to copy in reverse order on little endian machines, not sure how
  //   this will be affected on big-endian.  May be problemeatic.
  for (int i = 0; i < numChars; i++){
    memset((&outArray[i]), newVal[numChars - (i+1)],1);
  }
}

/******************************************************************************
 ******************************************************************************
 ******************************************************************************
 ******************************************************************************
 ******************************************************************************
 ******************************************************************************/

record get_record(ifstream ifs){
    string new_header;
    string new_sequence;
    getline(ifs, new_header);
    getline(ifs, new_sequence);

    record new_record = {new_header,new_sequence};

    return new_record;
}
