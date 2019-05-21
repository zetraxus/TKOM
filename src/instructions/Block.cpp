//
// Created by adam on 05.05.19.
//

#include "Block.h"

Block::Block() {}

void Block::addInstruction(std::unique_ptr<Instruction> next) {
    instructions.push_back(std::move(next));
}
