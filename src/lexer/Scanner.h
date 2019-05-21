//
// Created by adam on 06.04.19.
//

#ifndef TKOM_SCANNER_H
#define TKOM_SCANNER_H


#include <vector>
#include <map>
#include "Source.h"
#include "Token.h"
#include <memory>

class Scanner {
private:

    bool ifLastWasPicked = false;
    std::shared_ptr<Token> last = nullptr;
    std::unique_ptr<Source> source;
    std::map<std::string, Token::Type> keyWords;
    bool flag; // set true if last token was Number and number was ended by non-digit symbol (instead of space)

    std::shared_ptr<Token> getAlphaToken(int firstChar);

    std::shared_ptr<Token> getNumberToken(int firstChar);

    std::shared_ptr<Token> getOperatorToken(int firstChar);


public:

    Scanner(std::unique_ptr<Source> source);

    std::shared_ptr<Token> getNextToken();

    std::shared_ptr<Token> peekNextToken();

};


#endif //TKOM_SCANNER_H
