//
// Created by adam on 05.05.19.
//

#include "Block.h"

Block::Block() {}

void Block::addInstruction(Instruction* next) {
    instructions.push_back(next);
}
