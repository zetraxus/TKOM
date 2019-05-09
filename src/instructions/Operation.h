//
// Created by adam on 06.05.19.
//

#ifndef TKOM_OPERATION_H
#define TKOM_OPERATION_H


#include <string>
#include "../lexer/Token.h"
#include "Variable.h"

class Operation {
public:
    enum Operator{
        Sum, // +
        Sub, // -
        Mul, // *
        Div, // /
        Par, // ()
    };

//private:
//    Token::TokenType type;
//    Token::TokenType unitType = Token::TokenType::BadType; // only if we have value + unit e.g. 10N
//    std::string val; // if type == identifier || type == value
public:
    void setVariable(Variable* variable);

private:
    Operation* left;
    Operation* right = nullptr;
    Operator _operator;
    Variable* variable;

public:
    Operation();

//    void setType(Token::TokenType type);

    void setLeft(Operation* left);

//    void setUnitType(Token::TokenType unitType);

    void setRight(Operation* right);

    void set_operator(Operator _operator);

//    void setVal(const std::string& val);

    Operation* getLeft() const;

    Operation* getRight() const;
};


#endif //TKOM_OPERATION_H
