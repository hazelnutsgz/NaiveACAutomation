//
//  main.cpp
//  Trie
//
//  Created by 佘国榛 on 2017/6/30.
//  Copyright © 2017年 佘国榛. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Trie.hpp"
void test(){
    std::ifstream fin("/Users/sgz/Desktop/test.txt");
    trie tr(std::cin);
    tr.ac_match_string(std::cin);
}

int main(int argc, const char * argv[]) {
    test();
}
