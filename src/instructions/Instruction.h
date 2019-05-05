//
// Created by adam on 05.05.19.
//

#ifndef TKOM_INSTRUCTION_H
#define TKOM_INSTRUCTION_H


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

};


#endif //TKOM_INSTRUCTION_H
