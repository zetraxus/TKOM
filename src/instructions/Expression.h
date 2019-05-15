//
// Created by adam on 06.05.19.
//

#ifndef TKOM_EXPRESSION_H
#define TKOM_EXPRESSION_H


#include "../lexer/Token.h"
#include "Operation.h"

class Expression {
    Token::Type type;
    Expression* leftExp;
    Expression* rightExp = nullptr;
    Operation* operation;

public:
    Expression();

    void setType(Token::Type type);

    void setLeft(Expression* left);

    void setRight(Expression* right);

    Token::Type getType() const;

    Expression* getLeft() const;

    Expression* getRight() const;

    void setOperation(Operation* operation);

    Operation* getOperation() const;

};


#endif //TKOM_EXPRESSION_H
