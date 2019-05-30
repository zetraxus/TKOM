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

public:
    Variable();

    explicit Variable(std::unique_ptr <Value> value);

    explicit Variable(const std::string& name);

    Variable(const std::string& name, const std::string& positionInContainer);

    void setName(const std::string& name);

    void setPositionInContainer(const std::string& positionInContainer);

    Value* getValue();

    Type getType() const;

    const std::string& getName() const;

    const std::string& getPositionInContainer() const;
};

#endif //TKOM_VARIABLE_H
