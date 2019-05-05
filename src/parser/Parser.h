//
// Created by adam on 04.05.19.
//

#ifndef TKOM_PARSER_H
#define TKOM_PARSER_H


#include "../lexer/Scanner.h"
#include "../instructions/DefinitionOfFunction.h"
#include "../instructions/Program.h"

class Parser {
    Scanner* scanner;
    Token* current;

public:
    Parser(Scanner* scanner);

    Program* parseProgram();

    DefinitionOfFunction* parseFunction();

    Block* parseBlock();

    Instruction* parseInstruction();
};


#endif //TKOM_PARSER_H
