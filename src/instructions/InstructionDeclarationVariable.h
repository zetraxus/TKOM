//
// Created by adam on 05.05.19.
//

#ifndef TKOM_INSTRUCTIONDECLARATIONVARIABLE_H
#define TKOM_INSTRUCTIONDECLARATIONVARIABLE_H


#include <string>
#include "Instruction.h"
#include "../lexer/Token.h"

class InstructionDeclarationVariable : public Instruction {
    Token::TokenType type;
    std::string identifier;

public:
    InstructionDeclarationVariable(Token::TokenType type, const std::string& identifier);
};


#endif //TKOM_INSTRUCTIONDECLARATIONVARIABLE_H
