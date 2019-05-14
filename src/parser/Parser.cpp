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

const bool THROW = true;
const bool NOTTHROW = false;

Parser::Parser(Scanner* scanner) : scanner(scanner) {}

Program* Parser::parseProgram() {
    auto* program = new Program();

    while(GetAndCheckIfNotToken({Token::EofSymbol}, NOTTHROW))
        program->addFunction(parseFunction());

    return program;
}

DefinitionOfFunction* Parser::parseFunction() {
    auto* function = new DefinitionOfFunction();

    CheckToken({Token::Int, Token::Unit}, THROW);
    function->setReturnType(current->getTokenType());
    GetAndCheckToken({Token::Identifier}, THROW);
    function->setIdentifier(current->getValue());
    GetAndCheckToken({Token::ParenthesesOpen}, THROW);
    bool flag = false;
    while(GetAndCheckToken({Token::Int, Token::Unit}, NOTTHROW)){
        auto* variable = new Variable();
        Token::Type type = current->getTokenType();

        if(GetAndCheckToken({Token::Identifier}, THROW)){
            variable->setName(current->getValue());
            function->addArgument(type, variable);
        }
        if(GetAndCheckToken({Token::Comma}, NOTTHROW)){ // dont need to throw exception here
            flag = true;
            continue;
        } else if (CheckToken({Token::ParenthesesClose}, THROW)){
            flag = false;
            break;
        }
    }
    CheckToken({Token::ParenthesesClose}, THROW);
    if(!flag){
        function->setBody(parseBlock());
        return function;
    } else
        throw std::runtime_error("Unexpected token.");
}

Block* Parser::parseBlock() {
    GetAndCheckToken({Token::CurlyBracketOpen}, THROW);
    auto* block = new Block();
    while(PeekAndCheckIfNotToken({Token::Type::CurlyBracketClose}, NOTTHROW))
        block->addInstruction(parseInstruction());
    current = scanner->getNextToken();
    return block;
}

Instruction* Parser::parseDeclaration(){
    current = scanner->getNextToken();
    Token::Type type = current->getTokenType();
    GetAndCheckToken({Token::Identifier}, THROW);
    std::string name = current->getValue();
    if(GetAndCheckToken({Token::SquareBracketsOpen}, NOTTHROW)){
        GetAndCheckToken({Token::Value}, THROW);
        std::string size = current->getValue();
        GetAndCheckToken({Token::SquareBracketsClose}, THROW);
        if(PeekAndCheckToken({Token::SemiColon}, NOTTHROW)){
            current = scanner->getNextToken();
            return new InstructionDeclarationContainer(type, name, size);
        } else if(PeekAndCheckToken({Token::CurlyBracketOpen}, THROW)){
            auto* instruction = new InstructionDeclarationContainer(type, name, size);
            bool flag;
            std::vector<std::pair<Token::Type, Variable*> > argumentList = parseArgumentList(flag, Token::CurlyBracketClose);
            instruction->setInitialValues(argumentList);
            CheckToken({Token::CurlyBracketClose}, THROW);
            if(!flag){
                GetAndCheckToken({Token::SemiColon}, THROW);
                return instruction;
            } else
                throw std::runtime_error("Unexpected token.");
        }

    } else if(CheckToken({Token::Type::SemiColon}, THROW))
        return new InstructionDeclarationVariable(type, name);
}

Instruction* Parser::parseFunctionCall(){
    std::string name = current->getValue();
    auto* instruction = new InstructionCallFunction(name);
    bool flag;
    std::vector<std::pair<Token::Type, Variable*> > argumentList = parseArgumentList(flag, Token::ParenthesesClose);
    instruction->setArguments(argumentList);
    CheckToken({Token::ParenthesesClose}, THROW);
    if(!flag){
        GetAndCheckToken({Token::SemiColon}, THROW);
        return instruction;
    } else
        throw std::runtime_error("Unexpected token.");
}

Instruction* Parser::parseAssignment(){
    auto* variable = parseVariable();
    GetAndCheckToken({Token::Assign}, THROW);
    auto* instruction = new InstructionAssignment(variable, parseOperation());
    GetAndCheckToken({Token::SemiColon}, THROW);
    return instruction;
}

Instruction* Parser::parseLoopFor() {
    GetAndCheckToken({Token::ParenthesesOpen}, THROW);
    GetAndCheckToken({Token::Int, Token::Unit}, THROW);
    Token::Type type = current->getTokenType();
    GetAndCheckToken({Token::Identifier}, THROW);
    std::string name = current->getValue();
    GetAndCheckToken({Token::Colon}, THROW);
    GetAndCheckToken({Token::Identifier}, THROW);
    std::string identifier = current->getValue();
    GetAndCheckToken({Token::ParenthesesClose}, THROW);

    auto* instruction = new For(type, name, identifier);
    instruction->setBody(parseBlock());
    return instruction;
}

