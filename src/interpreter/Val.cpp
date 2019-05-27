//
// Created by adam on 27.05.19.
//

#include "Val.h"

Val::Val(Token::Type type, size_t size, const std::vector<unsigned int>& values, const std::vector<Token::Type>& units)
    : type(type), size(size), values(values), units(units) {}

Val::Val(Token::Type type, const std::vector<unsigned int>& values, const std::vector<Token::Type>& units) : type(type),
                                                                                                           size(values.size()),
                                                                                                           values(
                                                                                                               values),
                                                                                                           units(
                                                                                                               units) {}

Val::Val(Token::Type type, const std::vector<unsigned int>& values) : type(type), size(values.size()), values(values) {}

Val::Val(Token::Type type, unsigned value) {
    this->type = type;
    this->values.emplace_back(value);
    this->size = 0;
}

Val::Val(Token::Type type, unsigned value, Token::Type unit) {
    this->type = type;
    this->values.emplace_back(value);
    this->units.emplace_back(unit);
    this->size = 0;
}

Token::Type Val::getType() const {
    return type;
}

size_t Val::getSize() const {
    return size;
}

const std::vector<unsigned int>& Val::getValues() const {
    return values;
}

const std::vector<Token::Type>& Val::getUnits() const {
    return units;
}
