//
//  Trie.cpp
//  Trie
//
//  Created by 佘国榛 on 2017/6/30.
//  Copyright © 2017年 佘国榛. All rights reserved.
//

#include "Trie.h"
#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <exception>
#include "MyException.h"
#include <map>
#include <vector>

/**
 *
 */
Trie::Trie() {
    root = new TrieNode();
    InitializeNode();
    InitializeFailPointer();
    finished_init = true;
    helper = "Usage:\nh --Help\ni <word> --Insert new word\nd <word> --Delete a word\nf <word> --Find a word\nq --Quit the AC-Automation\nm <string> --Caculate the matched word\nl <filename> --Text from file\n";
}

/**
 * Deconstruct the Trie recursively
 *
 * @param root the root of subTrie
**/
void Trie::DeconstructRec(TrieNode *root) {
    for (int i = 0; i < 26; i++) {
        if (root->child[i] != NULL) {
            DeconstructRec(root->child[i]);
            root->child[i] = NULL;
        }
    }

    delete root;
}

/**
 * Deconstructor of Trie
 *
**/
Trie::~Trie() {
    DeconstructRec(root);
}


void Trie::AcMatchFile(std::string& filename) {
    std::ifstream fin;
    try {
        fin.open(filename);
        if(!fin) throw CanNotOpenFileException(filename);
    }catch (CanNotOpenFileException e){
        throw e;
    }

    //利用先用getline存入数组再合并的方法来达到去掉文章中换行符的目的
    std::vector<std::string> passage;
    std::string line;

    auto iter = passage.begin();
    while(std::getline(fin, line, '\n')){
        iter = passage.insert(iter, line);
    }

    std::string passage_without_linefeed;
    iter = passage.begin();


    while(iter != passage.end()) {
        passage_without_linefeed += *iter;
        ++iter;
    }

    try {
        AcMatchString(passage_without_linefeed);
    }catch (InvalidLetterException e){
        e.showMessage();
        throw e;
    }
}

/**
 Interact with user

 @param fin :
 */
void Trie::Interact() {
    std::cout << "Welcome to AC automation, what do you want to do?(Type 'h' for help)" << std::endl << ">>>";
    char input_type;
    std::string raw_input;

    std::string word;     //匹配或者删除的单词
    std::string str;      //输入的匹配字符串
    std::string filename; //文件的名称

    //getline之前必须做的一个操作，目前不懂原理
    std::cin.ignore();


    //循环实现交互命令
    while (getline(std::cin, raw_input)) {
        //处理空行
        if(raw_input[0] == '\0') {
            std::cout << ">>>";
            continue;
        }
        input_type = raw_input[0];

        //单独处理不带参数的help命令
        if (input_type=='h'){
            std::cout << helper <<"\n>>>";
            continue;
        }

        //如果第二个位置不是空格，则说明格式错误
        if (raw_input[1] != ' ') {
            std::cout << "Wrong Format, Type h for more information.\n>>>";
        } else {
            //根据输入进行不同操作
            switch (input_type) {

                //插入
                case 'i':
                    word = raw_input.substr(2,raw_input.length()-1);
                    InsertWord(word);
                    std::cout << ">>>";
                    break;

                //删除
                case 'd':
                    word = raw_input.substr(2,raw_input.length()-1);
                    DeleteWord(word);
                    std::cout << ">>>";
                    break;

                //退出AC自动机
                case 'q':
                    std::cout << "Good Bye" << std::endl;
                    exit(0);

                //检查字典中是否有对应单词
                case 'f':
                    word = raw_input.substr(2,raw_input.length()-1);
                    FindWord(word);
                    std::cout << ">>>";
                    break;

                //利用输入文本进行匹配
                case 'm':
                    str = raw_input.substr(2,raw_input.length()-1);
                    try {
                       AcMatchString(str);
                    }catch(InvalidLetterException e){
                        e.showMessage();
                        std::cout << ">>>";
                    }
                    std::cout << ">>>";
                    break;

                //利用加载文件进行匹配
                case 'l':
                    filename = raw_input.substr(2,raw_input.length()-1);
                    try {
                        AcMatchFile(filename);
                    }catch (CanNotOpenFileException e){
                        e.showMessage();
                        continue;
                    }catch (InvalidLetterException e){
                        std::cout << "'" << filename << "' contains invalid character\n>>>";
                        continue;
                    }
                std::cout << ">>>";
                    break;
                //未找到匹配选项
                default:
                    std::cout << "Option not found, type h for more information" << std::endl << ">>>";
            }
        }
    }

}




