//
// Created by adam on 05.05.19.
//

#include "InstructionDeclarationVariable.h"

InstructionDeclarationVariable::InstructionDeclarationVariable(Token::TokenType type,
                                                               const std::string& identifier) : type(type),
                                                                                                identifier(
                                                                                                    identifier) {}