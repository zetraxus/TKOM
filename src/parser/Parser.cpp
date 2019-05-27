#include <memory>

#include <memory>

#include <memory>

#include <memory>

//
// Created by adam on 04.05.19.
//

#include <iostream>
#include "Parser.h"
#include "../instructions/InstructionDeclarationContainer.h"
#include "../instructions/InstructionCallFunction.h"
#include "../instructions/For.h"
#include "../instructions/InstructionDeclarationVariable.h"
#include "../instructions/InstructionAssignment.h"
#include "../instructions/InstructionReturnFromFunction.h"
#include "../instructions/IfElse.h"

const bool THROW = true;
const bool NOTTHROW = false;

Parser::Parser(std::unique_ptr<Scanner> scanner) : scanner(std::move(scanner)) {}

std::unique_ptr<Program> Parser::parseProgram() {
    std::unique_ptr <Program> program (new Program());

    while (GetAndCheckIfNotToken({Token::EofSymbol}, NOTTHROW))
        program->addFunction(parseFunction());

    return program;
}

std::unique_ptr<DefinitionOfFunction> Parser::parseFunction() {
    std::unique_ptr <DefinitionOfFunction> function (new DefinitionOfFunction());

    CheckToken({Token::Int, Token::Unit}, THROW);
    function->setReturnType(current->getTokenType());
    GetAndCheckToken({Token::Identifier}, THROW);
    function->setIdentifier(current->getValue());
    GetAndCheckToken({Token::ParenthesesOpen}, THROW);
    bool flag = false;
    while (GetAndCheckToken({Token::Int, Token::Unit}, NOTTHROW)) {
        std::unique_ptr<Variable> variable (new Variable());
        Token::Type type = current->getTokenType();

        if (GetAndCheckToken({Token::Identifier}, THROW)) {
            variable->setName(current->getValue());
            function->addArgument(type, std::move(variable));
        }
        if (GetAndCheckToken({Token::Comma}, NOTTHROW)) { // dont need to throw exception here
            flag = true;
            continue;
        } else if (CheckToken({Token::ParenthesesClose}, THROW)) {
            flag = false;
            break;
        }
    }
    CheckToken({Token::ParenthesesClose}, THROW);
    if (!flag) {
        function->setBody(parseBlock());
        return function;
    } else
        throw std::runtime_error("Unexpected token.");
}

std::unique_ptr<Block> Parser::parseBlock() {
    GetAndCheckToken({Token::CurlyBracketOpen}, THROW);

    std::unique_ptr <Block> block (new Block());
    while (PeekAndCheckIfNotToken({Token::Type::CurlyBracketClose}, NOTTHROW))
        block->addInstruction(parseInstruction());
    current = scanner->getNextToken();
    return block;
}

std::unique_ptr<Instruction> Parser::parseDeclaration() {
    current = scanner->getNextToken();
    Token::Type type = current->getTokenType();
    GetAndCheckToken({Token::Identifier}, THROW);
    std::string name = current->getValue();
    if (GetAndCheckToken({Token::SquareBracketsOpen}, NOTTHROW)) {
        GetAndCheckToken({Token::Value}, THROW);
        std::string size = current->getValue();
        GetAndCheckToken({Token::SquareBracketsClose}, THROW);
        if (PeekAndCheckToken({Token::SemiColon}, NOTTHROW)) {
            current = scanner->getNextToken();
            return std::make_unique<InstructionDeclarationContainer> (type, name, size);
        } else if (PeekAndCheckToken({Token::CurlyBracketOpen}, THROW)) {
            std::unique_ptr <InstructionDeclarationContainer> instruction (new InstructionDeclarationContainer(type, name, size));
            bool flag;
            std::vector<Token::Type> types;
            std::vector<std::unique_ptr<Variable>> variables;
            parseArgumentList(types, variables, flag, Token::CurlyBracketClose);
            instruction->setInitialValues(types, variables);
            CheckToken({Token::CurlyBracketClose}, THROW);
            if (!flag) {
                GetAndCheckToken({Token::SemiColon}, THROW);
                return instruction;
            } else
                throw std::runtime_error("Unexpected token.");
        }

    } else if (CheckToken({Token::Type::SemiColon}, THROW))
        return std::make_unique<InstructionDeclarationVariable> (type, name);
}

std::unique_ptr<Instruction> Parser::parseFunctionCall() {
    std::string name = current->getValue();
    std::unique_ptr <InstructionCallFunction> instruction (new InstructionCallFunction(name));
    bool flag;
    std::vector<Token::Type> types;
    std::vector<std::unique_ptr<Variable>> variables;
    parseArgumentList(types, variables, flag, Token::ParenthesesClose);
    instruction->setArguments(types, std::move(variables));
    CheckToken({Token::ParenthesesClose}, THROW);
    if (!flag) {
        GetAndCheckToken({Token::SemiColon}, THROW);
        return instruction;
    } else
        throw std::runtime_error("Unexpected token.");
}

