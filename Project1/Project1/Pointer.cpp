//
//  Pointer.cpp
//  Project1
//
//  Created by jr2339 on 4/16/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include "Pointer.hpp"


Page::Page(int page_number){
    
    
    //Allocate the memory for our page
    int total = pow(256, page_number);
    memory = malloc(sizeof(char)*total);
}


Page::~Page(){
    free(memory);
}



