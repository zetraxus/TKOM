//
// Created by adam on 05.05.19.
//

#include <iostream>
#include "Block.h"
#include "InstructionDeclarationVariable.h"
#include "InstructionDeclarationContainer.h"

Block::Block() {}

void Block::addInstruction(std::unique_ptr<Instruction> next) {
    instructions.emplace_back(std::move(next));
}

void Block::execute(SymbolMap& symbols) {
    std::vector <std::pair<std::string, std::unique_ptr<Val>>> replaced;

    for (auto& instruction : instructions) {
        if(dynamic_cast<InstructionDeclarationVariable*> (instruction.get())){
            std::string name = dynamic_cast<InstructionDeclarationVariable*> (instruction.get())->getIdentifier();
            if((symbols.find(name)) != nullptr)
                replaced.emplace_back(std::make_pair(name, std::move(symbols.remove(name))));
        } else if(dynamic_cast<InstructionDeclarationContainer*> (instruction.get())){
            std::string name = dynamic_cast<InstructionDeclarationContainer*> (instruction.get())->getIdentifier();
            if((symbols.find(name)) != nullptr)
                replaced.emplace_back(std::make_pair(name, std::move(symbols.remove(name))));
        }

        instruction->execute(symbols);

    }

    for(auto& pair : replaced)
        symbols.replace(pair.first, std::move(pair.second));
}
