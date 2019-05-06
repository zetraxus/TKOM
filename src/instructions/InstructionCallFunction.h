//
// Created by adam on 05.05.19.
//

#ifndef TKOM_INSTRUCTIONCALLFUNCTION_H
#define TKOM_INSTRUCTIONCALLFUNCTION_H


#include <string>
#include <vector>
#include "Instruction.h"

class InstructionCallFunction : public Instruction {
    std::string name;
    std::vector<std::string> arguments;

public:
    explicit InstructionCallFunction(const std::string& name);

    void addArgument(const std::string& next);
};


#endif //TKOM_INSTRUCTIONCALLFUNCTION_H
