//
// Created by adam on 05.05.19.
//

#include "Program.h"

Program::Program() {}

void Program::addFunction(DefinitionOfFunction* next) {
    functions.push_back(next);
}
