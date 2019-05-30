//
// Created by adam on 30.05.19.
//

#ifndef TKOM_DIVISION_H
#define TKOM_DIVISION_H


#include "Multiplication.h"

class Division {
    std::vector<Equation> equation;

    Division();

public:
    static Division* getInstance();

    Token::Type getResult(Token::Type arg1, Token::Type arg2);
};

#endif //TKOM_DIVISION_H
