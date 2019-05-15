//
// Created by adam on 05.05.19.
//

#ifndef TKOM_INSTRUCTIONCALLFUNCTION_H
#define TKOM_INSTRUCTIONCALLFUNCTION_H


#include <string>
#include <vector>
#include "Instruction.h"
#include "../lexer/Token.h"
#include "Variable.h"

class InstructionCallFunction : public Instruction {
    std::string name;
    std::vector<std::pair<Token::Type, Variable*> > arguments;

public:
    explicit InstructionCallFunction(const std::string& name);

    void addArgument(Token::Type type, Variable* next);

    void setArguments(const std::vector<std::pair<Token::Type, Variable*>>& arguments);
};


#endif //TKOM_INSTRUCTIONCALLFUNCTION_H
