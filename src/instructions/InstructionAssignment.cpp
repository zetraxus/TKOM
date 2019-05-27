//
// Created by adam on 05.05.19.
//

#include "Operation.h"
#include "InstructionAssignment.h"

InstructionAssignment::InstructionAssignment(std::unique_ptr<Variable> variable, std::unique_ptr<Operation> operation) : variable(std::move(variable)),
                                                                                         operation(std::move(operation)) {}

void InstructionAssignment::execute() {

}

