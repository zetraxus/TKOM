//
// Created by adam on 05.05.19.
//

#ifndef TKOM_INSTUCTIONASSIGNMENT_H
#define TKOM_INSTUCTIONASSIGNMENT_H


#include <string>
#include "Instruction.h"
#include "Operation.h"
#include <memory>

class InstructionAssignment : public Instruction {
    std::unique_ptr<Variable> variable;
    std::unique_ptr<Operation> operation;
public:
    InstructionAssignment(std::unique_ptr<Variable> variable, std::unique_ptr<Operation> operation);
};


#endif //TKOM_INSTUCTIONASSIGNMENT_H
