//
// Created by adam on 10.05.19.
//

#include "Value.h"

Value::Value(Token::Type type, const std::string& value) : type(type), value(value) {}

std::string Value::getValue() const {
    return value;
}
