//
// Created by adam on 10.05.19.
//

#ifndef TKOM_VALUE_H
#define TKOM_VALUE_H


#include "../lexer/Token.h"

class Value {
    Token::TokenType type;
    std::string value;

public:
    Value(Token::TokenType type, const std::string& value);
};


#endif //TKOM_VALUE_H
