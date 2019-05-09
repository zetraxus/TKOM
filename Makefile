release:
	g++ --std=c++11 src/main.cpp src/instructions/* src/lexer/* src/parser/* -o compile/release
test:
	g++ --std=c++11 tests/LexerTests.cpp src/instructions/* src/lexer/* src/parser/* -o compile/tests -lboost_unit_test_framework
	cd compile && ./tests
clean:
	cd compile && rm release tests
