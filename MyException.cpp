//
//  MyException.cpp
//  AC_Automation
//
//  Created by 佘国榛 on 2017/7/3.
//  Copyright © 2017年 hazelnutsgz. All rights reserved.
//

#include "MyException.h"
#include <exception>
#include <iostream>
InvalidLetterException::InvalidLetterException(char wrong_letter){
    this->wrong_letter = wrong_letter;
}

void InvalidLetterException::showMessage(){
    std::cout << "InvalidLetterException:'" << wrong_letter << "' is not a letter\n";
}

InvalidWordException::InvalidWordException(std::string& wrong_word){
    this->wrong_word = wrong_word;
}

void InvalidWordException::showMessage(){
    std::cout << "InvalidWordException:'" << wrong_word << "' is not a word. Please try a new word\n";
}

CanNotOpenFileException::CanNotOpenFileException(std::string &filename) {
    this->filename = filename;
}

void CanNotOpenFileException::showMessage(){
    std::cout << "CanNotOpenFileException: Can't open file '" << filename << "'\n";
}