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
    std::vector<std::pair<Token::TokenType, Variable*> > arguments;

public:
    explicit InstructionCallFunction(const std::string& name);

    void addArgument(Token::TokenType type, Variable* next);
};


#endif //TKOM_INSTRUCTIONCALLFUNCTION_H
