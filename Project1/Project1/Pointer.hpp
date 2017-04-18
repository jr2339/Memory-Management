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
#include "Prefix_Trie.hpp"


typedef struct Index
{
    char page_index;
    char offset;
}Index;


//We still need to discuss the structure of the Page
typedef struct Page{
    Node* DNA_Sequence;
    
}Page;


#endif /* Pointer_hpp */
