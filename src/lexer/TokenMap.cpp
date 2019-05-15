//
// Created by adam on 10.04.19.
//

#include "TokenMap.h"

TokenMap::TokenMap() {
    tokens.insert(std::make_pair(Token::Type::Identifier, "Identifier"));
    tokens.insert(std::make_pair(Token::Type::Value, "value"));
    tokens.insert(std::make_pair(Token::Type::Int, "Int"));
    tokens.insert(std::make_pair(Token::Type::Unit, "Unit"));
    tokens.insert(std::make_pair(Token::Type::V, "V"));
    tokens.insert(std::make_pair(Token::Type::W, "W"));
    tokens.insert(std::make_pair(Token::Type::A, "A"));
    tokens.insert(std::make_pair(Token::Type::Om, "Om"));
    tokens.insert(std::make_pair(Token::Type::S, "S"));
    tokens.insert(std::make_pair(Token::Type::C, "C"));
    tokens.insert(std::make_pair(Token::Type::s, "s"));
    tokens.insert(std::make_pair(Token::Type::J, "J"));
    tokens.insert(std::make_pair(Token::Type::OpMul, "*"));
    tokens.insert(std::make_pair(Token::Type::OpDiv, "/"));
    tokens.insert(std::make_pair(Token::Type::OpSum, "+"));
    tokens.insert(std::make_pair(Token::Type::OpSub, "-"));
    tokens.insert(std::make_pair(Token::Type::Return, "Return"));
    tokens.insert(std::make_pair(Token::Type::If, "If"));
    tokens.insert(std::make_pair(Token::Type::Else, "Else"));
    tokens.insert(std::make_pair(Token::Type::For, "For"));
    tokens.insert(std::make_pair(Token::Type::CurlyBracketOpen, "{"));
    tokens.insert(std::make_pair(Token::Type::CurlyBracketClose, "}"));
    tokens.insert(std::make_pair(Token::Type::SquareBracketsOpen, "["));
    tokens.insert(std::make_pair(Token::Type::SquareBracketsClose, "]"));
    tokens.insert(std::make_pair(Token::Type::ParenthesesOpen, "("));
    tokens.insert(std::make_pair(Token::Type::ParenthesesClose, ")"));
    tokens.insert(std::make_pair(Token::Type::Colon, ":"));
    tokens.insert(std::make_pair(Token::Type::SemiColon, ";"));
    tokens.insert(std::make_pair(Token::Type::Comma, ","));
    tokens.insert(std::make_pair(Token::Type::Less, "<"));
    tokens.insert(std::make_pair(Token::Type::More, ">"));
    tokens.insert(std::make_pair(Token::Type::LessEq, "<="));
    tokens.insert(std::make_pair(Token::Type::MoreEq, ">="));
    tokens.insert(std::make_pair(Token::Type::Equal, "=="));
    tokens.insert(std::make_pair(Token::Type::NotEqual, "!="));
    tokens.insert(std::make_pair(Token::Type::LogicalOr, "||"));
    tokens.insert(std::make_pair(Token::Type::LogicalAnd, "&&"));
    tokens.insert(std::make_pair(Token::Type::Assign, "="));
    tokens.insert(std::make_pair(Token::Type::EofSymbol, "EOF"));
    tokens.insert(std::make_pair(Token::Type::BadType, "Uknown"));
}

std::string TokenMap::findTokenDescription(Token::Type token) {
    return tokens.find(token)->second;
}
