//
// Created by adam on 06.05.19.
//

#include "Expression.h"

Expression::Expression() {}

void Expression::setType(Token::Type type) {
    Expression::type = type;
}

void Expression::setOperation(std::unique_ptr<Operation> operation) {
    Expression::operation = std::move(operation);
}

Token::Type Expression::getType() const {
    return type;
}

void Expression::addExpression(std::unique_ptr<Expression> next) {
    expressions.emplace_back(std::move(next));
}
