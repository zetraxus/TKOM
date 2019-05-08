//
// Created by adam on 04.05.19.
//

#include <iostream>
#include "Parser.h"
#include "../instructions/DefinitionOfFunction.h"
#include "../instructions/InstructionAssignment.h"
#include "../instructions/InstructionDeclarationContainer.h"
#include "../instructions/InstructionDeclarationVariable.h"
#include "../instructions/InstructionCallFunction.h"
#include "../instructions/For.h"
#include "../instructions/InstructionReturnFromFunction.h"
#include "../instructions/Expression.h"
#include "../instructions/IfElse.h"

Parser::Parser(Scanner* scanner) : scanner(scanner) {}

Program* Parser::parseProgram() {
    auto* program = new Program();

    while ((current = scanner->getNextToken())->getTokenType() != Token::TokenType::EofSymbol)
        program->addFunction(parseFunction());

    return program;
}

DefinitionOfFunction* Parser::parseFunction() {
    auto* function = new DefinitionOfFunction();

    if (current->getTokenType() == Token::TokenType::Int ||
        current->getTokenType() == Token::TokenType::Unit) {
        function->setReturnType(current->getTokenType());
        if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Identifier) {
            function->setIdentifier(current->getValue());
            if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::ParenthesesOpen) {
                bool flag = false; // last token was ',' and need read more arguments
                while ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Int ||
                       current->getTokenType() == Token::TokenType::Unit) {

                    auto* variable = new Variable();
                    variable->setType(current->getTokenType());
                    if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Identifier) {
                        variable->setName(current->getValue());
                        function->addArgument(variable);
                    } else
                        throw std::runtime_error("TODO1");

                    if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Comma) {
                        flag = true;
                        continue;
                    } else if (current->getTokenType() == Token::ParenthesesClose) {
                        flag = false;
                        break;
                    } else
                        throw std::runtime_error("TODO2");
                }

                if (current->getTokenType() == Token::ParenthesesClose && !flag) {
                    function->setBody(parseBlock());
                    return function;
                } else
                    throw std::runtime_error("TODO3");
            } else
                throw std::runtime_error("TODO4");
        } else
            throw std::runtime_error("TODO5");
    } else
        throw std::runtime_error("TODO6");
}

Block* Parser::parseBlock() {
    if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::CurlyBracketOpen){
        std::cout << "parsuje blok" << std::endl;
        auto* block = new Block();
        while ((current = scanner->getNextToken())->getTokenType() != Token::TokenType::CurlyBracketClose)
            block->addInstruction(parseInstruction());
        return block;
    } else{
        std::cout << "%" << current->getTokenType();
        throw std::runtime_error("TODO7");
    }
}

