//
// Created by adam on 06.05.19.
//

#ifndef TKOM_OPERATION_H
#define TKOM_OPERATION_H


#include <string>
#include "../lexer/Token.h"
#include "Variable.h"

class Operation {
public:
    enum Operator {
        Sum, // +
        Sub, // -
        Mul, // *
        Div, // /
        Par, // ()
    };

public:
    void setVariable(Variable* variable);

private:
    Operation* left;
    Operation* right = nullptr;
    Operator _operator;
    Variable* variable;

public:
    Operation();

    void setLeft(Operation* left);

    void setRight(Operation* right);

    void set_operator(Operator _operator);

    Operation* getLeft() const;

    Operation* getRight() const;
};


#endif //TKOM_OPERATION_H
