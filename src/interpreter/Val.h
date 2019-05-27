//
// Created by adam on 27.05.19.
//

#ifndef TKOM_VAL_H
#define TKOM_VAL_H


#include <vector>
#include "../lexer/Token.h"

class Val {

    Token::Type type;
    size_t size; // 0 if variable, more if container
    std::vector<unsigned> values; // values[0] if variable
    std::vector<Token::Type> units; // values[0] if variable

public:
    Val(Token::Type type, size_t size, const std::vector<unsigned int>& values, const std::vector<Token::Type>& units);

    Val(Token::Type type, const std::vector<unsigned int>& values);

    Val(Token::Type type, const std::vector<unsigned int>& values, const std::vector<Token::Type>& units);

    Val(Token::Type type, unsigned value);

    Val(Token::Type type, unsigned value, Token::Type unit);

    Token::Type getType() const;

    size_t getSize() const;

    const std::vector<unsigned int>& getValues() const;

    const std::vector<Token::Type>& getUnits() const;
};


#endif //TKOM_VAL_H
