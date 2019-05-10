#include <iostream>
#include "lexer/Source.h"
#include "lexer/Scanner.h"
#include "parser/Parser.h"

int main(int argc, char** argv) {
    Source* source;
    Scanner* scanner;
    Parser* parser;

    if (argc > 1)
        try {
            source = new Source(argv[1]);
        } catch (const std::runtime_error& error) {
            std::cout << error.what() << std::endl;
            return -1;
        }
    else
        return -1;

    scanner = new Scanner(source);
    parser = new Parser(scanner);

    try {
        parser->parseProgram();
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << " in:" << std::endl << "line: "
                  << parser->getCurrent()->getStartPosition()->getLine() << std::endl << "position: "
                  << parser->getCurrent()->getStartPosition()->getPosition() << std::endl;
        return -1;
    }

    return 0;
}