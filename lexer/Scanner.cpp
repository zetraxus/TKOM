//
// Created by adam on 06.04.19.
//

#include <iostream>
#include "Scanner.h"

const int LineFeed = 10;

Token* Scanner::getNextToken() {

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
        token->setTokenTypeAndValue(Token::TokenType::Identifier, result);

    return token;
}

Token* Scanner::getNumberToken(int firstChar) {
    Token* token = new Token(new Position(*(source->getCurrentPosition())));

    std::string result;
    result += (char) firstChar;

    while (isdigit(source->peekNextChar()))
        result += source->getNextChar();

    token->setTokenTypeAndValue(Token::TokenType::Value, result);

    return token;
}

Token* Scanner::getOperatorToken(int firstChar) {
    Token* token = new Token(new Position(*(source->getCurrentPosition())));
    std::string result;
    result += (char) firstChar;

    char first = (char) firstChar;
    if (first == '*')
        token->setTokenType(Token::TokenType::OpMul);
    else if (first == '/')
        token->setTokenType(Token::TokenType::OpDiv);
    else if (first == '+')
        token->setTokenType(Token::TokenType::OpSum);
    else if (first == '-')
        token->setTokenType(Token::TokenType::OpSub);
    else if (first == '{')
        token->setTokenType(Token::TokenType::BracketOpen);
    else if (first == '}')
        token->setTokenType(Token::TokenType::BracketClose);
    else if (first == '(')
        token->setTokenType(Token::TokenType::ParenthesesOpen);
    else if (first == ')')
        token->setTokenType(Token::TokenType::ParenthesesClose);
    else if (first == ':')
        token->setTokenType(Token::TokenType::Colon);
    else if (first == ';')
        token->setTokenType(Token::TokenType::SemiColon);
    else if (first == '<') {
        if (source->peekNextChar() == '=') {
            source->getNextChar();
            token->setTokenType(Token::TokenType::LessEq);
        } else
            token->setTokenType(Token::TokenType::Less);
    } else if (first == '>') {
        if (source->peekNextChar() == '=') {
            source->getNextChar();
            token->setTokenType(Token::TokenType::MoreEq);
        } else
            token->setTokenType(Token::TokenType::More);
    } else if (first == '=') {
        if (source->peekNextChar() == '=') {
            source->getNextChar();
            token->setTokenType(Token::TokenType::Equal);
        } else
            token->setTokenType(Token::TokenType::Assign);
    } else if (first == '!') {
        if (source->peekNextChar() == '=') {
            source->getNextChar();
            token->setTokenType(Token::TokenType::NotEqual);
        } else
            token->setTokenType(Token::TokenType::BadType);
    } else if (first == '|') {
        if (source->peekNextChar() == '|') {
            source->getNextChar();
            token->setTokenType(Token::TokenType::LogicalOr);
        } else
            token->setTokenType(Token::TokenType::BadType);
    } else if (first == '&') {
        if (source->peekNextChar() == '&') {
            source->getNextChar();
            token->setTokenType(Token::TokenType::LogicalAnd);
        } else
            token->setTokenType(Token::TokenType::BadType);
    } else if (first == EOF)
        token->setTokenType(Token::TokenType::EofSymbol);
    else
        token->setTokenType(Token::TokenType::BadType);

    return token;
}

Scanner::Scanner(Source* source) : source(source) {
    keyWords.insert(std::make_pair("return", Token::TokenType::Return));
    keyWords.insert(std::make_pair("if", Token::TokenType::If));
    keyWords.insert(std::make_pair("else", Token::TokenType::Else));
    keyWords.insert(std::make_pair("for", Token::TokenType::For));
    keyWords.insert(std::make_pair("unit", Token::TokenType::Unit));
    keyWords.insert(std::make_pair("int", Token::TokenType::Int));
    keyWords.insert(std::make_pair("V", Token::TokenType::V));
    keyWords.insert(std::make_pair("W", Token::TokenType::W));
    keyWords.insert(std::make_pair("A", Token::TokenType::A));
    keyWords.insert(std::make_pair("Om", Token::TokenType::Om));
    keyWords.insert(std::make_pair("S", Token::TokenType::S));
    keyWords.insert(std::make_pair("C", Token::TokenType::C));
    keyWords.insert(std::make_pair("s", Token::TokenType::s));
    keyWords.insert(std::make_pair("J", Token::TokenType::J));
}

Scanner::~Scanner() {
    delete source;
}

void Scanner::printTokenList() {
    for (size_t i = 0; i < tokenList.size(); ++i) {
        std::cout << tokenList[i]->getTokenType() << " " << tokenList[i]->getValue()
        << " $$ " << tokenList[i]->getStartPosition()->getLine() << " " <<
            tokenList[i]->getStartPosition()->getPosition() <<std::endl;
    }

}

void Scanner::preparedTokenList() {
    Token* next;

    do
        tokenList.push_back(next = getNextToken());
    while (next->getTokenType() != Token::TokenType::EofSymbol);

}
