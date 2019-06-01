//
// Created by adam on 06.05.19.
//

#ifndef TKOM_IFELSE_H
#define TKOM_IFELSE_H


#include "Expression.h"
#include "Block.h"

class IfElse : public Instruction {
    std::unique_ptr<Operation> expression;
    std::unique_ptr<Block> blockIf;
    std::unique_ptr<Block> blockElse;

public:
    IfElse(std::unique_ptr<Operation> expression, std::unique_ptr<Block> blockIf, std::unique_ptr<Block> blockElse);

    void execute(SymbolMap& symbols) override;
};


#endif //TKOM_IFELSE_H
