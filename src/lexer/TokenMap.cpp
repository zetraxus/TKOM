//
// Created by adam on 10.04.19.
//

#include "TokenMap.h"

TokenMap::TokenMap() {
    tokens.insert(std::make_pair(Token::TokenType::Identifier, "Identifier"));
    tokens.insert(std::make_pair(Token::TokenType::Value, "value"));
    tokens.insert(std::make_pair(Token::TokenType::Int, "Int"));
    tokens.insert(std::make_pair(Token::TokenType::Unit, "Unit"));
    tokens.insert(std::make_pair(Token::TokenType::V, "V"));
    tokens.insert(std::make_pair(Token::TokenType::W, "W"));
    tokens.insert(std::make_pair(Token::TokenType::A, "A"));
    tokens.insert(std::make_pair(Token::TokenType::Om, "Om"));
    tokens.insert(std::make_pair(Token::TokenType::S, "S"));
    tokens.insert(std::make_pair(Token::TokenType::C, "C"));
    tokens.insert(std::make_pair(Token::TokenType::s, "s"));
    tokens.insert(std::make_pair(Token::TokenType::J, "J"));
    tokens.insert(std::make_pair(Token::TokenType::OpMul, "*"));
    tokens.insert(std::make_pair(Token::TokenType::OpDiv, "/"));
    tokens.insert(std::make_pair(Token::TokenType::OpSum, "+"));
    tokens.insert(std::make_pair(Token::TokenType::OpSub, "-"));
    tokens.insert(std::make_pair(Token::TokenType::Return, "Return"));
    tokens.insert(std::make_pair(Token::TokenType::If, "If"));
    tokens.insert(std::make_pair(Token::TokenType::Else, "Else"));
    tokens.insert(std::make_pair(Token::TokenType::For, "For"));
    tokens.insert(std::make_pair(Token::TokenType::CurlyBracketOpen, "{"));
    tokens.insert(std::make_pair(Token::TokenType::CurlyBracketClose, "}"));
    tokens.insert(std::make_pair(Token::TokenType::SquareBracketsOpen, "["));
    tokens.insert(std::make_pair(Token::TokenType::SquareBracketsClose, "]"));
    tokens.insert(std::make_pair(Token::TokenType::ParenthesesOpen, "("));
    tokens.insert(std::make_pair(Token::TokenType::ParenthesesClose, ")"));
    tokens.insert(std::make_pair(Token::TokenType::Colon, ":"));
    tokens.insert(std::make_pair(Token::TokenType::SemiColon, ";"));
    tokens.insert(std::make_pair(Token::TokenType::Comma, ","));
    tokens.insert(std::make_pair(Token::TokenType::Less, "<"));
    tokens.insert(std::make_pair(Token::TokenType::More, ">"));
    tokens.insert(std::make_pair(Token::TokenType::LessEq, "<="));
    tokens.insert(std::make_pair(Token::TokenType::MoreEq, ">="));
    tokens.insert(std::make_pair(Token::TokenType::Equal, "=="));
    tokens.insert(std::make_pair(Token::TokenType::NotEqual, "!="));
    tokens.insert(std::make_pair(Token::TokenType::LogicalOr, "||"));
    tokens.insert(std::make_pair(Token::TokenType::LogicalAnd, "&&"));
    tokens.insert(std::make_pair(Token::TokenType::Assign, "="));
    tokens.insert(std::make_pair(Token::TokenType::EofSymbol, "EOF"));
    tokens.insert(std::make_pair(Token::TokenType::BadType, "Uknown"));
}

std::string TokenMap::findTokenDescription(Token::TokenType token) {
    return tokens.find(token) -> second;
}
