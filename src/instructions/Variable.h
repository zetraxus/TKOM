//
// Created by adam on 05.05.19.
//

#ifndef TKOM_VARIABLE_H
#define TKOM_VARIABLE_H


#include "../lexer/Token.h"
#include "Value.h"
#include <memory>
#include <experimental/optional>

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
    std::unique_ptr <Value> value; // if type == val
//    std::experimental::optional<std::unique_ptr<Value>> value;

public:
    Variable();

    Variable(std::unique_ptr <Value> value);

    Variable(const std::string& name);

    Variable(const std::string& name, const std::string& positionInContainer);

    void setName(const std::string& name);

    void setPositionInContainer(const std::string& positionInContainer);
};


#endif //TKOM_VARIABLE_H
