//
//  Pointer.cpp
//  Project1
//
//  Created by jr2339 on 4/19/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include "../includes/Pointer.hpp"
#include "../includes/Prefix_Trie_custom.hpp"

/******************************************************************************
 ==============================================================================
 ------------------------------------------------------------------------------
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   MemoryAllocator   ~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ------------------------------------------------------------------------------
 ==============================================================================
 *****************************************************************************/

/**************************************************************************//**
*  Serves as an intermediate memory layer.
*
*  A vector of memory pages.  Templated to accept any type of object, but all
*  objects within a memory allocator must be of the same type.
******************************************************************************/
template <typename T> MemoryAllocator<T>::MemoryAllocator(){
    // The final page / offset combination is reserved for "NULL" pointers -
    //   pointers that have been instantiated but not initialized.
    next_page_address = 0;
    addPage();
}

/***************************************************************************//**
 *                        MemoryAllocator::~MemoryAllocator()
 *  -Default deconstructor.  Deletes All Pages in allocated Memory.
 ******************************************************************************/
template <typename T> MemoryAllocator<T>::~MemoryAllocator(){
  while(uint64_t i = pages.size()){
    delete(pages[i]);
  }
  pages.clear();
}


/***************************************************************************//**
 *                             MemoryAllocator::addPage()
 *  Used to add an additional page in the event that all previous pages are full
 *  @return The newly created page.
 ******************************************************************************/
template <typename T> Page<T>* MemoryAllocator<T>::addPage(){
    uint64_t root_address = next_page_address++;
    Page<T>* p = new Page<T>(root_address, (1 << (NOFFSETCHARS*8)));
    pages.push_back(p);
    return p;
}

/***************************************************************************//**
 *                              MemoryAllocator::smalloc()
 *  Small memory allocate
 *
 *  Creates a new pointer object and fills it with information regarding the
 *     memory location to which it points.
*******************************************************************************/
template <typename T> pointer MemoryAllocator<T>::smalloc(){
  struct pointer ptr = {.page={255,255,255}, .offset = {255,255}};
  Page<T> *p = pages.back();
  if (p->is_full()) {
    p = addPage();
  }
  uint64ToChars(pages.back()->getRootAddress(), (char)NPAGECHARS, (unsigned char*)(&(ptr.page)));
  uint64ToChars(p->get_next_address(), (char)NOFFSETCHARS, (unsigned char*)(&(ptr.offset)));
  return ptr;
}


/***************************************************************************//**
 *                              MemoryAllocator::smalloc()
 *  Small memory allocate
 *
 *  @param ptr The address of the pointer that we wish to smalloc.
 *  Creates a new pointer object and fills it with information regarding the
 *     memory location to which it points.
*******************************************************************************/
template <typename T> void MemoryAllocator<T>::smalloc(pointer &ptr){
  Page<T> *p = pages.back();
  if (p->is_full()) {
    p = addPage();
  }
  uint64ToChars(pages.back()->getRootAddress(), (char)NPAGECHARS, (unsigned char*)(&(ptr.page)));
  uint64ToChars(p->get_next_address(), (char)NOFFSETCHARS, (unsigned char*)(&(ptr.offset)));
}

template <typename T> std::vector<Page<T>*> MemoryAllocator<T>::getPages(){
  return pages;
}

/*
record get_record(ifstream ifs){
    string new_header;
    string new_sequence;
    getline(ifs, new_header);
    getline(ifs, new_sequence);

    record new_record = {new_header,new_sequence};

    return new_record;
}
*/


/***************************************************************************//**
 *                                 charsToUint64()
 *  -Converts char array to uint64_t
 *  @param chars The array of characters that we wish to convert to uint64_t
 *  @param numChars The number of characters.
 *  @return the uint64_t conversion of the characters that were passed in.
*******************************************************************************/
uint64_t charsToUint64(unsigned char *chars, char numChars){
  uint64_t uintVal = 0;
  for(int i = 0; i < numChars; i++){
    uintVal = uintVal | (chars[i] << ((numChars-(i+1))*8));
  }
  return uintVal;
}


/**************************************************************************//**
 *                                 uint64ToChars()
 *  - Converts uint64 to an array of characters.
 *  - Outputs directly into outArray.
 *  @param intVal The uint64_t value that we want to split into an array of chars.
 *  @param numChars The number of characters necessary to hold the new value.
 *  @param[out] outArray The character array to which we send the newly created
 *     value.
*******************************************************************************/
void uint64ToChars(uint64_t intVal, char numChars, unsigned char *outArray){
  // Cast int to char * so that we can iterate over bytes
  unsigned char *newVal = (unsigned char*) &intVal;
  // We have to copy in reverse order on little endian machines, not sure how
  //   this will be affected on big-endian.  May be problemeatic.
  for (int i = 0; i < numChars; i++){
    memset(&outArray[i], newVal[numChars - (i+1)],1);
  }
}


/***************************************************************************//**
 *                             isNull()
 *   - Checks whether or not a pointer is null
 *  @param ptr The pointer that we want to check for null.
 *  @return True if the pointer is null, false otherwise.
 *
 *  A pointer is considered null if both page and offset are at their max value.
*******************************************************************************/
bool isNull(pointer ptr){
  return (charsToUint64(ptr.page, NPAGECHARS) == ((1 << (NPAGECHARS*8))-1) &&
	  (charsToUint64(ptr.offset, NOFFSETCHARS) == (((1 << (NOFFSETCHARS*8))-1))));
}



template class MemoryAllocator<Node>;
