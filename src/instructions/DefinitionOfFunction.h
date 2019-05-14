//
// Created by adam on 05.05.19.
//

#ifndef TKOM_INSTRUCTIONDEFINITIONOFFUNCTION_H
#define TKOM_INSTRUCTIONDEFINITIONOFFUNCTION_H


#include <vector>
#include "Instruction.h"
#include "../lexer/Token.h"
#include "Variable.h"
#include "Block.h"

class DefinitionOfFunction {
    Token::Type returnType;
    std::string identifier;
    std::vector<std::pair<Token::Type, Variable*> > arguments;
    std::vector<Instruction*> instructions;
    Block* body;

public:
    void setReturnType(Token::Type returnType);

    void setIdentifier(const std::string& identifier);

    void setBody(Block* body);

    void addArgument(Token::Type type, Variable* next);

    void addInstruction(Instruction* next);
};


#endif //TKOM_INSTRUCTIONDEFINITIONOFFUNCTION_H
