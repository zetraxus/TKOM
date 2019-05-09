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
    positionInContainer), type(Type::Id) {}

Variable::Variable(Value* value) : value(value), type(Type::Val) {}
