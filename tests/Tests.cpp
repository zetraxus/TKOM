//
// Created by adam on 07.04.19.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE LexerTests
#include <boost/test/unit_test.hpp>
#include "../src/lexer/Scanner.h"
#include "../src/lexer/Source.h"
#include "../src/parser/Parser.h"
#include "../src/interpreter/SymbolMap.h"
#include "../src/interpreter/Interpreter.h"

std::unique_ptr<Parser> config(const std::string& program){
    std::stringstream input(program);

    std::unique_ptr<Source> source (new Source(program, 1));
    std::unique_ptr<Scanner> scanner (new Scanner(std::move(source)));
    return std::make_unique<Parser> (std::move(scanner));
}

std::unique_ptr<Interpreter> configInterpreter(const std::string& program){
    std::stringstream input(program);

    std::unique_ptr<Source> source (new Source(program, 1));
    std::unique_ptr<Scanner> scanner (new Scanner(std::move(source)));
    std::unique_ptr<Parser> parser (new Parser(std::move(scanner)));
    parser->parseProgram();

    return std::make_unique<Interpreter> (std::move(parser));
}

BOOST_AUTO_TEST_SUITE(INTERPRETER)

BOOST_AUTO_TEST_CASE(SYMBOLMAP_TEST_INSERT_AND_REPLACE){
    auto map = std::make_unique <SymbolMap>();
    auto a = std::make_unique<Val> (Token::Int, 10);
    auto b = std::make_unique<Val> (Token::Unit, 20, Token::A);
    auto c = std::make_unique<Val> (Token::Unit, 25, Token::W);
    auto newc = std::make_unique<Val> (Token::Unit, 30, Token::W);

    map->insert("a", std::move(a));
    map->insert("bb", std::move(b));
    map->insert("ccc", std::move(c));

    auto _a = map->find("a");
    auto _b = map->find("bb");
    auto _c = map->find("ccc");
    auto result = map->replace("ccc", std::move(newc));

    BOOST_CHECK_EQUAL((map->find("ccc"))->getValues()[0], 30);
    BOOST_CHECK_EQUAL(result->getValues()[0], 25);
    BOOST_CHECK_EQUAL(map->getSize(), 3);
}

BOOST_AUTO_TEST_CASE(SYMBOLMAP_TEST_REMOVE) {
    auto map = std::make_unique<SymbolMap>();
    auto a = std::make_unique<Val>(Token::Int, 10);
    auto b = std::make_unique<Val>(Token::Unit, 20, Token::A);

    map->insert("a", std::move(a));
    map->insert("bb", std::move(b));

    BOOST_CHECK_EQUAL(map->getSize(), 2);
    map->remove("a");
    BOOST_CHECK_EQUAL(map->getSize(), 1);
    map->remove("uknown");
    BOOST_CHECK_EQUAL(map->getSize(), 1);
}

BOOST_AUTO_TEST_CASE(ASSIGN_VALUE) {
    std::string program = "int main(){unit a; a = 10V * 5A;}";
    auto interpreter = configInterpreter(program);
    interpreter->execute();
    auto symbols = interpreter->getSymbols();

    BOOST_CHECK_EQUAL(symbols.find("a")->getValues()[0], 50);
    BOOST_CHECK_EQUAL(symbols.find("a")->getType(), Token::W);
}

BOOST_AUTO_TEST_CASE(ASSIGN_VALUE_TWICE) {
    std::string program = "int main(){unit a; a = 10V * 5A; a = 2 * 3s;}";
    auto interpreter = configInterpreter(program);
    interpreter->execute();
    auto symbols = interpreter->getSymbols();

    BOOST_CHECK_EQUAL(symbols.find("a")->getValues()[0], 6);
    BOOST_CHECK_EQUAL(symbols.find("a")->getType(), Token::s);
}

