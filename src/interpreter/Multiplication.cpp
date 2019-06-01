//
// Created by adam on 30.05.19.
//

#include "Multiplication.h"

Multiplication::Multiplication() {
    equation.emplace_back(Equation(Token::A, Token::V, Token::W));
    equation.emplace_back(Equation(Token::Om, Token::A, Token::V));
    equation.emplace_back(Equation(Token::S, Token::V, Token::A));
    equation.emplace_back(Equation(Token::s, Token::A, Token::C));
    equation.emplace_back(Equation(Token::W, Token::s, Token::J));
    equation.emplace_back(Equation(Token::Value, Token::Value, Token::Value));
}

Token::Type Multiplication::getResult(Token::Type arg1, Token::Type arg2) {
    for (auto& e : equation) {
        if ((arg1 == e.arg1 && arg2 == e.arg2) || (arg1 == e.arg2 && arg2 == e.arg1))
            return e.result;
    }
    return Token::BadType;
}

Multiplication* Multiplication::getInstance() {
    static Multiplication instance;
    return &instance;
}

Equation::Equation(Token::Type arg1, Token::Type arg2, Token::Type result) : arg1(arg1), arg2(arg2), result(result) {}
