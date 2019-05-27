//
// Created by adam on 10.05.19.
//

#ifndef TKOM_VALUE_H
#define TKOM_VALUE_H


#include <iostream>
#include "../lexer/Token.h"

class Value {
    Token::Type type;
    std::string value;

public:
    Value(Token::Type type, const std::string& value);
};


#endif //TKOM_VALUE_H