/**
 * Find whether a word is in the Trie
 *
 * @param word : the word to search
 * @return true: Find word
 *         false: Do not find word
 **/
bool Trie::FindWord(std::string &word) {
    TrieNode *cursor_node = root;
    int index = 0;

    while (word[index] != '\0') {
        if (cursor_node->child[word[index] - 'a']) {
            cursor_node = cursor_node->child[word[index] - 'a'];
            ++index;
        } else {
            std::cout << "The word '" << word << "' is not in the Trie\n>>>";
            return false;
        }
    }


    //Though matching with the input word, but the end of the word is not marked as exists;
    if (!cursor_node->exists) {
        std::cout << "The word '" << word << "'is not in the Trie\n>>>";
        return false;
    }

    std::cout << "The word '" << word << "' is in the Trie\n>>>";
    return true;
}


/**
 Reconstruct fail pointers when insert or delete a word

 @return true: success
         false: fail
 */
bool Trie::ReconstructFailPointer() {
    DeleteFailPointerRec(root);
    InitializeFailPointer();
    return true;
}


/**
 Delete all the fail pointer, aimed to reconstruct the fail pointer after insertion or deletion

 @return true: success
         fales: fail
 */
bool Trie::DeleteFailPointerRec(TrieNode *root) {
    for (int i = 0; i < 26; i++) {
        if (root->child[i] != NULL) {
            DeleteFailPointerRec(root->child[i]);
        }
    }

    root->fail = NULL;
    return true;
}


/**
 Insert a new word to Trie

 @param word : the new word need to insert
 */
void Trie::InsertWord(std::string &word){
    TrieNode *cursor_node = root;
    int index = 0;

    while (word[index]) {
        //node not existed, allocate a new space for it
        try {
            if (word[index] < 'a' || word[index] > 'z')
                throw InvalidLetterException(word[index]);
            if (cursor_node->child[word[index] - 'a'] == NULL) {
                cursor_node->child[word[index] - 'a'] = new TrieNode();
                cursor_node->child[word[index] - 'a']->key = word[index];
                cursor_node->child[word[index] - 'a']->parent = cursor_node;
            }
            cursor_node = cursor_node->child[word[index] - 'a'];
            ++index;
        } catch (InvalidLetterException e) {
            e.showMessage();
            throw InvalidWordException(word);
        }
    }


    //Duplicate insertion
    if (cursor_node->exists) {
        printf("Duplicated string! Try a new one please.\n>>>");
        return;
    }


    //Normal insertion
    cursor_node->word = word;
    std::cout << "Successfully insert a word: '" << cursor_node->word << "'\n>>>";
    cursor_node->exists = true;

    //if this is the insertion after the initialization, we need to reconstruct_fail_pointer
    if (finished_init)
        ReconstructFailPointer();

}




bool Trie::DeleteWord(std::string &word) {
    DeleteWordRec(word, root, 0);
    ReconstructFailPointer();
    return true;
}

bool Trie::DeleteWordRec(std::string &word, TrieNode *root, int index) {

    if (word[index] == '\0') {
        std::cout << "Successfully delete the word '" << word << "'\n>>>";
        //pay attention: Deleting a word does not mean deleting a node, whether delete a node depends on if this node's all children are NULL
        root->exists = false;

    } else if (!root->child[word[index] - 'a']) {
        std::cout << "Do not find the word '" << word << "'\n>>>";
        return false;
    } else {
        //recursively delete the child
        DeleteWordRec(word, root->child[word[index] - 'a'], index + 1);
    }

    //If the current node do not contain a word, we will delete it if he has no child
    if (!root->exists) {
        //check if he has child
        for (int i = 0; i < 26; i++) {
            if (root->child[i])
                return false;
        }

        //has no child, should be delete(don't forget to delete the connection between the node deleted and his father)
        if (root == this->root) {
            std::cout << "The dictionary is empty now!\n>>>";
            return true;
        } else {
            root->parent->child[word[index - 1] - 'a'] = NULL;
            delete root;
            return true;
        }
    }

    //this node contain a string, so it can not be deleted whether it has child
    return false;
}


