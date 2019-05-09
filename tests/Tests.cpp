//
// Created by adam on 07.04.19.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE LexerTests
#include <boost/test/unit_test.hpp>
#include "../src/lexer/Scanner.h"
#include "../src/lexer/Source.h"
#include "../src/parser/Parser.h"

Parser* config(const std::string& program){
    std::stringstream input(program);

    auto* source = new Source(program, 1);
    auto* scanner = new Scanner(source);
    return new Parser(scanner);
}

BOOST_AUTO_TEST_CASE(SIMPLE_CORRECT_EXAMPLE){
    std::string program = "int a(){}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(SIMPLE_INCORRECT_EXAMPLE){
    std::string program = "int a(){a}";
    auto* parser = config(program);

    BOOST_CHECK_THROW(parser->parseProgram(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(TWO_FUNCTIONS){
    std::string program = "int a(){} int b(){}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(UNIT_RETURN_FUNCTION){
    std::string program = "unit a(){}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(DECLARATION_VARIABLE_INT){
    std::string program = "int a(){int b;}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(DECLARATION_VARIABLE_UNIT){
    std::string program = "int a(){unit b;}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(CALL_FUNCTION){
    std::string program = "int a(){ b();}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(RETURN_FROM_FUNCTION_WITH_INT_VALUE){
    std::string program = "int a(){return 5;}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(RETURN_FROM_FUNCTION_WITH_UNIT_VALUE){
    std::string program = "unit a(){return 5A;}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(RETURN_FROM_FUNCTION_WITH_VARIABLE){
    std::string program = "int a(){return b;}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(RETURN_FROM_FUNCTION_WITH_VARIABLE_IN_CONTAINER){
    std::string program = "int a(){return b[1];}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(IF_WITHOUT_ELSE){
    std::string program = "int a(){if(){}}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(IF_WITH_ELSE){
    std::string program = "int a(){if(){}else{}}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}


BOOST_AUTO_TEST_CASE(IF_WITH_AND_EXPRESSION){
    std::string program = "int a(){if(b && c){}}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(IF_WITH_OR_EXPRESSION){
    std::string program = "int a(){if(b || c){}}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(IF_WITH_LESS_EXPRESSION){
    std::string program = "int a(){if(b < c){}}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}


BOOST_AUTO_TEST_CASE(IF_WITH_LESS_EQUAL_EXPRESSION){
    std::string program = "int a(){if(b <= c){}}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(IF_WITH_MORE_EXPRESSION){
    std::string program = "int a(){if(b > c){}}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(IF_WITH_MORE_EQUAL_EXPRESSION){
    std::string program = "int a(){if(b >= c){}}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(IF_WITH_EQUAL_EXPRESSION){
    std::string program = "int a(){if(b == c){}}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(IF_WITH_NOT_EQUAL_EXPRESSION){
    std::string program = "int a(){if(b != c){}}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(IF_WITH_Parentheses_IN_EXPRESSION){
    std::string program = "int a(){if(b && (c || d)){}}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(FOOR_LOOP_UNIT){
    std::string program = "int a(){for(unit u : table){}}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(FOOR_LOOP_INT){
    std::string program = "int a(){for(int u : table){}}";
    auto* parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}