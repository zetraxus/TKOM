//
// Created by adam on 06.04.19.
//

#include "Scanner.h"

const int LineFeed = 10;

Token* Scanner::getNextToken() {

    int nextChar; //code in ASCII

    do{
        nextChar = source -> getNextChar();
    } while (isspace(nextChar) || nextChar == LineFeed);

}
