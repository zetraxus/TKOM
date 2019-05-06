//
// Created by adam on 06.04.19.
//

#include <iostream>
#include "Token.h"


Token::Token(Position* startPosition) : startPosition(startPosition) {}

Token::~Token() {
    delete startPosition;
}

void Token::setTokenType(TokenType tokenType) {
    this->tokenType = tokenType;
}

void Token::setTokenTypeAndValue(TokenType tokenType, std::string value) {
    this->tokenType = tokenType;
    this->value = value;
}

Token::TokenType Token::getTokenType() const {
    return tokenType;
}

const std::string& Token::getValue() const {
    return value;
}

Position* Token::getStartPosition() const {
    return startPosition;
}



//lvl0 = lvl1 {+ lvl1} | lvl1 {- lvl1};
//lvl1 = lvl2 {* lvl2} | lvl2 {/ lvl2};
//lvl2 = (lvl0) | identifier | value