Instruction* Parser::parseInstruction() {
    if(current->getTokenType() == Token::TokenType::Int || current->getTokenType() == Token::TokenType::Unit){ // declaration variable or container
        Token::TokenType type = current->getTokenType();
        if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Identifier){
            std::string name = current->getValue();
            if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::SquareBracketsOpen){
                if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Value){
                    std::string size = current->getValue();
                    if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::SquareBracketsClose){
                        if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::SemiColon)
                            return new InstructionDeclarationContainer(type, name, size);
                        else
                            throw std::runtime_error("TODO8");
                    } else
                        throw std::runtime_error("TODO8");
                } else
                    throw std::runtime_error("TODO8");
            } else if(current->getTokenType() == Token::TokenType::SemiColon)
                return new InstructionDeclarationVariable(type, name);
            else
                throw std::runtime_error("TODO8");
        } else
            throw std::runtime_error("TODO9");
    } else if(current->getTokenType() == Token::TokenType::Identifier) {
        std::string name = current->getValue();
        if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::ParenthesesOpen) { // function call
            auto* instruction = new InstructionCallFunction(name);
            bool flag = false; // last token was ',' and need read more arguments
            while ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Identifier) { // TODO now container can't be an argument
                instruction->addArgument(current->getValue());
                if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Comma) {
                    flag = true;
                    continue;
                } else if (current->getTokenType() == Token::ParenthesesClose) {
                    flag = false;
                    break;
                } else
                    throw std::runtime_error("TODO10");
            }
            if (current->getTokenType() == Token::ParenthesesClose && !flag) {
                if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::SemiColon)
                    return instruction;
                else
                    throw std::runtime_error("TODO11");
            } else
                throw std::runtime_error("TODO12");
        } else if (current->getTokenType() == Token::TokenType::Assign){
            auto* instruction = new InstructionAssignment(name, parseOperation());
            if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::SemiColon)
                return instruction;
            else
                throw std::runtime_error("TODO12.1");
        }
        else
            throw std::runtime_error("TODO12.2");
    } else if(current->getTokenType() == Token::TokenType::For){ //for
        if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::ParenthesesOpen){
            if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Int || current->getTokenType() == Token::TokenType::Unit){
                Token::TokenType type = current->getTokenType();
                if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Identifier){
                    std::string name = current->getValue();
                    if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Colon){
                        if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Identifier){
                            std::string identifier = current->getValue();
                            if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::ParenthesesClose){
                                auto* instruction = new For(type, name, identifier);
                                instruction->setBody(parseBlock());
                                return instruction;
                            } else
                                throw std::runtime_error("TODO13");
                        } else
                            throw std::runtime_error("TODO14");
                    } else
                        throw std::runtime_error("TODO15");
                } else
                    throw std::runtime_error("TODO16");
            } else
                throw std::runtime_error("TODO17");
        } else
            throw std::runtime_error("TODO18");
    } else if(current->getTokenType() == Token::TokenType::Return){ //return
        if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Identifier)
            return new InstructionReturnFromFunction(0, current->getValue());
        else if(current->getTokenType() == Token::TokenType::Value)
            return new InstructionReturnFromFunction(1, current->getValue());
        else
            throw std::runtime_error("TODO18");
    } else if(current->getTokenType() == Token::TokenType::If){ // if-else
        if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::ParenthesesOpen){
            auto* expression = parseExpression();
            if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::ParenthesesClose){
                auto* ifBlock = parseBlock();
                if((scanner->peekNextToken())->getTokenType() == Token::TokenType::Else){
                    scanner->getNextToken();
                    auto* elseBlock = parseBlock();
                    return new IfElse(expression, ifBlock, elseBlock);
                } else
                    return new IfElse(expression, ifBlock, nullptr);
            } else{
                std::cout << current->getTokenType();
                throw std::runtime_error("TODO20");
            }
        } else
            throw std::runtime_error("TODO21");
    } else
        throw std::runtime_error("TODO22");
}

Expression* Parser::parseExpression() { //TODO fix it
    std::cout << "parseExpression" << std::endl;
    auto* exp = new Expression();
    Expression* newExp;

    exp->setLeft(parseExpressionAnd());
    while ((peeked = scanner->peekNextToken())->getTokenType() == Token::TokenType::LogicalOr){
        current = scanner->getNextToken();
        exp->setType(current->getTokenType());
        exp->setRight(parseExpressionAnd());

        newExp = new Expression;
        newExp->setLeft(exp);
        exp = newExp;
    }
    return exp->getRight() == nullptr ? exp->getLeft() : exp;
}

Expression* Parser::parseExpressionAnd() {
    std::cout << "parseExpressionAnd" << std::endl;
    auto* exp = new Expression();
    Expression* newExp;

    exp->setLeft(parseExpressionEq());
    while ((peeked = scanner->peekNextToken())->getTokenType() == Token::TokenType::LogicalAnd){
        current = scanner->getNextToken();
        exp->setType(current->getTokenType());
        exp->setRight(parseExpressionEq());

        newExp = new Expression;
        newExp->setLeft(exp);
        exp = newExp;
    }
    return exp->getRight() == nullptr ? exp->getLeft() : exp;
}

Expression* Parser::parseExpressionEq() {
    std::cout << "parseExpressionEq" << std::endl;
    auto* exp = new Expression();
    Expression* newExp;

    exp->setLeft(parseExpressionLessMore());
    while ((peeked = scanner->peekNextToken())->getTokenType() == Token::TokenType::Equal || peeked->getTokenType() == Token::TokenType::NotEqual){
        current = scanner->getNextToken();
        exp->setType(current->getTokenType());
        exp->setRight(parseExpressionLessMore());

        newExp = new Expression;
        newExp->setLeft(exp);
        exp = newExp;
    }
    return exp->getRight() == nullptr ? exp->getLeft() : exp;
}

