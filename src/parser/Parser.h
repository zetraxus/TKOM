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

    bool CheckToken(std::initializer_list<Token::Type> list, bool isIf);

    bool GetAndCheckToken(std::initializer_list<Token::Type> list, bool isIf);

    bool PeekAndCheckToken(std::initializer_list<Token::Type> list, bool isIf);

    bool CheckIfNotToken(std::initializer_list<Token::Type> list, bool isIf);

    bool GetAndCheckIfNotToken(std::initializer_list<Token::Type> list, bool isIf);

    bool PeekAndCheckIfNotToken(std::initializer_list<Token::Type> list, bool isIf);

    std::vector<std::pair<Token::Type, Variable*> > parseArgumentList(bool& flag, Token::Type endListSymbol);

    Program* parseProgram();

    DefinitionOfFunction* parseFunction();

    Block* parseBlock();

    Instruction* parseInstruction();

    Instruction* parseDeclaration();

    Instruction* parseFunctionCall();

    Instruction* parseAssignment();

    Instruction* parseLoopFor();

    Instruction* parseReturnInstruction();

    Instruction* parseIfInstruction();

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
