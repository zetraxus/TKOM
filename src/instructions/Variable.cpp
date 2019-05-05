//
// Created by adam on 05.05.19.
//

#include "Variable.h"

Variable::Variable() {}

void Variable::setType(Token::TokenType type) {
    Variable::type = type;
}

void Variable::setName(const std::string& name) {
    Variable::name = name;
}
