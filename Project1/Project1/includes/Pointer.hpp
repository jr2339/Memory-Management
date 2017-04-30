//
//  Pointer.hpp
//  Project1
//
//  Created by jr2339 on 4/19/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#ifndef Pointer_hpp
#define Pointer_hpp

#include <iostream>
#include <fstream>
#include <stdint.h> //including <cstdint> gives an error...?
#include <vector>
#include <cstring>
#include <cstdlib>

#define NPAGECHARS 3
#define NOFFSETCHARS 2


//@TODO remove using namespace std?  It's typically considered bad practice
using namespace std;


#define NPAGECHARS 3
#define NOFFSETCHARS 2

/***************************************************************************//**
*                                     pointer{}
*  @brief Miniature pointer struct.
*
*  Comprises page and offset character arrays to minimize the information needed
*  to access an object within a page.
*******************************************************************************/
struct pointer{
  unsigned char page[NPAGECHARS];
  unsigned char offset[NOFFSETCHARS];
};

/***************************************************************************//**
*                                      Page
*  @brief A preallocated chunck of memory.
*
*  Intended to loosely mimic the memory scheme of the operating system. Sets
*    aside a chunk of memory, then allocates pieces within that chunk whenever
*    we need it.  Templated to allow for objects of any type, but all objects
*    within a page must be the same type.
*******************************************************************************/

template<typename T> class Page{
public:
  Page(uint64_t, unsigned int);
  ~Page();
  bool is_full();
  uint64_t get_next_address();
  uint64_t getRootAddress();
  T* get_memory_of(unsigned int);
  void set(uint64_t, T);
  void *get_reference_of(unsigned int);

private:
  T *memory;
  const unsigned int max_count;
  unsigned int current_offset;
  const uint64_t root_address;
};


/***************************************************************************//**
*                                   MemoryAllocator
*  @brief A custom memory layer.  Essentially a vector of equally sized pages.
*
*  Intended to loosely mimic the memory scheme of the operating system. Sets
*    aside a chunk of memory, then allocates pieces within that chunk whenever
*    we need it.  Templated to allow for objects of any type, but all objects
*    within the memory layer must be the same type.
*******************************************************************************/
template<typename T> class MemoryAllocator{
public:
  MemoryAllocator();
  ~MemoryAllocator();
  uint64_t allocate();
  void* memory(uint64_t);
  void* reference(uint64_t);
  void smalloc(pointer &);
  pointer smalloc();
  std::vector<Page<T>*> getPages();

private:
  uint64_t next_page_address;
  std::vector<Page<T>*>pages;
  Page<T>* addPage();
  unsigned int get_total_page_size(unsigned int Node_size);
};

uint64_t charsToUint64(unsigned char *, char);
void uint64ToChars(uint64_t, char, unsigned char *);
bool isNull(pointer ptr);


//store one header and one DNA sequence, we put each record to one Node and store it to the trie 
struct record{
  string header;
  string sequence;
};
#endif /* Pointer_hpp */