Expression* Parser::parseExpressionLessMore() {
    std::cout << "parseExpressionLessMore" << std::endl;
    auto* exp = new Expression();
    Expression* newExp;

    exp->setLeft(parseExpressionPar());
    std::cout << "debug: " << scanner->peekNextToken()->getTokenType() << std::endl;
    while ((peeked = scanner->peekNextToken())->getTokenType() == Token::TokenType::Less || peeked->getTokenType() == Token::TokenType::More || peeked->getTokenType() == Token::TokenType::LessEq || peeked->getTokenType() == Token::TokenType::MoreEq){
        std::cout << "debug2: " << scanner->peekNextToken()->getTokenType() << std::endl;
        current = scanner->getNextToken();
        exp->setType(current->getTokenType());
        exp->setRight(parseExpressionPar());

        newExp = new Expression;
        newExp->setLeft(exp);
        exp = newExp;
    }
    return exp->getRight() == nullptr ? exp->getLeft() : exp;
}

Expression* Parser::parseExpressionPar() {
    std::cout << "parseExpressionPar" << std::endl;
    auto* exp = new Expression();
    if((peeked = scanner->peekNextToken())->getTokenType() == Token::TokenType::ParenthesesOpen){
        current = scanner->getNextToken();
        exp->setType(current->getTokenType());
        exp->setLeft(parseExpression());
        if ((current = scanner->getNextToken())->getTokenType() != Token::TokenType::ParenthesesClose){
            throw std::runtime_error("TODO22.5");
        }
    } else{
        std::cout << "kuku1" << std::endl;
        exp->setOperation(parseOperation());
        std::cout << "kuku2" << std::endl;
    }

    return exp;
}

Operation* Parser::parseOperation() {
    std::cout << "parseOperation" << std::endl;
    auto* op = new Operation();
    Operation* newOp;

    op->setLeft(parseOperationMulDiv());
    std::cout << "parseOperation2" << std::endl;
    while ((peeked = scanner->peekNextToken())->getTokenType() == Token::TokenType::OpSum || peeked->getTokenType() == Token::TokenType::OpSub){
        current = scanner->getNextToken();
        current->getTokenType() == Token::TokenType::OpSum ? op->set_operator(Operation::Sum) : op->set_operator(Operation::Sub);
        op->setRight(parseOperationMulDiv());

        newOp = new Operation;
        newOp->setLeft(op);
        op = newOp;
    }
    return op->getRight() == nullptr ? op->getLeft() : op;
}

Operation* Parser::parseOperationMulDiv() {
    std::cout << "parseOperationMulDiv" << std::endl;
    auto* op = new Operation;
    Operation* newOp;

    op->setLeft(parseOperationParIdVal());
    std::cout << "parseOperationMulDiv2" << std::endl;
    while ((peeked = scanner->peekNextToken())->getTokenType() == Token::TokenType::OpMul || peeked->getTokenType() == Token::TokenType::OpDiv){
        current = scanner->getNextToken();
        current->getTokenType() == Token::TokenType::OpMul ? op->set_operator(Operation::Mul) : op->set_operator(Operation::Div);
        op->setRight(parseOperationParIdVal());

        newOp = new Operation;
        newOp->setLeft(op);
        op = newOp;
    }
    return op->getRight() == nullptr ? op->getLeft() : op;
}

Operation* Parser::parseOperationParIdVal() {
    std::cout << "parseOperationParIdVal" << std::endl;
    auto* op = new Operation;
    if ((peeked = scanner->getNextToken())->getTokenType() == Token::TokenType::ParenthesesOpen){
        current = scanner->getNextToken();
        op->set_operator(Operation::Par);
        op->setLeft(parseOperation());

        if((scanner->peekNextToken())->isUnitType()){
            current = scanner->getNextToken();
            op->setUnitType(current->getTokenType());
        }
        if ((current = scanner->getNextToken())->getTokenType() != Token::TokenType::ParenthesesClose){
            throw std::runtime_error("TODO23");
        }
    } else if((peeked = scanner->peekNextToken())->getTokenType() == Token::TokenType::Identifier || peeked->getTokenType() == Token::TokenType::Value) {
        current = scanner->getNextToken();
        op->setType(current->getTokenType());
        op->setVal(current->getValue());
    }
//    } else{ // TODO fix it
//        std::cout << current->getTokenType();
//        throw std::runtime_error("TODO24");
//    }
    return op;
}

