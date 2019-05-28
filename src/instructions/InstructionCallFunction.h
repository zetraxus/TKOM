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
#include <memory>

class InstructionCallFunction : public Instruction {
    std::string name;
    std::vector<Token::Type> types;
    std::vector<std::unique_ptr<Variable>> variables;
public:
    explicit InstructionCallFunction(const std::string& name);

    void addArgument(Token::Type type, std::unique_ptr<Variable> next);

    void setArguments(std::vector<Token::Type> types, std::vector<std::unique_ptr<Variable>> variables);

    void execute(SymbolMap& symbols) override;
};


#endif //TKOM_INSTRUCTIONCALLFUNCTION_H
