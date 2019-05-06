//
// Created by adam on 06.05.19.
//

#ifndef TKOM_OPERATION_H
#define TKOM_OPERATION_H


#include <string>
#include "../lexer/Token.h"

class Operation {
public:
    enum Operator{
        Sum, // +
        Sub, // -
        Mul, // *
        Div, // /
        Par, // ()
        Default, // TODO for test
    };

private:
    Token::TokenType type;
    Operation* left;
    Operation* right = nullptr;
    Operator _operator = Default;
    std::string val; // if type == identifier || type == value

public:
    Operation();

    void setType(Token::TokenType type);

    void setLeft(Operation* left);

    void setRight(Operation* right);

    void set_operator(Operator _operator);

    void setVal(const std::string& val);


    //TODO all getters needed only to debug, should be deleted it in release

    Token::TokenType getType() const;

    Operation* getLeft() const;

    Operation* getRight() const;

    Operator get_operator() const;

    const std::string& getVal() const;
};


#endif //TKOM_OPERATION_H
