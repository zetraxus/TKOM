//
// Created by adam on 06.05.19.
//

#include "IfElse.h"

IfElse::IfElse(std::unique_ptr<Operation> expression, std::unique_ptr<Block> blockIf, std::unique_ptr<Block> blockElse)
    : expression(std::move(expression)), blockIf(std::move(blockIf)),
      blockElse(std::move(blockElse)) {}

void IfElse::execute(SymbolMap& symbols) {
    if (expression->calculate(symbols).first)
        blockIf->execute(symbols);
    else
        blockElse->execute(symbols);
}
