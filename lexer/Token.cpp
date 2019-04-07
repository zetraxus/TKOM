//
// Created by adam on 06.04.19.
//

#include "Token.h"


Token::Token(Position* startPosition) : startPosition(startPosition) {}

Token::~Token() {
    delete startPosition;
}
