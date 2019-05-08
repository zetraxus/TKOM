//
// Created by adam on 06.04.19.
//

#ifndef TKOM_TOKEN_H
#define TKOM_TOKEN_H


#include <string>
#include "Source.h"

class Token {
public:
    enum TokenType {
        Identifier,
        Value,
        Int, // int
        Unit, // unit
        V, // Volt
        W, // Watt
        A, // Amper
        Om, // Ohm
        S, // Siemens
        C, // Coulomb
        s, // second
        J, // Joule
        OpMul, // *
        OpDiv, // /
        OpSum, // +
        OpSub, // -
        Return,
        If,
        Else,
        For,
        CurlyBracketOpen, // {
        CurlyBracketClose, // }
        SquareBracketsOpen, // [
        SquareBracketsClose, // ]
        ParenthesesOpen, // (
        ParenthesesClose, // )
        Colon, // :
        SemiColon, // ;
        Comma, // ,
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
        BadType,
    };

private:

    TokenType tokenType;
    std::string value;
    Position* startPosition;

public:

    Token(Position* startPosition);

    ~Token();

    void setTokenType(TokenType tokenType);

    void setTokenTypeAndValue(TokenType tokenType, std::string value);

    TokenType getTokenType() const;

    const std::string& getValue() const;

    Position* getStartPosition() const;

    bool isUnitType() const;

};


#endif //TKOM_TOKEN_H
