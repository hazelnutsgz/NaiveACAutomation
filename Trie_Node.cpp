//
//  Trie_Node.cpp
//  Trie
//
//  Created by 佘国榛 on 2017/6/30.
//  Copyright © 2017年 佘国榛. All rights reserved.
//

#include "Trie_Node.hpp"

trie_node::trie_node(){
    key = '\0';
    for(int i = 0; i < 26; i++){
        child[i] = NULL;
    }
    fail = NULL;
    parent = NULL;
    exists = false;
}

trie_node::~trie_node(){
}
