#include <iostream>
#include "lexer/Source.h"

int main(int argc, char** argv) {
    Source* source;

    if (argc > 1)
        source = new Source(argv[1]);

    source->getNextChar();


    return 0;
}