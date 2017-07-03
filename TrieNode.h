//
//  TrieNode.hpp
//  Trie
//
//  Created by 佘国榛 on 2017/6/30.
//  Copyright © 2017年 佘国榛. All rights reserved.
//

#ifndef TrieNode_hpp
#define TrieNode_hpp

#include <iostream>
class TrieNode{
public:
    char key;   //the value of node, such as 'a', 'b', 'c'........
    TrieNode* child[26];
    bool exists;    //whether the node is the end of a word
    std::string word;   //if exists = true, word means the word it contain
    TrieNode* parent; //the father of the node
    TrieNode* fail;    //fail pointer, which is similar to KMP algorithm
    TrieNode();
    ~TrieNode();
};
#endif /* TrieNode_hpp */
