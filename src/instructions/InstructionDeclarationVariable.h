//
// Created by adam on 05.05.19.
//

#ifndef TKOM_INSTRUCTIONDECLARATIONVARIABLE_H
#define TKOM_INSTRUCTIONDECLARATIONVARIABLE_H


#include <string>
#include "Instruction.h"
#include "../lexer/Token.h"

class InstructionDeclarationVariable : public Instruction {
    Token::Type type;
    std::string identifier;

public:
    InstructionDeclarationVariable(Token::Type type, const std::string& identifier);

    void execute(SymbolMap& symbols) override;

    const std::string& getIdentifier() const;
};


#endif //TKOM_INSTRUCTIONDECLARATIONVARIABLE_H
