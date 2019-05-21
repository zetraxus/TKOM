//
// Created by adam on 05.05.19.
//

#ifndef TKOM_BLOCK_H
#define TKOM_BLOCK_H


#include <vector>
#include "Instruction.h"
#include <memory>

class Block {
    std::vector<std::unique_ptr<Instruction>> instructions;
public:
    Block();

    void addInstruction(std::unique_ptr<Instruction> next);
};


#endif //TKOM_BLOCK_H