int Trie::NaiveMatchString(std::string &str) {
    int len = (int) str.length();
    int counter = 0;

    for (int i = 0; i < len; i++)
        for (int j = i; j < len; j++) {
            std::string temp;
            temp = str.substr(i, j - i + 1);
            if (FindWord(temp)) {
                std::cout << "Match with " << temp << std::endl;
                ++counter;
            }
        }

    return counter;
}

int Trie::InitializeNode() {
    std::cout << "Initialize your AC-Automation...." << std::endl;
    std::string word;
    std::string strnum;
    int numberOfWords = 0;
    std::cout << "How many words does your dictionary contain?\n>>>";

    std::cin >> strnum;
    numberOfWords = atoi((char *) strnum.c_str());

    while (numberOfWords == 0) {
        std::cout << "Bad Input, Please type a number\n>>>";
        std::cin >> strnum;
        numberOfWords = atoi((char *) strnum.c_str());
    }
    std::cout << "Please fill your dictionary\n>>>";
    for (int i = 0; i < numberOfWords; i++) {
        std::cin >> word;
        try {
            InsertWord(word);
        } catch (InvalidWordException e) {
            e.showMessage();
            ++numberOfWords;
        }
    }

    std::cout << "Successfully Initialize your AC-Automation!" << std::endl;
    return 0;
}

int Trie::InitializeFailPointer() {
    std::queue<TrieNode *> bfs_queue;
    root->fail = root;
    for (int i = 0; i < 26; i++) {
        if (root->child[i]) {
            bfs_queue.push(root->child[i]);
        }
    }

    while (!bfs_queue.empty()) {
        TrieNode *ptr_all_node = bfs_queue.front();
        bfs_queue.pop();

        for (int i = 0; i < 26; i++) {
            if (ptr_all_node->child[i]) {
                bfs_queue.push(ptr_all_node->child[i]);
            }
        }


        TrieNode *ptr_fail_node = ptr_all_node->parent->fail; //the node traverse the parent's fail pointer, until meet the end;
        bool traverse_twice_root = false;
        bool find_match = false;
        while (ptr_fail_node != root || !traverse_twice_root) {
            //You can only traverse root once
            if (ptr_fail_node == root) traverse_twice_root = true;

            TrieNode *match_child = ptr_fail_node->child[ptr_all_node->key - 'a'];
            if (match_child && match_child != ptr_all_node) {
                ptr_all_node->fail = match_child;
                find_match = true;

            }

            //if matched, break this loop;
            if (find_match) break;
                //if not match, continuely traverse with fail pointer
            else
                ptr_fail_node = ptr_fail_node->fail;
        }

        //if this node match no suibtable item, then set its fail pointer to root;
        if (!find_match) ptr_all_node->fail = root;
    }

    return 0;
}

int Trie::AcMatchString(std::string &text) {
    std::map<std::string, int> WordCounter;
    TrieNode *pnode_tr = root;   //traverse node;
    int index = 0;
    bool bHasFindWord = false;
    //the outer loop traverse the string need matching, never go backward
    while (text[index]) {
        if(text[index]<'a' || text[index]>'z')
            throw InvalidLetterException(text[index]);

        if (pnode_tr->child[text[index] - 'a']) {
            pnode_tr = pnode_tr->child[text[index] - 'a'];
            ++index;
        } else {
            if (pnode_tr == root) ++index;
            pnode_tr = pnode_tr->fail;
        }

        if (pnode_tr->exists) {
            if (!WordCounter[pnode_tr->word])
                WordCounter[pnode_tr->word] = 1;
            else {
                ++WordCounter[pnode_tr->word];
            }
            bHasFindWord = true;
        }
    }

    if (!bHasFindWord) {
        std::cout << "No word in dictionary match your text" << std::endl;
        return 0;
    }

    std::map<std::string, int>::iterator iter = WordCounter.begin();
    std::cout << "Match Word          " << "Count\n";
    while (iter != WordCounter.end()) {
        std::cout << iter->first << "                     " << iter->second << std::endl;
        ++iter;
    }
    return 0;
}