std::unique_ptr<Instruction> Parser::parseAssignment() {
    std::unique_ptr <Variable> variable = parseVariable();
    GetAndCheckToken({Token::Assign}, THROW);
    std::unique_ptr <InstructionAssignment> instruction (new InstructionAssignment(std::move(variable), std::move(parseOperation())));
    GetAndCheckToken({Token::SemiColon}, THROW);
    return instruction;
}

std::unique_ptr<Instruction> Parser::parseLoopFor() {
    GetAndCheckToken({Token::ParenthesesOpen}, THROW);
    GetAndCheckToken({Token::Int, Token::Unit}, THROW);
    Token::Type type = current->getTokenType();
    GetAndCheckToken({Token::Identifier}, THROW);
    std::string name = current->getValue();
    GetAndCheckToken({Token::Colon}, THROW);
    GetAndCheckToken({Token::Identifier}, THROW);
    std::string identifier = current->getValue();
    GetAndCheckToken({Token::ParenthesesClose}, THROW);

    std::unique_ptr <For> instruction (new For(type, name, identifier));
    instruction->setBody(parseBlock());
    return instruction;
}

std::unique_ptr<Instruction> Parser::parseReturnInstruction() {
    current = scanner->getNextToken();
    std::unique_ptr <Variable> variable = parseVariable();
    GetAndCheckToken({Token::SemiColon}, THROW);
    return std::make_unique<InstructionReturnFromFunction> (std::move(variable));
}

std::unique_ptr<Instruction> Parser::parseIfInstruction() {
    GetAndCheckToken({Token::ParenthesesOpen}, THROW);
    std::unique_ptr <Expression> expression = parseExpression();
    GetAndCheckToken({Token::ParenthesesClose}, THROW);
    std::unique_ptr <Block> ifBlock = parseBlock();
    if (PeekAndCheckToken({Token::Else}, NOTTHROW)) {
        scanner->getNextToken();
        std::unique_ptr <Block> elseBlock = parseBlock();
        return std::make_unique<IfElse> (std::move(expression), std::move(ifBlock), std::move(elseBlock));
    }
    return std::make_unique<IfElse> (std::move(expression), std::move(ifBlock), nullptr);
}

std::unique_ptr<Instruction> Parser::parseInstruction() {
    if (PeekAndCheckToken({Token::Int, Token::Unit}, NOTTHROW)) {
        return parseDeclaration();
    } else if (PeekAndCheckToken({Token::Identifier}, NOTTHROW)) {
        current = scanner->getNextToken();
        if (PeekAndCheckToken({Token::ParenthesesOpen}, NOTTHROW))
            return parseFunctionCall();
        else
            return parseAssignment();
    } else if (GetAndCheckToken({Token::For}, NOTTHROW))
        return parseLoopFor();
    else if (CheckToken({Token::Return}, NOTTHROW))
        return parseReturnInstruction();
    else if (CheckToken({Token::If}, THROW))
        return parseIfInstruction();
}

std::unique_ptr<Expression> Parser::parseExpression() {
    std::unique_ptr<Expression> exp (new Expression());

    exp->addExpression(parseExpressionAnd());
    while (PeekAndCheckToken({Token::LogicalOr}, NOTTHROW)) {
        current = scanner->getNextToken();
        exp->setType(current->getTokenType());
        exp->addExpression(parseExpressionAnd());
    }

    return exp;
}

std::unique_ptr<Expression> Parser::parseExpressionAnd() {
    std::unique_ptr<Expression> exp (new Expression());

    exp->addExpression(parseExpressionEq());
    while (PeekAndCheckToken({Token::LogicalAnd}, NOTTHROW)) {
        current = scanner->getNextToken();
        exp->setType(current->getTokenType());
        exp->addExpression(parseExpressionEq());
    }

    return exp;
}

std::unique_ptr<Expression> Parser::parseExpressionEq() {
    std::unique_ptr<Expression> exp (new Expression());

    exp->addExpression(parseExpressionLessMore());
    while (PeekAndCheckToken({Token::Equal, Token::NotEqual}, NOTTHROW)) {
        current = scanner->getNextToken();
        exp->setType(current->getTokenType());
        exp->addExpression(parseExpressionLessMore());
    }

    return exp;
}

std::unique_ptr<Expression> Parser::parseExpressionLessMore() {
    std::unique_ptr<Expression> exp (new Expression());

    exp->addExpression(parseExpressionPar());
    while (PeekAndCheckToken({Token::Less, Token::More, Token::LessEq, Token::MoreEq}, NOTTHROW)) {
        current = scanner->getNextToken();
        exp->setType(current->getTokenType());
        exp->addExpression(parseExpressionPar());
    }

    return exp;
}

