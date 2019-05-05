//
// Created by adam on 04.05.19.
//

#include <iostream>
#include "Parser.h"
#include "../instructions/DefinitionOfFunction.h"

Parser::Parser(Scanner* scanner) : scanner(scanner) {}

Program* Parser::parseProgram() {
    Program* program = new Program();

    do{
        program->addFunction(parseFunction());

    } while(current->getTokenType() != Token::TokenType::EofSymbol); // TODO check it

    return program;
}

DefinitionOfFunction* Parser::parseFunction() {
    DefinitionOfFunction* function = new DefinitionOfFunction();

    if((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Int || current->getTokenType() == Token::TokenType::Unit){
        function->setReturnType(current->getTokenType());
        if((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Identifier){
            function->setIdentifier(current->getValue());
            if((current = scanner->getNextToken())->getTokenType() == Token::TokenType::ParenthesesOpen){
                bool flag = false; // last token was ',' and need read more arguments
                while((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Int || current->getTokenType() == Token::TokenType::Unit){

                    Variable* variable = new Variable();
                    variable->setType(current->getTokenType());
                    if((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Identifier){
                        variable->setName(current->getValue());
                        function->addArgument(variable);
                    } else
                        throw std::runtime_error ("TODO1");

                    if((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Comma){
                        flag = true;
                        continue;
                    }
                    else if(current->getTokenType() == Token::ParenthesesClose){
                        flag = false;
                        break;
                    }
                    else
                        throw std::runtime_error ("TODO2");
                }

                if(current->getTokenType() == Token::ParenthesesClose && !flag)
                    function->setBody(parseBlock());
                else
                    throw std::runtime_error ("TODO6");
            } else
                throw std::runtime_error ("TODO3");
        } else
            throw std::runtime_error ("TODO4");
    } else
        throw std::runtime_error ("TODO5");

    return function;
}

Block* Parser::parseBlock() {
    
}


