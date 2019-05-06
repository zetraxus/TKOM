//
// Created by adam on 05.05.19.
//

#ifndef TKOM_FOR_H
#define TKOM_FOR_H


#include "../lexer/Token.h"
#include "Instruction.h"
#include "Block.h"

class For : public Instruction {
    Token::TokenType type;
    std::string itName;
    std::string container;
    Block* body;

public:
    For(Token::TokenType type, const std::string& itName, const std::string& container);

    void setBody(Block* body);
};


#endif //TKOM_FOR_H
