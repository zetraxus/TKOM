//
// Created by adam on 05.05.19.
//

#include "InstructionDeclarationVariable.h"

InstructionDeclarationVariable::InstructionDeclarationVariable(Token::Type type,
                                                               const std::string& identifier) : type(type),
                                                                                                identifier(
                                                                                                    identifier) {}

void InstructionDeclarationVariable::execute(SymbolMap& symbols) {
    std::unique_ptr<Val> value(new Val(type));
    symbols.insert(identifier, std::move(value));
}

const std::string& InstructionDeclarationVariable::getIdentifier() const {
    return identifier;
}
