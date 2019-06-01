//
// Created by adam on 05.05.19.
//

#include <iostream>
#include "For.h"

For::For(Token::Type type, const std::string& itName, const std::string& container) : type(type), itName(itName),
                                                                                      container(container) {}

void For::setBody(std::unique_ptr<Block> body) {
    For::body = std::move(body);
}

void For::execute(SymbolMap& symbols) {
    auto val = symbols.find(container);
    for(size_t i = 0; i < val->getSize(); ++i){
        auto next = val->getValue(i);
        symbols.insert(itName, std::make_unique<Val>(next.second, next.first));
        body->execute(symbols);
        auto result = symbols.remove(itName);
        val->setValue(i, std::make_pair(result->getValue(0).first, result->getValue(0).second));
    }
}
