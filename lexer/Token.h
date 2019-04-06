//
// Created by adam on 06.04.19.
//

#ifndef TKOM_TOKEN_H
#define TKOM_TOKEN_H


#include <string>
#include "Source.h"

class Token {
    enum TokenType {
        Type,
        Identifier,
        Value,
        Unit, // V, W, A, Om, S, C, s, J
        OpMul, // *
        OpDiv, // /
        OpSum, // +
        OpSub, // -
        Return,
        If,
        Else,
        For,
        BracketOpen, // {
        BracketClose, // }
        ParenthesesOpen, // (
        ParenthesesClose, // )
        Colon, // :
        SemiColon, // ;
        Less, // <
        More, // >
        LessEq, // <=
        MoreEq, // >=
        Equal, // ==
        NotEqual, // !=
        LogicalOr, // ||
        LogicalAnd, // &&
        Assign, // =
        EofSymbol,
    };

private:

    TokenType tokenType;
    std::string value;
    Position startPosition;
    Position endPosition;

};


#endif //TKOM_TOKEN_H
