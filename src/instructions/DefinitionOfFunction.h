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
#include <memory>

class DefinitionOfFunction {
    Token::Type returnType;
    std::string identifier;
    std::vector<std::pair<Token::Type, std::unique_ptr<Variable>> > arguments;
    std::unique_ptr <Block> body;

public:
    void setReturnType(Token::Type returnType);

    void setIdentifier(const std::string& identifier);

    void setBody(std::unique_ptr<Block> body);

    void addArgument(Token::Type type, std::unique_ptr<Variable> next);

    const std::string& getIdentifier() const;

    Block* getBlock();
};


#endif //TKOM_INSTRUCTIONDEFINITIONOFFUNCTION_H
