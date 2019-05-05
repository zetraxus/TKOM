//
// Created by adam on 05.05.19.
//

#include "InstructionCallFunction.h"

InstructionCallFunction::InstructionCallFunction(const std::string& name) {

}

void InstructionCallFunction::addArgument(const std::string& next) {
    arguments.push_back(next);
}
