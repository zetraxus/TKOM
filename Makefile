release:
	g++ --std=c++17 src/main.cpp src/instructions/* src/lexer/* src/parser/* src/interpreter/* -o compile/release
test:
	g++ --std=c++17 tests/Tests.cpp src/instructions/* src/lexer/* src/parser/* src/interpreter/* -o compile/tests -lboost_unit_test_framework
	cd compile && ./tests
clean:
	cd compile && rm release tests
