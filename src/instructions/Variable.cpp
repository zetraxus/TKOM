//
// Created by adam on 05.05.19.
//

#include "Variable.h"

Variable::Variable() {}

void Variable::setName(const std::string& name) {
    Variable::name = name;
}

void Variable::setPositionInContainer(const std::string& positionInContainer) {
    Variable::positionInContainer = positionInContainer;
}

Variable::Variable(const std::string& name, const std::string& positionInContainer) : name(name), positionInContainer(
    positionInContainer), type(Type::Id) {
    value = std::make_unique<Value> (Token::BadType, "");
}

Variable::Variable(std::unique_ptr <Value> value) : value(std::move(value)), type(Type::Val) {}

Variable::Variable(const std::string& name) : name(name) {}

std::string Variable::getValue() {
    return value->getValue();
}

const std::string& Variable::getName() const {
    return name;
}
