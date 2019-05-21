//
// Created by adam on 05.05.19.
//

#include "DefinitionOfFunction.h"

void DefinitionOfFunction::setReturnType(Token::Type returnType) {
    DefinitionOfFunction::returnType = returnType;
}

void DefinitionOfFunction::setIdentifier(const std::string& identifier) {
    DefinitionOfFunction::identifier = identifier;
}

void DefinitionOfFunction::addArgument(Token::Type type, std::unique_ptr<Variable> next) {
    arguments.emplace_back(std::make_pair(type, std::move(next)));
}

void DefinitionOfFunction::setBody(std::unique_ptr<Block> body) {
    DefinitionOfFunction::body = std::move(body);
}
