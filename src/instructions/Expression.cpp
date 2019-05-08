//
// Created by adam on 06.05.19.
//

#include "Expression.h"

Expression::Expression() {}

void Expression::setType(Token::TokenType type) {
    Expression::type = type;
}

void Expression::setLeft(Expression* left) {
    Expression::leftExp = left;
}

void Expression::setRight(Expression* right) {
    Expression::rightExp = right;
}

void Expression::setOperation(Operation* operation) {
    Expression::operation = operation;
}

Token::TokenType Expression::getType() const {
    return type;
}

Expression* Expression::getLeft() const {
    return leftExp;
}

Expression* Expression::getRight() const {
    return rightExp;
}

Operation* Expression::getOperation() const {
    return operation;
}
