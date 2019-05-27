//
// Created by adam on 06.05.19.
//

#ifndef TKOM_EXPRESSION_H
#define TKOM_EXPRESSION_H


#include "../lexer/Token.h"
#include "Operation.h"
#include <memory>
#include <vector>

class Expression {
    Token::Type type;

    std::vector<std::unique_ptr<Expression>> expressions;
    std::unique_ptr<Operation> operation;

public:
    Expression();

    void setType(Token::Type type);

    Token::Type getType() const;

    void addExpression(std::unique_ptr<Expression> next);

    void setOperation(std::unique_ptr<Operation> operation);

};


#endif //TKOM_EXPRESSION_H
