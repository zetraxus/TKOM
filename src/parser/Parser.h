//
// Created by adam on 04.05.19.
//

#ifndef TKOM_PARSER_H
#define TKOM_PARSER_H


#include <memory>
#include "../lexer/Scanner.h"
#include "../instructions/DefinitionOfFunction.h"
#include "../instructions/Program.h"
#include "../instructions/Expression.h"
#include "../instructions/Operation.h"

class Parser {
    std::unique_ptr<Scanner> scanner;
    std::shared_ptr<Token> current;
    std::shared_ptr<Token> peeked;

public:
    Parser(std::unique_ptr<Scanner> scanner);

    std::shared_ptr<Token> getCurrent() const;

    bool CheckToken(std::initializer_list<Token::Type> list, bool isIf);

    bool GetAndCheckToken(std::initializer_list<Token::Type> list, bool isIf);

    bool PeekAndCheckToken(std::initializer_list<Token::Type> list, bool isIf);

    bool CheckIfNotToken(std::initializer_list<Token::Type> list, bool isIf);

    bool GetAndCheckIfNotToken(std::initializer_list<Token::Type> list, bool isIf);

    bool PeekAndCheckIfNotToken(std::initializer_list<Token::Type> list, bool isIf);

    void parseArgumentList(std::vector<Token::Type>& types, std::vector<std::unique_ptr<Variable>>& variables, bool& flag, Token::Type endListSymbol);

    std::unique_ptr <Program> parseProgram();

    std::unique_ptr <DefinitionOfFunction> parseFunction();

    std::unique_ptr <Block> parseBlock();

    std::unique_ptr <Instruction> parseInstruction();

    std::unique_ptr <Instruction> parseDeclaration();

    std::unique_ptr <Instruction> parseFunctionCall();

    std::unique_ptr <Instruction> parseAssignment();

    std::unique_ptr <Instruction> parseLoopFor();

    std::unique_ptr <Instruction> parseReturnInstruction();

    std::unique_ptr <Instruction> parseIfInstruction();

    std::unique_ptr <Expression> parseExpression();

    std::unique_ptr <Expression> parseExpressionAnd();

    std::unique_ptr <Expression> parseExpressionEq();

    std::unique_ptr <Expression> parseExpressionLessMore();

    std::unique_ptr <Expression> parseExpressionPar();

    std::unique_ptr <Operation> parseOperation();

    std::unique_ptr <Operation> parseOperationMulDiv();

    std::unique_ptr <Operation> parseOperationParIdVal();

    std::unique_ptr <Variable> parseVariable();
};


#endif //TKOM_PARSER_H
