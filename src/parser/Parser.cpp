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

const bool IF = true;
const bool WHILE = false;

Parser::Parser(Scanner* scanner) : scanner(scanner) {}

Program* Parser::parseProgram() {
    auto* program = new Program();

    while(GetAndCheckIfNotToken({Token::Type::EofSymbol}, WHILE))
        program->addFunction(parseFunction());

    return program;
}

DefinitionOfFunction* Parser::parseFunction() {
    auto* function = new DefinitionOfFunction();

    CheckToken({Token::Type::Int, Token::Type::Unit}, IF);
    function->setReturnType(current->getTokenType());
    GetAndCheckToken({Token::Type::Identifier}, IF);
    function->setIdentifier(current->getValue());
    GetAndCheckToken({Token::Type::ParenthesesOpen}, IF);
    bool flag = false;
    while(GetAndCheckToken({Token::Type::Int, Token::Type::Unit}, WHILE)){
        auto* variable = new Variable();
        Token::Type type = current->getTokenType();

        if(GetAndCheckToken({Token::Type::Identifier}, IF)){
            variable->setName(current->getValue());
            function->addArgument(type, variable);
        }
        if(GetAndCheckToken({Token::Type::Comma}, WHILE)){ // dont need to throw exception here
            flag = true;
            continue;
        } else if (CheckToken({Token::Type::ParenthesesClose}, IF)){
            flag = false;
            break;
        }
    }
    CheckToken({Token::Type::ParenthesesClose}, IF);
    if(!flag){
        function->setBody(parseBlock());
        return function;
    } else
        throw std::runtime_error("Unexpected token.");
}

Block* Parser::parseBlock() {
    GetAndCheckToken({Token::Type::CurlyBracketOpen}, IF);
    auto* block = new Block();
    while(PeekAndCheckIfNotToken({Token::Type::CurlyBracketClose}, WHILE))
        block->addInstruction(parseInstruction());
    current = scanner->getNextToken();
    return block;
}

