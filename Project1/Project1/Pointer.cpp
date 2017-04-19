//
//  Pointer.cpp
//  Project1
//
//  Created by jr2339 on 4/16/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include "Pointer.hpp"

int count_pages(const char* filename){
    int total_pages =0;
    int size =0;
    int row =0;
    FILE *fp = fopen(filename, "r");
    
    if (!fp) {
        fprintf(stderr, "can't open file for reading\n");
    }
    
    while (1) {
        int ch = getc(fp);
        while (ch == '>') {
            do{
                ch = getc(fp);
            }
            while (ch!='\n');
            ch = getc(fp);
        }
        if (feof(fp)) {
            break;
        }
        size++;
        if (ch =='\n') {
            row++;
        }
        
    }
    total_pages = row/1024; // this means each page has 1024 row
    
    return total_pages;
}



Page** page_Pointer(int size, const char* filename){
    
    int total_pages = count_pages(filename);
    
    Page** pages = (Page**)malloc(total_pages*sizeof(Page*));
    
    
    
    
    
    
    
    return pages;
    
}
























