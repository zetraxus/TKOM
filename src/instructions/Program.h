//
// Created by adam on 05.05.19.
//

#ifndef TKOM_PROGRAM_H
#define TKOM_PROGRAM_H


#include <vector>
#include "DefinitionOfFunction.h"

class Program {
    std::vector<DefinitionOfFunction*> functions;
public:
    Program();
    void addFunction(DefinitionOfFunction* next);
};


#endif //TKOM_PROGRAM_H
