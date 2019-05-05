cmake_minimum_required(VERSION 3.5)
project(TKOM)

set(CMAKE_CXX_STANDARD 11)

add_executable(src src/main.cpp src/lexer/Scanner.cpp src/lexer/Scanner.h src/lexer/Token.cpp src/lexer/Token.h src/lexer/Source.cpp src/lexer/Source.h src/lexer/TokenMap.cpp src/lexer/TokenMap.h src/parser/Parser.cpp src/parser/Parser.h src/instructions/Block.cpp src/instructions/Block.h src/instructions/Instruction.cpp src/instructions/Instruction.h src/instructions/InstructionDeclarationVariable.cpp src/instructions/InstructionDeclarationVariable.h src/instructions/InstructionDeclarationContainer.cpp src/instructions/InstructionDeclarationContainer.h src/instructions/InstuctionAssignment.cpp src/instructions/InstuctionAssignment.h src/instructions/InstructionCallFunction.cpp src/instructions/InstructionCallFunction.h src/instructions/InstructionReturnFromFunction.cpp src/instructions/InstructionReturnFromFunction.h src/instructions/DefinitionOfFunction.cpp src/instructions/DefinitionOfFunction.h src/instructions/Program.cpp src/instructions/Program.h src/instructions/Variable.cpp src/instructions/Variable.h)
