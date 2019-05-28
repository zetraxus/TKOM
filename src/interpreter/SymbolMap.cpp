//
// Created by adam on 27.05.19.
//

#include <iostream>
#include "SymbolMap.h"

SymbolMap::SymbolMap() {}

void SymbolMap::insert(std::string name, std::unique_ptr<Val> value) {
    std::cout << "dodano " << std::endl;
    value->print();
    symbols.insert(std::make_pair(std::move(name), std::move(value)));
}

Val* SymbolMap::find(std::string name) {
    auto search = symbols.find(name);
    if(search != symbols.end())
        return (search->second).get();
    else
        return nullptr;
}

std::unique_ptr<Val> SymbolMap::replace(std::string name, std::unique_ptr<Val> value) {
    auto search = symbols.find(name);
    if(search != symbols.end()){
        std::unique_ptr<Val> ret (std::move(search->second));
        search->second = std::move(value);
        return std::move(ret);
    } else
        return nullptr;
}

size_t SymbolMap::getSize() {
    return symbols.size();
}

std::unique_ptr<Val> SymbolMap::remove(std::string name) {
    auto search = symbols.find(name);
    if(search != symbols.end()){
        auto ret = std::move(search->second);
        symbols.erase(search);
        return ret;
    }
    return nullptr;
}
