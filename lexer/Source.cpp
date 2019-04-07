//
// Created by adam on 06.04.19.
//

#include "Source.h"

const int LineFeed = 10; // \n in ASCII

Source::Source(const std::string& fileName) : fileName(fileName) {
    current = new Position();
    inputStream.open(fileName.c_str());
    if (!inputStream)
        throw std::runtime_error("File not found.");
}

int Source::getNextChar() {
    int next = inputStream.get();
    next != LineFeed ? current->incrementPosition() : current->incrementLine();

    return next;
}

Source::~Source() {
    inputStream.close();

}

Position* Source::getCurrentPosition() const {
    return current;
}

int Source::peekNextChar() {
    return inputStream.peek();
}

Position::Position(unsigned int line, int position) : line(line), position(position) {}

void Position::incrementPosition() {
    ++position;
}

void Position::incrementLine() {
    ++line;
    position = 0;
}