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
#include "Trie_Node.hpp"
class trie{
private:
    trie_node* root;
    void deconstruct_rec(trie_node* root);
    bool delete_word_rec(char* str, trie_node* root);
    int initialize_fail_pointer();
    int initialize_node(std::istream& fin);
public:
    trie(std::istream& fin);
    bool find_word(char* str);
    void insert_word(std::string& str);
    bool delete_word(char* str);
    
    int naive_match_string(char* str);
    int ac_match_string(std::istream& fin);
    ~trie();
    
};
#endif /* Trie_hpp */
