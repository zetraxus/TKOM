//
// Created by adam on 06.04.19.
//

#include <iostream>
#include "Scanner.h"

const int LineFeed = 10;

Token* Scanner::getNextToken() {

    int nextChar; //code in ASCII

    do{
        nextChar = source -> getNextChar();
    } while (isspace(nextChar) || nextChar == LineFeed);

    if(isalpha(nextChar)){
        getAlphaToken(nextChar);
    } else if (isdigit(nextChar)){

    }
}

Token* Scanner::getAlphaToken(int firstChar) {
    Token* token = new Token(source->getCurrentPosition());
    std::string result;
    result += (char) firstChar;

    int nextChar;
    while(isalpha(nextChar = source -> getNextChar()) || isdigit(nextChar)){
        result += (char) nextChar;
    }

    std::cout <<result << " ";
}

Token* Scanner::getNumberToken(int firstChar) {
    return nullptr;
}

Token* Scanner::getOperatorToken(int firstChar) {
    return nullptr;
}

Scanner::Scanner(Source* source) : source(source) {}

Scanner::~Scanner() {
    delete source;
}
