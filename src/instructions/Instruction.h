//
// Created by adam on 05.05.19.
//

#ifndef TKOM_INSTRUCTION_H
#define TKOM_INSTRUCTION_H


#include "../interpreter/SymbolMap.h"

class Instruction {
    enum InstructionType {
        DeclarationVariable,
        DeclarationContainer,
        DefinitionOfFunction,
        Assignment,
        CallFunction,
        ReturnFromFunction
    };

    InstructionType instructionType;

public:
    Instruction();

    virtual void execute(SymbolMap& symbols) = 0;
};


#endif //TKOM_INSTRUCTION_H
