//
// Created by adam on 06.05.19.
//

#include "Operation.h"

Operation::Operation() {}

void Operation::addOperation(std::unique_ptr<Operation> next) {
    operations.emplace_back(std::move(next));
}

void Operation::set_operator(Operation::Operator _operator) {
    Operation::_operator = _operator;
}

void Operation::setVariable(std::unique_ptr<Variable> variable) {
    Operation::variable = std::move(variable);
}