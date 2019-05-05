//
// Created by adam on 05.05.19.
//

#ifndef TKOM_INSTRUCTIONDECLARATIONCONTAINER_H
#define TKOM_INSTRUCTIONDECLARATIONCONTAINER_H


#include <string>
#include "Instruction.h"
#include "../lexer/Token.h"

class InstructionDeclarationContainer : public Instruction {
    Token::TokenType type;
    std::string identifier;
    std::string size;
public:
    InstructionDeclarationContainer(Token::TokenType type, const std::string& identifier, const std::string& size);
};


#endif //TKOM_INSTRUCTIONDECLARATIONCONTAINER_H
