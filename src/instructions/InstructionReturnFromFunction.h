//
// Created by adam on 05.05.19.
//

#ifndef TKOM_INSTRUCTIONRETURNFROMFUNCTION_H
#define TKOM_INSTRUCTIONRETURNFROMFUNCTION_H


#include <string>
#include "Instruction.h"
#include "Variable.h"

class InstructionReturnFromFunction : public Instruction {
    Variable* variable;
public:
    InstructionReturnFromFunction(Variable* variable);
};


#endif //TKOM_INSTRUCTIONRETURNFROMFUNCTION_H
