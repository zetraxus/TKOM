//
// Created by adam on 27.05.19.
//

#include "SymbolMap.h"

SymbolMap::SymbolMap() {}

void SymbolMap::insert(std::string name, std::unique_ptr<Val> value) {
    symbols.insert(std::make_pair(std::move(name), std::move(value)));
}

Val* SymbolMap::find(std::string name) {
    auto search = symbols.find(name);
    if(search != symbols.end())
        return (search->second).get();
}

std::unique_ptr<Val> SymbolMap::replace(std::string name, std::unique_ptr<Val> value) {
    auto search = symbols.find(name);
    if(search != symbols.end()){
        std::unique_ptr<Val> ret (std::move(search->second));
        search->second = std::move(value);
        return std::move(ret);
    }
}
