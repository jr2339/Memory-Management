//
//  Pointer.cpp
//  Project1
//
//  Created by jr2339 on 4/19/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include "../includes/Pointer.hpp"
#include "../includes/Prefix_Trie_custom.hpp"

/***************************************************************************//**
                                     Page()
* @param address The index of the page.
* @param max The total number of T typed objects that can be stored in the array.
*******************************************************************************/

template<typename T> Page<T>::Page(uint64_t address, unsigned int max):
  //uses an initializer list to set const class member variables
    max_count(max),root_address(address){
    current_offset = 0;
    memory = new T[max_count];
}


/***************************************************************************//**
*                                 Page::~Page()
* -Default deconstructor.  Deletes All Nodes in each page.
 ******************************************************************************/
template<typename T> Page<T> ::~Page(){
  //left blank
}


/***************************************************************************//**
 *                                 Page::is_full()
 *  -Determine whether or not the page is full.
 *  @return True if no unused space is available, false otherwise.
 ******************************************************************************/

template <typename T> bool Page<T>::is_full(){
  return current_offset >= max_count;
}


/***************************************************************************//**
*                               Page::get_next_address()
*  -Get the next available space in the page.
*  @return The next available space in the page.
 ******************************************************************************/

template <typename T> uint64_t Page<T>::get_next_address(){
    if (is_full()) {
        cout << "This Page is full" <<endl;
        return 0;
    }
    return current_offset++;
}


/***************************************************************************//**
*                             Page::getRootAddress()
*  -Getter for root_address (page index)
*  @return The address / index of the page.
******************************************************************************/
template <typename T> uint64_t Page<T>::getRootAddress(){
    return root_address;
}

/***************************************************************************//**
 *                                Page::get_memory_of()
 *  -Get the memory at a specific offset.
 *  @param offset The index of the item that we want to grab.
 *  @return The object at the specified index.
 ******************************************************************************/
template <typename T> T *Page<T>::get_memory_of(unsigned int offset) {
    return &memory[offset];
}

/***************************************************************************//**
*                                   Page::set()
*  -Sets memory at <offset> to <value>
*  @param offset The index that we want to set.
*  @param val The value that we want to place at the specified offset.
*******************************************************************************/

template <typename T> void Page<T>::set(uint64_t offset, T val) {
  this->memory[offset] = val;
}

template class Page<Node>;
