//
// Created by adam on 05.05.19.
//

#include "InstructionDeclarationContainer.h"

InstructionDeclarationContainer::InstructionDeclarationContainer(Token::TokenType type, const std::string& identifier,
                                                                 const std::string& size) : type(type),
                                                                                            identifier(identifier),
                                                                                            size(size) {}

void InstructionDeclarationContainer::setInitialValues(
    const std::vector<std::pair<Token::TokenType, Variable*>>& initialValues) {
    InstructionDeclarationContainer::initialValues = initialValues;
}

