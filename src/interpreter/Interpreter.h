//
// Created by adam on 27.05.19.
//

#ifndef TKOM_INTERPRETER_H
#define TKOM_INTERPRETER_H


#include <memory>
#include "../parser/Parser.h"

class Interpreter {
    std::unique_ptr<Parser> parser;
    SymbolMap symbols;

public:
    explicit Interpreter(std::unique_ptr<Parser> parser);

    void execute();

    SymbolMap getSymbols();
};


#endif //TKOM_INTERPRETER_H
