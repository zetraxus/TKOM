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

std::pair<int, std::experimental::optional<Token::Type>> Operation::calculate() {

}

void Operation::setEmpty(bool empty) {
    Operation::empty = empty;
}

bool Operation::isEmpty() const {
    return empty;
}

bool Operation::opEmpty(size_t id) const {
    return operations[id]->isEmpty();
}
