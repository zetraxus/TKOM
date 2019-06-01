//
// Created by adam on 30.05.19.
//

#include "Division.h"

Division::Division() {
    equation.emplace_back(Equation(Token::V, Token::A, Token::Om));
    equation.emplace_back(Equation(Token::V, Token::Om, Token::A));
    equation.emplace_back(Equation(Token::A, Token::V, Token::S));
    equation.emplace_back(Equation(Token::A, Token::S, Token::V));
    equation.emplace_back(Equation(Token::C, Token::A, Token::s));
    equation.emplace_back(Equation(Token::C, Token::s, Token::A));
    equation.emplace_back(Equation(Token::W, Token::A, Token::V));
    equation.emplace_back(Equation(Token::W, Token::V, Token::A));
    equation.emplace_back(Equation(Token::J, Token::W, Token::s));
    equation.emplace_back(Equation(Token::J, Token::s, Token::W));
}

Token::Type Division::getResult(Token::Type arg1, Token::Type arg2) {
    for (auto& e : equation) {
        if (arg1 == e.arg1 && arg2 == e.arg2)
            return e.result;
    }

    return Token::BadType;
}

Division* Division::getInstance() {
    static Division instance;
    return &instance;
}