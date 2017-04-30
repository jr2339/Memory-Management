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

template<typename T> Page<T>::Page(uint64_t address, unsigned int max):
  //uses an initializer list to set const class member variables
    max_count(max),root_address(address){
    current_offset = 0;
    memory = new T[max_count];
}
/*******************************************************************************
 ~Page()
 -Default deconstructor.  Deletes All Nodes in each page.
 ******************************************************************************/
template<typename T> Page<T> ::~Page(){
    free(memory);
}
/*******************************************************************************
 Page::is_full()
 -Using current_offsets and max_count to check page is filled with node or not
 ******************************************************************************/

template <typename T> bool Page<T>::is_full(){
  return current_offset >= max_count;
}


/*******************************************************************************
 Page::get_next_address()
 -If the page is not full, we use current_offset to find the offset within the
    page.
 ******************************************************************************/

template <typename T> uint64_t Page<T>::get_next_address(){
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
template <typename T> uint64_t Page<T>::getRootAddress(){
  return root_address;
}

/*******************************************************************************
 Page::get_memory_of(unsigned int offset)
 -We need to decide the node locate in which page
 and we can return how many memory we need
 ******************************************************************************/
template <typename T> T *Page<T>::get_memory_of(unsigned int offset) {
  return memory[offset];
}


/******************************************************************************
 ==============================================================================
 ------------------------------------------------------------------------------
                               MemoryAllocator
 ------------------------------------------------------------------------------
 ==============================================================================
 ******************************************************************************/

/***********************************************************************
After we figure out page construct, we will allocate memory
 ************************************************************************/

template <typename T> MemoryAllocator<T>::MemoryAllocator(int size){
    //init the 1st page address
    next_page_address = 1;
    addPage();
}
/*******************************************************************************
 ~MemoryAllocator()
 -Default deconstructor.  Deletes All Pages in allocated Memory.
 ******************************************************************************/
template <typename T> MemoryAllocator<T>::~MemoryAllocator(){
  while(uint64_t i = pages.size()){
    delete(pages[i]);
  }
  pages.clear();
}


/*******************************************************************************
addPage()
Used for page is not enough
 ******************************************************************************/
template <typename T> Page<T>* MemoryAllocator<T>::addPage(){
    uint64_t root_address = next_page_address++;
    Page<T>* p = new Page<T>(root_address);
    pages.push_back(p);
    return p;
}

/*******************************************************************************
                             smalloc()
    - Small memory allocate
    - Creates a new pointer object and fills it with information regarding the
        memory location to which it points.
*******************************************************************************/
template <typename T> pointer MemoryAllocator<T>::smalloc(){
  struct pointer ptr;
  Page<T> *p = pages.back();
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
template <typename T> void MemoryAllocator<T>::smalloc(pointer *ptr){
  Page<T> *p = pages.back();
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
template <typename T> uint64_t MemoryAllocator<T>::charsToUint64(unsigned char *chars, char numChars){
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
template <typename T> void MemoryAllocator<T>::uint64ToChars(uint64_t intVal, char numChars, unsigned char *outArray){
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
