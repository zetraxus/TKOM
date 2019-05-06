//
// Created by adam on 06.05.19.
//

#ifndef TKOM_IFELSE_H
#define TKOM_IFELSE_H


#include "Expression.h"
#include "Block.h"

class IfElse : public Instruction {
    Expression* expression;
    Block* blockIf;
    Block* blockElse;

public:
    IfElse(Expression* expression, Block* blockIf, Block* blockElse);
};


#endif //TKOM_IFELSE_H
