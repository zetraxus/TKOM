//
// Created by adam on 06.05.19.
//

#include <iostream>
#include "Operation.h"

Operation::Operation() {}

void Operation::setType(Token::TokenType type) {
    Operation::type = type;
}

void Operation::setLeft(Operation* left) {
    Operation::left = left;
}

void Operation::setRight(Operation* right) {
    Operation::right = right;
}

void Operation::set_operator(Operation::Operator _operator) {
    Operation::_operator = _operator;
}

void Operation::setVal(const std::string& val) {
    Operation::val = val;
}

Token::TokenType Operation::getType() const {
    return type;
}

Operation* Operation::getLeft() const {
    return left;
}

Operation* Operation::getRight() const {
    return right;
}

Operation::Operator Operation::get_operator() const {
    return _operator;
}

const std::string& Operation::getVal() const {
    return val;
}