Instruction* Parser::parseReturnInstruction() {
    current = scanner->getNextToken();
    auto* variable = parseVariable();
    GetAndCheckToken({Token::SemiColon}, THROW);
    return new InstructionReturnFromFunction(variable);
}

Instruction* Parser::parseIfInstruction() {
    GetAndCheckToken({Token::ParenthesesOpen}, THROW);
    auto* expression = parseExpression();
    GetAndCheckToken({Token::ParenthesesClose}, THROW);
    auto* ifBlock = parseBlock();
    if(PeekAndCheckToken({Token::Else}, NOTTHROW)){
        scanner->getNextToken();
        auto* elseBlock = parseBlock();
        return new IfElse(expression, ifBlock, elseBlock);
    }
    return new IfElse(expression, ifBlock, nullptr);
}

Instruction* Parser::parseInstruction() {
    if(PeekAndCheckToken({Token::Int, Token::Unit}, NOTTHROW)){
        return parseDeclaration();
    } else if(PeekAndCheckToken({Token::Identifier}, NOTTHROW)){
        current = scanner->getNextToken();
        if(PeekAndCheckToken({Token::ParenthesesOpen}, NOTTHROW))
            return parseFunctionCall();
        else
            return parseAssignment();
    } else if(GetAndCheckToken({Token::For}, NOTTHROW))
        return parseLoopFor();
    else if(CheckToken({Token::Return}, NOTTHROW))
        return parseReturnInstruction();
    else if(CheckToken({Token::If}, THROW))
        return parseIfInstruction();
}

Expression* Parser::parseExpression() {
    auto* exp = new Expression();
    Expression* newExp;

    exp->setLeft(parseExpressionAnd());
    while (PeekAndCheckToken({Token::LogicalOr}, NOTTHROW)) {
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
    while (PeekAndCheckToken({Token::LogicalAnd}, NOTTHROW)) {
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
    while (PeekAndCheckToken({Token::Equal, Token::NotEqual}, NOTTHROW)) {
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
    while (PeekAndCheckToken({Token::Less, Token::More, Token::LessEq, Token::MoreEq}, NOTTHROW)) {
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
    if (PeekAndCheckToken({Token::ParenthesesOpen}, NOTTHROW)) {
        current = scanner->getNextToken();
        exp->setType(current->getTokenType());
        exp->setLeft(parseExpression());
        GetAndCheckToken({Token::ParenthesesClose}, THROW);
    } else
        exp->setOperation(parseOperation());

    return exp;
}

Operation* Parser::parseOperation() {
    auto* op = new Operation();
    Operation* newOp;

    op->setLeft(parseOperationMulDiv());
    while (PeekAndCheckToken({Token::OpSum, Token::OpSub}, NOTTHROW)) {
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
    while (PeekAndCheckToken({Token::OpMul, Token::OpDiv}, NOTTHROW)) {
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
    if(PeekAndCheckToken({Token::ParenthesesOpen}, NOTTHROW)){
        current = scanner->getNextToken();
        op->set_operator(Operation::Par);
        op->setLeft(parseOperation());
        GetAndCheckToken({Token::ParenthesesClose}, THROW);
    } else if(PeekAndCheckToken({Token::Identifier, Token::Value}, NOTTHROW)){
        current = scanner->getNextToken();
        op->setVariable(parseVariable());
    }

    return op;
}
//Variable* Parser::parseVariable(){
//    if(CheckToken({Token::Identifier}, NOTTHROW)){
//        std::string id = current->getValue();
//        PeekAndCheckToken({Token::SquareBracketsOpen}, THROW);
//        current = scanner->getNextToken();
//        GetAndCheckToken({Token::Value}, THROW);
//        std::string position = current->getValue();
//        GetAndCheckToken({Token::SquareBracketsClose}, THROW);
//        return new Variable(id, position);
//    } else if(CheckToken({Token::Value}, THROW)){
//        std::string value = current->getValue();
//        if ((peeked = scanner->peekNextToken())->isUnitType()) {
//            current = scanner->getNextToken();
//            return new Variable(new Value(current->getTokenType(), value)); // e.g Value(A, 10)
//        } else
//            return new Variable(new Value(current->getTokenType(), value)); // e.g. Value(Value, 10)
//    }
//}
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