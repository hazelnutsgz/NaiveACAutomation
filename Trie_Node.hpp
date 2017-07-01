//
//  Trie_Node.hpp
//  Trie
//
//  Created by 佘国榛 on 2017/6/30.
//  Copyright © 2017年 佘国榛. All rights reserved.
//

#ifndef Trie_Node_hpp
#define Trie_Node_hpp

#include <iostream>
class trie_node{
public:
    char key;   //the value of node, such as 'a', 'b', 'c'........
    trie_node* child[26];
    bool exists;
    std::string word;
    trie_node* parent;
    trie_node* fail;
    trie_node();
    ~trie_node();
};
#endif /* Trie_Node_hpp */
