cmake_minimum_required(VERSION 3.7)
project(AC_)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        MyException.cpp
        MyException.h
        Trie.cpp
        Trie.h
        TrieNode.cpp
        TrieNode.h)

add_executable(AC_ ${SOURCE_FILES})