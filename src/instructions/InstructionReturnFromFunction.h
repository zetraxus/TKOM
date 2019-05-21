//
// Created by adam on 05.05.19.
//

#ifndef TKOM_INSTRUCTIONRETURNFROMFUNCTION_H
#define TKOM_INSTRUCTIONRETURNFROMFUNCTION_H


#include <string>
#include "Instruction.h"
#include "Variable.h"
#include <memory>

class InstructionReturnFromFunction : public Instruction {
    std::unique_ptr <Variable> variable;
public:
    explicit InstructionReturnFromFunction(std::unique_ptr <Variable> variable);
};


#endif //TKOM_INSTRUCTIONRETURNFROMFUNCTION_H
