#include <iostream>
#include "lexer/Source.h"
#include "lexer/Scanner.h"

int main(int argc, char** argv) {
    Source* source;
    Scanner* scanner;

    if (argc > 1)
        try {
            source = new Source(argv[1]);
        } catch (const std::runtime_error& error) {
            std::cout << error.what() << std::endl;
            return -1;
        }

    scanner = new Scanner(source);

    try {
        scanner->preparedTokenList();
        scanner->printTokenList();
    } catch (const std::runtime_error& error) {
        std::cout << error.what() << std::endl;
        return -1;
    }

    return 0;
}