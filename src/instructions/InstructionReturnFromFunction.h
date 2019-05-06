//
// Created by adam on 05.05.19.
//

#ifndef TKOM_INSTRUCTIONRETURNFROMFUNCTION_H
#define TKOM_INSTRUCTIONRETURNFROMFUNCTION_H


#include <string>
#include "Instruction.h"

class InstructionReturnFromFunction : public Instruction {
    bool flag; // 0 = identifier, 1 = value
    std::string returnValue;
public:
    InstructionReturnFromFunction(bool flag, const std::string& returnValue);
};


#endif //TKOM_INSTRUCTIONRETURNFROMFUNCTION_H
