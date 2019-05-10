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
                    Token::TokenType type = current->getTokenType();
                    if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Identifier) {
                        variable->setName(current->getValue());
                        function->addArgument(type, variable);
                    } else
                        throw std::runtime_error("1");

                    if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Comma) {
                        flag = true;
                        continue;
                    } else if (current->getTokenType() == Token::ParenthesesClose) {
                        flag = false;
                        break;
                    } else
                        throw std::runtime_error("2");
                }

                if (current->getTokenType() == Token::ParenthesesClose && !flag) {
                    function->setBody(parseBlock());
                    return function;
                } else
                    throw std::runtime_error("3");
            } else
                throw std::runtime_error("4");
        } else
            throw std::runtime_error("5");
    } else
        throw std::runtime_error("6");
}

Block* Parser::parseBlock() {
    if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::CurlyBracketOpen){
        auto* block = new Block();
        while ((peeked = scanner->peekNextToken())->getTokenType() != Token::TokenType::CurlyBracketClose)
            block->addInstruction(parseInstruction());
        current = scanner->getNextToken();
        return block;
    } else
        throw std::runtime_error("7");
}

Instruction* Parser::parseInstruction() {
    if((peeked = scanner->peekNextToken())->getTokenType() == Token::TokenType::Int || peeked->getTokenType() == Token::TokenType::Unit){ // declaration variable or container
        current = scanner->getNextToken();
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
                            throw std::runtime_error("8");
                    } else
                        throw std::runtime_error("9");
                } else
                    throw std::runtime_error("10");
            } else if(current->getTokenType() == Token::TokenType::SemiColon)
                return new InstructionDeclarationVariable(type, name);
            else
                throw std::runtime_error("11");
        } else
            throw std::runtime_error("12");
    } else if(peeked->getTokenType() == Token::TokenType::Identifier) {
        current = scanner->getNextToken();
        std::string name = current->getValue();
        if ((peeked = scanner->peekNextToken())->getTokenType() == Token::TokenType::ParenthesesOpen) { // function call
            current = scanner->getNextToken();
            auto* instruction = new InstructionCallFunction(name);
            bool flag = false; // last token was ',' and need read more arguments
            while ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Identifier) {
                instruction->addArgument(current->getTokenType(), parseVariable());
                if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Comma) {
                    flag = true;
                    continue;
                } else if (current->getTokenType() == Token::ParenthesesClose) {
                    flag = false;
                    break;
                } else
                    throw std::runtime_error("13");
            }
            if (current->getTokenType() == Token::ParenthesesClose && !flag) {
                if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::SemiColon)
                    return instruction;
                else
                    throw std::runtime_error("14");
            } else
                throw std::runtime_error("15");
        } else {
            auto* variable = parseVariable();
            if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Assign){
                auto* instruction = new InstructionAssignment(variable, parseOperation());
                if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::SemiColon)
                    return instruction;
                else
                    throw std::runtime_error("16");
            }
        }
    } else if((current = scanner->getNextToken())->getTokenType() == Token::TokenType::For){ //for
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
                                throw std::runtime_error("18");
                        } else
                            throw std::runtime_error("19");
                    } else
                        throw std::runtime_error("20");
                } else
                    throw std::runtime_error("21");
            } else
                throw std::runtime_error("22");
        } else
            throw std::runtime_error("23");
    } else if(current->getTokenType() == Token::TokenType::Return){ //return
        current = scanner->getNextToken();
        auto* variable = parseVariable();
        if ((current = scanner->getNextToken())->getTokenType() == Token::TokenType::SemiColon){
            return new InstructionReturnFromFunction(variable);
        } else
            throw std::runtime_error("23.1");
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
            } else
                throw std::runtime_error("25");
        } else
            throw std::runtime_error("26");
    } else
        throw std::runtime_error("27");
}

Expression* Parser::parseExpression() {
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
    auto* exp = new Expression();
    Expression* newExp;

    exp->setLeft(parseExpressionPar());
    while ((peeked = scanner->peekNextToken())->getTokenType() == Token::TokenType::Less || peeked->getTokenType() == Token::TokenType::More || peeked->getTokenType() == Token::TokenType::LessEq || peeked->getTokenType() == Token::TokenType::MoreEq){
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
    auto* exp = new Expression();
    if((peeked = scanner->peekNextToken())->getTokenType() == Token::TokenType::ParenthesesOpen){
        current = scanner->getNextToken();
        exp->setType(current->getTokenType());
        exp->setLeft(parseExpression());
        if ((current = scanner->getNextToken())->getTokenType() != Token::TokenType::ParenthesesClose)
            throw std::runtime_error("28");
    } else
        exp->setOperation(parseOperation());

    return exp;
}

Operation* Parser::parseOperation() {
    auto* op = new Operation();
    Operation* newOp;

    op->setLeft(parseOperationMulDiv());
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
    auto* op = new Operation;
    Operation* newOp;

    op->setLeft(parseOperationParIdVal());
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

Operation* Parser::parseOperationParIdVal() { // TODO add minus operator (e.g. -5)
    auto* op = new Operation;
    if ((peeked = scanner->peekNextToken())->getTokenType() == Token::TokenType::ParenthesesOpen){
        current = scanner->getNextToken();
        op->set_operator(Operation::Par);
        op->setLeft(parseOperation());

        if ((current = scanner->getNextToken())->getTokenType() != Token::TokenType::ParenthesesClose){
            throw std::runtime_error("29");
        }
    } else if((peeked = scanner->peekNextToken())->getTokenType() == Token::TokenType::Identifier || peeked->getTokenType() == Token::TokenType::Value) {
        current = scanner->getNextToken();
        op->setVariable(parseVariable());
    } //TODO what if else?

    return op;
}

Variable* Parser::parseVariable() {
    if(current->getTokenType() == Token::TokenType::Identifier){
        std::string id = current->getValue();
        if((peeked = scanner->peekNextToken())->getTokenType() == Token::TokenType::SquareBracketsOpen){
            current= scanner->getNextToken();
            if((current = scanner->getNextToken())->getTokenType() == Token::TokenType::Value){
                std::string position = current->getValue();
                if((current = scanner->getNextToken())->getTokenType() == Token::TokenType::SquareBracketsClose)
                    return new Variable(id, position);
                else
                    throw std::runtime_error("30");
            } else
                throw std::runtime_error("31");
        }
    } else if(current->getTokenType() == Token::TokenType::Value){
        std::string value = current->getValue();
        if((peeked = scanner->peekNextToken())->isUnitType()){
            current = scanner->getNextToken();
            return new Variable(new Value(current->getTokenType(), value)); // e.g Value(A, 10)
        } else
            return new Variable(new Value(current->getTokenType(), value)); // e.g. Value(Value, 10)
    } else
        throw std::runtime_error("32");
}

Token* Parser::getCurrent() const {
    return current;
}

