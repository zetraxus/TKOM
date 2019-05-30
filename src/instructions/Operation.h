//
// Created by adam on 06.05.19.
//

#ifndef TKOM_OPERATION_H
#define TKOM_OPERATION_H


#include <string>
#include "../lexer/Token.h"
#include "Variable.h"
#include "../interpreter/SymbolMap.h"
#include <memory>
#include <vector>

typedef std::experimental::optional<Token::Type> optToken;
typedef std::pair<int, optToken> ValueType;

class Operation {
public:
    enum Operator {
        Sum, // +
        Sub, // -
        Mul, // *
        Div, // /
        Par, // ()
        LogMul, // &&
        LogSum, // ||
        L, // <
        LE, // <=
        M, // >
        ME, // >=
        E, // ==
        NE, // !=
    };

private:
    std::vector<std::unique_ptr<Operation>> operations;
    std::vector<Operator> operators;
//    Operator _operator;
    std::unique_ptr<Variable> variable;
    bool empty = false;

public:
    Operation();

    void addOperation(std::unique_ptr<Operation> next);

    void addOperators(Operator op);

    void setEmpty(bool empty);

    void setVariable(std::unique_ptr<Variable> variable);

//    void set_operator(Operator _operator);

    bool isEmpty() const;

    bool opEmpty(size_t id) const;

    ValueType calculate(SymbolMap& symbols);

    ValueType calculate(ValueType arg1, ValueType arg2, Operator op);

    Variable* getVariable();
};


#endif //TKOM_OPERATION_H
