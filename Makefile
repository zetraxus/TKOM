all:
	g++ -std=c++11 -Wall -pedantic -o exe *.cpp lexer/*.cpp
test:
	g++ -std=c++11 -o test tests/LexerTests.cpp -lboost_unit_test_framework
