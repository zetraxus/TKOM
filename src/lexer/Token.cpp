//
// Created by adam on 06.04.19.
//

#include <iostream>
#include "Token.h"


Token::Token(std::shared_ptr<Position> startPosition) : startPosition(startPosition) {}

void Token::setTokenType(Type tokenType) {
    this->tokenType = tokenType;
}

void Token::setTokenTypeAndValue(Type tokenType, std::string value) {
    this->tokenType = tokenType;
    this->value = value;
}

Token::Type Token::getTokenType() const {
    return tokenType;
}

const std::string& Token::getValue() const {
    return value;
}

std::shared_ptr<Position> Token::getStartPosition() const {
    return startPosition;
}

bool Token::isUnitType() const {
    return tokenType == V || tokenType == W || tokenType == A || tokenType == Om || tokenType == S || tokenType == C ||
           tokenType == s || tokenType == J;
}
