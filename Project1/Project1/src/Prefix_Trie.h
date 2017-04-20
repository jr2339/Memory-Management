//
//  Prefix_Trie.hpp
//  Project1
//
//  Created by jr2339 on 4/18/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#ifndef Prefix_Trie_h
#define Prefix_Trie_h

#include <stdio.h>



//@@TODO change Node* to our pointer types
typedef struct Node
{
    Node* A;
    Node* C;
    Node* G;
    Node* T;
    Node* N;
    bool terminal;
}Node;

#endif /* Prefix_Trie_hpp */