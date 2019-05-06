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
        auto* block = new Block();
        while ((current = scanner->getNextToken())->getTokenType() != Token::TokenType::CurlyBracketClose)
            block->addInstruction(parseInstruction());
        return block;
    } else
        throw std::runtime_error("TODO7");
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
            if (current->getTokenType() == Token::TokenType::SemiColon)
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
                if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Else){ // TODO now else block is obligatory
                    auto* elseBlock = parseBlock();
                    return new IfElse(expression, ifBlock, elseBlock);
                } else
                    throw std::runtime_error("TODO19");
            } else
                throw std::runtime_error("TODO20");
        } else
            throw std::runtime_error("TODO21");
    } else
        throw std::runtime_error("TODO22");
}

Expression* Parser::parseExpression() { //TODO
    auto* exp = new Expression();
    Expression* newExp;

    exp->setLeft(parseExpressionAnd());
    while (current->getTokenType() == Token::TokenType::LogicalOr){
        exp->setType(current->getTokenType());
        exp->setRight(parseExpressionAnd());

        newExp = new Expression;
        newExp->setLeft(exp);
        exp = newExp;
    }
    return exp->getRight() == nullptr ? exp->getLeft() : exp;
}

Expression* Parser::parseExpressionAnd() {
    auto* exp = new Expression();
    Expression* newExp;

    exp->setLeft(parseExpressionEq());
    while ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::LogicalAnd){
        exp->setType(current->getTokenType());
        exp->setRight(parseExpressionEq());

        newExp = new Expression;
        newExp->setLeft(exp);
        exp = newExp;
    }
    return exp->getRight() == nullptr ? exp->getLeft() : exp;
}

Expression* Parser::parseExpressionEq() {
    auto* exp = new Expression();
    Expression* newExp;

    exp->setLeft(parseExpressionLessMore());
    while ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Equal || current->getTokenType() == Token::TokenType::NotEqual){
        exp->setType(current->getTokenType());
        exp->setRight(parseExpressionLessMore());

        newExp = new Expression;
        newExp->setLeft(exp);
        exp = newExp;
    }
    return exp->getRight() == nullptr ? exp->getLeft() : exp;
}

Expression* Parser::parseExpressionLessMore() {
    auto* exp = new Expression();
    Expression* newExp;

    exp->setLeft(parseExpressionPar());
    while ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Less || current->getTokenType() == Token::TokenType::More || current->getTokenType() == Token::TokenType::LessEq || current->getTokenType() == Token::TokenType::MoreEq){
        exp->setType(current->getTokenType());
        exp->setRight(parseExpressionPar());

        newExp = new Expression;
        newExp->setLeft(exp);
        exp = newExp;
    }
    return exp->getRight() == nullptr ? exp->getLeft() : exp;
}

Expression* Parser::parseExpressionPar() {
    auto* exp = new Expression();
    if((current = scanner->getNextToken())->getTokenType() == Token::TokenType::ParenthesesOpen){
        exp->setType(current->getTokenType());
        exp->setLeft(parseExpression());
        if (current->getTokenType() != Token::TokenType::ParenthesesClose){
            throw std::runtime_error("TODO22.5");
        }
    } else
        exp->setOperation(parseOperation());

    return exp;
}

Operation* Parser::parseOperation() {
    auto* op = new Operation();
    Operation* newOp;

    op->setLeft(parseOperationMulDiv());
    while (current->getTokenType() == Token::TokenType::OpSum || current->getTokenType() == Token::TokenType::OpSub){
        current->getTokenType() == Token::TokenType::OpSum ? op->set_operator(Operation::Sum) : op->set_operator(Operation::Sub);
        op->setRight(parseOperationMulDiv());

        newOp = new Operation;
        newOp->setLeft(op);
        op = newOp;
    }
    return op->getRight() == nullptr ? op->getLeft() : op;
}

Operation* Parser::parseOperationMulDiv() {
    auto* op = new Operation;
    Operation* newOp;

    op->setLeft(parseOperationParIdVal());
    while ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::OpMul || current->getTokenType() == Token::TokenType::OpDiv){
        current->getTokenType() == Token::TokenType::OpMul ? op->set_operator(Operation::Mul) : op->set_operator(Operation::Div);
        op->setRight(parseOperationParIdVal());

        newOp = new Operation;
        newOp->setLeft(op);
        op = newOp;
    }
    return op->getRight() == nullptr ? op->getLeft() : op;
}

Operation* Parser::parseOperationParIdVal() { // TODO add value + unit (e.g. 10N)
    auto* op = new Operation;
    if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::ParenthesesOpen){
        op->set_operator(Operation::Par);
        op->setLeft(parseOperation());

        if (current->getTokenType() != Token::TokenType::ParenthesesClose){
            throw std::runtime_error("TODO23");
        }
    } else if(current->getTokenType() == Token::TokenType::Identifier || current->getTokenType() == Token::TokenType::Value){
        op->setType(current->getTokenType());
        op->setVal(current->getValue());
    } else
        throw std::runtime_error("TODO24");
    return op;
}

