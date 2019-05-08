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

Operation* Operation::getLeft() const {
    return left;
}

Operation* Operation::getRight() const {
    return right;
}

void Operation::setUnitType(Token::TokenType unitType) {
    Operation::unitType = unitType;
}
