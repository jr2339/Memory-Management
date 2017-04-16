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
#include <cmath>

//tring to allocate memory by using C language, it looks lije to difficult
//So, I am tring to use C++ to solve it
class Page{
public:
    Page(int page_number);
    ~Page();
    
    
private:
   void* memory;
    unsigned int max_count;
    unsigned int current_poistion;
    
};
#endif /* Pointer_hpp */
