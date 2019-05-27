#include <memory>

//
// Created by adam on 06.04.19.
//

#include <iostream>
#include "Source.h"

const int LineFeed = 10; // \n in ASCII

Source::Source(const std::string& fileNameOrInput, bool mode) : mode(mode) {
    if (mode == 0) { // release
        fileName = fileNameOrInput;
        current = std::make_shared<Position>();
        inputStream.open(fileName.c_str());
        if (!inputStream)
            throw std::runtime_error("File not found.");
    } else {
        current = std::make_shared<Position>();
        input << fileNameOrInput;
    }
}

int Source::getNextChar() {
    int next;
    mode ? next = input.get() : next = inputStream.get();

    next != LineFeed ? current->incrementPosition() : current->incrementLine();
    return next;
}

Source::~Source() {
    if (inputStream.is_open())
        inputStream.close();
}

std::shared_ptr<Position> Source::getCurrentPosition() const {
    return current;
}

int Source::peekNextChar() {
    return mode ? input.peek() : inputStream.peek();
}

Position::Position(unsigned int line, int position) : line(line), position(position) {}

void Position::incrementPosition() {
    ++position;
}

void Position::incrementLine() {
    ++line;
    position = 0;
}

unsigned int Position::getLine() const {
    return line;
}

int Position::getPosition() const {
    return position;
}

Position::Position(const Position& other) : line(other.line), position(other.position) {}
