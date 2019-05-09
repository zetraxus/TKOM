//
// Created by adam on 06.05.19.
//

#include <iostream>
#include "Operation.h"

Operation::Operation() {}

void Operation::setLeft(Operation* left) {
    Operation::left = left;
}

void Operation::setRight(Operation* right) {
    Operation::right = right;
}

void Operation::set_operator(Operation::Operator _operator) {
    Operation::_operator = _operator;
}

Operation* Operation::getLeft() const {
    return left;
}

Operation* Operation::getRight() const {
    return right;
}

void Operation::setVariable(Variable* variable) {
    Operation::variable = variable;
}