std::unique_ptr<Expression> Parser::parseExpressionPar() {
    std::unique_ptr<Expression> exp (new Expression());

    if (PeekAndCheckToken({Token::ParenthesesOpen}, NOTTHROW)) {
        current = scanner->getNextToken();
        exp->setType(current->getTokenType());
        exp->addExpression(parseExpression());
        GetAndCheckToken({Token::ParenthesesClose}, THROW);
    } else
        exp->setOperation(parseOperation());

    return exp;
}

std::unique_ptr<Operation> Parser::parseOperation() {
    std::unique_ptr<Operation> op (new Operation());

    op->addOperation(parseOperationMulDiv());
    while (PeekAndCheckToken({Token::OpSum, Token::OpSub}, NOTTHROW)) {
        current = scanner->getNextToken();
        current->getTokenType() == Token::Type::OpSum ? op->set_operator(Operation::Sum) : op->set_operator(
            Operation::Sub);
        op->addOperation(parseOperationMulDiv());
    }

    return op;
}

std::unique_ptr<Operation> Parser::parseOperationMulDiv() {
    std::unique_ptr<Operation> op (new Operation());

    op->addOperation(parseOperationParIdVal());
    while (PeekAndCheckToken({Token::OpMul, Token::OpDiv}, NOTTHROW)) {
        current = scanner->getNextToken();
        current->getTokenType() == Token::Type::OpMul ? op->set_operator(Operation::Mul) : op->set_operator(
            Operation::Div);
        op->addOperation(parseOperationParIdVal());
    }

    return op;
}

std::unique_ptr<Operation> Parser::parseOperationParIdVal() {
    std::unique_ptr<Operation> op (new Operation());

    if (PeekAndCheckToken({Token::ParenthesesOpen}, NOTTHROW)) {
        current = scanner->getNextToken();
        op->set_operator(Operation::Par);
        op->addOperation(parseOperation());
        GetAndCheckToken({Token::ParenthesesClose}, THROW);
    } else if (PeekAndCheckToken({Token::Identifier, Token::Value}, NOTTHROW)) {
        current = scanner->getNextToken();
        op->setVariable(parseVariable());
    }

    return op;
}

std::unique_ptr<Variable> Parser::parseVariable() {
    if (CheckToken({Token::Identifier}, NOTTHROW)) {
        std::string id = current->getValue();
        if (PeekAndCheckToken({Token::SquareBracketsOpen}, NOTTHROW)) {
            current = scanner->getNextToken();
            GetAndCheckToken({Token::Value}, THROW);
            std::string position = current->getValue();
            GetAndCheckToken({Token::SquareBracketsClose}, THROW);
            return std::make_unique<Variable> (id, position);
        } else
            return std::make_unique<Variable> (id, current->getValue()); // todo check it
    } else if (CheckToken({Token::Value}, THROW)) {
        std::string value = current->getValue();
        if ((peeked = scanner->peekNextToken())->isUnitType()) {
            current = scanner->getNextToken();
            return std::make_unique<Variable> (std::make_unique<Value>(current->getTokenType(), value)); // e.g Value(A, 10)
        } else
            return std::make_unique<Variable> (std::make_unique<Value>(current->getTokenType(), value)); // e.g. Value(Value, 10)
    }
}

std::shared_ptr<Token> Parser::getCurrent() const {
    return current;
}

void Parser::parseArgumentList(std::vector<Token::Type>& types, std::vector<std::unique_ptr<Variable>>& variables, bool& flag, Token::Type endListSymbol) {
    current = scanner->getNextToken();
    flag = false; // last token was ',' and need read more arguments
    while (GetAndCheckToken({Token::Identifier, Token::Value}, NOTTHROW)) {
        types.emplace_back(current->getTokenType());
        variables.emplace_back(parseVariable());

        if (GetAndCheckToken({Token::Type::Comma}, NOTTHROW)) {
            flag = true;
            continue;
        } else if (CheckToken({endListSymbol}, THROW)) {
            flag = false;
            break;
        }
    }
}

bool Parser::CheckToken(std::initializer_list<Token::Type> list, bool isIf) {
    for (auto token : list) {
        if (current->getTokenType() == token)
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
    for (auto token : list) {
        if (peeked->getTokenType() == token)
            return true;
    }
    return isIf ? throw std::runtime_error("Unexpected token.") : false;
}

bool Parser::CheckIfNotToken(std::initializer_list<Token::Type> list, bool isIf) {
    for (auto token : list) {
        if (current->getTokenType() == token)
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
    for (auto token : list) {
        if (peeked->getTokenType() == token)
            return isIf ? throw std::runtime_error("Unexpected token.") : false;
    }
    return true;
}