BOOST_AUTO_TEST_CASE(ASSIGN_VALUE_TO_CONTAINER) {
    std::string program = "int main(){unit b[5] {2V, 3A, 5W}; b[3] = b[0] * b[1]; b[4] = b[3] / b[0];}";
    auto interpreter = configInterpreter(program);
    interpreter->execute();
    auto symbols = interpreter->getSymbols();

    BOOST_CHECK_EQUAL(symbols.find("b")->getValues()[3], 6);
    BOOST_CHECK_EQUAL(symbols.find("b")->getUnits()[3], Token::W);
    BOOST_CHECK_EQUAL(symbols.find("b")->getValues()[4], 3);
    BOOST_CHECK_EQUAL(symbols.find("b")->getUnits()[4], Token::A);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(PARSER)

BOOST_AUTO_TEST_CASE(SIMPLE_INCORRECT_EXAMPLE){
    std::string program = "int a(){a}";
    auto parser = config(program);

    BOOST_CHECK_THROW(parser->parseProgram(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(SIMPLE_CORRECT_EXAMPLE){
    std::string program = "int a(){}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(FUNCTION_WITH_PARAMETER){
    std::string program = "int a(int b){}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(FUNCTION_WITH_PARAMETERS){
    std::string program = "int a(int b, unit c){}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(TWO_FUNCTIONS){
    std::string program = "int a(){} int b(){}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(UNIT_RETURN_FUNCTION){
    std::string program = "unit a(){}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(DECLARATION_VARIABLE_INT){
    std::string program = "int a(){int b;}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(DECLARATION_VARIABLE_UNIT){
    std::string program = "int a(){unit b;}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(DECLARATION_CONTAINER){
    std::string program = "int a(){unit b[5];}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(DECLARATION_CONTAINER_WITH_INITIAL_VALUES){
    std::string program = "int a(){unit b[5] {1A, 2W};}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(ASSIGN_OTHER_VARIABLE){
    std::string program = "int a(){int b; int c; b = c;}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(ASSIGN_OTHER_VARIABLE_FROM_CONTAINER){
    std::string program = "int a(){int b; int c[5]; b = c[0];}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(ASSIGN_OTHER_VARIABLE_IN_CONTAINER){
    std::string program = "int a(){int b; int c[5]; c[0] = b;}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(ASSIGN_INT_VALUE){
    std::string program = "int a(){int b; b = 5;}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(ASSIGN_NEGATIVE_VALUE){
    std::string program = "int a(){int b; b = -3; }";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(ASSIGN_UNIT_VALUE){
    std::string program = "int a(){unit b; b = 5A;}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(ASSIGN_VALUE_FROM_EXPRESSION_MULTIPLICATION){
    std::string program = "int a(){unit b; b = 5 * 10A;}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(ASSIGN_VALUE_FROM_EXPRESSION_DIVISION){
    std::string program = "int a(){int b[5]; b[0] = b[3] / b[2];}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(ASSIGN_VALUE_FROM_EXPRESSION_ADDITION){
    std::string program = "int a(){int b; int c; b = b + c;}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(ASSIGN_VALUE_FROM_EXPRESSION_SUBTRACTION){
    std::string program = "int a(){int b; b = 10 - b;}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(CALL_FUNCTION){
    std::string program = "int a(){ b();}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(CALL_FUNCTION_WITH_INT_PARAMETER){
    std::string program = "int a(int b){ int c; a(c);}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(CALL_FUNCTION_WITH_PARAMETER_FROM_CONTAINER){
    std::string program = "int a(int b){ int c[10]; a(c[0]);}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(CALL_FUNCTION_WITH_PARAMETERS){
    std::string program = "int a(int b, int c){ int d; a(d,d);}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(RETURN_FROM_FUNCTION_WITH_INT_VALUE){
    std::string program = "int a(){return 5;}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(RETURN_FROM_FUNCTION_WITH_UNIT_VALUE){
    std::string program = "unit a(){return 5A;}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(RETURN_FROM_FUNCTION_WITH_VARIABLE){
    std::string program = "int a(){return b;}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(RETURN_FROM_FUNCTION_WITH_VARIABLE_IN_CONTAINER){
    std::string program = "int a(){return b[1];}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(IF_WITHOUT_ELSE){
    std::string program = "int a(){if(){}}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(IF_WITH_ELSE){
    std::string program = "int a(){if(){}else{}}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}


BOOST_AUTO_TEST_CASE(IF_WITH_AND_EXPRESSION){
    std::string program = "int a(){if(b && c){}}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(IF_WITH_OR_EXPRESSION){
    std::string program = "int a(){if(b || c){}}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(IF_WITH_LESS_EXPRESSION){
    std::string program = "int a(){if(b < c){}}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}


BOOST_AUTO_TEST_CASE(IF_WITH_LESS_EQUAL_EXPRESSION){
    std::string program = "int a(){if(b <= c){}}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(IF_WITH_MORE_EXPRESSION){
    std::string program = "int a(){if(b > c){}}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(IF_WITH_MORE_EQUAL_EXPRESSION){
    std::string program = "int a(){if(b >= c){}}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(IF_WITH_EQUAL_EXPRESSION){
    std::string program = "int a(){if(b == c){}}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(IF_WITH_NOT_EQUAL_EXPRESSION){
    std::string program = "int a(){if(b != c){}}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(IF_WITH_Parentheses_IN_EXPRESSION){
    std::string program = "int a(){if(b && (c || d)){}}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(FOOR_LOOP_UNIT){
    std::string program = "int a(){for(unit u : table){}}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_CASE(FOOR_LOOP_INT){
    std::string program = "int a(){for(int u : table){}}";
    auto parser = config(program);

    BOOST_CHECK_NO_THROW(parser->parseProgram());
}

BOOST_AUTO_TEST_SUITE_END()