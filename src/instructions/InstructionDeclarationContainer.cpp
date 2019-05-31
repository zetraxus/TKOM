#include <utility>

//
// Created by adam on 05.05.19.
//

#include "InstructionDeclarationContainer.h"

InstructionDeclarationContainer::InstructionDeclarationContainer(Token::Type type, const std::string& identifier,
                                                                 const std::string& size) : type(type),
                                                                                            identifier(identifier),
                                                                                            size(size) {}

void InstructionDeclarationContainer::setInitialValues(std::string size, std::vector<Token::Type>& types, std::vector<std::unique_ptr<Variable>>& variables) {
    InstructionDeclarationContainer::size = std::move(size);
    InstructionDeclarationContainer::types = types;
    InstructionDeclarationContainer::variables = std::move(variables);
}

void InstructionDeclarationContainer::execute(SymbolMap& symbols) {
    std::vector<int> values;
    std::vector<Token::Type> typeList;
    for(auto& v : variables){
        int next = stoi(v->getValue()->getValue());
        typeList.emplace_back(v->getValue()->getType());
        values.emplace_back(next);
    }
    std::unique_ptr<Val> value (new Val(type, stoi(size), values, typeList));
    symbols.insert(identifier, std::move(value));
}

const std::string& InstructionDeclarationContainer::getIdentifier() const {
    return identifier;
}