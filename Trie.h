//
//  Trie.hpp
//  Trie
//
//  Created by 佘国榛 on 2017/6/30.
//  Copyright © 2017年 佘国榛. All rights reserved.
//

#ifndef Trie_hpp
#define Trie_hpp

#include <iostream>
#include "TrieNode.h"
class Trie{
private:
    std::string helper;
    TrieNode* root;
    bool finished_init;
private:
    void DeconstructRec(TrieNode* root);
    bool DeleteWordRec(std::string& word, TrieNode* root, int index);
    int InitializeFailPointer();
    int InitializeNode();
    void InsertWord(std::string& word);
    bool DeleteFailPointerRec(TrieNode* root);
    bool ReconstructFailPointer();
    void AcMatchFile(std::string& str);
public:
    Trie();
    bool FindWord(std::string& word);
    bool DeleteWord(std::string& word);
    int NaiveMatchString(std::string& str);
    int AcMatchString(std::string& str);
    void Interact();
    ~Trie();

};
#endif /* Trie_hpp */
