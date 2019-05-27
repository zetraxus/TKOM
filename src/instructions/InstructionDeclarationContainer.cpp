//
// Created by adam on 05.05.19.
//

#include "InstructionDeclarationContainer.h"

InstructionDeclarationContainer::InstructionDeclarationContainer(Token::Type type, const std::string& identifier,
                                                                 const std::string& size) : type(type),
                                                                                            identifier(identifier),
                                                                                            size(size) {}

void InstructionDeclarationContainer::setInitialValues(std::vector<Token::Type>& types, std::vector<std::unique_ptr<Variable>>& variables) {
    InstructionDeclarationContainer::types = types;
    InstructionDeclarationContainer::variables = std::move(variables);
}

void InstructionDeclarationContainer::execute() {

}

