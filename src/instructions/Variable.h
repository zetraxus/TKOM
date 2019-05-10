//
// Created by adam on 05.05.19.
//

#ifndef TKOM_VARIABLE_H
#define TKOM_VARIABLE_H


#include "../lexer/Token.h"
#include "Value.h"

class Variable {
public:
    enum Type {
        Id,
        Val,
    };

private:
    Type type;
    std::string name; // if type == id
    std::string positionInContainer; // (optional) if type == id
    Value* value; // if type == val

public:
    Variable();

    Variable(Value* value);

    Variable(const std::string& name);

    Variable(const std::string& name, const std::string& positionInContainer);

    void setName(const std::string& name);

    void setPositionInContainer(const std::string& positionInContainer);
};


#endif //TKOM_VARIABLE_H
