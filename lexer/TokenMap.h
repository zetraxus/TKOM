//
// Created by adam on 10.04.19.
//

#ifndef TKOM_TOKENSMAP_H
#define TKOM_TOKENSMAP_H


#include <map>
#include "Token.h"

class TokensMap { // for test
    std::map<Token::TokenType, std::string> tokens;
public:
    TokensMap();

    std::string findTokenDescription(Token::TokenType token);
};

#endif //TKOM_TOKENSMAP_H
