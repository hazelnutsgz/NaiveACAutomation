//
//  MyException.hpp
//  AC_Automation
//
//  Created by 佘国榛 on 2017/7/3.
//  Copyright © 2017年 hazelnutsgz. All rights reserved.
//

#ifndef MyException_h
#define MyException_h

#include <iostream>
#include <exception>

class CanNotOpenFileException:public std::exception{
public:
    CanNotOpenFileException(std::string& filename);
    void showMessage();
private:
    std::string filename;
};

class InvalidLetterException: public std::exception{
public:
    InvalidLetterException(char wrong_letter);
    void showMessage();
private:
    char wrong_letter;
};

class InvalidWordException: public std::exception{
public:
    InvalidWordException(std::string& wrong_word);
    void showMessage();
private:
    std::string wrong_word;
};

#endif /* MyException_hpp */
