//
// Created by adam on 07.04.19.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE LexerTests
#include <boost/test/unit_test.hpp>
#include "../src/lexer/Scanner.h"
#include "../src/lexer/Source.h"
#include "../src/parser/Parser.h"

BOOST_AUTO_TEST_CASE(test1){
    std::string program = "int a(){}";
    std::stringstream input(program);

    auto* source = new Source(program, 1);
    auto* scanner = new Scanner(source);
    auto* parser = new Parser(scanner);

    parser->parseProgram();

    BOOST_CHECK(2 + 2 == 4);
}