//
// Created by adam on 05.05.19.
//

#include "Operation.h"
#include "InstructionAssignment.h"

InstructionAssignment::InstructionAssignment(std::unique_ptr<Variable> variable, std::unique_ptr<Operation> operation) : variable(std::move(variable)),
                                                                                         operation(std::move(operation)) {}

void InstructionAssignment::execute(SymbolMap& symbols) {
    std::string name = variable->getName();
    if(symbols.find(name) == nullptr)
        throw std::runtime_error("Variable " + name + " did not declarated.");

    std::pair<int, std::experimental::optional<Token::Type>> result = operation->calculate(symbols);
    std::cout << "Debug: " << result.first << std::endl;

}