Instruction* Parser::parseInstruction() {
    if ((peeked = scanner->peekNextToken())->getTokenType() == Token::Type::Int ||
        peeked->getTokenType() == Token::Type::Unit) { // declaration variable or container
        current = scanner->getNextToken();
        Token::Type type = current->getTokenType();
        if ((current = scanner->getNextToken())->getTokenType() == Token::Type::Identifier) {
            std::string name = current->getValue();
            if ((current = scanner->getNextToken())->getTokenType() == Token::Type::SquareBracketsOpen) {
                if ((current = scanner->getNextToken())->getTokenType() == Token::Type::Value) {
                    std::string size = current->getValue();
                    if ((current = scanner->getNextToken())->getTokenType() == Token::Type::SquareBracketsClose) {
                        if ((peeked = scanner->peekNextToken())->getTokenType() == Token::Type::SemiColon){
                            current = scanner->getNextToken();
                            return new InstructionDeclarationContainer(type, name, size);
                        } else if(peeked->getTokenType() == Token::Type::CurlyBracketOpen){
                            auto* instruction = new InstructionDeclarationContainer(type, name, size);
                            bool flag;
                            std::vector<std::pair<Token::Type, Variable*> > argumentList = parseArgumentList(flag, Token::CurlyBracketClose);
                            instruction->setInitialValues(argumentList);
                            if (current->getTokenType() == Token::CurlyBracketClose && !flag) {
                                if ((current = scanner->getNextToken())->getTokenType() == Token::Type::SemiColon)
                                    return instruction;
                                else
                                    throw std::runtime_error("7.1");
                            } else
                                throw std::runtime_error("7.2");
                        } else
                            throw std::runtime_error("8");
                    } else
                        throw std::runtime_error("9");
                } else
                    throw std::runtime_error("10");
            } else if (current->getTokenType() == Token::Type::SemiColon)
                return new InstructionDeclarationVariable(type, name);
            else
                throw std::runtime_error("11");
        } else
            throw std::runtime_error("12");
    } else if (peeked->getTokenType() == Token::Type::Identifier) {
        current = scanner->getNextToken();
        std::string name = current->getValue();
        if ((peeked = scanner->peekNextToken())->getTokenType() == Token::Type::ParenthesesOpen) { // function call
            auto* instruction = new InstructionCallFunction(name);
            bool flag;
            std::vector<std::pair<Token::Type, Variable*> > argumentList = parseArgumentList(flag, Token::ParenthesesClose);
            instruction->setArguments(argumentList);
            if (current->getTokenType() == Token::ParenthesesClose && !flag) {
                if ((current = scanner->getNextToken())->getTokenType() == Token::Type::SemiColon)
                    return instruction;
                else
                    throw std::runtime_error("14");
            } else
                throw std::runtime_error("15");
        } else {
            auto* variable = parseVariable();
            if ((current = scanner->getNextToken())->getTokenType() == Token::Type::Assign) {
                auto* instruction = new InstructionAssignment(variable, parseOperation());
                if ((current = scanner->getNextToken())->getTokenType() == Token::Type::SemiColon)
                    return instruction;
                else
                    throw std::runtime_error("16");
            }
        }
    } else if ((current = scanner->getNextToken())->getTokenType() == Token::Type::For) { //for
        if ((current = scanner->getNextToken())->getTokenType() == Token::Type::ParenthesesOpen) {
            if ((current = scanner->getNextToken())->getTokenType() == Token::Type::Int ||
                current->getTokenType() == Token::Type::Unit) {
                Token::Type type = current->getTokenType();
                if ((current = scanner->getNextToken())->getTokenType() == Token::Type::Identifier) {
                    std::string name = current->getValue();
                    if ((current = scanner->getNextToken())->getTokenType() == Token::Type::Colon) {
                        if ((current = scanner->getNextToken())->getTokenType() == Token::Type::Identifier) {
                            std::string identifier = current->getValue();
                            if ((current = scanner->getNextToken())->getTokenType() ==
                                Token::Type::ParenthesesClose) {
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
    } else if (current->getTokenType() == Token::Type::Return) { //return
        current = scanner->getNextToken();
        auto* variable = parseVariable();
        if ((current = scanner->getNextToken())->getTokenType() == Token::Type::SemiColon) {
            return new InstructionReturnFromFunction(variable);
        } else
            throw std::runtime_error("23.1");
    } else if (current->getTokenType() == Token::Type::If) { // if-else
        if ((current = scanner->getNextToken())->getTokenType() == Token::Type::ParenthesesOpen) {
            auto* expression = parseExpression();
            if ((current = scanner->getNextToken())->getTokenType() == Token::Type::ParenthesesClose) {
                auto* ifBlock = parseBlock();
                if ((scanner->peekNextToken())->getTokenType() == Token::Type::Else) {
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
    while ((peeked = scanner->peekNextToken())->getTokenType() == Token::Type::LogicalOr) {
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
    while ((peeked = scanner->peekNextToken())->getTokenType() == Token::Type::LogicalAnd) {
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
    while ((peeked = scanner->peekNextToken())->getTokenType() == Token::Type::Equal ||
           peeked->getTokenType() == Token::Type::NotEqual) {
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
    while ((peeked = scanner->peekNextToken())->getTokenType() == Token::Type::Less ||
           peeked->getTokenType() == Token::Type::More || peeked->getTokenType() == Token::Type::LessEq ||
           peeked->getTokenType() == Token::Type::MoreEq) {
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
    if ((peeked = scanner->peekNextToken())->getTokenType() == Token::Type::ParenthesesOpen) {
        current = scanner->getNextToken();
        exp->setType(current->getTokenType());
        exp->setLeft(parseExpression());
        if ((current = scanner->getNextToken())->getTokenType() != Token::Type::ParenthesesClose)
            throw std::runtime_error("28");
    } else
        exp->setOperation(parseOperation());

    return exp;
}

Operation* Parser::parseOperation() {
    auto* op = new Operation();
    Operation* newOp;

    op->setLeft(parseOperationMulDiv());
    while ((peeked = scanner->peekNextToken())->getTokenType() == Token::Type::OpSum ||
           peeked->getTokenType() == Token::Type::OpSub) {
        current = scanner->getNextToken();
        current->getTokenType() == Token::Type::OpSum ? op->set_operator(Operation::Sum) : op->set_operator(
            Operation::Sub);
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
    while ((peeked = scanner->peekNextToken())->getTokenType() == Token::Type::OpMul ||
           peeked->getTokenType() == Token::Type::OpDiv) {
        current = scanner->getNextToken();
        current->getTokenType() == Token::Type::OpMul ? op->set_operator(Operation::Mul) : op->set_operator(
            Operation::Div);
        op->setRight(parseOperationParIdVal());

        newOp = new Operation;
        newOp->setLeft(op);
        op = newOp;
    }
    return op->getRight() == nullptr ? op->getLeft() : op;
}

Operation* Parser::parseOperationParIdVal() {
    auto* op = new Operation;
    if ((peeked = scanner->peekNextToken())->getTokenType() == Token::Type::ParenthesesOpen) {
        current = scanner->getNextToken();
        op->set_operator(Operation::Par);
        op->setLeft(parseOperation());

        if ((current = scanner->getNextToken())->getTokenType() != Token::Type::ParenthesesClose) {
            throw std::runtime_error("29");
        }
    } else if ((peeked = scanner->peekNextToken())->getTokenType() == Token::Type::Identifier ||
               peeked->getTokenType() == Token::Type::Value) {
        current = scanner->getNextToken();
        op->setVariable(parseVariable());
    }

    return op;
}

Variable* Parser::parseVariable() {
    if (current->getTokenType() == Token::Type::Identifier) {
        std::string id = current->getValue();
        if ((peeked = scanner->peekNextToken())->getTokenType() == Token::Type::SquareBracketsOpen) {
            current = scanner->getNextToken();
            if ((current = scanner->getNextToken())->getTokenType() == Token::Type::Value) {
                std::string position = current->getValue();
                if ((current = scanner->getNextToken())->getTokenType() == Token::Type::SquareBracketsClose)
                    return new Variable(id, position);
                else
                    throw std::runtime_error("30");
            } else
                throw std::runtime_error("31");
        }
    } else if (current->getTokenType() == Token::Type::Value) {
        std::string value = current->getValue();
        if ((peeked = scanner->peekNextToken())->isUnitType()) {
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

std::vector<std::pair<Token::Type, Variable*> > Parser::parseArgumentList(bool& flag, Token::Type endListSymbol){
    std::vector<std::pair<Token::Type, Variable*> > argumentList;
    current = scanner->getNextToken();
    flag = false; // last token was ',' and need read more arguments
    while ((current = scanner->getNextToken())->getTokenType() == Token::Type::Identifier || current->getTokenType() == Token::Type::Value) {
        argumentList.emplace_back(current->getTokenType(), parseVariable());
        if ((current = scanner->getNextToken())->getTokenType() == Token::Type::Comma) {
            flag = true;
            continue;
        } else if (current->getTokenType() == endListSymbol) {
            flag = false;
            break;
        } else
            throw std::runtime_error("13");
    }

    return argumentList;
}

bool Parser::CheckToken(std::initializer_list<Token::Type> list, bool isIf) {
    for (auto token : list){
        if(current->getTokenType() == token)
            return true;
    }
    return isIf ? throw std::runtime_error("Unexpected token.") : false;
}

bool Parser::GetAndCheckToken(std::initializer_list<Token::Type> list, bool isIf) {
    current = scanner->getNextToken();
    return CheckToken(list, isIf);
}

bool Parser::PeekAndCheckToken(std::initializer_list<Token::Type> list, bool isIf) {
    peeked = scanner->peekNextToken();
    for (auto token : list){
        if(peeked->getTokenType() == token)
            return true;
    }
    return isIf ? throw std::runtime_error("Unexpected token.") : false;
}

bool Parser::CheckIfNotToken(std::initializer_list<Token::Type> list, bool isIf) {
    for (auto token : list){
        if(current->getTokenType() == token)
            return isIf ? throw std::runtime_error("Unexpected token.") : false;
    }
    return true;
}

bool Parser::GetAndCheckIfNotToken(std::initializer_list<Token::Type> list, bool isIf) {
    current = scanner->getNextToken();
    return CheckIfNotToken(list, isIf);
}

bool Parser::PeekAndCheckIfNotToken(std::initializer_list<Token::Type> list, bool isIf) {
    peeked = scanner->peekNextToken();
    for (auto token : list){
        if(peeked->getTokenType() == token)
            return isIf ? throw std::runtime_error("Unexpected token.") : false;
    }
    return true;
}
