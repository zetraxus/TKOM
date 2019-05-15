//
// Created by adam on 05.05.19.
//

#ifndef TKOM_INSTRUCTIONDECLARATIONCONTAINER_H
#define TKOM_INSTRUCTIONDECLARATIONCONTAINER_H


#include <string>
#include <vector>
#include "Instruction.h"
#include "../lexer/Token.h"
#include "Variable.h"

class InstructionDeclarationContainer : public Instruction {
    Token::Type type;
    std::string identifier;
    std::string size;
    std::vector<std::pair<Token::Type, Variable*>> initialValues;

public:
    InstructionDeclarationContainer(Token::Type type, const std::string& identifier, const std::string& size);

    void setInitialValues(const std::vector<std::pair<Token::Type, Variable*>>& initialValues);
};


#endif //TKOM_INSTRUCTIONDECLARATIONCONTAINER_H
