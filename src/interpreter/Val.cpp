//
// Created by adam on 27.05.19.
//

#include <iostream>
#include "Val.h"

Val::Val(Token::Type type, size_t size, const std::vector<int>& values, const std::vector<Token::Type>& units)
    : type(type), size(size) {
    this->values = values;
    this->values.resize(size);
    this->units = units;
    this->units.resize(size);
    for(size_t i = values.size(); i < size; ++i){
        this->values[i] = 0;
        this->units[i] = Token::Value;
    }
}

Val::Val(Token::Type type, const std::vector<int>& values, const std::vector<Token::Type>& units) : type(type),
                                                                                                    size(values.size()),
                                                                                                    values(
                                                                                                        values),
                                                                                                    units(
                                                                                                        units) {}

Val::Val(Token::Type type, const std::vector<int>& values) : type(type), size(values.size()), values(values) {}

Val::Val(Token::Type type, int value) {
    this->type = type;
    this->values.emplace_back(value);
    this->units.emplace_back(Token::Value);
    this->size = 0;
}

Val::Val(Token::Type type, int value, Token::Type unit) {
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

const std::vector<int>& Val::getValues() const {
    return values;
}

const std::vector<Token::Type>& Val::getUnits() const {
    return units;
}

Val::Val(Token::Type type) : type(type), size(0) {}

std::pair<int, Token::Type> Val::getValue(int position) {
    if (position > size || position < 0)
        throw std::runtime_error("Bad array index");

    return std::make_pair(values[position], units[position]);
}

void Val::setValue(int position, std::pair<int, Token::Type> newValue) {
    if (position > size || position < 0)
        throw std::runtime_error("Bad array index");

    values[position] = newValue.first;
    units[position] = newValue.second;
}


void Val::setOnPosition(Token::Type type, int value, int position) {
    if (position > size || position < 0)
        throw std::runtime_error("Bad array index");
    this->values[position] = value;
    this->units[position] = type;
}
