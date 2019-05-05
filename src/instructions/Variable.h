//
// Created by adam on 05.05.19.
//

#ifndef TKOM_VARIABLE_H
#define TKOM_VARIABLE_H


#include "../lexer/Token.h"

class Variable {
    Token::TokenType type;
    std::string name;

public:
    Variable();

    void setType(Token::TokenType type);

    void setName(const std::string& name);
};


#endif //TKOM_VARIABLE_H
