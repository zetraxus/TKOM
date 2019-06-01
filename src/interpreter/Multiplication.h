//
// Created by adam on 30.05.19.
//

#ifndef TKOM_MULTIPLICATION_H
#define TKOM_MULTIPLICATION_H


#include <vector>
#include "../lexer/Token.h"

struct Equation {
    Token::Type arg1;
    Token::Type arg2;
    Token::Type result;

    Equation(Token::Type arg1, Token::Type arg2, Token::Type result);
};

class Multiplication {
    std::vector<Equation> equation;

    Multiplication();

public:
    static Multiplication* getInstance();

    Token::Type getResult(Token::Type arg1, Token::Type arg2);
};


#endif //TKOM_MULTIPLICATION_H
