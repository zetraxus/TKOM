release:
	g++ --std=c++14 src/main.cpp src/instructions/* src/lexer/* src/parser/* -o compile/release
test:
	g++ --std=c++14 tests/Tests.cpp src/instructions/* src/lexer/* src/parser/* -o compile/tests -lboost_unit_test_framework
	cd compile && ./tests
clean:
	cd compile && rm release tests
