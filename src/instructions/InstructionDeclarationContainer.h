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
#include <memory>

class InstructionDeclarationContainer : public Instruction {
    Token::Type type;
    std::string identifier;
    std::string size;
    std::vector<Token::Type> types; //initial values
    std::vector<std::unique_ptr<Variable>> variables; //initial values

public:
    InstructionDeclarationContainer(Token::Type type, const std::string& identifier, const std::string& size);

    void setInitialValues(std::string size, std::vector<Token::Type>& types,
                          std::vector<std::unique_ptr<Variable>>& variables);

    void execute(SymbolMap& symbols) override;

    const std::string& getIdentifier() const;
};


#endif //TKOM_INSTRUCTIONDECLARATIONCONTAINER_H
