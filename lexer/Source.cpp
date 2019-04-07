//
// Created by adam on 06.04.19.
//

#include "Source.h"
#include <iostream>

const int LineFeed = 10; // \n in ASCII

Source::Source(const std::string& fileName) : fileName(fileName) {
    current = new Position();
    inputStream.open(fileName.c_str());
    if(!inputStream)
        throw std::runtime_error ("File not found.");
}

int Source::getNextChar() {
    int next = inputStream.get();
    next != LineFeed ? current->incrementPosition() : current->incrementLine();

    return inputStream.get();
}

Source::~Source() {
    inputStream.close();

}

Position::Position(unsigned int line, unsigned int position) : line(line), position(position) {}

void Position::incrementPosition(){
    ++position;
}

void Position::incrementLine(){
    ++line;
    position = 0;
}