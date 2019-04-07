#include <iostream>
#include "lexer/Source.h"
#include "lexer/Scanner.h"

int main(int argc, char** argv) {
    Source* source;
    Scanner* scanner;

    if (argc > 1)
        source = new Source(argv[1]);

    scanner = new Scanner(source);

    scanner->getNextToken();
    scanner->getNextToken();
    scanner->getNextToken();


    return 0;
}