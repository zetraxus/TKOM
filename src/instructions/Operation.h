//
// Created by adam on 06.05.19.
//

#ifndef TKOM_OPERATION_H
#define TKOM_OPERATION_H


#include <string>
#include "../lexer/Token.h"
#include "Variable.h"
#include <memory>
#include <vector>

class Operation {
public:
    enum Operator {
        Sum, // +
        Sub, // -
        Mul, // *
        Div, // /
        Par, // ()
    };

private:
    std::vector<std::unique_ptr<Operation>> operations;
    Operator _operator;
    std::unique_ptr<Variable> variable;

public:
    Operation();

    void addOperation(std::unique_ptr<Operation> next);

    void setVariable(std::unique_ptr<Variable> variable);

    void set_operator(Operator _operator);
};


#endif //TKOM_OPERATION_H
