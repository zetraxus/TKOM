//
// Created by adam on 05.05.19.
//

#include "InstructionCallFunction.h"

InstructionCallFunction::InstructionCallFunction(const std::string& name) : name (name){

}

void InstructionCallFunction::addArgument(Token::Type type, std::unique_ptr<Variable> next) {
    types.emplace_back(type);
    variables.emplace_back(std::move(next));
}

void InstructionCallFunction::setArguments(std::vector<Token::Type> types, std::vector<std::unique_ptr<Variable>> variables) {
    InstructionCallFunction::types = types;
    InstructionCallFunction::variables = std::move(variables);
}

void InstructionCallFunction::execute() {

}
