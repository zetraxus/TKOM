cmake_minimum_required(VERSION 3.12)
project(TKOM)

set(CMAKE_CXX_STANDARD 11)

add_executable(TKOM main.cpp lexer/Scanner.cpp lexer/Scanner.h lexer/Token.cpp lexer/Token.h lexer/Source.cpp lexer/Source.h tests/LexerTests.cpp lexer/TokenMap.cpp lexer/TokenMap.h)