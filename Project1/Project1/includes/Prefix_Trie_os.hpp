//
//  Prefix_Trie.hpp
//  Project1
//
//  Created by jr2339 on 4/19/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#ifndef Prefix_Trie_os_hpp
#define Prefix_Trie_os_hpp

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Node{
public:
    Node();
    ~Node();
    Node *deepCopy();
    Node *getChild(char);
    Node *setChild(char, int*);
    bool isTerminal();
    void setTerminal(bool);
private:
    Node *A;
    Node *C;
    Node *G;
    Node *T;
    bool terminal;
};

class Trie{
public:
    Trie();
    Trie(char **, int, int);
    Trie(Trie*);
    ~Trie();
    void addWord(char *, int);
    bool searchWord(char *, int);
    std::vector<int> traverse(char *, int, int);
    int getSize();
private:
    Node *root;
    int size;
};

#endif /* Prefix_Trie_os_hpp */
