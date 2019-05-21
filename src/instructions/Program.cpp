//
// Created by adam on 05.05.19.
//

#include "Program.h"

Program::Program() {}

void Program::addFunction(std::unique_ptr<DefinitionOfFunction> next){
    functions.push_back(std::move(next));
}
