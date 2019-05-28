#include <iostream>
#include "lexer/Source.h"
#include "lexer/Scanner.h"
#include "parser/Parser.h"
#include "interpreter/SymbolMap.h"
#include "interpreter/Interpreter.h"
#include <memory>

int main(int argc, char** argv) {
    std::unique_ptr<Source> source;
    std::unique_ptr<Scanner> scanner;
    std::unique_ptr<Parser> parser;
    std::unique_ptr<Interpreter> interpreter;

    if (argc > 1)
        try {
            source = std::make_unique<Source>(argv[1]);
        } catch (const std::runtime_error& error) {
            std::cout << "Source error: " << error.what() << std::endl;
            return -1;
        }
    else
        return -1;

    scanner = std::make_unique<Scanner>(std::move(source));
    parser = std::make_unique<Parser>(std::move(scanner));

    try {
        parser->parseProgram();
    } catch (const std::runtime_error& e) {
        std::cout << "Parser error: " << e.what() << " in:" << std::endl << "line: "
                  << parser->getCurrent()->getStartPosition()->getLine() << std::endl << "position: "
                  << parser->getCurrent()->getStartPosition()->getPosition() << std::endl;
        return -1;
    }

    interpreter = std::make_unique<Interpreter>(std::move(parser));

    try{
        interpreter->execute();
    } catch(const std::runtime_error& e){
        std::cout << "Interpreter error: " << e.what() << std::endl;
    }

    return 0;
}