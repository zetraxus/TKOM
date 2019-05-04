cmake_minimum_required(VERSION 3.5)
project(TKOM)

set(CMAKE_CXX_STANDARD 11)

add_executable(src src/main.cpp src/lexer/Scanner.cpp src/lexer/Scanner.h src/lexer/Token.cpp src/lexer/Token.h src/lexer/Source.cpp src/lexer/Source.h src/lexer/TokenMap.cpp src/lexer/TokenMap.h)
