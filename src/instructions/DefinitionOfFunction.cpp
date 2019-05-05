//
// Created by adam on 05.05.19.
//

#include "DefinitionOfFunction.h"

void DefinitionOfFunction::setReturnType(Token::TokenType returnType) {
    DefinitionOfFunction::returnType = returnType;
}

void DefinitionOfFunction::setIdentifier(const std::string& identifier) {
    DefinitionOfFunction::identifier = identifier;
}

void DefinitionOfFunction::addArgument(Variable* next) {
    arguments.push_back(next);
}

void DefinitionOfFunction::addInstruction(Instruction* next) {
    instructions.push_back(next);
}

void DefinitionOfFunction::setBody(Block* body) {
    DefinitionOfFunction::body = body;
}
