//
// Created by adam on 04.05.19.
//

#ifndef TKOM_PARSER_H
#define TKOM_PARSER_H


#include "../lexer/Scanner.h"
#include "../instructions/DefinitionOfFunction.h"
#include "../instructions/Program.h"
#include "../instructions/Expression.h"
#include "../instructions/Operation.h"

class Parser {
    Scanner* scanner;
    Token* current;
    Token* peeked;

public:
    Parser(Scanner* scanner);

    Token* getCurrent() const;

    std::vector<std::pair<Token::TokenType, Variable*> > parseArgumentList(bool& flag, Token::TokenType endListSymbol);

    Program* parseProgram();

    DefinitionOfFunction* parseFunction();

    Block* parseBlock();

    Instruction* parseInstruction();

    Expression* parseExpression();

    Expression* parseExpressionAnd();

    Expression* parseExpressionEq();

    Expression* parseExpressionLessMore();

    Expression* parseExpressionPar();

    Operation* parseOperation();

    Operation* parseOperationMulDiv();

    Operation* parseOperationParIdVal();

    Variable* parseVariable();
};


#endif //TKOM_PARSER_H
