//
// Created by adam on 27.05.19.
//

#include "Interpreter.h"

Interpreter::Interpreter(std::unique_ptr<Parser> parser) : parser(std::move(parser)) {}

void Interpreter::execute() {
    Program* program = parser->getParsedProgram();
    DefinitionOfFunction* main = program->getMain();

    main->getBlock()->execute(symbols);
}
