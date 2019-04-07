//
// Created by adam on 06.04.19.
//

#ifndef TKOM_SCANNER_H
#define TKOM_SCANNER_H


#include <vector>
#include "Source.h"
#include "Token.h"

class Scanner {
private:

    Source* source;
    std::vector<Token*> tokenList;

public:

    Token* getNextToken();

};


#endif //TKOM_SCANNER_H
