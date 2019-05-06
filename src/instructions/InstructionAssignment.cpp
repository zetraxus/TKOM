//
// Created by adam on 05.05.19.
//

#include "Operation.h"
#include "InstructionAssignment.h"

InstructionAssignment::InstructionAssignment(const std::string& identifier, Operation* operation) : identifier(
    identifier), operation(operation) {}
