//
// Created by adam on 06.04.19.
//

#include <iostream>
#include "Scanner.h"

const int LineFeed = 10;

Token* Scanner::peekNextToken() {
    last = getNextToken();
    ifLastWasPicked = true;
    return last;
}

Token* Scanner::getNextToken() {
    if (ifLastWasPicked) {
        ifLastWasPicked = false;
        return last;
    }

    int nextChar; //code in ASCII
    Token* nextToken;

    do
        nextChar = source->getNextChar();
    while (isspace(nextChar) || nextChar == LineFeed);

    if (isalpha(nextChar))
        nextToken = getAlphaToken(nextChar);
    else if (isdigit(nextChar))
        nextToken = getNumberToken(nextChar);
    else
        nextToken = getOperatorToken(nextChar);

    ifLastWasPicked = false;
    return nextToken;
}

Token* Scanner::getAlphaToken(int firstChar) {
    Token* token = new Token(new Position(*(source->getCurrentPosition())));

    std::string result;
    result += (char) firstChar;

    int nextChar;
    while (isalpha(nextChar = source->peekNextChar()) || isdigit(nextChar)) {
        result += source->getNextChar();
    }

    auto it = keyWords.find(result);
    if (it != keyWords.end())
        token->setTokenType(it->second);
    else
        token->setTokenTypeAndValue(Token::Type::Identifier, result);

    if (flag && token->getTokenType() == Token::Type::Identifier)
        token->setTokenTypeAndValue(Token::Type::BadType, result);
    else
        flag = false;

    return token;
}

Token* Scanner::getNumberToken(int firstChar) {
    Token* token = new Token(new Position(*(source->getCurrentPosition())));

    std::string result;
    result += (char) firstChar;

    while (isdigit(source->peekNextChar()))
        result += source->getNextChar();

    if (isalpha(source->peekNextChar()))
        flag = true;

    token->setTokenTypeAndValue(Token::Type::Value, result);

    return token;
}

Token* Scanner::getOperatorToken(int firstChar) {
    Token* token = new Token(new Position(*(source->getCurrentPosition())));
    std::string result;
    result += (char) firstChar;

    char first = (char) firstChar;
    if (first == '*')
        token->setTokenType(Token::Type::OpMul);
    else if (first == '/')
        token->setTokenType(Token::Type::OpDiv);
    else if (first == '+')
        token->setTokenType(Token::Type::OpSum);
    else if (first == '-')
        token->setTokenType(Token::Type::OpSub);
    else if (first == '{')
        token->setTokenType(Token::Type::CurlyBracketOpen);
    else if (first == '}')
        token->setTokenType(Token::Type::CurlyBracketClose);
    else if (first == '[')
        token->setTokenType(Token::Type::SquareBracketsOpen);
    else if (first == ']')
        token->setTokenType(Token::Type::SquareBracketsClose);
    else if (first == '(')
        token->setTokenType(Token::Type::ParenthesesOpen);
    else if (first == ')')
        token->setTokenType(Token::Type::ParenthesesClose);
    else if (first == ':')
        token->setTokenType(Token::Type::Colon);
    else if (first == ';')
        token->setTokenType(Token::Type::SemiColon);
    else if (first == ',')
        token->setTokenType(Token::Type::Comma);
    else if (first == '<') {
        if (source->peekNextChar() == '=') {
            source->getNextChar();
            token->setTokenType(Token::Type::LessEq);
        } else
            token->setTokenType(Token::Type::Less);
    } else if (first == '>') {
        if (source->peekNextChar() == '=') {
            source->getNextChar();
            token->setTokenType(Token::Type::MoreEq);
        } else
            token->setTokenType(Token::Type::More);
    } else if (first == '=') {
        if (source->peekNextChar() == '=') {
            source->getNextChar();
            token->setTokenType(Token::Type::Equal);
        } else
            token->setTokenType(Token::Type::Assign);
    } else if (first == '!') {
        if (source->peekNextChar() == '=') {
            source->getNextChar();
            token->setTokenType(Token::Type::NotEqual);
        } else
            token->setTokenType(Token::Type::BadType);
    } else if (first == '|') {
        if (source->peekNextChar() == '|') {
            source->getNextChar();
            token->setTokenType(Token::Type::LogicalOr);
        } else
            token->setTokenType(Token::Type::BadType);
    } else if (first == '&') {
        if (source->peekNextChar() == '&') {
            source->getNextChar();
            token->setTokenType(Token::Type::LogicalAnd);
        } else
            token->setTokenType(Token::Type::BadType);
    } else if (first == EOF)
        token->setTokenType(Token::Type::EofSymbol);
    else
        token->setTokenType(Token::Type::BadType);

    return token;
}

Scanner::Scanner(Source* source) : source(source), flag(false) {
    keyWords.insert(std::make_pair("return", Token::Type::Return));
    keyWords.insert(std::make_pair("if", Token::Type::If));
    keyWords.insert(std::make_pair("else", Token::Type::Else));
    keyWords.insert(std::make_pair("for", Token::Type::For));
    keyWords.insert(std::make_pair("unit", Token::Type::Unit));
    keyWords.insert(std::make_pair("int", Token::Type::Int));
    keyWords.insert(std::make_pair("V", Token::Type::V));
    keyWords.insert(std::make_pair("W", Token::Type::W));
    keyWords.insert(std::make_pair("A", Token::Type::A));
    keyWords.insert(std::make_pair("Om", Token::Type::Om));
    keyWords.insert(std::make_pair("S", Token::Type::S));
    keyWords.insert(std::make_pair("C", Token::Type::C));
    keyWords.insert(std::make_pair("s", Token::Type::s));
    keyWords.insert(std::make_pair("J", Token::Type::J));
}

Scanner::~Scanner() {
    delete source;
}
