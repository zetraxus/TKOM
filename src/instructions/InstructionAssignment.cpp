//
// Created by adam on 05.05.19.
//

#include "Operation.h"
#include "InstructionAssignment.h"

InstructionAssignment::InstructionAssignment(Variable* variable, Operation* operation) : variable(variable),
                                                                                         operation(operation) {}

Operation* InstructionAssignment::getOperation() const {
    return operation;
}
