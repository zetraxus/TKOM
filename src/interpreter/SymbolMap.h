//
// Created by adam on 27.05.19.
//

#ifndef TKOM_SYMBOLMAP_H
#define TKOM_SYMBOLMAP_H

#include <unordered_map>
#include "Val.h"

class SymbolMap {
    std::unordered_map<std::string, std::unique_ptr<Val>> symbols;

public:
    SymbolMap();

    size_t getSize();

    void insert(std::string name, std::unique_ptr<Val> value);

    void update(std::string name, int positionInContainer, int value, Token::Type type);

    Val* find(std::string name);

    std::unique_ptr<Val> replace(std::string name, std::unique_ptr<Val> value);

    std::unique_ptr<Val> remove(std::string name);
};


#endif //TKOM_SYMBOLMAP_H
