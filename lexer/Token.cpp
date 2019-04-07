//
// Created by adam on 06.04.19.
//

#include "Token.h"

Token::Token(Token::TokenType tokenType, const std::string& value, const Position& startPosition,
             const Position& endPosition) : tokenType(tokenType), value(value), startPosition(startPosition),
                                            endPosition(endPosition) {}
