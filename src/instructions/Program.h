//
// Created by adam on 05.05.19.
//

#ifndef TKOM_PROGRAM_H
#define TKOM_PROGRAM_H


#include <vector>
#include <bits/unique_ptr.h>
#include "DefinitionOfFunction.h"

class Program {
    std::vector<std::unique_ptr<DefinitionOfFunction>> functions;
public:
    Program();

    void addFunction(std::unique_ptr<DefinitionOfFunction> next);
};


#endif //TKOM_PROGRAM_H
