//
//  main.cpp
//  Project1
//
//  Created by jr2339 on 4/19/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#include <iostream>
#include "Pointer.hpp"
#include "Prefix_Trie.hpp"



int main(int argc, const char * argv[]) {
    
    
    if(argc < 3){
        perror("We need 3 arguments");
        exit(1);//if the nunber is not 0, not access to error
    }
    else if(argc > 3){
        perror("Too many arguments");
        exit(1);//if the nunber is not 0, not access to error
    }
    
     //input stream for file handle
    ifstream ifs;
    // opening input FASTA file
    ifs.open (argv[1], ifstream::in);
    
    MemoryAllocator *memory;
    memory = new MemoryAllocator(sizeof(pointer));
    Trie* prefix = new Trie();
    
    //record to add in to the Node
    record new_reord;
    char c;
    
    while (ifs.get(c)) {
        string header;
        string sequence;
        getline(ifs, header);
        getline(ifs, sequence);
        
        record new_record = {header,sequence};
        //need to figure out how to add DNA Sequence to our Trie
        //prefix->addWord(new_reord.sequence, sizeof(sequence));
        
    }
    
    return 0;
}
