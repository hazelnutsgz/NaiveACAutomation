//
//  Trie.cpp
//  Trie
//
//  Created by 佘国榛 on 2017/6/30.
//  Copyright © 2017年 佘国榛. All rights reserved.
//

#include "Trie.hpp"
#include <iostream>
#include <queue>
#include <fstream>

/*  
 Initialize trie with file input or stdin
*/
trie::trie(std::istream& fin){
    root = new trie_node();
    initialize_node(fin);
    initialize_fail_pointer();
}


void trie::deconstruct_rec(trie_node* root){
    for(int i = 0; i < 26; i++){
        if(root->child[i] != NULL){
            deconstruct_rec(root->child[i]);
            root->child[i] = NULL;
        }
    }
    
    delete root;
}


trie::~trie(){
    deconstruct_rec(root);
}

bool trie::find_word(char* str){
    trie_node* cursor_node = root;
    char* cursor_str = str;
    
    while(*cursor_str != '\0'){
        if(cursor_node->child[*cursor_str - 'a']){
            cursor_node = cursor_node->child[*cursor_str - 'a'];
            ++cursor_str;
        }else{
//            std::cout << "Fail to find the string:" << std::endl;
            return false;
        }
    }
    
    if(!cursor_node->exists){
//        std::cout << "Fail to find the string:" << std::endl;
        return false;
    }
    
//    std::cout << "Successfully locate the string" << std::endl;
    return true;
}


void trie::insert_word(std::string& str){
    trie_node* cursor_node = root;
    int index = 0;
    
    while(str[index]){
        //node not existed, allocate a new space for it
        if(cursor_node->child[str[index]-'a'] == NULL){
            cursor_node->child[str[index]-'a'] = new trie_node();
            cursor_node->child[str[index]-'a']->key = str[index];
            cursor_node->child[str[index]-'a']->parent = cursor_node;
        }
        cursor_node = cursor_node->child[str[index] - 'a'];
        ++index;
    }
    
    
    //Duplicate insertion
    if(cursor_node->exists){
        printf("Duplicated string! Try a new one please.\n");
        return;
    }
    
    
    //Normal insertion
    cursor_node->word = str;
    std::cout << "Successfully insert a word:" << cursor_node->word <<std::endl;
    cursor_node->exists = true;
}


/*recursively delete the node, which means if you a child has been deleted, and the father has no other child, so the father should also be deleted, we can implement by recursive
 
 :pragma
 :
 :
 :ret  if delete a node, return true, or return false;
 */

bool trie::delete_word(char* str){
    return delete_word_rec(str, root);
}

bool trie::delete_word_rec(char* str, trie_node* root){
    
    if(*str == '\0'){
        delete root;
        std::cout << "Successfully delete the child" <<std::endl;
        return true;
    }
    
    if(!root->child[*str-'a']){
        std::cout << "No match when deleting!" <<std::endl;
        return false;
    }
    
    
    //recursively delete the child
    delete_word_rec(str+1, root->child[*str-'a']);
        
    
    
    //If the current node do not contain a word, we will delete it if he has no child
    if(!root->exists){
        //check if he has child
        for(int i = 0; i < 26; i++){
            if(root->child[i])
                return false;
        }
        
        //has no child, should be delete(don't forget to delete the connection between this node deleted and his father)
        root->parent->child[*str-'a'] = NULL;
        delete root;
        return true;
    }
    
    //this node contain a string, so it can not be deleted whether it has child
    return false;
}



int trie::naive_match_string(char* str){
    int len = (int) strlen(str);
    int counter = 0;
    
    for(int i = 0; i < len; i++)
        for(int j = i; j < len; j++){
            char* temp = new char[len];
            strncpy(temp, str+i, j-i+1);
            temp[j-i+1] = '\0';
            if (find_word(temp)){
                std::cout << "Match with " << temp <<std::endl;
                ++counter;
            }
            
            delete [] temp;
        }
    
    return counter;
}

int trie::initialize_node(std::istream& fin){
    std::string word;
    int numberOfWords;
    std::cout << "How many words does your dictionary contain?" <<std::endl;
    fin >> numberOfWords;
    std::cout << "Fill your dictionary please." <<std::endl;
    for(int i = 0; i < numberOfWords; i++){
        fin >> word;
        insert_word(word);
    }
    return 0;
}

int trie::initialize_fail_pointer(){
    std::queue<trie_node*> bfs_queue;
    root->fail = root;
    for(int i = 0; i < 26; i++){
        if(root->child[i]){
            bfs_queue.push(root->child[i]);
        }
    }
    
    while (!bfs_queue.empty()) {
        trie_node* ptr_all_node = bfs_queue.front();
        bfs_queue.pop();
        
        for(int i = 0; i < 26; i++){
            if(ptr_all_node->child[i]){
                bfs_queue.push(ptr_all_node->child[i]);
            }
        }
        
        
        
        trie_node* ptr_fail_node = ptr_all_node->parent->fail; //the node traverse the parent's fail pointer, until meet the end;
        bool traverse_twice_root = false;
        bool find_match = false;
        while(ptr_fail_node != root || !traverse_twice_root){
            //You can only traverse root once
            if(ptr_fail_node == root) traverse_twice_root = true;
            
            trie_node* match_child = ptr_fail_node->child[ptr_all_node->key-'a'];
            if(match_child && match_child != ptr_all_node){
                ptr_all_node->fail = match_child;
                find_match = true;

            }
        
        //if matched, break this loop;
        if(find_match) break;
        //if not match, continuely traverse with fail pointer
        else
            ptr_fail_node = ptr_fail_node->fail;
    }
        
    //if this node match no suibtable item, then set its fail pointer to root;
    if(!find_match) ptr_all_node->fail = root;
}
    
    return 0;
}

int trie::ac_match_string(std::istream& fin){
    trie_node* pnode_tr = root;   //traverse node;
    std::string input_text;
    std::cout << "Please type the sample string: " <<std::endl;
    fin >> input_text;
    int index = 0;
    
    //the outer loop traverse the string need matching, never go backward
    while(input_text[index]){
        if(pnode_tr->child[input_text[index]-'a']){
            pnode_tr = pnode_tr->child[input_text[index]-'a'];
            ++index;
        }else{
            if(pnode_tr == root) ++index;
            pnode_tr = pnode_tr->fail;
        }
        
        if(pnode_tr->exists) std::cout << "Find word " << pnode_tr->word << std::endl;
    }
    
    return 0;
}


