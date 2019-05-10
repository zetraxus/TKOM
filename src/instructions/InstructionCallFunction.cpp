//
// Created by adam on 05.05.19.
//

#include "InstructionCallFunction.h"

InstructionCallFunction::InstructionCallFunction(const std::string& name) {

}

void InstructionCallFunction::addArgument(Token::TokenType type, Variable* next) {
    arguments.emplace_back(std::make_pair(type, next));
}

void InstructionCallFunction::setArguments(const std::vector<std::pair<Token::TokenType, Variable*>>& arguments) {
    InstructionCallFunction::arguments = arguments;
}
