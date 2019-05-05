//
// Created by adam on 05.05.19.
//

#ifndef TKOM_BLOCK_H
#define TKOM_BLOCK_H


#include <vector>
#include "Instruction.h"

class Block {
    std::vector<Instruction*> instructions;
public:
    Block();

    void addInstruction(Instruction* next);
};


#endif //TKOM_BLOCK_H
