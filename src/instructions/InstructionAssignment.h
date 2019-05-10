//
// Created by adam on 05.05.19.
//

#ifndef TKOM_INSTUCTIONASSIGNMENT_H
#define TKOM_INSTUCTIONASSIGNMENT_H


#include <string>
#include "Instruction.h"
#include "Operation.h"

class InstructionAssignment : public Instruction {
    Variable* variable;
    Operation* operation;
public:
    InstructionAssignment(Variable* variable, Operation* operation);

    Operation* getOperation() const;
};


#endif //TKOM_INSTUCTIONASSIGNMENT_H
