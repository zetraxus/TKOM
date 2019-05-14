//
// Created by adam on 06.04.19.
//

#ifndef TKOM_SCANNER_H
#define TKOM_SCANNER_H


#include <vector>
#include <map>
#include "Source.h"
#include "Token.h"

class Scanner {
private:

    bool ifLastWasPicked = false;
    Token* last = nullptr;
    Source* source;
    std::map<std::string, Token::Type> keyWords;
    bool flag; // set true if last token was Number and number was ended by non-digit symbol (instead of space)

    Token* getAlphaToken(int firstChar);

    Token* getNumberToken(int firstChar);

    Token* getOperatorToken(int firstChar);


public:

    Scanner(Source* source);

    ~Scanner();

    Token* getNextToken();

    Token* peekNextToken();

};


#endif //TKOM_SCANNER_H
